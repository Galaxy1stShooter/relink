#include "visibility_graph/grid_map.hpp"


/* Function init
operates the initialization of the grid map. */
void GridMap::init(double resolution, double x_size, double y_size, double z_size)
{

    Eigen::Vector3d map_lb, map_ub;
    map_lb << - x_size/2.0, - y_size/2.0,     0.0;
    map_ub << + x_size/2.0, + y_size/2.0,  z_size;
    
    m_gl_xl = map_lb(0);
    m_gl_yl = map_lb(1);
    m_gl_zl = map_lb(2);

    m_gl_xu = map_ub(0);
    m_gl_yu = map_ub(1);
    m_gl_zu = map_ub(2);

    m_resolution = resolution;
    m_inv_resolution = 1.0 / m_resolution;

    m_GLX_SIZE = (int)(x_size * m_inv_resolution);
    m_GLY_SIZE = (int)(y_size * m_inv_resolution);
    m_GLZ_SIZE = (int)(z_size * m_inv_resolution);
    m_GLYZ_SIZE  = m_GLY_SIZE * m_GLZ_SIZE;
    m_GLXYZ_SIZE = m_GLX_SIZE * m_GLYZ_SIZE;

    // Storage the data of grid map that a grid is occupied or not
    m_data = new uint16_t[m_GLXYZ_SIZE];
    memset(m_data, 0, m_GLXYZ_SIZE * sizeof(uint16_t));

    m_grid_nodes = new GridNodePtr ** [m_GLX_SIZE];
    for(int i = 0; i < m_GLX_SIZE; i++)
    {
        m_grid_nodes[i] = new GridNodePtr * [m_GLY_SIZE];
        for(int j = 0; j < m_GLY_SIZE; j++)
        {
            m_grid_nodes[i][j] = new GridNodePtr [m_GLZ_SIZE];
            for(int k = 0; k < m_GLZ_SIZE; k++)
            {
                Eigen::Vector3i tmpIdx(i,j,k);
                Eigen::Vector3d pos = gridIndex2coord(tmpIdx);
                m_grid_nodes[i][j][k] = new GridNode(tmpIdx, pos);
                // m_grid_nodes[i][j][k]->id = count;

                // std::vector<Eigen::Vector3i> tmp_neighbors_idx = getNeighbors(tmpIdx);
            }
        }
    }

}


/* Function setObs
use m_data to count PCL point in each grid
further, a grid is occupied only when the PCL point count excess specific threshold. */
void GridMap::setObs(const double coord_x, const double coord_y, const double coord_z)
{

    if( coord_x <  m_gl_xl || coord_y <  m_gl_yl || coord_z <  m_gl_zl || 
        coord_x >= m_gl_xu || coord_y >= m_gl_yu || coord_z >= m_gl_zu )
        return;

    int idx_x = static_cast<int>( (coord_x - m_gl_xl) * m_inv_resolution);
    int idx_y = static_cast<int>( (coord_y - m_gl_yl) * m_inv_resolution);
    int idx_z = static_cast<int>( (coord_z - m_gl_zl) * m_inv_resolution);      

    // m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] = 1;
    m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] += 1;
}


void GridMap::calAdjacencyMatrix()
{

    m_adj_mat = Eigen::MatrixXd::Zero(m_GLXYZ_SIZE, m_GLXYZ_SIZE);

    int count = 0;
    std::vector<int> occ_arr;
    for(int i = 0; i < m_GLX_SIZE; i++)
    {
        for(int j = 0; j < m_GLY_SIZE; j++)
        {
            for(int k = 0; k < m_GLZ_SIZE; k++)
            {
                Eigen::Vector3i tmpIdx(i,j,k);
                m_adj_mat(count, count) = count;
                if (isOccupied(tmpIdx))
                {
                    occ_arr.push_back(count);
                    count++;

                    continue;
                }

                // std::vector<Eigen::Vector3i> tmp_neighbors_idx = getNeighbors(tmpIdx);  // radius=2
                // std::vector<Eigen::Vector3i> tmp_neighbors_idx = getNeighborsByRadius(tmpIdx, 2);  // Pruning
                std::vector<Eigen::Vector3i> tmp_neighbors_idx = getNeighborsByRadius(tmpIdx, 8);  // DP comparison

                for (auto idx : tmp_neighbors_idx)
                {
                    if (isOccupied(idx)) continue;
                    if( idx(0) <           0 || idx(1) <           0 || idx(2) <         0 || 
                        idx(0) >= m_GLX_SIZE || idx(1) >= m_GLY_SIZE || idx(2) >= m_GLZ_SIZE )
                        continue;

                    int index_1d = idx(0) * m_GLYZ_SIZE + idx(1) * m_GLZ_SIZE + idx(2);
                    m_adj_mat(count, index_1d) = (idx - tmpIdx).cast<double>().norm() * m_resolution;
                }

                count++;
            }
        }
    }

    // slicing zeros row and column
    for (size_t i = occ_arr.size(); i > 0; i--)
    {
        int idx = occ_arr[i - 1];
        removeRow(m_adj_mat, idx);
        removeColumn(m_adj_mat, idx);
    }
//    std::cout << "MATRIX!!!!!!" << std::endl;
//    std::cout << m_adj_mat(1) << std::endl;

}


