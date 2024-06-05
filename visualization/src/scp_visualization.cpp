///* This file visualize star convex subscribed from pkg: optimizer by rviz::Marker
// * */
//
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include "message_files/StarConvexPolytope.h"
#include "message_files/StarConvexPolytopesStamped.h"
#include "messsage_files/entity_identifier.h"
#include <std_msgs/UInt32.h>

#include <eigen3/Eigen/Eigen>
#include "backward-cpp/backward.hpp"

namespace backward {

    backward::SignalHandling sh;

} // namespace backward

visualization_msgs::Marker target_visualization_SCPs;
visualization_msgs::Marker waypoint_visualization_SCPs;
visualization_msgs::Marker uav_visualization_SCPs;
visualization_msgs::Marker solution_visualization_SCPs;
visualization_msgs::Marker bs_visualization_SCPs;

visualization_msgs::MarkerArray entity_SCPs;
visualization_msgs::MarkerArray predict_SCPs;

ros::Publisher scp_visualization_pub;
ros::Publisher predict_scp_visualization_pub;

template<typename Point>
/// The calculation process looks the same for flipping in and out
/// \tparam Point: Point has field x, y, z
/// \param x_: The point waiting for flip of type Point, should has field x, y, z
/// \param ball_radius: The radius of ball flip transformation
/// \param c: The centre of ball flip transformation
/// \return Flipped point of type Point
Point flip(Point x_, double ball_radius, const Eigen::Vector3d &c) {
    Eigen::Vector3d x(x_.x, x_.y, x_.z);
    double coe = 2 * (ball_radius - (x - c).norm());
    x = x + coe * (x - c).normalized();

    x_.x = x(0);
    x_.y = x(1);
    x_.z = x(2);

    return x_;
}

double ball_radius = 0.0;

void init_SCP_mesh(visualization_msgs::Marker& visualization_SCPs, std::string name, unsigned id, const ros::NodeHandle& n) {
    visualization_SCPs.header.frame_id = "/world";
    visualization_SCPs.ns = name;
    visualization_SCPs.id = id;
    visualization_SCPs.type = visualization_msgs::Marker::TRIANGLE_LIST;
    visualization_SCPs.action = visualization_msgs::Marker::ADD;
    visualization_SCPs.scale.x = 1.0;
    visualization_SCPs.scale.y = 1.0;
    visualization_SCPs.scale.z = 1.0;
    visualization_SCPs.pose.orientation.w = 1;
    visualization_SCPs.pose.orientation.x = 0;
    visualization_SCPs.pose.orientation.y = 0;
    visualization_SCPs.pose.orientation.z = 0;
    visualization_SCPs.color.r = 1.0;
    visualization_SCPs.color.g = 1.0;
    visualization_SCPs.color.b = 1.0;
    visualization_SCPs.color.a = n.param("scp_a", 0.6);
    visualization_SCPs.colors.clear();
    visualization_SCPs.points.clear();
}

void drawScpMeshCallback(const message_files::StarConvexPolytopesStampedConstPtr& scp_meshes, const ros::NodeHandle& n) {
    /**
     * Called once received a set of all types of SCPs
     * For testing star convex correctness by visualization
     * Draw them separately by type
    */
    entity_SCPs.markers.clear();
    unsigned count = 0;
    unsigned total = scp_meshes->SCPs.size();
    for (auto& cur_star_convex : scp_meshes->SCPs) {
        ++count;
        Eigen::Vector3d c(cur_star_convex.center.x, cur_star_convex.center.y, cur_star_convex.center.z);

        size_t tool = 0; while (std::isalpha(cur_star_convex.name_id[tool])) ++tool;
        auto type = cur_star_convex.name_id.substr(0, tool);
        visualization_msgs::Marker* typed_SCP = &target_visualization_SCPs;
        if (type == "uav") typed_SCP = &uav_visualization_SCPs;
        else if (type == "bs") typed_SCP = &bs_visualization_SCPs;
        init_SCP_mesh(*typed_SCP, type, count, n);

        // Show convex inside
        std_msgs::ColorRGBA color;
        color.r = 0.1882 + ((double)count / total / 100.0);  // 48 + [0, 2.55]
        color.g = 0.5491 + ((double)count / total / 100.0);  // 140 + [0, 2.55]
        color.b = 0.7765 + ((double)count / total / 100.0);  // 198 + [0, 2.55]
        color.a = n.param("scp_a", 0.6);

        // For each face of current SCP, push back 1 color and 3 points to SCP array
        for (auto &mesh: cur_star_convex.polygons) {
            // color.a = 0.6 + 0.01 * (rand() % 10);
            typed_SCP->colors.push_back(color);

            for (auto &vertex: mesh.points) {
                geometry_msgs::Point p;
                p.x = vertex.x;
                p.y = vertex.y;
                p.z = vertex.z;
                typed_SCP->points.push_back(flip(p, ball_radius, c));
//                typed_SCP.points.push_back(p);
            }
        }
        entity_SCPs.markers.emplace_back(*typed_SCP);
    }
}


