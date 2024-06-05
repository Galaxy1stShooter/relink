#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <Eigen/Eigen>
#include <ros/ros.h>

#include <geometry_msgs/PoseArray.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include "message_files/PoseStampedArray.h"
#include "messsage_files/entity_identifier.h"

#include "network.hpp"

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<double> rand_x;
std::uniform_real_distribution<double> rand_y;
std::uniform_real_distribution<double> rand_w;
std::uniform_real_distribution<double> rand_h;

struct VisualConfig
{
    VisualConfig(const std::string &&name, const std::string &&mesh_path, std::tuple<double, double, double, double>&& rgba):
    name(name), mesh_path(mesh_path), rgba(rgba) {}

    std::string name;
    std::string mesh_path;
    std::tuple<double, double, double, double> rgba;
    double scale;  // Set by parametre server
};

VisualConfig* type_config[4] = {
    new VisualConfig(std::string("target"),
                    //  "package://visualization/meshes/bugatti.ply",
                    "package://visualization/meshes/untitled.stl",
                     std::make_tuple(0.0, 0.0, 1.0, 1.0)),
    new VisualConfig(std::string("base_station"),
                     "package://visualization/meshes/SSN.dae",
                     std::make_tuple(1.0, 1.0, 1.0, 1.0)),
    new VisualConfig(std::string("uav"),
                     "package://visualization/meshes/hummingbird.mesh",
                     std::make_tuple(0.0, 1.0, 0.0, 1.0)),
    new VisualConfig(std::string("solution"),
                     "package://visualization/meshes/hummingbird.mesh",
                     std::make_tuple(1.0, 0.0, 0.0, 1.0))};

ros::Publisher entityMarkerPub;

visualization_msgs::Marker curr_marker;  // Predefined variable

visualization_msgs::MarkerArray uav_marker_array;
visualization_msgs::MarkerArray target_marker_array;
visualization_msgs::MarkerArray bs_marker_array;
visualization_msgs::MarkerArray solution_marker_array;

void updateEntityMarker(const std::map<unsigned, Eigen::Vector3d> &poses, visualization_msgs::MarkerArray &container, int type)
{   
    // ROS_INFO("[entities_visualization] Entity drawer called for %s", type_config[type]->name.c_str());
    curr_marker.ns = type_config[type]->name; // ns together with id form a unique identifier

    /* Marker drawing configuration */
    if (type_config[type]->mesh_path.size() == 0) {
        curr_marker.type = visualization_msgs::Marker::SPHERE;
        curr_marker.mesh_resource = "";
    } else {
        curr_marker.type = visualization_msgs::Marker::MESH_RESOURCE;
        curr_marker.mesh_resource = type_config[type]->mesh_path;
    }
    std::tie(curr_marker.color.r,
             curr_marker.color.g,
             curr_marker.color.b,
             curr_marker.color.a) = type_config[type]->rgba;
    curr_marker.action = visualization_msgs::Marker::ADD;
    curr_marker.scale.x =
    curr_marker.scale.y =
    curr_marker.scale.z = type_config[type]->scale;

    container.markers.clear();
    unsigned id = 0;
    for (auto &[entity_id, entity_pose] : poses)
    {
        curr_marker.id = id++;
        curr_marker.pose.position.x = entity_pose(0);
        curr_marker.pose.position.y = entity_pose(1);
        if (type == BASE_STATION) curr_marker.pose.position.z = 0.0;
        else curr_marker.pose.position.z = entity_pose(2);
        container.markers.push_back(curr_marker);
    }
}