std::vector<Eigen::Vector3i> GridMap::getNeighbors(const Eigen::Vector3i & index)
{

    std::vector<Eigen::Vector3i> neighbors_idx;
    Eigen::Vector3i tmp_idx = index;

    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);

    tmp_idx(0) -= 1;
    tmp_idx(1) += 1;
    tmp_idx(2) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);

    tmp_idx(0) -= 1;
    tmp_idx(1) += 1;
    tmp_idx(2) -= 2;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(1) -= 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);
    tmp_idx(0) += 1;
    neighbors_idx.push_back(tmp_idx);

    return neighbors_idx;

}


std::vector<Eigen::Vector3i> GridMap::getNeighborsByRadius(const Eigen::Vector3i & index, const int & radius)
{

    std::vector<Eigen::Vector3i> neighbors_idx;
    Eigen::Vector3i tmp_idx = index;

    // tmp_idx(0) -= radius + 1;
    // tmp_idx(1) -= radius + 1;
    // tmp_idx(2) -= radius + 1;

    for (int i = -radius; i < radius + 1; i++)
    {
        tmp_idx(0) = index(0) + i;
        for (int j = -radius; j < radius + 1; j++)
        {
            tmp_idx(1) = index(1) + j;
            for (int k = -radius; k < radius + 1; k++)
            {
                tmp_idx(2) = index(2) + k;
                if (tmp_idx == index) continue;
                if (!checkLineOfSight(gridIndex2coord(index), gridIndex2coord(tmp_idx))) {
                    continue;
                }
                neighbors_idx.push_back(tmp_idx);
            }
        }
    }

    return neighbors_idx;

}


Eigen::Vector3d GridMap::gridIndex2coord(const Eigen::Vector3i & index)
{

    Eigen::Vector3d pt;

    pt(0) = ((double)index(0) + 0.5) * m_resolution + m_gl_xl;
    pt(1) = ((double)index(1) + 0.5) * m_resolution + m_gl_yl;
    pt(2) = ((double)index(2) + 0.5) * m_resolution + m_gl_zl;

    return pt;

}


Eigen::Vector3i GridMap::coord2gridIndex(const Eigen::Vector3d & pt) 
{

    Eigen::Vector3i idx;
    idx <<  std::min(std::max( int( (pt(0) - m_gl_xl) * m_inv_resolution), 0), m_GLX_SIZE - 1),
            std::min(std::max( int( (pt(1) - m_gl_yl) * m_inv_resolution), 0), m_GLY_SIZE - 1),
            std::min(std::max( int( (pt(2) - m_gl_zl) * m_inv_resolution), 0), m_GLZ_SIZE - 1);
  
    return idx;

}


Eigen::Vector3d GridMap::adjMatIdx2coord(const int & index)
{

    Eigen::Vector3i idx;
    idx <<  index / m_GLYZ_SIZE,
            (index % m_GLYZ_SIZE) / m_GLZ_SIZE,
            index % m_GLZ_SIZE;

    return gridIndex2coord(idx);

}


int GridMap::coord2adjMatIdx(const Eigen::Vector3d & coord)
{

    Eigen::Vector3i grid_index = coord2gridIndex(coord);
    if (isOccupied(grid_index)) {
        Eigen::Vector3i nearest_neighbour_index;
        double min_neighbour_distance = INFINITY;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int x_ = grid_index(0) + dx, y_ = grid_index(1) + dy;
                if (x_ < 0 || x_ >= m_GLX_SIZE || y_ < 0 || y_ >= m_GLY_SIZE) continue;
                Eigen::Vector3i neighbour_index(x_, y_, grid_index(2));
                if (!isOccupied(neighbour_index)) {
                    Eigen::Vector3d neighbour_coord = gridIndex2coord(neighbour_index);
                    if ((neighbour_coord - coord).norm() < min_neighbour_distance) {
                        min_neighbour_distance = (neighbour_coord - coord).norm();
                        nearest_neighbour_index = neighbour_index;
                    }
                }
            }
        }
        grid_index = nearest_neighbour_index;
    }
    
    return grid_index(0) * m_GLYZ_SIZE + grid_index(1) * m_GLZ_SIZE + grid_index(2);

}


Eigen::Vector3d GridMap::coordRounding(const Eigen::Vector3d & coord)
{

    return gridIndex2coord(coord2gridIndex(coord));

}