void drawPredictScpMeshCallback(const message_files::StarConvexPolytopesStampedConstPtr& scp_meshes, const ros::NodeHandle& n) {
    /**
     * Called once received a set of all types of SCPs
     * For testing star convex correctness by visualization
     * Draw them separately by type
    */
    predict_SCPs.markers.clear();
    unsigned count = 0;
    unsigned total = scp_meshes->SCPs.size();
    for (auto& cur_star_convex : scp_meshes->SCPs) {
        ++count;
        Eigen::Vector3d c(cur_star_convex.center.x, cur_star_convex.center.y, cur_star_convex.center.z);

        size_t tool = 0; while (std::isalpha(cur_star_convex.name_id[tool])) ++tool;
        auto type = cur_star_convex.name_id.substr(0, tool);
        visualization_msgs::Marker* typed_SCP = &target_visualization_SCPs;
        if (type == "solution") typed_SCP = &solution_visualization_SCPs;
        else if (type == "bs") typed_SCP = &bs_visualization_SCPs;
        init_SCP_mesh(*typed_SCP, type, count, n);

        // Show convex inside
        std_msgs::ColorRGBA color;
        color.r = 0.0000 + ((double)count / total / 100.0);  // 0 + [0, 2.55]
        color.g = 0.6549 + ((double)count / total / 100.0);  // 167 + [0, 2.55]
        color.b = 0.2196 + ((double)count / total / 100.0);  // 56 + [0, 2.55]
        color.a = n.param("scp_a", 0.6);

        // For each face of current SCP, push back 1 color and 3 points to SCP array
        for (auto &mesh: cur_star_convex.polygons) {
            // color.a = 0.6 + 0.01 * (rand() % 10);
            typed_SCP->colors.push_back(color);

            for (auto &vertex: mesh.points) {
                geometry_msgs::Point p;
                p.x = vertex.x;
                p.y = vertex.y;
                p.z = vertex.z;
                typed_SCP->points.push_back(flip(p, ball_radius, c));
//                typed_SCP.points.push_back(p);
            }
        }
        predict_SCPs.markers.emplace_back(*typed_SCP);
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "scp_visualization");
    ros::NodeHandle n("~");

    ball_radius = n.param("/algorithm/ball_radius_multiplier", 2.0) * n.param("/algorithm/radius_comm", 5.0);

    ros::Subscriber sub_scp = n.subscribe<message_files::StarConvexPolytopesStamped>("/algorithm/star_convex", 1,
                          boost::bind(&drawScpMeshCallback, _1, boost::ref(n)));

    ros::Subscriber sub_predict_scp = n.subscribe<message_files::StarConvexPolytopesStamped>("/algorithm/predict_star_convex", 1,
                          boost::bind(&drawPredictScpMeshCallback, _1, boost::ref(n)));

    scp_visualization_pub = n.advertise<visualization_msgs::MarkerArray>("scp_meshes", 1, true);
    predict_scp_visualization_pub = n.advertise<visualization_msgs::MarkerArray>("predict_scp_meshes", 1, true);

    while (ros::ok()) {
        ros::spinOnce();
        scp_visualization_pub.publish(entity_SCPs);
        predict_scp_visualization_pub.publish(predict_SCPs);
    }

    return 0;
}
