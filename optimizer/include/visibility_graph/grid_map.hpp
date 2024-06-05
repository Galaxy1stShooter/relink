#pragma once

#ifndef _GRID_MAP_H_
#define _GRID_MAP_H_

#include <iostream>
#include <ros/ros.h>
#include <ros/console.h>
#include <Eigen/Eigen>

#include <visualization_msgs/Marker.h>

#include "visibility_graph/node.h"


class GridMap
{

    public:
        void init(double resolution, double x_size, double y_size, double z_size);
        void setObs(const double coord_x, const double coord_y, const double coord_z);

        Eigen::Vector3d coordRounding(const Eigen::Vector3d & coord);
        int adjMatIdxRounding(const int & idx);
        std::vector<Eigen::Vector3i> getNeighbors(const Eigen::Vector3i & index);
        std::vector<Eigen::Vector3i> getNeighborsByRadius(const Eigen::Vector3i & index, const int & radius);
        void calAdjacencyMatrix();
        Eigen::MatrixXd* getAdjacencyMatrix();
        Eigen::Vector3d adjMatIdx2coord(const int & index);
        int coord2adjMatIdx(const Eigen::Vector3d & coord);
        bool checkLineOfSight(const Eigen::Vector3d & pt_1, const Eigen::Vector3d & pt_2);

        visualization_msgs::Marker drawGridMap();

        uint16_t occupy_threshold;  // a grid is occupied only when the PCL point count in that grid excess specific threshold

    private:
        uint16_t * m_data;
        GridNodePtr *** m_grid_nodes;
        Eigen::MatrixXd m_adj_mat;

        int m_GLX_SIZE, m_GLY_SIZE, m_GLZ_SIZE;
        int m_GLXYZ_SIZE, m_GLYZ_SIZE;

        double m_resolution, m_inv_resolution;
        double m_gl_xl, m_gl_yl, m_gl_zl;
        double m_gl_xu, m_gl_yu, m_gl_zu;

        bool isOccupied(const int & idx_x, const int & idx_y, const int & idx_z) const;
        bool isOccupied(const Eigen::Vector3i & index) const;
        bool isFree(const int & idx_x, const int & idx_y, const int & idx_z) const;
        bool isFree(const Eigen::Vector3i & index) const;

        Eigen::Vector3d gridIndex2coord(const Eigen::Vector3i & index);
        Eigen::Vector3i coord2gridIndex(const Eigen::Vector3d & pt);
        // Eigen::Vector3d adjMatIdx2coord(const int & index);
        int transformIdx(const Eigen::Vector3i);
        // std::vector<Eigen::Vector3i> getNeighbors(const Eigen::Vector3i & index);
        // void calAdjacencyMatrix();

        void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove);
        void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove);

};


#endif