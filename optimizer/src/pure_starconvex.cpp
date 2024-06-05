#include <iostream>
#include <vector>
#include <cmath>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/surface/convex_hull.h>
#include <pcl/filters/voxel_grid.h>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseArray.h>
#include "visualization_msgs/Marker.h"
#include "message_files/StarConvexPolytope.h"
#include "message_files/StarConvexPolytopesStamped.h"

#include <eigen3/Eigen/Eigen>

template <typename Point>
/// The calculation process looks the same for flipping in and out
/// \tparam Point: Point has field x, y, z
/// \param x_: The point waiting for flip of type Point, should has field x, y, z
/// \param ball_radius: The sense_radius of ball flip transformation
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
    pcl::KdTreeFLANN<pcl::PointXYZ> global_kd_tree;
    pcl::PointCloud<pcl::PointXYZ> global_pcl;

    float sense_radius;
    double ball_radius;
    double voxel_size;
    int num_augment;

    StarConvexGenerator() = default;

    void init(const ros::NodeHandle &n)
    {
        sense_radius = n.param("sense_radius", 5.0);
        ball_radius = sense_radius * n.param("ball_radius_multiplier", 2.0);
        voxel_size = n.param("down_sampling_size", 0.3);
        num_augment = (int)(pow(sense_radius, 2) * n.param("augment_multiplier", 100));
    }

    /// \param centre_pos : The centre position that expected to generate scp from
    /// \return message_files::StarConvexPolytope : Message consist of header, centre point position and scp (by triangle meshes)
    message_files::StarConvexPolytope getSingleStarConvex(const Eigen::Vector3d &centre_pos)
    {
        // Send for star convex optimization
        message_files::StarConvexPolytope star_convex;
        // star_convex.header.frame_id = "world";
        star_convex.header.stamp = ros::Time::now();
        star_convex.center.x = centre_pos(0);
        star_convex.center.y = centre_pos(1);
        star_convex.center.z = centre_pos(2);

        // Retrieve points based on communication range query
        pcl::PointXYZ target_pose(centre_pos(0), centre_pos(1), centre_pos(2));
        Eigen::Vector3d c(centre_pos(0), centre_pos(1), centre_pos(2)); // for flipping calculation

        // retrieve the local point cloud flipped_points surround the point ci by the range query
        pcl::PointCloud<pcl::PointXYZ> flipped_points;
        std::vector<int> idx_in_pcl; // Index in global_kd_tree of retrieved points
        std::vector<float> sqDist;   // The resultant squared distances to the neighboring points
        // Retrieve all points in given sense_radius, no upper bound
        if (!global_pcl.empty())
            global_kd_tree.radiusSearch(target_pose, sense_radius, idx_in_pcl, sqDist);
        pcl::PointCloud<pcl::PointXYZ> retrieved_points;
        std::for_each(idx_in_pcl.begin(), idx_in_pcl.end(), [&](int idx)
                      { retrieved_points.push_back(global_pcl[idx]); });

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
            pcl::PointXYZ x_(sense_radius * cos(theta) * sin(phi) + target_pose.x,
                             sense_radius * sin(theta) * sin(phi) + target_pose.y,
                             sense_radius * cos(phi) + target_pose.z);
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

        return star_convex;
    }

    inline void init_SCP_mesh(visualization_msgs::Marker &visualization_SCP)
    {
        visualization_SCP.header.frame_id = "/map";
        visualization_SCP.type = visualization_msgs::Marker::TRIANGLE_LIST;
        visualization_SCP.action = visualization_msgs::Marker::ADD;
        visualization_SCP.scale.x = 1.0;
        visualization_SCP.scale.y = 1.0;
        visualization_SCP.scale.z = 1.0;
        visualization_SCP.pose.orientation.w = 1;
        visualization_SCP.pose.orientation.x = 0;
        visualization_SCP.pose.orientation.y = 0;
        visualization_SCP.pose.orientation.z = 0;
        visualization_SCP.color.r = 1.0;
        visualization_SCP.color.g = 1.0;
        visualization_SCP.color.b = 1.0;
        visualization_SCP.color.a = 0.6;
        visualization_SCP.colors.clear();
        visualization_SCP.points.clear();
    }

    visualization_msgs::Marker drawScpMesh(const message_files::StarConvexPolytope &scp_meshes)
    {
        /**
         * Called once received a set of all types of SCPs
         * For testing star convex correctness by visualization
         * Draw them separately by type
         */

        Eigen::Vector3d c(scp_meshes.center.x, scp_meshes.center.y, scp_meshes.center.z);

        size_t tool = 0;
        while (std::isalpha(scp_meshes.name_id[tool]))
            ++tool;
        auto type = scp_meshes.name_id.substr(0, tool);
        visualization_msgs::Marker SCP;
        init_SCP_mesh(SCP);

        // Show convex inside
        std_msgs::ColorRGBA color;
        color.r = 0.1882; // 48
        color.g = 0.5491; // 140
        color.b = 0.7765; // 198
        color.a = 0.6;

        // For each face of current SCP, push back 1 color and 3 points to SCP array
        for (auto &mesh : scp_meshes.polygons)
        {
            // color.a = 0.6 + 0.01 * (rand() % 10);
            SCP.colors.push_back(color);

            for (auto &vertex : mesh.points)
            {
                geometry_msgs::Point p;
                p.x = vertex.x;
                p.y = vertex.y;
                p.z = vertex.z;
                SCP.points.push_back(flip(p, ball_radius, c));
                //                typed_SCP.points.push_back(p);
            }
        }

        return SCP;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pure_starconvex");
    ros::NodeHandle n("~");

    pcl::PointCloud<pcl::PointXYZ>::Ptr orig_cloud_pcl(new pcl::PointCloud<pcl::PointXYZ>);
    std::string pcd_path = ;
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(pcd_path, *orig_cloud_pcl) == -1)
    {
        PCL_ERROR("Couldn't read file: %s \n", pcd_path.c_str());
        return (-1);
    }
    ROS_INFO("Start star convex generation");
    StarConvexGenerator scp_generator;
    scp_generator.init(n);
    scp_generator.global_pcl = *orig_cloud_pcl;
    scp_generator.global_kd_tree.setInputCloud(orig_cloud_pcl);
    auto SCP = scp_generator.getSingleStarConvex({1, 0, 0});
    ROS_INFO("Finished star convex generation, start publishing visualization message");
    auto visualize_SCP = scp_generator.drawScpMesh(SCP);
    ros::Publisher visualize = n.advertise<visualization_msgs::Marker>("pure_SCP", 1, true);

    while (ros::ok())
    {
        visualize.publish(visualize_SCP);
    }

    return 0;
}
