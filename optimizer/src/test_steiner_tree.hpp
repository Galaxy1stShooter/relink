/*
 * File:   main.cpp
 * Author: Prasanna Subburaj
 * Approximation Algorithm for Steiner Tree Implementaion
 * Reference Paper: [1] http://monet.skku.ac.kr/course_materials/undergraduate/al/lecture/2006/TM.pdf
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include <ros/ros.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/UInt32.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include "visibility_graph/graph_constructor.hpp"
#include "visibility_graph/grid_map.hpp"
#include "hungarianAlgorithm.hpp"

#include "message_files/PoseStampedArray.h"
#include "message_files/SteinerTreeNode.h"
#include "message_files/SteinerTreeArray.h"
#include "message_files/Assign.h"

#define DISADJ 0
typedef double weight_type;
typedef unsigned nodeid_type;
size_t VERTICES = 10;                       // Define the number of vertices |V| in the graph G = (V,E)
map<nodeid_type, std::string> node_to_name; // Map from vg node id to initial identifier of entity, format "typeid" (no other chars)

/**
 *Class to implement of Graph
 */
class Graph
{
public:
    weight_type **AdjacencyMatrix;
    Eigen::MatrixXd *originalGraph;

    struct edge
    {
        nodeid_type vertex1, vertex2;
        weight_type weight;

        edge(nodeid_type v1, nodeid_type v2, weight_type w = INFINITY) : vertex1(v1), vertex2(v2), weight(w)
        {
            if (vertex1 > vertex2)
                std::swap(vertex1, vertex2);
        }

        bool operator==(const edge &other)
        {
            return vertex1 == other.vertex1 && vertex2 == other.vertex2;
        }
    };
    vector<edge> edges;

    vector<nodeid_type> steinerterminals;

    Graph(nodeid_type n)
    {
        AdjacencyMatrix = new weight_type *[n];
        for (nodeid_type idx = 0; idx < n; ++idx)
            AdjacencyMatrix[idx] = new weight_type[n];

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                AdjacencyMatrix[i][j] = DISADJ;
            }
        }
    }

    Graph(nodeid_type n, Eigen::MatrixXd &adjMat)
    {
        originalGraph = &adjMat;
        AdjacencyMatrix = new weight_type *[n];
        for (size_t i = 0; i < n; ++i)
        {
            AdjacencyMatrix[i] = new weight_type[n];
        }

        for (size_t i = 0; i < n; ++i)
        {
            AdjacencyMatrix[i][i] = DISADJ;
            for (size_t j = i + 1; j < n; ++j)
            {
                if (adjMat(i, j) > 0)
                {
                    // In visibility graph, only positive numbers refer to existing edge weight
                    // assign weight to AdjacencyMatrix and store corresponding edge
                    AdjacencyMatrix[i][j] = AdjacencyMatrix[j][i] = adjMat(i, j);
                    edges.emplace_back(i, j, AdjacencyMatrix[i][j]);
                }
                else
                {
                    AdjacencyMatrix[i][j] = AdjacencyMatrix[j][i] = DISADJ;
                }
            }
        }
    }

    ros::Publisher pub_requirement;
    ros::Publisher pub_tree_array;
    ros::Publisher pub_grid_or_network;
    void initPublisher(ros::NodeHandle &n)
    {
        // Tell plan_manage appropriate initial position of UAVs
        pub_requirement = n.advertise<message_files::PoseStampedArray>("/init_uav_pos", 1, true);
        pub_tree_array = n.advertise<message_files::SteinerTreeArray>("/algorithm/tree", 1);
        pub_grid_or_network = n.advertise<visualization_msgs::MarkerArray>("/algorithm/grid_map", 1);
    }

    void assign_steiner_terminals(vector<nodeid_type> &a)
    {
        steinerterminals = a;
    }

    weight_type getEdgeWeight(nodeid_type v1, nodeid_type v2)
    {
        return AdjacencyMatrix[v1][v2];
    }

    bool isDisconnected(nodeid_type v1, nodeid_type v2)
    {
        weight_type weight = getEdgeWeight(v1, v2);
        return fabs(weight - DISADJ) < 0.01;
    }

    std::map<std::string, std::set<std::string>> getAllocation(
        std::map<unsigned, Eigen::Vector3d> &target_poses,
        std::map<unsigned, Eigen::Vector3d> &bs_poses,
        std::map<unsigned, Eigen::Vector3d> &uav_poses,
        GridMap &interface,
        ros::NodeHandle &n);
    void insertedge(nodeid_type, nodeid_type, weight_type);
    void printadjacencymatrix(nodeid_type);
    vector<nodeid_type> pathfind(set<nodeid_type>, nodeid_type);
    std::pair<vector<edge>, set<nodeid_type>> steiner();
    std::pair<vector<edge>, set<nodeid_type>> SteinerTreeRecursive();
};

