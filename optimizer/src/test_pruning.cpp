#include <bits/stdc++.h>
#include "visibility_graph/los_checker.hpp"
#include "steiner_tree.hpp"
using namespace std;

#include "backward-cpp/backward.hpp"
namespace backward
{

    backward::SignalHandling sh;

} // namespace backward

struct SteinerTreeNode {
    std::string node_type_id;
    nodeid_type id;
    Eigen::Vector3d pos;
    set<SteinerTreeNode*> children;
    SteinerTreeNode* parent;

    SteinerTreeNode(nodeid_type id) {
        this->id = id;
    }
};

const nodeid_type dummy_root_id = INT_MAX;

bool TestCheckLineOfSight(Eigen::Vector3d pt1, Eigen::Vector3d pt2) {

}

SteinerTreeNode* BuildTreeExampleFromEdgeList(const vector<Graph::edge>& E, const vector<nodeid_type>& roots) {
    // Initialize with one dummy root
    map<nodeid_type, SteinerTreeNode*> Index_to_NodePtr;
    SteinerTreeNode* dummy_root = new SteinerTreeNode(dummy_root_id);
    Index_to_NodePtr[dummy_root_id] = dummy_root;
    for (nodeid_type root_id : roots) {
        auto current_node = new SteinerTreeNode(root_id);
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
                if (!Index_to_NodePtr.count(v2)) Index_to_NodePtr[v2] = new SteinerTreeNode(v2);
                SteinerTreeNode* next_node_ptr = Index_to_NodePtr[v2];
                it->second->children.insert(next_node_ptr);
                next_node_ptr->parent = it->second;
                edge_visited[idx] = 1;
                --edge_count;
                ROS_INFO("%zu", edge_count);
                break;
            }
        }
    }

    return dummy_root;
}

bool isVisible(SteinerTreeNode* from, SteinerTreeNode* to) {
    if (from->id == 1 && to->id == 8) return true;
    if (from->id == 1 && to->id == 9) return true;
    if (from->id == 1 && to->id == 11) return true;
    if (from->id == 2 && to->id == 6) return true;
    if (from->id == 2 && to->id == 7) return true;
    if (from->id == 5 && to->id == 7) return true;
    return false;
}

bool isDeletable(SteinerTreeNode* node) {
    if (node->id == dummy_root_id) return false;
    if (node->children.empty()) return false;
    return true;
}

void connectToCurrentRootAndPush(SteinerTreeNode* root, SteinerTreeNode* child, queue<SteinerTreeNode*>& Q) {
    root->children.insert(child);
    child->parent = root;
    Q.push(child);
}

void Prune(SteinerTreeNode* root) {
    if (root == nullptr) return;
    if (root->id != dummy_root_id) {
        queue<SteinerTreeNode*> Q;
        for (SteinerTreeNode* child : root->children) {
            Q.push(child);
        }
        while (!Q.empty()) {
            SteinerTreeNode* curr_child = Q.front(); Q.pop();
            if (!isDeletable(curr_child)) continue;
            if (!all_of(curr_child->children.begin(), curr_child->children.end(), boost::bind(isVisible, root, _1))) continue;
            for (SteinerTreeNode* child : curr_child->children) {
                connectToCurrentRootAndPush(root, child, Q);
            }
            root->children.erase(curr_child);
            ROS_INFO("Deleted %u", curr_child->id);
            delete curr_child;
        }
    }
    for (SteinerTreeNode* child : root->children) {
        Prune(child);
    }
}

void TransformTreeToEdgeList(SteinerTreeNode* root, vector<Graph::edge>& edge_list) {
    for (SteinerTreeNode* child : root->children) {
        if (root->id != dummy_root_id) edge_list.emplace_back(root->id, child->id);
        TransformTreeToEdgeList(child, edge_list);
    }
}

int main() {
//    ros::init(argc, argv, "test_pruning");
//    ros::NodeHandle n("~");
//    LosChecker los_checker;
//    los_checker.init(n);
//    ros::Duration(2.0).sleep(); // Wait the map generation, can be deleted
//    ros::spinOnce();
//    std::shared_ptr<GridMap> grid_map_ptr = los_checker.grid_map_interface();
//    std::function<bool(Eigen::Vector3d, Eigen::Vector3d)> checkLineOfSight = grid_map_ptr->checkLineOfSight;
    std::function<bool(Eigen::Vector3d, Eigen::Vector3d)> checkLineOfSight = TestCheckLineOfSight;

      /* Test */
    vector<Graph::edge> E;
//    VERTICES = 11;
//    Graph g(VERTICES);
//    g.insertedge(1, 2, 2);
//    g.insertedge(2, 3, 3);
//    g.insertedge(1, 5, 3);
//    g.insertedge(2, 6, 9);
//    g.insertedge(3, 7, 2);
//    g.insertedge(3, 4, 8);
//    g.insertedge(4, 8, 9);
//    g.insertedge(5, 6, 4);
//    g.insertedge(5, 9, 6);
//    g.insertedge(7, 6, 1);
//    g.insertedge(7, 8, 4);
//    g.insertedge(9, 10, 7);
//    g.insertedge(6, 10, 10);
//    g.insertedge(8, 10, 5);
//    auto terminals = vector<nodeid_type>{1, 4, 5, 9, 10};
//    SteinerTreeNode* root = BuildTreeExampleFromEdgeList(steiner_answer.first, {1});

    VERTICES = 12;
    Graph g(VERTICES);
    g.insertedge(1, 2, 2);  // temp edge, to convert the forest to tree
    g.insertedge(1, 3, 1);
    g.insertedge(1, 4, 1);
    g.insertedge(3, 8, 1);
    g.insertedge(3, 9, 1);
    g.insertedge(4, 10, 1);
    g.insertedge(4, 11, 1);
    g.insertedge(2, 5, 1);
    g.insertedge(5, 6, 1);
    g.insertedge(6, 7, 1);
    auto terminals = vector<nodeid_type>{1,2,3,4,5,6,7,8,9,10,11};
    g.assign_steiner_terminals(terminals);
    auto steiner_answer = g.SteinerTreeRecursive();
    // Remove temp edge. Only for test.
    for (auto it = steiner_answer.first.begin(); it != steiner_answer.first.end(); ++it) {
        if (it->weight == 2) {
            steiner_answer.first.erase(it);
            break;
        }
    }

    SteinerTreeNode* root = BuildTreeExampleFromEdgeList(steiner_answer.first, {1, 2});
    Prune(root);
    vector<Graph::edge> edge_list;
    TransformTreeToEdgeList(root, edge_list);
    for (auto& edge : edge_list) cout << edge << endl;
    /* Test */

    return 0;
}
