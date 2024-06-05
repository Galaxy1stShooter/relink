#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>
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

#include "message_files/PoseStampedArray.h"
#include "message_files/SteinerTreeNode.h"
#include "message_files/SteinerTreeArray.h"
#include "message_files/Assign.h"

#include "visibility_graph/graph_constructor.hpp"
#include "visibility_graph/grid_map.hpp"
#include "visibility_graph/los_checker.hpp"

#include "hungarianAlgorithm.hpp"

#define DISADJ 0
typedef double weight_type;
typedef unsigned nodeid_type;
size_t VERTICES;  // Define the number of vertices |V| in the graph G = (V,E), SET BY algorithm.cpp
map<nodeid_type, std::string> node_to_name; // Map from vg node id to initial identifier of entity, format "typeid" (no other chars)
unsigned available_uav_num = 0;  // used to tell max available UAV count
unsigned uav_num = 0;  // used to record spawned UAV count
unsigned last_uav_requirement = 0;  // used to mark UAV count requirement calculated in last iteration

const nodeid_type dummy_root_id = INT_MAX;
struct SteinerTreeNode {
    std::string node_type_id;  // entity identifier
    nodeid_type id;  // corresponding node id in grid map
    Eigen::Vector3d pos;  // real position for exisiting entity, goal position for UAV
    set<shared_ptr<SteinerTreeNode>> children;
    shared_ptr<SteinerTreeNode> parent;
    set<shared_ptr<SteinerTreeNode>> neighbours;

    explicit SteinerTreeNode(nodeid_type id) {
        this->id = id;
    }

    SteinerTreeNode(nodeid_type id, Eigen::Vector3d pos) {
        this->id = id;
        this->pos = std::move(pos);
        if (node_to_name.count(id)) node_type_id = node_to_name[id];
        else node_type_id = "";
    }
};

/**
 *Class to implement of Graph
 */
class Graph
{
public:
    shared_ptr<GridMap> interface;
    weight_type **AdjacencyMatrix;
    Eigen::MatrixXd *originalGraph{};

    struct edge
    {
        nodeid_type vertex1, vertex2;
        weight_type weight;

        edge(nodeid_type v1, nodeid_type v2, weight_type w = INFINITY) : vertex1(v1), vertex2(v2), weight(w)
        {
            if (vertex1 > vertex2)
                std::swap(vertex1, vertex2);
        }

        bool operator==(const edge &other) const
        {
            return vertex1 == other.vertex1 && vertex2 == other.vertex2;
        }
    };
    vector<edge> edges;

    vector<nodeid_type> steinerterminals;

    explicit Graph(nodeid_type n)
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

        originalGraph = nullptr;
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
    ros::Publisher pub_tree_network;
    void initPublisher(ros::NodeHandle &n)
    {
        // Tell plan_manage appropriate initial position of UAVs
        pub_requirement = n.advertise<message_files::PoseStampedArray>("/init_uav_pos", 1, true);
        pub_tree_array = n.advertise<message_files::SteinerTreeArray>("/algorithm/tree", 1, true);
        pub_tree_network = n.advertise<visualization_msgs::MarkerArray>("/algorithm/tree_visualization", 1, true);
    }

    void assign_steiner_terminals(vector<nodeid_type> &a)
    {
        steinerterminals = a;
    }

    weight_type getEdgeWeight(nodeid_type v1, nodeid_type v2) const
    {
        return AdjacencyMatrix[v1][v2];
    }

    bool isDisconnected(nodeid_type v1, nodeid_type v2) const
    {
        weight_type weight = getEdgeWeight(v1, v2);
        return fabs(weight - DISADJ) < 0.01;
    }

