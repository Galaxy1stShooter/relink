#include "visibility_graph/los_checker.hpp"

void LosChecker::init(ros::NodeHandle &nh)
{

    m_nh = nh;

    m_nh.param("los_checker/x_size", m_x_size, 5.0);
    m_nh.param("los_checker/y_size", m_y_size, 5.0);
    m_nh.param("los_checker/z_size", m_z_size, 5.0);
    m_nh.param("los_checker/resolution", m_grid_resolution, 1.0);
    ROS_INFO("[node: los_checker] Initialized with:\n"
             "x_size %f\n"
             "y_size %f\n"
             "z_size %f\n"
             "grid_resolution %f\n",
             m_x_size,
             m_y_size,
             m_z_size,
             m_grid_resolution);

    m_map_sub = m_nh.subscribe<sensor_msgs::PointCloud2>("/global_map", 1, &LosChecker::rcvMapCallback, this);
    m_click_sub = m_nh.subscribe<sensor_msgs::PointCloud2>("/click_map", 1, &LosChecker::clickMapCallback, this);

    m_grid_map_ptr = std::make_shared<GridMap>();
    m_grid_map_ptr->init(m_grid_resolution, m_x_size, m_y_size, m_z_size);

    // // for test
    // Eigen::Vector3d tmp(1.05, 3.05, 3.05);
    // std::cout << "Rounding: " << m_grid_map_ptr->coordRounding(tmp) << std::endl;
    // int tmp = 9;
    // std::cout << "Rounding: " << m_grid_map_ptr->adjMatIdxRounding(tmp) << std::endl;

}

bool LosChecker::checkLineOfSight(const Eigen::Vector3d & pt_1, const Eigen::Vector3d & pt_2) {
    return m_grid_map_ptr->checkLineOfSight(pt_1, pt_2);
}


void LosChecker::rcvMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg)
{

    if (m_had_map) return;
    ROS_INFO("[los_checker]: Received global map\n");
    ROS_INFO("[los_checker]: No map calculated, start construction\n");

    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(*msg, cloud);
    int pts_num = cloud.points.size();

    if (pts_num == 0) return;

    pcl::PointXYZ pt;
    for (int idx = 0; idx < pts_num; idx++)
    {
        pt = cloud.points[idx];

        // set obstalces into grid map
        m_grid_map_ptr->setObs(pt.x, pt.y, pt.z);
    }

    ROS_INFO("[los_checker]: Construction successes!\n");

    m_had_map = true;

}

void LosChecker::clickMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg) {
    ROS_INFO("[los_checker]: Received click map update\n");

    // TODO: Future work: 能否做增量式更新？
    ROS_INFO("[los_checker]: Update click obstacle generation\n");

    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(*msg, cloud);

    int pts_num = cloud.points.size();
    if (pts_num == 0) return;

    pcl::PointXYZ pt;
    for (int idx = 0; idx < pts_num; idx++)
    {
        pt = cloud.points[idx];
        m_grid_map_ptr->setObs(pt.x, pt.y, pt.z);
    }

    ROS_INFO("[los_checker]: Update successes!\n");
}
