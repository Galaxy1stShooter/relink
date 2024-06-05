#include <vector>
#include <boost/filesystem.hpp>

#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <visualization_msgs/Marker.h>

#include "message_files/PoseStampedArray.h"
#include "message_files/SteinerTreeArray.h"
#include "message_files/SteinerTreeNode.h"
#include "messsage_files/entity_identifier.h"
// #include "visibility_graph/los_checker.hpp"
#include <random>

#include <Eigen/Eigen>
#include <std_msgs/UInt32.h>
#include "backward-cpp/backward.hpp"

namespace backward {

    backward::SignalHandling sh;

} // namespace backward

std::map<unsigned, Eigen::Vector3d> uav_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> target_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> targetwp_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> bs_poses;  // key: id of entity, separate by type
std::map<unsigned, Eigen::Vector3d> solution_poses;  // key: id of entity, separate by type
std::map<std::string, Eigen::Vector3d> nameid_poses;
ros::Time init_start;
ros::Time init_end;
ros::Time click_time;
ros::Time solution_time;
int uav_num;
bool first_click = true;

inline std::string getName(int type, int id) {
    if (type == BASE_STATION) {
        return "bs_" + std::to_string(id);
    } else if (type == UAV) {
        return "uav_" + std::to_string(id);
    } else if (type == TARGET) {
        return "target_" + std::to_string(id);
    } else if (type == SOLUTION) {
        return "solution_" + std::to_string(id);
    } else {
        return "waypoint_" + std::to_string(id);
    }
}

void updateEntityPoseCallback(const message_files::PoseStampedArrayConstPtr &poses, std::map<unsigned, Eigen::Vector3d> &container, int type)
{
    if (type == SOLUTION) {
        init_start = poses->init_start;
        init_end = poses->init_end;
        click_time = poses->start;
        solution_time = poses->end;
    }
    container.clear();
    for (auto &pose : poses->poses)
    {
        container[pose.header.seq] = Eigen::Vector3d(pose.pose.position.x,
                                                     pose.pose.position.y,
                                                     pose.pose.position.z);
        nameid_poses[getName(type, pose.header.seq)] = container[pose.header.seq];
    }
}

std::map<std::string, std::set<std::string>> entity_neighbours;
void storeNeighbourhoodCallback(const message_files::SteinerTreeArrayConstPtr& msg) {
    entity_neighbours.clear();
    for (auto& treeEdge : msg->entity_neighbours) {
        entity_neighbours[treeEdge.name_id].insert(treeEdge.neighbour_type_id.begin(), treeEdge.neighbour_type_id.end());
    }
    uav_num = entity_neighbours.size();
}


std::map<unsigned, double> uav_trajlength;
std::map<unsigned, visualization_msgs::MarkerConstPtr> uav_traj;
void updateUAVTrajCallback(const visualization_msgs::MarkerConstPtr& traj, int uav_id) {
    uav_traj[uav_id] = traj;
}

double calTravelDistance() {
    double total = 0.0;
    for (auto& [uav_id, traj] : uav_traj) {
        double dist = 0.0;
        for (size_t i = 1; i < traj->points.size(); ++i) {
            dist += sqrt(pow(traj->points[i].x - traj->points[i - 1].x, 2) +
                         pow(traj->points[i].y - traj->points[i - 1].y, 2) +
                         pow(traj->points[i].z - traj->points[i - 1].z, 2));
        }
        uav_trajlength[uav_id] = dist;
        ROS_INFO("[measure] UAV %d traveled %f", uav_id, dist);
        total += dist;
    }
    return total;
}

std::pair<int, double> calCommunicationQuality() {
    // TODO: More decent measurement
    // FIXME: Why inf???
    double total_edge_length = 0.0;
    int relay_count = 0;
    for (auto [name_id, neighbours] : entity_neighbours) {
        if (name_id[0] == 'u') ++relay_count;
        Eigen::Vector3d self_loc = nameid_poses[name_id];
        for (const std::string& neighbour : neighbours) {
            total_edge_length += pow((self_loc - nameid_poses[neighbour]).norm(), 2);
        }
    }
    total_edge_length *= 0.5;  // Due to duplicate calculation
    ROS_INFO("[measure] Use %d relays and total link length is %f", relay_count, total_edge_length);
    return std::make_pair(relay_count, total_edge_length);
}

std::pair<double, double> calRunTime() {
    ros::Duration initialization_time = init_end - init_start;
    ros::Duration calculation_time = solution_time - click_time;
    ROS_INFO("[measure] Calculation of last episode spent %lf s", calculation_time.toSec());
    return {initialization_time.toSec(), calculation_time.toSec()};
}

int seq = 1;
int episode = 0;
void clickCallback(const geometry_msgs::PoseStampedPtr &msg) {
    ++episode;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "measurement_calculator");
    ros::NodeHandle n("~");

    // Episode Utils
    ros::Subscriber click_sub = n.subscribe("/move_base_simple/goal", 1, clickCallback);

    ros::Subscriber sub_tree_array = n.subscribe("/algorithm/tree", 1, storeNeighbourhoodCallback);   

    // Energy cost Utils
    ros::Subscriber sub_uav = n.subscribe<message_files::PoseStampedArray>("/uav_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(uav_poses), UAV));
    ros::Subscriber sub_solution = n.subscribe<message_files::PoseStampedArray>("/optimizer/solution", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(solution_poses), SOLUTION));
    ros::Subscriber sub_target = n.subscribe<message_files::PoseStampedArray>("/target_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(target_poses), TARGET));
    ros::Subscriber sub_targetwp = n.subscribe<message_files::PoseStampedArray>("/target_waypoint", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(targetwp_poses), -1));
    ros::Subscriber sub_bs = n.subscribe<message_files::PoseStampedArray>("/bs_pos", 1, boost::bind(updateEntityPoseCallback, _1, boost::ref(bs_poses), BASE_STATION));

    uav_num = n.param("/available_uav_num", 0);
    std::vector<ros::Subscriber> sub_uavtraj;
    for (int i = 0; i < uav_num; ++i) {
        sub_uavtraj.push_back(n.subscribe<visualization_msgs::Marker>("/uav" + std::to_string(i) + "/planning/travel_traj", 1, boost::bind(updateUAVTrajCallback, _1, i)));
    }   

    while (ros::ok()) {
        ros::spinOnce();
        if (episode == 2) {
            // reset();
            seq = n.param("/simulation_seq", 1);
            episode = 0;

            // Every twice waypoint clicked, a new episode starts, calculate measurements for last episode
            double dist = calTravelDistance();
            auto [relay_cnt, total_len] = calCommunicationQuality();
            auto [ini_t, r_t] = calRunTime();

            std::ofstream writeFile;
            std::string path = ros::package::getPath("map_generator") + "/map/examples/episode_" + std::to_string(seq) + "/";
            if (!boost::filesystem::exists(path)) {
                boost::filesystem::create_directories(path);
            }
            writeFile.open(path + "result");
            writeFile << ini_t << std::endl;
            writeFile << r_t << std::endl;
            writeFile << (ini_t + r_t) << std::endl;
            writeFile << relay_cnt << std::endl;
            writeFile << total_len << std::endl;
            writeFile << dist << std::endl;
            writeFile.close();
        }
    }

    return 0;
}
