#include "visibility_graph/los_checker.hpp"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_los");
    ros::NodeHandle n("~");

    LosChecker los_checker;
    los_checker.init(n);
    
    ros::Duration(2.0).sleep(); // Wait the map generation, can be deleted
    ros::spinOnce();

    std::shared_ptr<GridMap> grid_map_ptr = los_checker.grid_map_interface();
    Eigen::Vector3d pt_1, pt_2;
    for (int i= -8; i < 9; ++i)
    {
        pt_1 << -3.0, 0.0 + i, 1.0;
        pt_2 <<  3.0, 0.0 + i, 1.0;
        std::cout << grid_map_ptr->checkLineOfSight(pt_1, pt_2) << std::endl;
    }

    return 0;
}