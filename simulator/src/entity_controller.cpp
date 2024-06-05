/* This file generate initial position of targets and UAVs, and control of targets
 * Publish separately to topic "target" and "init_pos"
 * May subscribe data from map generator, for reasonable setup of environment
 * TODO: In the future version, this file is merely the interface for pose
 * */

#include <vector>
#include <iostream>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/surface/convex_hull.h>
#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>

#include "message_files/PoseStampedArray.h"
#include <random>

#include <Eigen/Eigen>
#include <std_msgs/UInt32.h>
#include "backward-cpp/backward.hpp"

namespace backward {

    backward::SignalHandling sh;

} // namespace backward

ros::Subscriber sub_global_map;
std::random_device rd;
std::default_random_engine random_engine(rd());
std::uniform_int_distribution<int> int_uniform;
std::uniform_real_distribution<float> real_uniform(0, 1.0);
double x_low, x_high;
double y_low, y_high;
double z_low, z_high;
double epsilon = 1.0;

struct SceneData {
    std::map<unsigned, Eigen::VectorXf> uavid_pose;
    std::map<unsigned, Eigen::VectorXf> targetid_pose;
    std::map<unsigned, Eigen::VectorXf> targetid_waypoint;
    std::map<unsigned, Eigen::VectorXf> bsid_pose;
    pcl::KdTreeFLANN<pcl::PointXYZ> global_kd_tree;
    pcl::PointCloud<pcl::PointXYZ> global_pcl;

    SceneData() = default;
};

SceneData instance;

message_files::PoseStampedArray generateEntities(const ros::NodeHandle &n, std::map<unsigned, Eigen::VectorXf> &positions, std::string&& name) {
    message_files::PoseStampedArray poses;
    bool random_generate = n.param(name + "_random", false);
    int entity_num = n.param(name + "_num", int_uniform(random_engine) % n.param("max_" + name + "_num", 5));

    for (int i = 0; i < entity_num; ++i) {
        Eigen::Vector3f position;

        int num_retrieved = 0;
        do {
            if (random_generate) {
                position = Eigen::Vector3f(real_uniform(random_engine) * (x_high - x_low) + x_low,
                                           real_uniform(random_engine) * (y_high - y_low) + y_low,
                                           name == "uav" ? 5.0 : 0.0);
                
                pcl::PointXYZ collision_check(position(0), position(1), position(2));
                std::vector<int> whatever;
                std::vector<float> however;
                double epsilon = n.param("/steiner_treegrid_map/resolution", 3.0);
                num_retrieved = instance.global_kd_tree.radiusSearch(collision_check, epsilon, whatever, however);
            } else {
                std::string name_idx = name + std::to_string(i);
                position = Eigen::Vector3f(n.param(name_idx + "_x", float(0.0)),
                                           n.param(name_idx + "_y", float(0.0)),
                                           n.param(name_idx + "_z", float(0.0)));
            }
        } while (num_retrieved > 0);

        positions[i] = position;
        geometry_msgs::PoseStamped pos;
        pos.header.seq = i;
        pos.pose.position.x = position(0);
        pos.pose.position.y = position(1);
        pos.pose.position.z = position(2);
        poses.poses.emplace_back(pos);
    }
    ROS_INFO("[entity_controller] Generated %zu %s", positions.size(), name.c_str());
    return poses;
}

void setInputMapCallback(const sensor_msgs::PointCloud2 &global_map) {
    pcl::fromROSMsg(global_map, instance.global_pcl);
    if (!instance.global_pcl.empty()) instance.global_kd_tree.setInputCloud(instance.global_pcl.makeShared());
}

void episodeControllerCallback(const std_msgs::UInt32ConstPtr& msg, unsigned *episode_seq, bool *reset_episode) {
    if (*episode_seq != msg->data) {
        *episode_seq = msg->data;
        *reset_episode = true;
    }
}

