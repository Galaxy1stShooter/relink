#include "star_convex.hpp"
#include "steiner_tree.hpp"
#include "optimizer/optimizer.hpp"

#include "backward-cpp/backward.hpp"
namespace backward
{

    backward::SignalHandling sh;

} // namespace backward

StarConvexGenerator scp_generator;

bool topology_initialized = false;

void setInputMapCallback(const sensor_msgs::PointCloud2ConstPtr &global_map)
{
    pcl::fromROSMsg(*global_map, scp_generator.global_pcl);
    if (!scp_generator.global_pcl.empty()) scp_generator.global_kd_tree.setInputCloud(scp_generator.global_pcl.makeShared());
}

void updateEntityPoseCallback(const message_files::PoseStampedArrayConstPtr &poses, std::map<unsigned, Eigen::Vector3d> &container, int type)
{
    container.clear();
    for (auto &pose : poses->poses)
    {
        container[pose.header.seq] = std::move(Eigen::Vector3d(pose.pose.position.x,
                                                               pose.pose.position.y,
                                                               pose.pose.position.z));
    }
}

void episodeControllerCallback(const std_msgs::UInt32ConstPtr &msg, unsigned& episode_seq, bool& reset_episode)
{
    if (episode_seq != msg->data)
    {
        episode_seq = msg->data;
        reset_episode = true;
    }
}

void clickCallback(const geometry_msgs::PoseStampedPtr &msg) {
    topology_initialized = false;
}

// struct Agent {
//     Eigen::Vector3d curr_pos;
//     Eigen::Vector3d curr_goal;
//     message_files::StarConvexPolytopesStamped SCPs;  // Header.seq: uav_id

//     Agent() = default;
//     // Agent()
// };
message_files::PoseStampedArray solveOptimalPoseCentrally(const std::set<std::shared_ptr<SteinerTreeNode>>& tree_node_set, StarConvexOptimizer& optimizer) {
    message_files::PoseStampedArray curr_solutions;
    curr_solutions.header.frame_id = "/world";

    bool no_solution_yet = scp_generator.solution_poses.empty();
    for (shared_ptr<SteinerTreeNode> TreeNodePtr : tree_node_set) {
        auto uav_id_type = TreeNodePtr->node_type_id;
        if (uav_id_type[0] != 'u') continue;
        unsigned uav_id = std::stoi(uav_id_type.substr(4));  // uav_id_type.find_first_of('_') + 1

        if (no_solution_yet) {
            scp_generator.solution_poses[uav_id] = TreeNodePtr->pos;
        }
    }

    // Generate SCPs of entities (for visualization) and solutions (predict, for optimization) separately
    scp_generator.generateStarConvex();

    std::vector<Agent> UAV_data_array;
    UAV_data_array.resize(available_uav_num);
    for (shared_ptr<SteinerTreeNode> TreeNodePtr : tree_node_set) {
        auto uav_id_type = TreeNodePtr->node_type_id;
        if (uav_id_type[0] != 'u') continue;
        unsigned uav_id = std::stoi(uav_id_type.substr(4));  // uav_id_type.find_first_of('_') + 1

        UAV_data_array[uav_id].SCPs.header.seq = uav_id;
        for (shared_ptr<SteinerTreeNode> neighbour : TreeNodePtr->neighbours)
        {
            std::string neighbour_name_id = neighbour->node_type_id;
            if (neighbour_name_id[0] == 'u') neighbour_name_id = "solution_" + neighbour_name_id.substr(4);
            UAV_data_array[uav_id].SCPs.SCPs.emplace_back(scp_generator.predict_SCPs.SCPs[scp_generator.nameid_SCP_index[neighbour_name_id]]);
        }
        UAV_data_array[uav_id].current_position = scp_generator.uav_poses[uav_id];
        UAV_data_array[uav_id].goal_position = TreeNodePtr->pos;
    }

    Eigen::VectorXd optimal_pose_array = optimizer.solveOptimalPoseArray(UAV_data_array);
    // Eigen::VectorXd optimal_pose_array;
    for (unsigned uav_id = 0; uav_id < available_uav_num; ++uav_id) {
        Eigen::Vector3d optimal_pose = optimal_pose_array.segment(uav_id * 3, 3);
        if (optimal_pose == Eigen::Vector3d::Zero()) continue;
        scp_generator.solution_poses[uav_id] = optimal_pose;
        // Store the goal point
        geometry_msgs::PoseStamped goal_pt;
        goal_pt.header.seq = uav_id;
        goal_pt.pose.position.x = optimal_pose(0);
        goal_pt.pose.position.y = optimal_pose(1);
        goal_pt.pose.position.z = optimal_pose(2);
        curr_solutions.poses.push_back(goal_pt);
    }

    return curr_solutions;
}

