#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/conditional_removal.h>
#include <iostream>

#include <ros/console.h>
#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/PointCloud2.h>

#include <Eigen/Geometry>

int main(int argc, char ** argv) {
    ros::init(argc, argv, "test_load_pcd");
    ros::NodeHandle nh("~");

    ros::Publisher real_map_pub = nh.advertise<sensor_msgs::PointCloud2>("/real_map", 1);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    sensor_msgs::PointCloud2 msg;
    std::string map_path = ros::package::getPath(ROS_PACKAGE_NAME) + "/map/filtered_street.pcd";
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(map_path, *cloud) == -1) {
        PCL_ERROR("Couldn't read file .pcd\n");
        return(-1);
    }

    Eigen::Affine3f transformation = Eigen::Affine3f::Identity();
	transformation.translation() << nh.param("x_translate", 0.0),
                                    nh.param("y_translate", 0.0),
                                    nh.param("z_translate", 0.0);
    std::cout << cloud->sensor_origin_ << std::endl;
    transformation.scale(nh.param("scale", 0.5));  // FIXME: How to assign origin to the PCL
    // Eigen::Matrix3f m;
    // m = Eigen::AngleAxisf(nh.param("x_rotate", 0.0), Eigen::Vector3f::UnitZ())
    //   * Eigen::AngleAxisf(nh.param("y_rotate", 0.0), Eigen::Vector3f::UnitY())
    //   * Eigen::AngleAxisf(nh.param("z_rotate", 0.0), Eigen::Vector3f::UnitZ());
    // transformation.rotate(m);
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::transformPointCloud(*cloud, *transformed, transformation);

    // pcl::ConditionalRemoval<pcl::PointXYZ> conditional_remove;
    // pcl::ConditionAnd<pcl::PointXYZ>::Ptr range_cloud(new pcl::ConditionAnd<pcl::PointXYZ> ());
    // range_cloud->addComparison(pcl::FieldComparison<pcl::PointXYZ>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::GT, 0.0)));
    // range_cloud->addComparison(pcl::FieldComparison<pcl::PointXYZ>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZ>("x", pcl::ComparisonOps::GT, -70.0)));
    // conditional_remove.setCondition(range_cloud);
    // conditional_remove.setInputCloud(transformed);
    // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>());
    // conditional_remove.filter(*cloud_filtered);
    // pcl::io::savePCDFile(ros::package::getPath(ROS_PACKAGE_NAME) + "/map/filtered_global_map.pcd", *cloud_filtered);

    pcl::toROSMsg(*transformed, msg);
    msg.header.frame_id = "world";

    ros::Rate loop_rate(1);
    while (ros::ok()) {
        real_map_pub.publish(msg);
        // ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}