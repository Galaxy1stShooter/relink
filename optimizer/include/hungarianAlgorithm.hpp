#pragma once

#include <vector>
#include <map>
#include <Eigen/Eigen>
using namespace std;

bool findPath(int x, size_t N, const vector<vector<double>> &weights,
              vector<int> &optimal_match, vector<double> &label_x, vector<double> &label_y,
              vector<bool> &visit_x, vector<bool> &visit_y, vector<double> &slack)
{
    visit_x[x] = true;

    for (size_t y = 0; y < N; ++y)
    {
        if (visit_y[y])
            continue;
        if (fabs(weights[x][y] - (label_x[x] + label_y[y])) < 1e-5)
        {
            visit_y[y] = true;
            if (optimal_match[y] == -1 ||
                findPath(optimal_match[y], N, weights, optimal_match, label_x, label_y, visit_x, visit_y, slack))
            {
                optimal_match[y] = x;
                return true;
            }
        }
        else
        {
            slack[y] = fmin(slack[y], label_x[x] + label_y[y] - weights[x][y]);
        }
    }

    return false;
}

vector<int> KM(const vector<vector<double>> &weights)
{
    /**
     * MATCH ONCE
     * Kuhn-Munkres Algorithm for the optimal matching of bipartite graph
     * weights: the weight matrix of the bipartite graph
     */
    size_t N = weights.size(); // the order of weight matrix

    // Initialization

    vector<int> optimal_match = vector<int>(N, -1);
    vector<double> label_x(N, -INFINITY);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) label_x[i] = fmax(label_x[i], weights[i][j]);
    }
    vector<double> label_y = vector<double>(N, 0);

    for (size_t x = 0; x < N; ++x)
    {
        vector<double> slack(N, INFINITY);

        while (true)
        {
            vector<bool> visit_x = vector<bool>(N, false);
            vector<bool> visit_y = vector<bool>(N, false);

            if (findPath(x, N, weights, optimal_match, label_x, label_y, visit_x, visit_y, slack))
                break;

            double temp = INFINITY;
            for (size_t y = 0; y < N; ++y)
            {
                if (!visit_y[y] && slack[y] < temp)
                    temp = slack[y];
            }
            if (temp != temp)
            {
                std::cout << "[KM] NO SOLUTION" << std::endl;
                return {};
            }

            for (size_t i = 0; i < N; ++i)
            {
                if (visit_x[i])
                    label_x[i] -= temp;
                if (visit_y[i])
                    label_y[i] += temp;
                else
                    slack[i] -= temp;
            }
        }
    }

    return optimal_match;
}

template <typename nodeid_type>
map<nodeid_type, int> assign(map<unsigned, Eigen::Vector3d> uav_locs, map<nodeid_type, Eigen::Vector3d> node_locs)
{
    size_t N = max(uav_locs.size(), node_locs.size());
    vector<vector<double>> weights(N, vector<double>(N));
    vector<unsigned> uav_id;
    vector<nodeid_type> node_id;
    for (auto& uav_id_loc : uav_locs) uav_id.push_back(uav_id_loc.first);
    for (auto& node_id_loc : node_locs) node_id.push_back(node_id_loc.first);
    
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            // KM is for maximum match, so take negative amount to achieve shortest distance
            // if (i < uav_id.size() && j < node_locs.size()) weights[i][j] = -(uav_locs[uav_id[i]] - node_locs[node_id[j]]).norm();
            if (i < uav_id.size() && j < node_locs.size()) weights[i][j] = -(uav_locs[uav_id[i]] - node_locs[node_id[j]]).squaredNorm();
            // else  weights[i][j] = -1000;
            else  weights[i][j] = 0;  // give dummy node/UAV higher priority
        }
    }
    auto optimal_match = KM(weights);  // index: node id, value: uav id
    for (int i = 0; i < N; ++i) {
        printf("[DEBUG] Optimal match: Node %d <--> UAV %d\n", i, optimal_match[i]);
    }

    // TODO: UAV amount greater than nodes
    printf("[KM] Optimal match:\n");
    map<nodeid_type, int> node_uav;
    for (size_t node_index = 0; node_index < N; ++node_index) {
        if (node_index < node_locs.size()) {
            // Real nodes. Assume UAV is enough to cover existing nodes
            node_uav[node_id[node_index]] = uav_id[optimal_match[node_index]];
            printf("[node: id %d] <--> [uav: id %d]\n", node_id[node_index], uav_id[optimal_match[node_index]]);
        } else {
            // Dummy nodes due to extra UAV
            printf("[node: DUMMY] <--> [uav: id %d]\n", uav_id[optimal_match[node_index]]);
        }
        // if (optimal_match[i] < (int)uav_id.size() && optimal_match[i] != -1) {
        //     node_uav[node_id[i]] = uav_id[optimal_match[i]];
        //     printf("[node: id %d] to [uav: id %d]\n", node_id[i], uav_id[optimal_match[i]]);
        // } else {
        //     printf("[node: id %d] to [DUMMY]\n", node_id[i]);
        // }
    }
    return node_uav;
}

// int main()
// {
//     vector<vector<double>> a{{2, 3, 0, 3, 4},
//                              {0, 4, 2, 0, 5},
//                              {2, 6, 0, 0, 6},
//                              {0, 8, 7, 9, 4},
//                              {1, 0, 7, 0, 9}};
//     auto optimal_match = KM(a);
//     for (auto& elem: optimal_match) printf("%zu ", elem);
//     return 0;
// }