    /**
     * Use edge list provided by Steiner tree algorithm to build a tree consist of SteinerTreeNode
     * @param E: Edge list of type Graph::edge
     * @param roots: Corresponding grid map node id of base stations, to specify the forest
     * @return Dummy root of the tree structure generated (the children of this node are nodes correspond to base stations)
     * */
    shared_ptr<SteinerTreeNode> BuildTreeFromEdgeList(const vector<edge>& E, const vector<nodeid_type>& roots) {
        // Initialize with one dummy root
        map<nodeid_type, shared_ptr<SteinerTreeNode>> Index_to_NodePtr;
        shared_ptr<SteinerTreeNode> dummy_root = make_shared<SteinerTreeNode>(dummy_root_id, interface->adjMatIdx2coord(dummy_root_id));
        Index_to_NodePtr[dummy_root_id] = dummy_root;
        for (nodeid_type root_id : roots) {
            auto current_node = make_shared<SteinerTreeNode>(root_id, interface->adjMatIdx2coord(root_id));
            Index_to_NodePtr[root_id] = current_node;
            current_node->parent = dummy_root;
            dummy_root->children.insert(current_node);
        }

        // Build the tree start from roots built above. Orderly to keep the direct
        size_t edge_count = E.size();
        vector<int> edge_visited(edge_count, 0);
        while (edge_count) {
            for (size_t idx = 0; idx < E.size(); ++idx) {
                if (edge_visited[idx]) continue;
                auto curr_edge = E[idx];
                for (auto [v1, v2] : {pair<nodeid_type, nodeid_type>{curr_edge.vertex1, curr_edge.vertex2}, pair<nodeid_type, nodeid_type>{curr_edge.vertex2, curr_edge.vertex1}}) {
                    auto it = Index_to_NodePtr.find(v1);
                    if (it == Index_to_NodePtr.end()) continue;

                    // If at least one node already in the tree, add the tree edge and remove it from edge list (lazy)
                    if (!Index_to_NodePtr.count(v2)) {
                        Index_to_NodePtr[v2] = make_shared<SteinerTreeNode>(v2, interface->adjMatIdx2coord(v2));
                    }
                    shared_ptr<SteinerTreeNode> next_node_ptr = Index_to_NodePtr[v2];
                    it->second->children.insert(next_node_ptr);
                    next_node_ptr->parent = it->second;
                    edge_visited[idx] = 1;
                    --edge_count;
//                    ROS_INFO("%zu", edge_count);
                    break;
                }
            }
        }

        return dummy_root;
    }

    set<shared_ptr<SteinerTreeNode>> getAllocation(
        std::map<unsigned, Eigen::Vector3d> &target_poses,
        std::map<unsigned, Eigen::Vector3d> &bs_poses,
        std::map<unsigned, Eigen::Vector3d> &uav_poses,
        ros::NodeHandle &n);

