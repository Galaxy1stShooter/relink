#include "test_steiner_tree.hpp"
#include "star_convex.hpp"
#include "backward-cpp/backward.hpp"
namespace backward
{

    backward::SignalHandling sh;

} // namespace backward

StarConvexGenerator generator;

void setInputMapCallback(const sensor_msgs::PointCloud2ConstPtr &global_map)
{
    pcl::fromROSMsg(*global_map, generator.global_pcl);
    generator.global_kd_tree.setInputCloud(generator.global_pcl.makeShared());
}

void updateEntityPoseCallback(const message_files::PoseStampedArrayConstPtr &poses, std::map<unsigned, Eigen::Vector3d> &container)
{
    container.clear();
    for (auto &pose : poses->poses)
    {
        container[pose.header.seq] = std::move(Eigen::Vector3d(pose.pose.position.x,
                                                               pose.pose.position.y,
                                                               pose.pose.position.z));
    }
}

void updateNeighbourCallback(const message_files::SteinerTreeNodeConstPtr &msg)
{
    // if (msg->header.seq != MY_IDENTIFIER) return;
    auto uav_id = msg->header.seq;
    if (generator.uav_neighbours.count(uav_id))
        generator.uav_neighbours[uav_id].clear();
    else
        generator.uav_neighbours[uav_id] = std::set<std::string>();
    auto &neighbour_set = generator.uav_neighbours[uav_id];

    for (auto &neighbour : msg->neighbour_type_id)
    {
        neighbour_set.insert(neighbour);
    }
}

void episodeControllerCallback(const std_msgs::UInt32ConstPtr &msg, unsigned *episode_seq, bool *reset_episode)
{
    if (*episode_seq != msg->data)
    {
        *episode_seq = msg->data;
        *reset_episode = true;
    }
}

void redrawClickMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg, const ros::NodeHandle &n)
{
    generator.generateStarConvex(n);
}

map<unsigned, message_files::SteinerTreeNode> uav_tree;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "star_convex");
    ros::NodeHandle n("~");

    generator.radius_comm = n.param("/algorithm/radius_comm", 5.0);
    n.setParam("grid_map/resolution", n.param("/algorithm/radius_comm", 5.0) / (2 * std::sqrt(3)));

    ros::Subscriber sub_click_map = n.subscribe<sensor_msgs::PointCloud2>("/pcl_render_node/local_map", 1, boost::bind(&redrawClickMapCallback, _1, n));
    ros::Subscriber sub_global_map = n.subscribe("/map_generator/inflated_global_cloud", 1, setInputMapCallback);

    ros::Subscriber sub_target = n.subscribe<message_files::PoseStampedArray>("target_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(generator.target_poses)));
    ros::Subscriber sub_bs = n.subscribe<message_files::PoseStampedArray>("bs_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(generator.bs_poses)));
    ros::Subscriber sub_uav = n.subscribe<message_files::PoseStampedArray>("uav_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(generator.uav_poses)));

    while (generator.global_pcl.empty()) ros::spinOnce();
    /**
     * Get graph (only depend on the map generated) from vg_constructor and other information
     * Vertices: all vertices in graph, in pre-decided struct Vertex {id: nodeid_type, info: TBD(required flag: BS, target, normal visiblity graph node)}
     * Edges: edges in graph, in struct adjacent matrix (m[i][j] is weight of edge(v_i, v_j))
     * Other informations
     */
    GraphConstructor vg_constructor;
    vg_constructor.init(n);
    Eigen::MatrixXd *adjMatPtr = nullptr;
    while ((adjMatPtr = vg_constructor.getAdjacencyMatrix()) == nullptr) ros::spinOnce();
    VERTICES = std::sqrt(adjMatPtr->size());

    Graph g(VERTICES, *adjMatPtr);
    g.initPublisher(n);

    auto *episode_seq = new unsigned(0);
    auto *reset_episode = new bool(false);
    ros::Subscriber sub_episode = n.subscribe<std_msgs::UInt32>("/episode_controller/episode_seq", 1, boost::bind(&episodeControllerCallback, _1, episode_seq, reset_episode));
    bool topology_initiaized = true;
    std::map<std::string, std::set<std::string>> nodename_neighbourname;

    while (ros::ok())
    {
        ROS_INFO("[algorithm] checking episode\n");
        while (!*reset_episode)
        {
            // Update pose information of targets and bss
            generator.target_poses.clear(); generator.bs_poses.clear(); generator.uav_poses.clear();
            while (generator.target_poses.empty() || generator.bs_poses.empty()) ros::spinOnce();  // Update targets and bss' poses

            /* Initial assignment */
            // if (topology_generation_required)
            if (topology_initiaized) {
                topology_initiaized = false;
                // Run steiner tree once to get uav number and publish, get uav poses and network topology

                g.getAllocation(generator.target_poses, generator.bs_poses, generator.uav_poses,
                                                         *vg_constructor.grid_map_interface(), n);
                ROS_INFO("[algorithm] Network topology of episode %d initialized", *episode_seq);
            }
        }
        /* One episode complete, reset framework */
        *reset_episode = false;
        topology_initiaized = true;
        nodename_neighbourname.clear();
        generator.reset();
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