message_files::PoseStampedArray noOptimization(const std::set<std::shared_ptr<SteinerTreeNode>>& tree_node_set, StarConvexOptimizer& optimizer) {
    message_files::PoseStampedArray curr_solutions;
    curr_solutions.header.frame_id = "/world";

    bool no_solution_yet = scp_generator.solution_poses.empty();
    for (shared_ptr<SteinerTreeNode> TreeNodePtr : tree_node_set) {
        auto uav_id_type = TreeNodePtr->node_type_id;
        if (uav_id_type[0] != 'u') continue;
        unsigned uav_id = std::stoi(uav_id_type.substr(4));  // uav_id_type.find_first_of('_') + 1

        if (no_solution_yet) {
            scp_generator.solution_poses[uav_id] = TreeNodePtr->pos;
        }

        geometry_msgs::PoseStamped goal_pt;
        goal_pt.header.seq = uav_id;
        goal_pt.pose.position.x = TreeNodePtr->pos.x();
        goal_pt.pose.position.y = TreeNodePtr->pos.y();
        goal_pt.pose.position.z = TreeNodePtr->pos.z();
        curr_solutions.poses.push_back(goal_pt);
    }

    return curr_solutions;
}

message_files::PoseStampedArray solveOptimalPoseSeparately(const std::set<std::shared_ptr<SteinerTreeNode>>& tree_node_set, StarConvexOptimizer& optimizer) {
    message_files::PoseStampedArray curr_solutions;
    curr_solutions.header.frame_id = "/world";

    // TODO: priority of optimization or other distributed optimization scheme
    std::deque<std::pair<unsigned, shared_ptr<SteinerTreeNode>>> q;
    bool no_solution_yet = scp_generator.solution_poses.empty();
    for (shared_ptr<SteinerTreeNode> TreeNodePtr : tree_node_set) {
        auto uav_id_type = TreeNodePtr->node_type_id;
        if (uav_id_type[0] != 'u') continue;
        unsigned uav_id = std::stoi(uav_id_type.substr(4));  // uav_id_type.find_first_of('_') + 1
        q.emplace_front(uav_id, TreeNodePtr);

        if (no_solution_yet) {
            scp_generator.solution_poses[uav_id] = TreeNodePtr->pos;
        }
    }

    // Generate SCPs of entities (for visualization) and solutions (predict, for optimization) separately
    scp_generator.generateStarConvex();

    // Call optimizer for each UAV based on its pose and its neighbours' SCPs
    while (!q.empty()) {
        auto& [uav_id, TreeNodePtr] = q.front();
        auto& cur_pos = scp_generator.uav_poses[uav_id];

        message_files::StarConvexPolytopesStamped SCPs;
        SCPs.header.seq = uav_id;
        for (shared_ptr<SteinerTreeNode> neighbour : TreeNodePtr->neighbours)
        {
            std::string neighbour_name_id = neighbour->node_type_id;
            if (neighbour_name_id[0] == 'u') neighbour_name_id = "solution_" + neighbour_name_id.substr(4);
            SCPs.SCPs.emplace_back(scp_generator.predict_SCPs.SCPs[scp_generator.nameid_SCP_index[neighbour_name_id]]);
        }
        // Call optimizer interface
        Eigen::Vector3d optimal_pose = optimizer.solveOptimalPose(cur_pos, TreeNodePtr->pos, SCPs);
        scp_generator.solution_poses[uav_id] = optimal_pose;
        // Store the goal point
        geometry_msgs::PoseStamped goal_pt;
        goal_pt.header.seq = uav_id;
        goal_pt.pose.position.x = optimal_pose(0);
        goal_pt.pose.position.y = optimal_pose(1);
        goal_pt.pose.position.z = optimal_pose(2);
        curr_solutions.poses.push_back(goal_pt);
        q.pop_front();
    }

    return curr_solutions;
}

