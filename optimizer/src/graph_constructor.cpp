#include "visibility_graph/graph_constructor.hpp"


void GraphConstructor::init(ros::NodeHandle &nh)
{

    m_nh = nh;

    m_nh.param("graph_constructor/x_size", m_x_size, 5.0);
    m_nh.param("graph_constructor/y_size", m_y_size, 5.0);
    m_nh.param("graph_constructor/z_size", m_z_size, 5.0);
    m_nh.param("grid_map/resolution", m_grid_resolution, 1.0);
    ROS_INFO("[node: graph_constructor] Initialized with:\n"
             "x_size %f\n"
             "y_size %f\n"
             "z_size %f\n"
             "grid_resolution %f\n",
             m_x_size,
             m_y_size,
             m_z_size,
             m_grid_resolution);

    m_map_sub = m_nh.subscribe<sensor_msgs::PointCloud2>("/global_map", 1, &GraphConstructor::rcvMapCallback, this);
    m_click_sub = m_nh.subscribe<sensor_msgs::PointCloud2>("/click_map", 1, &GraphConstructor::clickMapCallback, this);

    m_grid_map_ptr = std::make_shared<GridMap>();
    m_grid_map_ptr->init(m_grid_resolution, m_x_size, m_y_size, m_z_size);

    pub_grid_map = m_nh.advertise<visualization_msgs::Marker>("/algorithm/grid_map", 1, true);

}


void GraphConstructor::rcvMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg)
{
    mapCache = msg;
    if (m_had_map) {
        return;
    }

    ROS_INFO("[graph_constructor]: No map calculated, start construction\n");

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
    Eigen::Vector3i tmp(1, 1, 1);

    m_grid_map_ptr->calAdjacencyMatrix();

    ROS_INFO("[graph_constructor]: Construction successes!\n");

    m_had_map = true;

}


void GraphConstructor::clickMapCallback(const sensor_msgs::PointCloud2ConstPtr &msg) {
    ROS_INFO("[graph_constructor]: Received click map update\n");

    // TODO: Future work: 能否做增量式更新？
    ROS_INFO("[graph_constructor]: Update click obstacle generation\n");

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
    Eigen::Vector3i tmp(1, 1, 1);

    m_grid_map_ptr->calAdjacencyMatrix();

    ROS_INFO("[graph_constructor]: Update successes!\n");
}


Eigen::MatrixXd* GraphConstructor::getAdjacencyMatrix()
{

    return m_had_map ? m_grid_map_ptr->getAdjacencyMatrix() : nullptr;

}

void GraphConstructor::drawGridMap() {
    pub_grid_map.publish(m_grid_map_ptr->drawGridMap());
}


// int main(int argc, char **argv)
// {

//     ros::init(argc, argv, "graph_constructor");
//     GraphConstructor graph_constructor;
//     ros::NodeHandle nh("~");
//     graph_constructor.init(nh);
//     ros::spin();

//     return 0;

// }
