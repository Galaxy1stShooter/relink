/* This file calculate star convex for optimization after getting new map/entity poses
 * Publish the star convex in form of list of triangles
 * May subscribe data required for optimization. e.g. targets location
 * */

#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/surface/convex_hull.h>
#include <pcl/filters/voxel_grid.h>

#include <ros/ros.h>
#include <std_msgs/UInt32.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseArray.h>
#include <visualization_msgs/Marker.h>
#include "message_files/StarConvexPolytope.h"
#include "message_files/StarConvexPolytopesStamped.h"
#include "message_files/PoseStampedArray.h"
#include "message_files/Optimize.h"
#include "message_files/SteinerTreeNode.h"
#include "message_files/Assign.h"

#include <eigen3/Eigen/Eigen>

#include "messsage_files/entity_identifier.h"

ros::Publisher pub_entity_SCPs;
ros::Publisher pub_predict_SCPs;

template <typename Point>
/// The calculation process looks the same for flipping in and out
/// \tparam Point: Point has field x, y, z
/// \param x_: The point waiting for flip of type Point, should has field x, y, z
/// \param ball_radius: The radius of ball flip transformation
/// \param c: The centre of ball flip transformation
/// \return Flipped point of type Point
Point flip(Point x_, double ball_radius, const Eigen::Vector3d &c)
{
    Eigen::Vector3d x(x_.x, x_.y, x_.z);
    double coe = 2 * (ball_radius - (x - c).norm());
    x = x + coe * (x - c).normalized();

    x_.x = x(0);
    x_.y = x(1);
    x_.z = x(2);

    return x_;
}

class StarConvexGenerator
{
public:
    std::map<unsigned, Eigen::Vector3d> uav_poses;
    std::map<unsigned, Eigen::Vector3d> solution_poses;
    std::map<unsigned, Eigen::Vector3d> target_poses;
    std::map<unsigned, Eigen::Vector3d> bs_poses;
    pcl::KdTreeFLANN<pcl::PointXYZ> global_kd_tree;
    pcl::PointCloud<pcl::PointXYZ> global_pcl;
    std::map<std::string, size_t> nameid_SCP_index;  // Help optimizer retrieve required SCPs by name_id
    message_files::StarConvexPolytopesStamped entity_SCPs;  // SCP at real position, for visualization
    message_files::StarConvexPolytopesStamped predict_SCPs;  // SCP at solution/predict position, for optimization
    float radius_comm;
    double ball_radius;
    double voxel_size;
    int num_augment;

    StarConvexGenerator() = default;

    void init(const ros::NodeHandle &n) {
        radius_comm = n.param("radius_comm", 5.0);
        ball_radius = radius_comm * n.param("ball_radius_multiplier", 2.0);
        voxel_size = n.param("down_sampling_size", 0.3);
        num_augment = (int)(pow(radius_comm, 2) * n.param("augment_multiplier", 100));
    }

    void reset()
    {
        uav_poses.clear();
        solution_poses.clear();
        target_poses.clear();
        bs_poses.clear();
        global_pcl.clear();
        nameid_SCP_index.clear();
        entity_SCPs.SCPs.clear();
        predict_SCPs.SCPs.clear();
    }