void updateUAVsCallback(const nav_msgs::OdometryConstPtr& msg, unsigned id) {
    Eigen::Vector3f pose(msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
    instance.uavid_pose[id] = pose;
}

void updateTargetsCallback(const nav_msgs::OdometryConstPtr& msg, unsigned id) {
    Eigen::Vector3f pose(msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
    instance.targetid_pose[id] = pose;
}

void updateTargetWaypointsCallback(const nav_msgs::PathConstPtr& msg, unsigned id) {
    // Predict future location of targets (use the waypoint of car)
    Eigen::Vector3f pose(msg->poses[0].pose.position.x, msg->poses[0].pose.position.y, msg->poses[0].pose.position.z);
    instance.targetid_waypoint[id] = pose;
}

message_files::PoseStampedArray translatePoseArray(std::map<unsigned, Eigen::VectorXf>& id_pose) {
    message_files::PoseStampedArray poseArray;
    poseArray.header.stamp = ros::Time::now();
    for (auto& [id, pose] : id_pose) {
        geometry_msgs::PoseStamped curr_pose;
        curr_pose.header.seq = id;
        curr_pose.pose.position.x = pose(0);
        curr_pose.pose.position.y = pose(1);
        curr_pose.pose.position.z = pose(2);
        poseArray.poses.push_back(curr_pose);
    }
    return std::move(poseArray);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "entity_controller");
    ros::NodeHandle n("~");

    double x_size = n.param("/map_generator/map_size_x_", 20.0); x_low = -x_size / 2; x_high = x_size / 2;
    double y_size = n.param("/map_generator/map_size_y_", 20.0); y_low = -y_size / 2; y_high = y_size / 2;
    double z_size = n.param("/map_generator/map_size_z_", 10.0); z_low = 0; z_high = z_size;

    auto* episode_seq = new unsigned(0);
    auto* reset_episode = new bool(false);
    ros::Subscriber sub_episode = n.subscribe<std_msgs::UInt32>("/episode_controller/episode_seq", 1,
                                                                boost::bind(&episodeControllerCallback, _1, episode_seq, reset_episode));
    // ros::Subscriber sub_uav_num = n.subscribe<std_msgs::UInt32>("uav_num", 1, getUavRequirement);
    std::vector<ros::Subscriber> sub_uav;
    for (int i = 0; i < 10; ++i) {
        sub_uav.push_back(n.subscribe<nav_msgs::Odometry>("/uav" + std::to_string(i) + "/visual_slam/odom", 1, boost::bind(updateUAVsCallback, _1, i)));
    }

    size_t target_num = n.param("target_number", 8);
    std::vector<ros::Subscriber> sub_target_pos;
    for (size_t i = 0; i < target_num; ++i) {
        sub_target_pos.push_back(n.subscribe<nav_msgs::Odometry>("/car" + std::to_string(i) + "/visual_slam/odom", 1, boost::bind(updateTargetsCallback, _1, i)));
    }

    std::vector<ros::Subscriber> sub_target_waypoint;
    for (size_t i = 0; i < target_num; ++i) {
        sub_target_waypoint.push_back(n.subscribe<nav_msgs::Path>("/car" + std::to_string(i) + "/waypoint_generator/waypoints", 1, boost::bind(updateTargetWaypointsCallback, _1, i)));
    }

    sub_global_map = n.subscribe("/global_map", 1, setInputMapCallback);

    ros::Publisher target_pub = n.advertise<message_files::PoseStampedArray>("target_pos", 1, true);
    ros::Publisher targetwp_pub = n.advertise<message_files::PoseStampedArray>("target_waypoint", 1, true);
    ros::Publisher uav_pub = n.advertise<message_files::PoseStampedArray>("uav_pos", 1, true);
    ros::Publisher bs_pub = n.advertise<message_files::PoseStampedArray>("bs_pos", 1, true);
    message_files::PoseStampedArray target_pose_array;
    message_files::PoseStampedArray target_waypoint_array;
    message_files::PoseStampedArray bs_pose_array;
    message_files::PoseStampedArray uav_pose_array;

//    ROS_INFO("[entity_controller] checking cloud map\n");
    while (instance.global_pcl.empty()) {
        ros::spinOnce();
    }

    while (ros::ok()) {
        // TODO: Initialize base stations, UAVs, targets in the same module
        // TODO: Make the position of base station locate at its top rather than its foot
        bs_pose_array = generateEntities(n, instance.bsid_pose, std::string("bs"));
        while (!*reset_episode) {
            ros::spinOnce();
            bs_pub.publish(bs_pose_array);

            uav_pose_array = translatePoseArray(instance.uavid_pose);
            uav_pub.publish(uav_pose_array);

            target_pose_array = translatePoseArray(instance.targetid_pose);
            if (target_num == target_pose_array.poses.size()) target_pub.publish(target_pose_array);
            // else ROS_INFO("[entity_controller] Target poses not complete");

            target_waypoint_array = translatePoseArray(instance.targetid_waypoint);
            if (target_num == target_waypoint_array.poses.size()) targetwp_pub.publish(target_waypoint_array);
            // else ROS_INFO("[entity_controller] Target waypoints not complete");
        }
        *reset_episode = false;
        // instance.uav_pts.clear();
        instance.uavid_pose.clear();
        instance.targetid_pose.clear();
        instance.targetid_waypoint.clear();
        instance.bsid_pose.clear();
        instance.global_pcl.clear();  
    }

    // std::ofstream writeFile;
    // // TODO: more formatted file name
    // writeFile.open(ros::package::getPath("map_generator") + "/map/examples/entities");
    // for (auto [x, y] : curr_random_obstacle_locs) {
    //     writeFile << x << " " << y << endl;    
    // }
    // writeFile.close();

    return 0;
}