int GridMap::adjMatIdxRounding(const int & idx)
{

    return coord2adjMatIdx(adjMatIdx2coord(idx));

}


inline bool GridMap::isOccupied(const Eigen::Vector3i & index) const
{
    return isOccupied(index(0), index(1), index(2));
}

inline bool GridMap::isFree(const Eigen::Vector3i & index) const
{

    return isFree(index(0), index(1), index(2));

}

inline bool GridMap::isOccupied(const int & idx_x, const int & idx_y, const int & idx_z) const 
{

    // return  (idx_x >= 0 && idx_x < m_GLX_SIZE && idx_y >= 0 && idx_y < m_GLY_SIZE && idx_z >= 0 && idx_z < m_GLZ_SIZE && 
    //         (m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] == 1));
    return  (idx_x >= 0 && idx_x < m_GLX_SIZE && idx_y >= 0 && idx_y < m_GLY_SIZE && idx_z >= 0 && idx_z < m_GLZ_SIZE && 
            (m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] >= occupy_threshold));

}

inline bool GridMap::isFree(const int & idx_x, const int & idx_y, const int & idx_z) const 
{

    // return (idx_x >= 0 && idx_x < m_GLX_SIZE && idx_y >= 0 && idx_y < m_GLY_SIZE && idx_z >= 0 && idx_z < m_GLZ_SIZE && 
    //        (m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] < 1));
    return  (idx_x >= 0 && idx_x < m_GLX_SIZE && idx_y >= 0 && idx_y < m_GLY_SIZE && idx_z >= 0 && idx_z < m_GLZ_SIZE && 
            (m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] < occupy_threshold));

}


Eigen::MatrixXd* GridMap::getAdjacencyMatrix()
{

    return &m_adj_mat;

}


// inline int GridMap::transformIdx(const Eigen::Vector3i)
// {

//     return (idx_x >= 0 && idx_x < m_GLX_SIZE && idx_y >= 0 && idx_y < m_GLY_SIZE && idx_z >= 0 && idx_z < m_GLZ_SIZE && 
//            (m_data[idx_x * m_GLYZ_SIZE + idx_y * m_GLZ_SIZE + idx_z] < 1));

// }


void GridMap::removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{

    unsigned int numRows = matrix.rows() - 1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows ) {
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) =
            matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);
    }

    matrix.conservativeResize(numRows,numCols);

}


void GridMap::removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{

    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols() - 1;

    if( colToRemove < numCols ) {
        matrix.block(0, colToRemove, numRows, numCols - colToRemove) =
            matrix.block(0, colToRemove + 1, numRows, numCols - colToRemove);
    }

    matrix.conservativeResize(numRows,numCols);

}


bool GridMap::checkLineOfSight(const Eigen::Vector3d & pt_1, const Eigen::Vector3d & pt_2)
{
    if ((pt_2 - pt_1).norm() > 15.0) return false;  // temp comm range check
    int split_num = (int)((pt_2 - pt_1).norm() * 5);
    Eigen::Vector3d cur_pt;
    unsigned collide_count = 0;
    for (int i = 0; i < split_num + 1; i++)
    {
        cur_pt = pt_1 + (pt_2 - pt_1) * (double)i / split_num;
        if (isOccupied(coord2gridIndex(cur_pt))) {
            ++collide_count;
        }
        if (collide_count > 1) return false;
    }

    return true;

}

visualization_msgs::Marker GridMap::drawGridMap() {
    visualization_msgs::Marker graph;
    graph.ns = "grid_map";
    graph.type = visualization_msgs::Marker::CUBE_LIST;
    graph.action = visualization_msgs::Marker::ADD;
    graph.header.frame_id = "/world";
    graph.pose.position.x = graph.pose.position.y = graph.pose.position.z = 0.0;
    graph.pose.orientation.x = 0;
    graph.pose.orientation.y = 0;
    graph.pose.orientation.z = 0;
    graph.pose.orientation.w = 1;
    graph.scale.x = m_resolution / 4;
    graph.scale.y = m_resolution / 4;
    graph.scale.z = m_resolution / 4;
    graph.color.r = 0.0;
    graph.color.g = 0.0;
    graph.color.b = 0.0;
    graph.color.a = 0.1;
    for(int i = 0; i < m_GLX_SIZE; i++)
    {
        for(int j = 0; j < m_GLY_SIZE; j++)
        {
            for(int k = 0; k < m_GLZ_SIZE; k++)
            {
                if (isOccupied({i, j, k})) continue;
                Eigen::Vector3d pt = gridIndex2coord({i, j, k});
                geometry_msgs::Point curr_node_centre;
                curr_node_centre.x = pt(0);
                curr_node_centre.y = pt(1);
                curr_node_centre.z = pt(2);
                graph.points.push_back(curr_node_centre);
                graph.colors.push_back(graph.color);
            }
        }
    }

    return graph;
}
