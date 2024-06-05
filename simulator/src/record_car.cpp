/* This file generate initial position of targets and UAVs, and control of targets
 * Publish separately to topic "target" and "init_pos"
 * May subscribe data from map generator, for reasonable setup of environment
 * TODO: In the future version, this file is merely the interface for pose
 * */

#include <vector>

#include <ros/ros.h>
#include <ros/package.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include "message_files/PoseStampedArray.h"

#include <Eigen/Eigen>
#include "backward-cpp/backward.hpp"

namespace backward {

    backward::SignalHandling sh;

} // namespace backward

int main(int argc, char **argv) {
    ros::init(argc, argv, "record_car");
    std::vector<nav_msgs::Odometry> odoms;
    std::vector<ros::Publisher> odom_pubs;
    ros::NodeHandle n("~");

    // double x_size = n.param("/map_generator/map_size_x_", 20.0); double x_low = -x_size / 2; double x_high = x_size / 2;
    // double y_size = n.param("/map_generator/map_size_y_", 20.0); double y_low = -y_size / 2; double y_high = y_size / 2;
    // double z_size = n.param("/map_generator/map_size_z_", 10.0); double z_low = 0; double z_high = z_size;
    int target_number = n.param("target_number", 8);
    for (int i = 0; i < target_number; ++i) {
        nav_msgs::Odometry this_pos;
        this_pos.pose.pose.position.x = n.param("/car" + std::to_string(i) + "/init_x", 0.0); 
        this_pos.pose.pose.position.y = n.param("/car" + std::to_string(i) + "/init_y", 0.0);
        this_pos.pose.pose.position.z = n.param("/car" + std::to_string(i) + "/init_z", 0.0);
        odoms.push_back(this_pos);
        odom_pubs.push_back(n.advertise<nav_msgs::Odometry>("/car" + std::to_string(i) + "/visual_slam/odom", 10));
    }

    while (ros::ok()) {
        for (int i = 0; i < target_number; ++i) {
            odom_pubs[i].publish(odoms[i]);
        }
    }

    return 0;
}