    ///
    /// \param n : ros::NodeHandle that provide star-convex-related parameters
    /// \param entity : The position of current entity that expected to generate scp from
    /// \param seq : Marking ID of current star convex, irrelevant to entity type
    /// \return message_files::StarConvexPolytope : Message consist of header, centre point position and scp (by triangle meshes)
    message_files::StarConvexPolytope getSingleStarConvex(const Eigen::Vector3d &entity, std::string& name_id)
    {
        // generate bigger star convex
        float radius = radius_comm + 0.0;
        // Send for star convex optimization
        message_files::StarConvexPolytope star_convex;
        star_convex.header.frame_id = "world";
        star_convex.header.stamp = ros::Time::now();
        star_convex.name_id = name_id;
        star_convex.center.x = entity(0);
        star_convex.center.y = entity(1);
        star_convex.center.z = entity(2);

        // Retrieve points based on communication range query
        pcl::PointXYZ target_pose(entity(0), entity(1), entity(2));
        Eigen::Vector3d c(entity(0), entity(1), entity(2)); // for flipping calculation

        // retrieve the local point cloud flipped_points surround the point ci by the range query
        pcl::PointCloud<pcl::PointXYZ> flipped_points;
        std::vector<int> idx_in_pcl; // Index in global_kd_tree of retrieved points
        std::vector<float> sqDist;   // The resultant squared distances to the neighboring points
        // Retrieve all points in given radius, no upper bound
        if (!global_pcl.empty()) global_kd_tree.radiusSearch(target_pose, radius, idx_in_pcl, sqDist);
        pcl::PointCloud<pcl::PointXYZ> retrieved_points;
        std::for_each(idx_in_pcl.begin(), idx_in_pcl.end(), [&](int idx) { retrieved_points.push_back(global_pcl[idx]); });

        // Down-sampling
        pcl::VoxelGrid<pcl::PointXYZ> voxel_handler;
        pcl::PointCloud<pcl::PointXYZ> raw_pcl(retrieved_points);
        voxel_handler.setInputCloud(raw_pcl.makeShared());
        voxel_handler.setLeafSize(voxel_size, voxel_size, voxel_size);
        voxel_handler.filter(retrieved_points);

        // ROS_INFO("Number of retrieved points: %zu\n", retrieved_points.size());
        std::for_each(retrieved_points.begin(), retrieved_points.end(), [&](pcl::PointXYZ &pt)
                      {
            // Flip out retrieved obstacle points
            flipped_points.push_back(flip(pt, ball_radius, c)); });

        // Plus augment points evenly retrieved from sphere boundary
        for (int augment_idx = 1; augment_idx <= num_augment; ++augment_idx)
        {
            double phi = acos(-1.0 + (2.0 * augment_idx - 1.0) / num_augment);
            double theta = sqrt(num_augment * M_PI) * phi;
            pcl::PointXYZ x_(radius * cos(theta) * sin(phi) + target_pose.x,
                             radius * sin(theta) * sin(phi) + target_pose.y,
                             radius * cos(phi) + target_pose.z);
            flipped_points.push_back(flip(x_, ball_radius, c));
        }

        // ROS_INFO("Number of retrieved and augmented points: %zu\n", flipped_points.size());
        //        flipped_points.push_back(target_pose);

        // Calculate convex hull of flipped points
        pcl::ConvexHull<pcl::PointXYZ> hull;
        pcl::PointCloud<pcl::PointXYZ> hull_points;
        std::vector<pcl::Vertices> hull_polygons;
        hull.setInputCloud(flipped_points.makeShared());
        hull.reconstruct(hull_points, hull_polygons);

        // ROS_INFO("Number of meshes: %zu\n", hull_polygons.size());

        for (auto &face : hull_polygons)
        {
            // Each face a triangle
            geometry_msgs::Polygon cur_triangle;
            // Discard current triangle if all vertices of it are underground
            if (std::all_of(face.vertices.begin(), face.vertices.end(), [&](unsigned vertex_id)
                            { return hull_points[vertex_id].z <= 0; }))
                continue;

            for (auto vertex_idx : face.vertices)
            {
                auto vertex = hull_points[vertex_idx];
                // auto debug_flip = flip(vertex, ball_radius, c);
                // printf("%f, %f, %f", debug_flip.x, debug_flip.y, debug_flip.z);
                // For optimization, should pass flipped polygons
                geometry_msgs::Point32 p_;
                p_.x = vertex.x;
                p_.y = vertex.y;
                p_.z = vertex.z;
                cur_triangle.points.push_back(p_);
            }
            star_convex.polygons.push_back(cur_triangle);
        }

        return std::move(star_convex);
    }

    void generateStarConvex()
    {
        // Generate SCP for all real position, solution/predict position
        // TODO: How to implement ID list elegantly
        predict_SCPs.SCPs.clear(); entity_SCPs.SCPs.clear();
        predict_SCPs.header.frame_id = entity_SCPs.header.frame_id = "world";
        predict_SCPs.header.stamp = entity_SCPs.header.stamp = ros::Time::now();
        size_t index = 0;  // Mark index of SCP in predict_SCPs
        // Calculate and publish star convex of each entity, published msgs MARK by Header.seq
        message_files::StarConvexPolytope curr_SCP;

        for (auto &[id, uav_pose] : uav_poses)
        {
            std::string name_id = "uav_" + std::to_string(id);
            curr_SCP = getSingleStarConvex(uav_pose, name_id);
            entity_SCPs.SCPs.push_back(curr_SCP);
        }

        for (auto &[id, solution_pose] : solution_poses)
        {
            std::string name_id = "solution_" + std::to_string(id);
            nameid_SCP_index[name_id] = index++;

            curr_SCP = getSingleStarConvex(solution_pose, name_id);
            predict_SCPs.SCPs.push_back(curr_SCP);
        }

        for (auto &[id, target_pose] : target_poses)
        {
            std::string name_id = "target_" + std::to_string(id);
            nameid_SCP_index[name_id] = index++;

            curr_SCP = getSingleStarConvex(target_pose, name_id);
            entity_SCPs.SCPs.push_back(curr_SCP);
            predict_SCPs.SCPs.push_back(curr_SCP);
        }

        for (auto &[id, bs_pose] : bs_poses)
        {
            std::string name_id = "bs_" + std::to_string(id);
            nameid_SCP_index[name_id] = index++;

            curr_SCP = getSingleStarConvex(bs_pose, name_id);
            entity_SCPs.SCPs.push_back(curr_SCP);
            predict_SCPs.SCPs.push_back(curr_SCP);
        }

        pub_entity_SCPs.publish(entity_SCPs);
        pub_predict_SCPs.publish(predict_SCPs);
    }
};
