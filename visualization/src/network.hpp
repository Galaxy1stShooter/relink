#include <iostream>
#include <fstream>
#include <string.h>
#include <Eigen/Eigen>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <nav_msgs/Odometry.h>

#include "colormap/colormap.h"

#include "message_files/PoseStampedArray.h"
#include "message_files/SteinerTreeArray.h"
#include "message_files/SteinerTreeNode.h"

#include "visibility_graph/los_checker.hpp"

// #define UAV_UAV 0
// #define UAV_TARGET 1
// #define UAV_BS 2
// #define TARGET_BS 3

visualization_msgs::MarkerArray edge_marker_array;  // Different types of edge separated by namespace
visualization_msgs::Marker edge_list;  // Pre-defined variable of LINE_LIST
ros::Publisher pub_edge;

std::map<unsigned, Eigen::Vector3d> uav_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> target_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> bs_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> solution_poses;  // key: id of entity, separate by type
int uav_num;
double QOS_THRESHOLD = 5.0;
std::function<bool(const Eigen::Vector3d & pt_1, const Eigen::Vector3d & pt_2)> isVisible;

double attenuation(double d) {

    return std::pow(d / QOS_THRESHOLD, 2);

}

std::map<unsigned, std::set<std::string>> uav_neighbours;
void storeNeighbourhoodCallback(const message_files::SteinerTreeArrayConstPtr& msg) {
    uav_neighbours.clear();
    for (auto& treeEdge : msg->entity_neighbours) {
        if (treeEdge.name_id[0] != 'u') continue;
        uav_neighbours[treeEdge.header.seq].insert(treeEdge.neighbour_type_id.begin(), treeEdge.neighbour_type_id.end());
    }
    uav_num = uav_neighbours.size();
}

void addEdge(Eigen::Vector3d& p1, Eigen::Vector3d& p2) {
    geometry_msgs::Point p;
    p.x = p1(0); p.y = p1(1); p.z = p1(2);
    edge_list.points.push_back(p);
    p.x = p2(0); p.y = p2(1); p.z = p2(2);
    edge_list.points.push_back(p);

    bool visible = isVisible(p1, p2);  // Check both distance (in entities_visualization) and visibility(in los_checker)

    std_msgs::ColorRGBA color;
    if (visible) {
        colormap::IDL::BlueWhiteLinear colormap;
        colormap::Color c = colormap.getColor(attenuation((p1 - p2).norm()));
        color.r = c.r;
        color.g = c.g;
        color.b = c.b;
        color.a = c.a;
    } else if ((p1 - p2).norm() < QOS_THRESHOLD) {
        // If opponent entity in range but blocked by obstacle, draw red line
        color.r = 0.8;
        color.g = 0.0;
        color.b = 0.0;
        color.a = 0.5;
    }
    edge_list.colors.push_back(color);  // color of line list is vertex-based
    edge_list.colors.push_back(color);

}

double weak_edge_a = 0.2;
void addWeakEdge(Eigen::Vector3d& p1, Eigen::Vector3d& p2) {
    if (!isVisible(p1, p2)) return;
    geometry_msgs::Point p;
    p.x = p1(0); p.y = p1(1); p.z = p1(2);
    edge_list.points.push_back(p);
    p.x = p2(0); p.y = p2(1); p.z = p2(2);
    edge_list.points.push_back(p);

    std_msgs::ColorRGBA color;
    color.r = 0.0;
    color.g = 0.0;
    color.b = 0.0;
    color.a = weak_edge_a;
    edge_list.colors.push_back(color);  // color of line list is vertex-based
    edge_list.colors.push_back(color);
}

void generateNetworkMarker() {
    edge_marker_array.markers.clear();
    
    // UAV-UAV communication
    edge_list.ns = "uav_uav_edge"; edge_list.points.clear(); edge_list.colors.clear();
    for (auto& [uav_id_1, pose_1] : uav_poses) {
        for (auto& [uav_id_2, pose_2] : uav_poses) {
            if (uav_id_1 == uav_id_2) continue;
            // Special treatment of non-neighbour "neighbours"
            if (!uav_neighbours[uav_id_1].count("uav_" + std::to_string(uav_id_2))) addWeakEdge(pose_1, pose_2);
            else addEdge(pose_1, pose_2);
        }
    }
    edge_marker_array.markers.push_back(edge_list);

    // UAV-target communication
    edge_list.ns = "uav_target_edge"; edge_list.points.clear(); edge_list.colors.clear();
    for (auto& [uav_id, uav_pose] : uav_poses) {
        for (auto& [target_id, target_pose] : target_poses) {
            // Special treatment of non-neighbour "neighbours"
            if (!uav_neighbours[uav_id].count("target_" + std::to_string(target_id))) addWeakEdge(uav_pose, target_pose);
            else addEdge(uav_pose, target_pose);
        }
    }
    edge_marker_array.markers.push_back(edge_list);

    // UAV_BS
    edge_list.ns = "uav_bs_edge"; edge_list.points.clear(); edge_list.colors.clear();
    for (auto& [uav_id, uav_pose] : uav_poses) {
        for (auto& [bs_id, bs_pose] : bs_poses) {
            // Special treatment of non-neighbour "neighbours"
            if (!uav_neighbours[uav_id].count("bs_" + std::to_string(bs_id))) addWeakEdge(uav_pose, bs_pose);
            else addEdge(uav_pose, bs_pose);
        }
    }
    edge_marker_array.markers.push_back(edge_list);

    // TARGET_BS
    edge_list.ns = "target_bs_edge"; edge_list.points.clear(); edge_list.colors.clear();
    for (auto& [bs_id, bs_pose] : bs_poses) {
        for (auto& [target_id, target_pose] : target_poses) {
            addEdge(bs_pose, target_pose);
        }
    }
    edge_marker_array.markers.push_back(edge_list);

    // TARGET_TARGET
    edge_list.ns = "target_target_edge"; edge_list.points.clear(); edge_list.colors.clear();
    for (auto& [target_id_1, target_pose_1] : target_poses) {
        for (auto& [target_id_2, target_pose_2] : target_poses) {
            if (target_id_1 == target_id_2) continue;
            addEdge(target_pose_1, target_pose_2);
        }
    }
    edge_marker_array.markers.push_back(edge_list);
}