void updateEntityPoseCallback(const message_files::PoseStampedArrayConstPtr &poses, std::map<unsigned, Eigen::Vector3d> &container, int type)
{
    container.clear();
    for (auto &pose : poses->poses)
    {
        container[pose.header.seq] = Eigen::Vector3d(pose.pose.position.x,
                                                     pose.pose.position.y,
                                                     pose.pose.position.z);
    }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "entities_visualization");
    ros::NodeHandle n("~");

    n.param("radius_comm", QOS_THRESHOLD, 5.0);
    ROS_INFO("[visualization] Communication range radius set to %f", QOS_THRESHOLD);

    LosChecker los_checker;
    los_checker.init(n);
    los_checker.grid_map_interface()->occupy_threshold = 1;
    isVisible = [&](const Eigen::Vector3d & pt_1, const Eigen::Vector3d & pt_2) {
        // Call visibility_graph/los_checker to check visibility
        if ((pt_1 - pt_2).norm() > QOS_THRESHOLD) return false;
        return los_checker.checkLineOfSight(pt_1, pt_2);
    };

    // TODO: What if change to MarkerArray
    entityMarkerPub = n.advertise<visualization_msgs::MarkerArray>("entities", 10, false);
    pub_edge = n.advertise<visualization_msgs::MarkerArray>("edge", 10, false);

    ros::Subscriber sub_tree_array = n.subscribe("/algorithm/tree", 1, storeNeighbourhoodCallback);   

    ros::Subscriber sub_target = n.subscribe<message_files::PoseStampedArray>("/target_pos", 10, boost::bind(updateEntityPoseCallback, _1, boost::ref(target_poses), TARGET));
    ros::Subscriber sub_bs = n.subscribe<message_files::PoseStampedArray>("/bs_pos", 10, boost::bind(updateEntityPoseCallback, _1, boost::ref(bs_poses), BASE_STATION));
    ros::Subscriber sub_uav = n.subscribe<message_files::PoseStampedArray>("/uav_pos", 10, boost::bind(updateEntityPoseCallback, _1, boost::ref(uav_poses), UAV));
    ros::Subscriber sub_solution = n.subscribe<message_files::PoseStampedArray>("/optimizer/solution", 10, boost::bind(updateEntityPoseCallback, _1, boost::ref(solution_poses), SOLUTION));

    curr_marker.header.frame_id = std::string("/world");
    curr_marker.pose.position.x = 0;
    curr_marker.pose.position.y = 0;
    curr_marker.pose.position.z = 0;
    curr_marker.pose.orientation.w = 1;
    curr_marker.pose.orientation.x = 0;
    curr_marker.pose.orientation.y = 0;
    curr_marker.pose.orientation.z = 0;

    type_config[TARGET]->scale = n.param("target_size", 0.2);
    type_config[BASE_STATION]->scale = n.param("bs_size", 3.0);
    type_config[UAV]->scale = n.param("uav_size", 0.6);
    type_config[SOLUTION]->scale = n.param("uav_size", 0.6);

    edge_list.header.frame_id = std::string("/world");
    edge_list.header.stamp = ros::Time::now();
    edge_list.ns = std::string("edge");  // type-specified later
    edge_list.type = visualization_msgs::Marker::LINE_LIST;
    edge_list.action = visualization_msgs::Marker::ADD;
    edge_list.pose.position.x = 0;
    edge_list.pose.position.y = 0;
    edge_list.pose.position.z = 0;
    edge_list.pose.orientation.w = 1;
    edge_list.pose.orientation.x = 0;
    edge_list.pose.orientation.y = 0;
    edge_list.pose.orientation.z = 0;
    edge_list.scale.x = n.param("edge_size", 0.2);
    edge_list.scale.y = 0;
    edge_list.scale.z = 0;
    edge_list.color.r = 0.0;
    edge_list.color.g = 1.0;
    edge_list.color.b = 0.0;
    edge_list.color.a = n.param("edge_a", 0.8);
    weak_edge_a = n.param("weak_edge_a", 0.2);

    while (ros::ok()) {
        ros::spinOnce();

        // updateEntityMarker(target_poses, target_marker_array, TARGET); entityMarkerPub.publish(target_marker_array);
        updateEntityMarker(bs_poses, bs_marker_array, BASE_STATION); entityMarkerPub.publish(bs_marker_array);
        // updateEntityMarker(uav_poses, uav_marker_array, UAV); entityMarkerPub.publish(uav_marker_array);
        updateEntityMarker(solution_poses, solution_marker_array, SOLUTION); entityMarkerPub.publish(solution_marker_array);

        generateNetworkMarker();
        pub_edge.publish(edge_marker_array);
    }

    return 0;
}