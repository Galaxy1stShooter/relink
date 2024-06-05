#pragma once

#include <iostream>
#include <ros/ros.h>
#include <Eigen/Eigen>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <visualization_msgs/Marker.h>

#include "sensor_msgs/PointCloud2.h"
#include "visibility_graph/grid_map.hpp"
#include <geometry_msgs/PoseStamped.h>


class GraphConstructor
{

    public:
        void init(ros::NodeHandle &nh);
        Eigen::MatrixXd* getAdjacencyMatrix();
        std::shared_ptr<GridMap> grid_map_interface() const {return this->m_grid_map_ptr;}

        void drawGridMap();
        ros::Publisher pub_grid_map;

    private:
        ros::NodeHandle m_nh;
        ros::Subscriber m_map_sub;
        ros::Subscriber m_click_sub;

        std::shared_ptr<GridMap> m_grid_map_ptr;

        bool m_had_map = false;
        sensor_msgs::PointCloud2ConstPtr mapCache;
        double m_x_size, m_y_size, m_z_size;
        double m_grid_resolution;

        void rcvMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg);

        void clickMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg);

};