map<unsigned, message_files::SteinerTreeNode> uav_tree;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "star_convex");
    ros::NodeHandle n("~");

    available_uav_num = n.param("/available_uav_num", 0);

    ros::Subscriber sub_global_map = n.subscribe("/map_generator/global_cloud", 1, setInputMapCallback);
    ros::Subscriber click_sub = n.subscribe("/move_base_simple/goal", 1, clickCallback);

    scp_generator.init(n);
    ros::Subscriber sub_target = n.subscribe<message_files::PoseStampedArray>("target_waypoint", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(scp_generator.target_poses), TARGET));
    ros::Subscriber sub_bs = n.subscribe<message_files::PoseStampedArray>("bs_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(scp_generator.bs_poses), BASE_STATION));
    ros::Subscriber sub_uav = n.subscribe<message_files::PoseStampedArray>("uav_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(scp_generator.uav_poses), UAV));
    ros::Publisher pub_solutions = n.advertise<message_files::PoseStampedArray>("/optimizer/solution", 1, true);  // Array of [id: optimal position]
    pub_entity_SCPs = n.advertise<message_files::StarConvexPolytopesStamped>("star_convex", 1, true);
    pub_predict_SCPs = n.advertise<message_files::StarConvexPolytopesStamped>("predict_star_convex", 1, true);

    while (scp_generator.global_pcl.empty()) ros::spinOnce();

    ros::Time init_start = ros::Time::now();
    /**
     * Get graph (only depend on the map generated) from vg_constructor and other information
     * Vertices: all vertices in graph, in pre-decided struct Vertex {id: nodeid_type, info: TBD(required flag: BS, target, normal visiblity graph node)}
     * Edges: edges in graph, in struct adjacent matrix (m[i][j] is weight of edge(v_i, v_j))
     * Other informations
     */
    GraphConstructor vg_constructor;
    vg_constructor.init(n);
    vg_constructor.grid_map_interface()->occupy_threshold = 10;
    Eigen::MatrixXd *adjMatPtr = nullptr;
    while ((adjMatPtr = vg_constructor.getAdjacencyMatrix()) == nullptr) ros::spinOnce();
    vg_constructor.drawGridMap();

    // VERTICES = std::sqrt(adjMatPtr->size());
    // Graph g(VERTICES, *adjMatPtr);
    // g.initPublisher(n);
    // g.interface = vg_constructor.grid_map_interface();

    StarConvexOptimizer optimizer;
    optimizer.init(n);

    LosChecker los_checker;
    los_checker.init(n);
    los_checker.grid_map_interface()->occupy_threshold = 15;
    ros::spinOnce();
    std::shared_ptr<GridMap> grid_map_ptr = los_checker.grid_map_interface();
    ros::Time init_end = ros::Time::now();

    double grid_resolution = n.param("grid_map/resolution", 1.0);
    isVisible = [&](shared_ptr<SteinerTreeNode> from, shared_ptr<SteinerTreeNode> to) {
        // Call visibility_graph/los_checker to check visibility
        // Different from the function in entities_visualization, since pruning should be safer
        if ((from->pos - to->pos).norm() > scp_generator.radius_comm * 0.95) return false;
        // To improve relay to cars, use the bottom centre of grids on the ground to do more conservative pruning
        Eigen::Vector3d from_pos = from->pos; if (from_pos(2) < grid_resolution) from_pos(2) = 0.0;
        Eigen::Vector3d to_pos = to->pos; if (to_pos(2) < grid_resolution) to_pos(2) = 0.0;
        return los_checker.checkLineOfSight(from_pos, to_pos);
    };
    
    set<shared_ptr<SteinerTreeNode>> tree_node_set;  // key: UAVid_type

    double redeploy_rate;
    n.param("algorithm/redeploy_rate", redeploy_rate, 1.0);
    ROS_ASSERT(redeploy_rate > 0);
    ros::Rate rate(redeploy_rate);

    while (ros::ok())
    {
        ros::spinOnce();  // Check topology_initialized

        
        /* Initial assignment */
        // if (topology_generation_required)
        // Run only when target waypoints changed
        if (!topology_initialized) {
            ros::Duration(0.2).sleep();
            // Update pose information of targets
            scp_generator.target_poses.clear();
            while (scp_generator.target_poses.empty()) ros::spinOnce();  // Update targets' poses (waypoints)

            // Run steiner tree once to get uav number and publish, get uav poses and network topology
            ros::Time start = ros::Time::now();
            Eigen::MatrixXd *adjMatPt = nullptr;
            adjMatPt = vg_constructor.getAdjacencyMatrix();
            VERTICES = std::sqrt(adjMatPt->size());
            Graph g(VERTICES, *adjMatPt);
            g.initPublisher(n);
            g.interface = vg_constructor.grid_map_interface();

            tree_node_set = g.getAllocation(scp_generator.target_poses, scp_generator.bs_poses, scp_generator.uav_poses, n);
            uav_num = tree_node_set.size();
            ROS_INFO("[algorithm] Network topology initialized");
            topology_initialized = true;
            
            
            // message_files::PoseStampedArray curr_solutions = solveOptimalPoseSeparately(tree_node_set, optimizer);
            message_files::PoseStampedArray curr_solutions = solveOptimalPoseCentrally(tree_node_set, optimizer);
            // message_files::PoseStampedArray curr_solutions = noOptimization(tree_node_set, optimizer);
            ros::Time end = ros::Time::now();
            // curr_solutions.header.stamp = (end - start).;
            curr_solutions.init_start = init_start;
            curr_solutions.init_end = init_end;
            curr_solutions.start = start;
            curr_solutions.end = end;

            ROS_INFO("[optimizer] Optimization complete for %zu UAV spent %.5fs\n", scp_generator.uav_poses.size(), (end - start).toSec());
            pub_solutions.publish(curr_solutions);
        }
    }

    return 0;
}

// /* Test */
// Graph g(VERTICES);
// g.insertedge(1, 2, 2);
// g.insertedge(2, 3, 3);
// g.insertedge(1, 5, 3);
// g.insertedge(2, 6, 9);
// g.insertedge(3, 7, 2);
// g.insertedge(3, 4, 8);
// g.insertedge(4, 8, 9);
// g.insertedge(5, 6, 4);
// g.insertedge(5, 9, 6);
// g.insertedge(7, 6, 1);
// g.insertedge(7, 8, 4);
// g.insertedge(9, 10, 8);
// g.insertedge(6, 10, 4);
// g.insertedge(8, 10, 5);
// /* Test */