std::ostream &operator<<(std::ostream &c, Graph::edge &e)
{
    c << " V1= " << e.vertex1
      << " V2= " << e.vertex2
      << " W= " << e.weight;
    return c;
}

/**
 * This method is used to insert one edge at a time into the graph
 * @param origin
 * @param destination
 * @param weight
 */
void Graph::insertedge(nodeid_type origin, nodeid_type destination, weight_type weight)
{
    if (fabs(AdjacencyMatrix[origin][destination] - 0) > 0.01)
    {
        std::cout << "This edge already exits..\n";
    }
    else
    {
        AdjacencyMatrix[origin][destination] = weight;
        AdjacencyMatrix[destination][origin] = weight;
        edges.emplace_back(origin, destination, weight);
    }
}

/**
 * Prints the Adjacency Matrix of the formed graph
 * @param n
 */
void Graph::printadjacencymatrix(nodeid_type n)
{
    std::cout << "The Adjacency Matrix for the given graph\n\n";
    for (size_t i = 1; i < n; i++)
    {
        for (size_t j = 1; j < n; j++)
        {
            std::cout << AdjacencyMatrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

/**
 *Steiner Tree implementation to find the smallest cost subgraph of G that contains all the vertices in the subset S
 */
std::pair<vector<Graph::edge>, set<nodeid_type>> Graph::steiner()
{
    nodeid_type u;
    vector<nodeid_type> edges1;
    set<nodeid_type> finalVertices;
    vector<Graph::edge> finalEdges, finalEdges1;
    ROS_INFO("[DEBUG] Edges: %zu, Vertices: %zu", finalEdges1.size(), finalVertices.size());

    // Assign the first Vertex to the tree T1 so that V1={v1} and E1={empty}
    u = steinerterminals[0];
    finalVertices.insert(u);

    for (size_t i = 1; i < steinerterminals.size(); i++)
    {
        // select a vertex vi from S-Vi-1 and find the minimum path from any vertices in S-Vi-1 to vi
        if (finalVertices.count(steinerterminals[i]) == 0)
        {
            // Current terminal has not been added, go get the minimum path
            auto path = pathfind(finalVertices, steinerterminals[i]);

            // Adding the vertices on path to the tree Ti-1
            for (auto path_node : path)
            {
                finalVertices.insert(path_node);
                edges1.push_back(path_node);
            }

            // Adding edges on path to the Tree Ti-1 (built by connecting finalVertices)
            for (auto it1 = edges1.rbegin(), it2 = it1++; it1 != edges1.rend(); ++it2, ++it1)
            {
                finalEdges.emplace_back(*it1, *it2, INFINITY);
            }

            for (size_t s = 0; s < finalEdges.size(); s++)
            {
                size_t count = 0, dn = 0;
                for (Graph::edge &check_edge : edges)
                {
                    // find the same edge of finalEdges in edges
                    // find all the adjacent elements of the selected vertex
                    if (finalEdges[s] == check_edge)
                    {
                        count += std::count(finalEdges1.begin(), finalEdges1.end(), check_edge);
                        if (count == 0)
                        {
                            for (auto &final_edge : finalEdges1)
                            {
                                if (final_edge == check_edge)
                                {
                                    ++dn;
                                    if (final_edge.weight > check_edge.weight)
                                        final_edge = check_edge;
                                }
                            }
                            if (dn == 0)
                                finalEdges1.emplace_back(check_edge);
                        }
                    }
                }
            }
        }
    }

    std::cout << "[INSIDE ALGORITHM] The following are the steiner terminals:" << std::endl;
    // Print the Steiner Points in the Steiner Tree
    for (auto &steiner_t : steinerterminals)
    {
        finalVertices.erase(steiner_t);
        std::cout << steiner_t << std::endl;
    }
    std::cout << "[INSIDE ALGORITHM] The following are the steiner points:" << std::endl;
    for (auto &steiner_point : finalVertices)
    {
        std::cout << steiner_point << " corresponding node id: " << (*originalGraph)(steiner_point, steiner_point) << std::endl;
    }

    // Compute and print the cost of the Steiner Tree and also print the edges of the Steiner Tree
    weight_type sum = 0;
    std::cout << std::endl
              << "[INSIDE ALGORITHM] The following are the edges in the steiner tree:" << std::endl;
    for (auto &final_edge : finalEdges1)
    {
        std::cout << final_edge << std::endl;
        sum += final_edge.weight;
    }

    std::cout << std::endl
              << std::endl
              << "[INSIDE ALGORITHM] Cost of the Steiner Tree = " << sum << std::endl;
    // return finalEdges;
    return std::make_pair(finalEdges1, finalVertices);
}

/**
 *Compute the minimum cost path for the set of vertices in W to vertex v by Dijkstra algorithm
 *@param W It will contain the set of vertices in T which is a subset of S
 *@param v It is the new vertex for which we need to find the shortest path from all the vertices in W to v
 *@return The path whose cost is less than all the other shortest path in W
 */
vector<nodeid_type> Graph::pathfind(set<nodeid_type> W, nodeid_type v)
{
    struct id_dist
    {
        nodeid_type id;
        nodeid_type pred;
        weight_type dist;

        id_dist(nodeid_type id_, nodeid_type pred_, weight_type dist_) : id(id_), pred(pred_), dist(dist_) {}
    };
    struct compare_dist
    {
        bool operator()(const id_dist &a, const id_dist &b) { return a.dist > b.dist; }
    };

    priority_queue<id_dist, vector<id_dist>, compare_dist> min_heap;
    weight_type *dist = new weight_type[VERTICES]; // record final min dist from src
    std::for_each(dist, dist + VERTICES, [](weight_type &elem)
                  { elem = INFINITY; });
    bool *visited = new bool[VERTICES];
    std::for_each(visited, visited + VERTICES, [](bool &elem)
                  { elem = false; });
    nodeid_type *pred = new nodeid_type[VERTICES];
    nodeid_type dest = v;
    double min_dist = INFINITY;

    min_heap.emplace(v, 0, 0);
    while (!min_heap.empty())
    {
        auto cur_pair = min_heap.top();
        min_heap.pop();
        if (visited[cur_pair.id])
            continue;
        visited[cur_pair.id] = true;
        pred[cur_pair.id] = cur_pair.pred;
        if (W.count(cur_pair.id) && cur_pair.dist < min_dist)
        {
            dest = cur_pair.id;
            min_dist = cur_pair.dist;
        }

        for (nodeid_type adj = 0; adj < VERTICES; ++adj)
        {

            if (isDisconnected(cur_pair.id, adj))
                continue;
            dist[adj] = min(dist[adj], cur_pair.dist + getEdgeWeight(cur_pair.id, adj));
            if (dist[adj] < INFINITY)
                min_heap.emplace(adj, cur_pair.id, dist[adj]);
        }
    }

    // Return the Cost to the destination and the path to the destination by trying out all the Vj-1 to vi
    nodeid_type d = dest;
    vector<nodeid_type> path;
    while (d != v)
    {
        path.emplace_back(d);
        d = pred[d];
    }
    path.emplace_back(v);
    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * Recursive algorithm to get smallest Steiner tree (the smallest cost subgraph of G that contains all the vertices in the subset S)
 */
struct message
{
    message() = default;
    unsigned long long tp;
    union set_node
    {
        int node;
        unsigned long long set;
    } x, y;
};
void getTree(nodeid_type u, unsigned long long A, set<nodeid_type> &finalVertices, vector<Graph::edge> &finalEdges, const vector<vector<message>> &to)
{
    if (to[u][A].tp == 1)
    {
        // printf("%d ", (to[u][A].y.node + 1) >> 1);
        finalVertices.insert(to[u][A].y.node);
        finalEdges.emplace_back(u, to[u][A].y.node);
        // print(to[u][A].x, A);
        getTree(to[u][A].x.node, A, finalVertices, finalEdges, to);
    }
    if (to[u][A].tp == 2)
    {
        // print(u, to[u][A].x), print(u, to[u][A].y);
        getTree(u, to[u][A].x.set, finalVertices, finalEdges, to);
        getTree(u, to[u][A].y.set, finalVertices, finalEdges, to);
    }
}
std::pair<vector<Graph::edge>, set<nodeid_type>> Graph::SteinerTreeRecursive()
{
    nodeid_type u;
    set<nodeid_type> finalVertices;
    vector<Graph::edge> finalEdges;
    // vector<vector<weight_type>> shortestDistance(VERTICES, vector<weight_type>(VERTICES, INFINITY));
    // for (int k = 0; k < VERTICES; ++k)
    // {
    //     for (int i = 0; i < VERTICES; ++i)
    //     {
    //         for (int j = 0; j < VERTICES; ++j)
    //         {
    //             shortestDistance[i][j] = min(shortestDistance[i][j], shortestDistance[i][k] + shortestDistance[k][j]);
    //         }
    //     }
    // }
    unsigned long long max_set = (1 << steinerterminals.size()) - 1;
    auto to = vector<vector<message>>(VERTICES, vector<message>(max_set + 1));
    vector<vector<weight_type>> dp(VERTICES, vector<weight_type>(max_set + 1, INFINITY));
    for (auto it = steinerterminals.begin(); it != steinerterminals.end(); ++it) {
        dp[*it][1 << (it - steinerterminals.begin())] = 0;
    }
    for (unsigned long long S = 1; S <= max_set; S++) // 枚举K个关键点的所有状态
    {
        for (unsigned long long sub = S & (S - 1); sub; sub = S & (sub - 1)) // 枚举 S 的所有子集
        {
            for (int i = 0; i < VERTICES; ++i) // 枚举根节点
            {
                if (dp[i][sub] + dp[i][S ^ sub] < dp[i][S])
                {
                    dp[i][S] = dp[i][sub] + dp[i][S ^ sub];
                    to[i][S].tp = 2;
                    to[i][S].x.set = sub;
                    to[i][S].y.set = S ^ sub;
                }
            }
        }
        priority_queue<pair<weight_type, nodeid_type>, vector<pair<weight_type, nodeid_type>>, greater<pair<weight_type, nodeid_type>>> heap;
        for (nodeid_type i = 0; i < VERTICES; ++i)
            heap.push(make_pair(dp[i][S], i));
        while (!heap.empty())
        {
            nodeid_type u = heap.top().second;
            heap.pop();
            for (auto &edge : edges)
            {
                if (u != edge.vertex1 && u != edge.vertex2) continue;
                nodeid_type v = u == edge.vertex1 ? edge.vertex2 : edge.vertex1; 
                if (dp[v][S] > dp[u][S] + edge.weight)
                {
                    heap.emplace(dp[v][S] = dp[u][S] + edge.weight, v);
                    to[v][S].tp = 1;
                    to[v][S].x.node = u;
                    to[v][S].y.node = v;
                }
            }
            while (!heap.empty() && heap.top().first > dp[heap.top().second][S])
                heap.pop();
        } // 对状态 S 进行状态内转移
    }
    weight_type sum = INFINITY;
    nodeid_type root = 0;
    for (nodeid_type i = 0; i < VERTICES; ++i)
    {
        if (dp[i][max_set] < sum)
            sum = dp[i][max_set], root = i;
    }
    getTree(root, max_set, finalVertices, finalEdges, to);

    std::cout << "[INSIDE ALGORITHM] The following are the steiner terminals:" << std::endl;
    // Print the Steiner Points in the Steiner Tree
    for (auto &steiner_t : steinerterminals)
    {
        finalVertices.erase(steiner_t);
        std::cout << steiner_t << std::endl;
    }
    std::cout << "[INSIDE ALGORITHM] The following are the steiner points:" << std::endl;
    for (auto &steiner_point : finalVertices)
    {
        std::cout << steiner_point << " corresponding node id: " << (*originalGraph)(steiner_point, steiner_point) << std::endl;
    }

    // Compute and print the cost of the Steiner Tree and also print the edges of the Steiner Tree
    // weight_type sum = 0;
    std::cout << std::endl
              << "[INSIDE ALGORITHM] The following are the edges in the steiner tree:" << std::endl;
    for (auto &final_edge : finalEdges)
    {
        std::cout << final_edge << std::endl;
        // sum += final_edge.weight;
    }

    std::cout << std::endl
              << std::endl
              << "[INSIDE ALGORITHM] Cost of the Steiner Tree = " << sum << std::endl;
    // return finalEdges;
    return std::make_pair(finalEdges, finalVertices);
}

set<nodeid_type> convertIdentifier(const std::map<unsigned, Eigen::Vector3d> &container, GridMap &interface, string type)
{
    // Store pose info for graph generation
    // Store ID for tree generation, each target or bs linked to one graph-node
    set<nodeid_type> id_set;
    for (auto &id_pose : container) // id_pose: id is entity-specific id published by entity_controller
    {
        nodeid_type node_id = interface.coord2adjMatIdx(id_pose.second); // The initial id in graph
        id_set.insert(node_id);
        node_to_name[node_id] = type + to_string(id_pose.first);

        Eigen::Vector3d node_loc = interface.adjMatIdx2coord(node_id);
        ROS_INFO("[DEBUG] %s at (%.2f, %.2f, %.2f) match node %d at (%.2f, %.2f, %.2f)",
                 type.c_str(), id_pose.second(0), id_pose.second(1), id_pose.second(2),
                 node_id, node_loc(0), node_loc(1), node_loc(2));
    }
    return std::move(id_set);
}

void visualize_visibility_graph(const ros::Publisher &, double, GridMap &, Eigen::MatrixXd *, std::map<nodeid_type, std::set<nodeid_type>> &, std::vector<Graph::edge> &);

std::map<std::string, std::set<std::string>> Graph::getAllocation(
    std::map<unsigned, Eigen::Vector3d> &target_poses,
    std::map<unsigned, Eigen::Vector3d> &bs_poses,
    std::map<unsigned, Eigen::Vector3d> &uav_poses,
    GridMap &interface,
    ros::NodeHandle &n)
{

    set<nodeid_type> set_target_id = convertIdentifier(target_poses, interface, "target");
    set<nodeid_type> set_bs_id = convertIdentifier(bs_poses, interface, "bs");

    vector<nodeid_type> steiner_terminals; // Initial node id
    steiner_terminals.insert(steiner_terminals.end(), set_target_id.begin(), set_target_id.end());
    steiner_terminals.insert(steiner_terminals.end(), set_bs_id.begin(), set_bs_id.end());
    printf("Node IDs of Steiner terminals:\n");
    for (auto &node_id : steiner_terminals)
    {
        Eigen::Vector3d node_loc = interface.adjMatIdx2coord(node_id);
        ROS_INFO("[DEBUG] Node %d at (%.2f, %.2f, %.2f)",
                 node_id, node_loc(0), node_loc(1), node_loc(2));
    }

    vector<nodeid_type> terminals; // Convert to graph sub index (after deleting occupied nodes)
    for (auto &index : steiner_terminals)
    {
        for (nodeid_type i = 0; i < VERTICES; ++i)
        {
            if ((*originalGraph)(i, i) == index)
            {
                terminals.push_back(i);
                break;
            }
        }
    }
    ROS_INFO("[DEBUG] Terminals: %d", terminals.size());

    this->assign_steiner_terminals(terminals);
    // auto steiner_answer = this->steiner();
    auto steiner_answer = this->SteinerTreeRecursive();

    auto &final_edges = steiner_answer.first;
    auto &steiner_points = steiner_answer.second; // nodes added to steiner tree, in graph perspective
    {
        set<nodeid_type> tmp(steiner_points.begin(), steiner_points.end());
        steiner_points.clear();
        printf("[DEBUG] Steiner points:\n");
        for (auto &id : tmp)
        {
            steiner_points.insert((*originalGraph)(id, id));
            Eigen::Vector3d node_loc = interface.adjMatIdx2coord((*originalGraph)(id, id));
            printf("[DEBUG] Point %d aka Node %d at (%.2f, %.2f, %.2f)\n",
                   id, (int)(*originalGraph)(id, id), node_loc(0), node_loc(1), node_loc(2));
        }
    }

    /*
     * Reorganize edge data to build key-value map
     * key: id of vg-node (part of it should be converted to UAV later)
     * value: id of vg-node-neighbours
     */
    std::map<nodeid_type, std::set<nodeid_type>> node_neighbours; // key: node ID, value: IDs of all neighbours (all in graph)
    ROS_INFO("[DEBUG] Node_neighbours: %d", node_neighbours.size());
    for (Graph::edge &edge : final_edges)
    {
        node_neighbours[(*originalGraph)(edge.vertex1, edge.vertex1)].insert((*originalGraph)(edge.vertex2, edge.vertex2));
        node_neighbours[(*originalGraph)(edge.vertex2, edge.vertex2)].insert((*originalGraph)(edge.vertex1, edge.vertex1));
    }

    visualize_visibility_graph(pub_grid_or_network, n.param("grid_map/resolution", 3.0),
                               interface, originalGraph, node_neighbours, final_edges);
    return std::map<std::string, std::set<std::string>>();
}

visualization_msgs::MarkerArray graph_markers;
void visualize_visibility_graph(const ros::Publisher &pub_grid_or_network,
                                double grid_size, GridMap &interface, Eigen::MatrixXd *adjMatPtr,
                                std::map<nodeid_type, std::set<nodeid_type>> &node_neighbours, std::vector<Graph::edge> &final_edges)
{
    /* Test steiner tree solution */
    graph_markers.markers.clear();

    visualization_msgs::Marker graph;
    graph.ns = "grid_map";
    graph.id = 0;
    graph.type = visualization_msgs::Marker::CUBE_LIST;
    graph.action = visualization_msgs::Marker::ADD;
    graph.header.frame_id = "/world";
    graph.pose.position.x = graph.pose.position.y = graph.pose.position.z = 0.0;
    graph.pose.orientation.x = 0;
    graph.pose.orientation.y = 0;
    graph.pose.orientation.z = 0;
    graph.pose.orientation.w = 1;
    graph.scale.x = grid_size / 4;
    graph.scale.y = grid_size / 4;
    graph.scale.z = grid_size / 4;
    graph.color.r = 0.0;
    graph.color.g = 0.0;
    graph.color.b = 0.0;
    graph.color.a = 0.1;
    for (size_t i = 0; i < VERTICES; ++i)
    {
        Eigen::Vector3d curr = interface.adjMatIdx2coord((*adjMatPtr)(i, i));
        geometry_msgs::Point curr_node_centre;
        curr_node_centre.x = curr(0);
        curr_node_centre.y = curr(1);
        curr_node_centre.z = curr(2);
        graph.points.push_back(curr_node_centre);
        graph.colors.push_back(graph.color);
    }
    graph_markers.markers.push_back(graph);

    visualization_msgs::Marker tree;
    tree.ns = "tree_node";
    tree.id = 0;
    tree.type = visualization_msgs::Marker::CUBE_LIST;
    tree.action = visualization_msgs::Marker::ADD;
    tree.header.frame_id = "/world";
    tree.pose.position.x = tree.pose.position.y = tree.pose.position.z = 0.0;
    tree.pose.orientation.x = 0;
    tree.pose.orientation.y = 0;
    tree.pose.orientation.z = 0;
    tree.pose.orientation.w = 1;
    // double grid_size = n.param("grid_map/resolution", 3.0);
    tree.scale.x = grid_size;
    tree.scale.y = grid_size;
    tree.scale.z = grid_size;
    tree.color.r = 0.5;
    tree.color.g = 0.5;
    tree.color.b = 0.5;
    tree.color.a = 0.3;
    for (auto &[id, neighbour] : node_neighbours)
    {
        Eigen::Vector3d curr = interface.adjMatIdx2coord(id);
        geometry_msgs::Point curr_node_centre;
        curr_node_centre.x = curr(0);
        curr_node_centre.y = curr(1);
        curr_node_centre.z = curr(2);
        tree.points.push_back(curr_node_centre);
        tree.colors.push_back(tree.color);
    }
    graph_markers.markers.push_back(tree);

    visualization_msgs::Marker network;
    network.ns = "tree_edge";
    network.id = 0;
    network.type = visualization_msgs::Marker::LINE_LIST;
    network.action = visualization_msgs::Marker::ADD;
    network.header.frame_id = "/world";
    network.pose.position.x = network.pose.position.y = network.pose.position.z = 0.0;
    network.pose.orientation.x = 0;
    network.pose.orientation.y = 0;
    network.pose.orientation.z = 0;
    network.pose.orientation.w = 1;
    network.scale.x = 0.5;
    network.color.r = 0.5;
    network.color.g = 0.5;
    network.color.b = 0.5;
    network.color.a = 0.3;
    for (auto &edge : final_edges)
    {
        auto id_1 = edge.vertex1;
        auto id_2 = edge.vertex2;
        Eigen::Vector3d pt_1 = interface.adjMatIdx2coord((*adjMatPtr)(id_1, id_1));
        Eigen::Vector3d pt_2 = interface.adjMatIdx2coord((*adjMatPtr)(id_2, id_2));
        geometry_msgs::Point curr_node_centre;
        curr_node_centre.x = pt_1(0);
        curr_node_centre.y = pt_1(1);
        curr_node_centre.z = pt_1(2);
        network.points.push_back(curr_node_centre);
        curr_node_centre.x = pt_2(0);
        curr_node_centre.y = pt_2(1);
        curr_node_centre.z = pt_2(2);
        network.points.push_back(curr_node_centre);
    }
    graph_markers.markers.push_back(network);

    ROS_INFO("[DEBUG] Total node number: %zu", tree.points.size());
    pub_grid_or_network.publish(graph_markers);
    pub_grid_or_network.publish(graph_markers);
    pub_grid_or_network.publish(graph_markers);
}