    /**
     * This method is used to insert one edge at a time into the graph
     * @param origin
     * @param destination
     * @param weight
     */
    void insertedge(nodeid_type origin, nodeid_type destination, weight_type weight) {
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
     *Compute the minimum cost path for the set of vertices in W to vertex v by Dijkstra algorithm
     *@param W It will contain the set of vertices in T which is a subset of S
     *@param v It is the new vertex for which we need to find the shortest path from all the vertices in W to v
     *@return The path whose cost is less than all the other shortest path in W
     */
    vector<nodeid_type> pathfind(const set<nodeid_type>& W, nodeid_type v)
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
        auto *dist = new weight_type[VERTICES]; // record final min dist from src
        std::for_each(dist, dist + VERTICES, [](weight_type &elem)
        { elem = INFINITY; });
        bool *visited = new bool[VERTICES];
        std::for_each(visited, visited + VERTICES, [](bool &elem)
        { elem = false; });
        auto *pred = new nodeid_type[VERTICES];
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
     * Steiner Tree implementation to find the smallest cost subgraph of G that contains all the vertices in the subset S
     */
    std::pair<vector<edge>, set<nodeid_type>> steiner()
    {
        nodeid_type u;
        vector<nodeid_type> edges1;
        set<nodeid_type> finalVertices;
        vector<Graph::edge> finalEdges, finalEdges1;

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

                for (auto & finalEdge : finalEdges)
                {
                    size_t count = 0, dn = 0;
                    for (Graph::edge &check_edge : edges)
                    {
                        // find the same edge of finalEdges in edges
                        // find all the adjacent elements of the selected vertex
                        if (finalEdge == check_edge)
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

        // Print the Steiner Points in the Steiner Tree
        for (auto &steiner_t : steinerterminals)
        {
            finalVertices.erase(steiner_t);
            std::cout << steiner_t << std::endl;
        }
        return std::make_pair(finalEdges1, finalVertices);
    }
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
 * Recursive DP algorithm to get smallest Steiner tree (the smallest cost subgraph of G that contains all the vertices in the subset S)
 */
struct message
{
    message() = default;
    unsigned long long tp;
    union set_node
    {
        unsigned node;
        unsigned long long set;
    } x, y;
};
void getTree(nodeid_type u, unsigned long long A, set<nodeid_type> &vertex, vector<Graph::edge> &edge, const vector<vector<message>> &to, weight_type **matrix)
{
    if (to[u][A].tp == 1)
    {
        // printf("%d ", (to[u][A].y.node + 1) >> 1);
        vertex.insert(u);
        nodeid_type another = (u == to[u][A].x.node ? to[u][A].y.node : to[u][A].x.node);
        edge.emplace_back(u, another, matrix[u][another]);
        // print(to[u][A].x, A);
        getTree(another, A, vertex, edge, to, matrix);
    }
    if (to[u][A].tp == 2)
    {
        // print(u, to[u][A].x), print(u, to[u][A].y);
        getTree(u, to[u][A].x.set, vertex, edge, to, matrix);
        getTree(u, to[u][A].y.set, vertex, edge, to, matrix);
    }
}

std::pair<vector<Graph::edge>, set<nodeid_type>> Graph::SteinerTreeRecursive()
{
    set<nodeid_type> finalVertices;
    vector<Graph::edge> finalEdges;

    unsigned long long max_set = (1 << steinerterminals.size()) - 1;
    auto to = vector<vector<message>>(VERTICES, vector<message>(max_set + 1));
    vector<vector<weight_type>> dp(VERTICES, vector<weight_type>(max_set + 1, INFINITY));
    for (auto it = steinerterminals.begin(); it != steinerterminals.end(); ++it) {
        dp[*it][1 << (it - steinerterminals.begin())] = 0;
    }
    for (unsigned long long S = 1; S <= max_set; S++) // Enumerate all states defined by K key points
    {
        for (unsigned long long sub = S & (S - 1); sub; sub = S & (sub - 1)) // Enumerate subsets of current state
        {
            for (size_t i = 0; i < VERTICES; ++i) // Enumerate root
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
        priority_queue<pair<weight_type, nodeid_type>, vector<pair<weight_type, nodeid_type>>, greater<>> heap;
        for (size_t i = 0; i < VERTICES; ++i) heap.push(make_pair(dp[i][S], i));
        while (!heap.empty())  // Slack in S for shortest path
        {
            nodeid_type u = heap.top().second;
            heap.pop();
            for (auto &edge : edges)
            {
                if (u != edge.vertex1 && u != edge.vertex2) continue;
                nodeid_type v = u == edge.vertex1 ? edge.vertex2 : edge.vertex1; 
                if (dp[v][S] > dp[u][S] + edge.weight)  // use u-v-S to replace v-S
                {
                    heap.emplace(dp[v][S] = dp[u][S] + edge.weight, v);
                    to[v][S].tp = 1;
                    to[v][S].x.node = u;
                    to[v][S].y.node = v;
                }
            }
            while (!heap.empty() && heap.top().first > dp[heap.top().second][S])
                heap.pop();
        }
    }
    weight_type sum = INFINITY;
    nodeid_type root = 0;
    for (nodeid_type i = 0; i < VERTICES; ++i)
    {
        if (dp[i][max_set] < sum)
            sum = dp[i][max_set], root = i;
    }
    getTree(root, max_set, finalVertices, finalEdges, to, AdjacencyMatrix);  // Retrieve marks of DP

    for (auto &steiner_t : steinerterminals)
    {
        finalVertices.erase(steiner_t);
        std::cout << steiner_t << std::endl;
    }

    for (auto &final_edge : finalEdges)
    {
        std::cout << final_edge << std::endl;
    }

    return std::make_pair(finalEdges, finalVertices);
}

set<nodeid_type> convertIdentifier(const std::map<unsigned, Eigen::Vector3d> &container, const shared_ptr<GridMap>& interface, const string& type)
{
    // Store pose info for graph generation
    // Store ID for tree generation, each target or bs linked to one graph-node
    set<nodeid_type> id_set;
    for (auto &id_pose : container) // id_pose: id is entity-specific id published by entity_controller
    {
        nodeid_type node_id = interface->coord2adjMatIdx(id_pose.second); // The initial id in graph
        id_set.insert(node_id);
        node_to_name[node_id] = type + "_" + to_string(id_pose.first);
    }
    return id_set;
}

vector<nodeid_type> GridMapToInnerGraph(const set<nodeid_type>& steiner_terminals, Graph& g, const set<nodeid_type>& set_bs_id){
    // Convert to graph sub index (after deleting occupied nodes)
    vector<nodeid_type> terminals;
    vector<nodeid_type> converted_bs_id;
    nodeid_type converted_idx = 0;
    auto it = steiner_terminals.begin();
    while (it != steiner_terminals.end() && converted_idx< VERTICES) {
        if ((*(g.originalGraph))(converted_idx, converted_idx) == *it) {
            terminals.push_back(converted_idx);
            if (set_bs_id.count(*it)) converted_bs_id.push_back(converted_idx);
            ++it;
        }
        ++converted_idx;  // Assume i and *it both increase monotonously
    }

    // Add edges between base stations
    // TODO: Discuss the correctness of this method (which assume nodes belong to base stations are initially connected)
    for (size_t i = 0; i < converted_bs_id.size(); ++i) {
        for (size_t j = i + 1; j < converted_bs_id.size(); ++j) {
            g.insertedge(i, j, 0);
        }
    }

    return terminals;
}

std::function<bool(shared_ptr<SteinerTreeNode>, shared_ptr<SteinerTreeNode>)> isVisible;

void Prune(const shared_ptr<SteinerTreeNode>& root, const std::function<bool(shared_ptr<SteinerTreeNode>)>& isDeletable) {
    if (root == nullptr) return;
    if (root->id != dummy_root_id) {
        queue<shared_ptr<SteinerTreeNode>> Q;
        for (const shared_ptr<SteinerTreeNode>& child : root->children) {
            Q.push(child);
        }
        while (!Q.empty()) {
            shared_ptr<SteinerTreeNode> curr_child = Q.front(); Q.pop();
            if (curr_child == nullptr || !isDeletable(curr_child)) continue;
//            if (!all_of(curr_child->children.begin(), curr_child->children.end(), [Func = isVisible, root](auto && PH1) { return Func(root, std::forward<decltype(PH1)>(PH1)); })) continue;
            if (!all_of(curr_child->children.begin(), curr_child->children.end(), boost::bind(isVisible, root, _1))) continue;
            for (const shared_ptr<SteinerTreeNode>& child : curr_child->children) {
                root->children.insert(child);
                child->parent = root;
                Q.push(child);
            }
            root->children.erase(curr_child);
            cout << "[Prune] Deleted " << curr_child->id << "at " << curr_child->pos.transpose() << endl;
        }
    }
    for (const shared_ptr<SteinerTreeNode>& child : root->children) {
        Prune(child, isDeletable);
    }
}

void TraverseTree(const shared_ptr<SteinerTreeNode>& root, vector<Graph::edge>& edge_list, set<shared_ptr<SteinerTreeNode>>& steiner_nodes, map<nodeid_type, set<nodeid_type>> &node_neighbours) {
    if (root->id == dummy_root_id) {
        for (const shared_ptr<SteinerTreeNode>& child : root->children) TraverseTree(child, edge_list, steiner_nodes, node_neighbours);
        return;
    }

    if (root->node_type_id.empty()) steiner_nodes.insert(root);  // steiner point has no name yet
    if (root->parent->id != dummy_root_id) root->neighbours.insert(root->parent);
    for (const shared_ptr<SteinerTreeNode>& child : root->children) {
        // parent take responsibility to store its neighbour-relationship with child
        edge_list.emplace_back(root->id, child->id);
        node_neighbours[root->id].insert(child->id);
        node_neighbours[child->id].insert(root->id);
        root->neighbours.insert(child);
        TraverseTree(child, edge_list, steiner_nodes, node_neighbours);
    }
}

void visualize_visibility_graph(const ros::Publisher &, double, const shared_ptr<GridMap>&, Eigen::MatrixXd *, std::map<nodeid_type, std::set<nodeid_type>> &, std::vector<Graph::edge> &);

void update_UAV_poses(std::map<unsigned, Eigen::Vector3d> &uav_poses, unsigned required_amount) {
    uav_poses.clear();
    uav_num = required_amount;
    while (uav_poses.size() < uav_num)
    {
        ros::spinOnce();
    }
}

set<shared_ptr<SteinerTreeNode>> Graph::getAllocation(
    std::map<unsigned, Eigen::Vector3d> &target_poses,
    std::map<unsigned, Eigen::Vector3d> &bs_poses,
    std::map<unsigned, Eigen::Vector3d> &uav_poses,
    ros::NodeHandle &n)
{
    if (target_poses.empty()) return {};

    node_to_name.clear();
    set<nodeid_type> set_target_id = convertIdentifier(target_poses, interface, "target");
    set<nodeid_type> set_bs_id = convertIdentifier(bs_poses, interface, "bs");

    set<nodeid_type> steiner_terminals; // Initial node id
    steiner_terminals.insert(set_target_id.begin(), set_target_id.end());
    steiner_terminals.insert(set_bs_id.begin(), set_bs_id.end());

    vector<nodeid_type> terminals = GridMapToInnerGraph(steiner_terminals, *this, set_bs_id);

    this->assign_steiner_terminals(terminals);
    ROS_INFO("[steiner_tree] Started steiner tree generation");
    ros::Time start = ros::Time::now();
    auto steiner_answer = this->SteinerTreeRecursive();
    ros::Time end = ros::Time::now();
    ROS_INFO("[steiner_tree] Tree generation complete spent %.5fs\n", (end - start).toSec());

    // TODO: How to handle link between base stations
    vector<edge> steiner_edge_list;  // for building initial tree provided by Steiner algorithm
    std::for_each(steiner_answer.first.begin(), steiner_answer.first.end(), [&](edge e){
        steiner_edge_list.emplace_back((*originalGraph)(e.vertex1, e.vertex1), (*originalGraph)(e.vertex2, e.vertex2), e.weight);
    });

    // After getting initial Steiner tree topology, do pruning to improve the quality of solution
    vector<nodeid_type> roots(set_bs_id.begin(), set_bs_id.end());
    shared_ptr<SteinerTreeNode> root = BuildTreeFromEdgeList(steiner_edge_list, roots);
    // const std::function<bool(shared_ptr<SteinerTreeNode>)>& isDeletable = [&](const shared_ptr<SteinerTreeNode>& node) {
    //     // Function used to exclude nodes already linked to real entities
    //     return !set_target_id.count(node->id) && !set_bs_id.count(node->id);
    // };
    // Prune(root, isDeletable);
    vector<edge> final_edge_list;
    set<shared_ptr<SteinerTreeNode>> steiner_nodes; // set of UAV deployment nodes, also return as answer set
    std::map<nodeid_type, std::set<nodeid_type>> node_neighbours; // key: node ID, value: IDs of all neighbours
    TraverseTree(root, final_edge_list, steiner_nodes, node_neighbours);  // Rebuild edge list and node set, store neighbourhood

    /**
     * TODO: What to do if [3. Number requirement decreases]
     * TODO: Assign escort task to idle UAVs
     * Get the number of UAV required and calculate initial position
     * If UAVs had been initialized:
     *  1. Number requirement stay the same: do nothing, just update poses and do KM match
     *  2. Number requirement increases: publish requirement to 'generate' new UAV(s) from the 'camp' (same as the initialization process)
     *      (If some UAV(s) are already available, consider using them and only generate the extra part)
     *  3. Number requirement decreases: update poses, do KM match and only assign tasks to those matched UAVs
     */
    map<nodeid_type, Eigen::Vector3d> node_locations; // key: node ID, value: location of node. ONLY STEINER POINTS, for matching UAV and node
    for (const shared_ptr<SteinerTreeNode>& steiner_node_ptr : steiner_nodes)
    {
        node_locations[steiner_node_ptr->id] = steiner_node_ptr->pos;  // represent current goal position of UAV
    }
    unsigned current_requirement_number = steiner_nodes.size();

    if (current_requirement_number > available_uav_num) {
        ROS_ERROR("[steiner_tree] Require %u relays, but only %u UAVs available", current_requirement_number, available_uav_num);
        return {};
    }

    if (current_requirement_number > last_uav_requirement) {
        last_uav_requirement = current_requirement_number;
        if (current_requirement_number > uav_num) {
            // Generate new UAVs from 'camp' to satisfy current requirement
            message_files::PoseStampedArray requirement;
            requirement.header.seq = current_requirement_number;
            for (unsigned uav_seq = uav_num; uav_seq < current_requirement_number; ++uav_seq) {
                geometry_msgs::PoseStamped p;  // artificial initial position of UAVs
                p.header.seq = uav_seq;
                // p.pose.position.x = -10.0;
                // p.pose.position.y = -5.0 + 2.0 * uav_seq;
                // p.pose.position.z = 5.0;
                p.pose.position.x = -12.0;
                p.pose.position.y = -12.0;
                p.pose.position.z = 5.0;
                requirement.poses.push_back(p);
            }
            // Tell swarm planner UAV requirement and wait for initialization of UAVs
            pub_requirement.publish(requirement);
            ROS_INFO("[steiner_tree] Published requirement of %u UAVs", current_requirement_number);
            update_UAV_poses(uav_poses, current_requirement_number);
        }
    }

    // update UAV poses for best partial/full match
    update_UAV_poses(uav_poses, uav_num);

    /**
     * Translate vg-node-id to UAV id By assigning vg-nodes to UAVs following some rules
     * Result: key-value map from vg-node-id to UAV-id
     */
    std::map<nodeid_type, int> node_uav = assign(uav_poses, node_locations); // key: node ID, value: UAV ID that node assigned to
    for (auto &[node_id, uav_id] : node_uav)
    {
        string name = "uav_" + std::to_string(uav_id);
        node_to_name[node_id] = name;
        for (const shared_ptr<SteinerTreeNode>& steiner_node : steiner_nodes) {
            if (steiner_node->id == node_id) {
                steiner_node->node_type_id = name;
                break;
            }
        }
    }

    visualize_visibility_graph(pub_tree_network, n.param("/algorithm/grid_map/resolution", 3.0),
                               interface, originalGraph, node_neighbours, final_edge_list);
    // Publish all neighbourhood-edges, mainly for visualization and measurement
    message_files::SteinerTreeArray trees;
    for (auto &[node_id, neighbour] : node_neighbours)
    {
        message_files::SteinerTreeNode tmp;
        
        string name_id = node_to_name[node_id];
        tmp.name_id = name_id;
        
        unsigned uav_id = name_id[0] == 'u' ? stoi(name_id.substr(4)) : 0;
        tmp.header.seq = uav_id;

        auto node_loc = interface->adjMatIdx2coord(node_id);
        tmp.coordinate.x = node_loc(0);
        tmp.coordinate.y = node_loc(1);
        tmp.coordinate.z = node_loc(2);
        for (auto &neighbour_id : neighbour)
        {
            tmp.neighbour_type_id.push_back(node_to_name[neighbour_id]);
        }
        trees.entity_neighbours.push_back(tmp);
    }
    pub_tree_array.publish(trees);

    return steiner_nodes;
}

void visualize_visibility_graph(const ros::Publisher &pub_tree_network,
                                double grid_size, const shared_ptr<GridMap>& interface, Eigen::MatrixXd *adjMatPtr,
                                std::map<nodeid_type, std::set<nodeid_type>> &node_neighbours, std::vector<Graph::edge> &final_edges)
{
//    ROS_INFO("[DEBUG] Grid size is %.2f", grid_size);
    // Clear exisiting markers representing visibility graph
    visualization_msgs::MarkerArray deleteall;
    visualization_msgs::Marker tmp;
    tmp.action = visualization_msgs::Marker::DELETEALL;
    tmp.header.frame_id = "/world";
    tmp.ns = "grid_map";
    tmp.id = 2;
    deleteall.markers.push_back(tmp);
    tmp.ns = "tree_node";
    tmp.id = 0;
    deleteall.markers.push_back(tmp);
    tmp.ns = "tree_edge";
    tmp.id = 1;
    deleteall.markers.push_back(tmp);
    pub_tree_network.publish(deleteall);

    /* Test steiner tree solution */
    visualization_msgs::MarkerArray graph_markers;

    // visualization_msgs::Marker graph;
    // graph.ns = "grid_map";
    // graph.type = visualization_msgs::Marker::CUBE_LIST;
    // graph.action = visualization_msgs::Marker::ADD;
    // graph.header.frame_id = "/world";
    // graph.pose.position.x = graph.pose.position.y = graph.pose.position.z = 0.0;
    // graph.pose.orientation.x = 0;
    // graph.pose.orientation.y = 0;
    // graph.pose.orientation.z = 0;
    // graph.pose.orientation.w = 1;
    // graph.scale.x = grid_size / 4;
    // graph.scale.y = grid_size / 4;
    // graph.scale.z = grid_size / 4;
    // graph.color.r = 0.0;
    // graph.color.g = 0.0;
    // graph.color.b = 0.0;
    // graph.color.a = 0.1;
    // for (size_t i = 0; i < VERTICES; ++i)
    // {
    //     Eigen::Vector3d curr = interface->adjMatIdx2coord((*adjMatPtr)(i, i));
    //     geometry_msgs::Point curr_node_centre;
    //     curr_node_centre.x = curr(0);
    //     curr_node_centre.y = curr(1);
    //     curr_node_centre.z = curr(2);
    //     graph.points.push_back(curr_node_centre);
    //     graph.colors.push_back(graph.color);
    // }
    // graph_markers.markers.push_back(graph);

    visualization_msgs::Marker tree;
    tree.ns = "tree_node";
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
        Eigen::Vector3d curr = interface->adjMatIdx2coord(id);
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
        Eigen::Vector3d pt_1 = interface->adjMatIdx2coord(edge.vertex1);
        Eigen::Vector3d pt_2 = interface->adjMatIdx2coord(edge.vertex2);
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

    pub_tree_network.publish(graph_markers);
}

// // /* Test */
// // Graph g(VERTICES);
// // g.insertedge(1, 2, 2);
// // g.insertedge(2, 3, 3);
// // g.insertedge(1, 5, 3);
// // g.insertedge(2, 6, 9);
// // g.insertedge(3, 7, 2);
// // g.insertedge(3, 4, 8);
// // g.insertedge(4, 8, 9);
// // g.insertedge(5, 6, 4);
// // g.insertedge(5, 9, 6);
// // g.insertedge(7, 6, 1);
// // g.insertedge(7, 8, 4);
// // g.insertedge(9, 10, 8);
// // g.insertedge(6, 10, 4);
// // g.insertedge(8, 10, 5);
// // /* Test */
