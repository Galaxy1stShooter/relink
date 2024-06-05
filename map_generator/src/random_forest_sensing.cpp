#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
// #include <pcl/search/kdtree.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Vector3.h>
#include <math.h>
#include <nav_msgs/Odometry.h>
#include <ros/console.h>
#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/PointCloud2.h>
#include <Eigen/Eigen>
#include <random>

// #include <backward.hpp>

using namespace std;

// pcl::search::KdTree<pcl::PointXYZ> kdtreeLocalMap;
pcl::KdTreeFLANN<pcl::PointXYZ> kdtreeLocalMap;
vector<int> pointIdxRadiusSearch;
vector<float> pointRadiusSquaredDistance;

random_device rd;
default_random_engine eng(rd());
uniform_real_distribution<double> rand_x;
uniform_real_distribution<double> rand_y;
uniform_real_distribution<double> rand_w;
uniform_real_distribution<double> rand_h;

ros::Publisher pub_global_map;
ros::Publisher pub_inflated_global_map;
ros::Publisher _local_map_pub;
ros::Publisher click_map_pub_;
ros::Subscriber _odom_sub;

vector<double> _state;

int _obs_num;
double _x_size, _y_size, _z_size;
double _x_l, _x_h, _y_l, _y_h, _w_l, _w_h, _h_l, _h_h;
double _z_limit, _sensing_range, map_resolution, _sense_rate, _init_x, _init_y;

bool _map_ok = false;
bool _has_odom = false;

int circle_num_;
double radius_l_, radius_h_, z_l_, z_h_;
double theta_;
double grid_resolution;
uniform_real_distribution<double> rand_radius_;
uniform_real_distribution<double> rand_radius2_;
uniform_real_distribution<double> rand_theta_;
uniform_real_distribution<double> rand_z_;

sensor_msgs::PointCloud2 globalMap_pcd;
pcl::PointCloud<pcl::PointXYZ> cloudMap;
double gridSize_to_ObstacleWidth;

sensor_msgs::PointCloud2 inflated_globalMap_pcd;
pcl::PointCloud<pcl::PointXYZ> inflated_cloudMap;
double gridSize_to_InflatedWidth;

sensor_msgs::PointCloud2 localMap_pcd;
pcl::PointCloud<pcl::PointXYZ> clicked_cloud_;

vector<pair<double, double>> curr_random_obstacle_locs;

void RandomMapGenerate() {
    cloudMap.clear();
    inflated_cloudMap.clear();

    if (_obs_num == 0) {
        // Avoid empty point cloud, put a single point up in the sky
        pcl::PointXYZ pt;
        pt.x = pt.y = 0;
        pt.z = 10.0;

        cloudMap.points.push_back(pt);

        kdtreeLocalMap.setInputCloud(cloudMap.makeShared());

        inflated_cloudMap.points.push_back(pt);
    }

    pcl::PointXYZ pt_random;

    rand_x = uniform_real_distribution<double>(_x_l, _x_h);
    rand_y = uniform_real_distribution<double>(_y_l, _y_h);
    rand_w = uniform_real_distribution<double>(_w_l, _w_h);
    rand_h = uniform_real_distribution<double>(_h_l, _h_h);

    rand_radius_ = uniform_real_distribution<double>(radius_l_, radius_h_);
    rand_radius2_ = uniform_real_distribution<double>(radius_l_, 1.2);
    rand_theta_ = uniform_real_distribution<double>(-theta_, theta_);
    rand_z_ = uniform_real_distribution<double>(z_l_, z_h_);

    // generate polar obs
    for (int i = 0; i < _obs_num; i++) {
        double x, y, obstacle_width, inflated_width, h;
        x = rand_x(eng);
        y = rand_y(eng);
//        obstacle_width = rand_w(eng);
        obstacle_width = grid_resolution * gridSize_to_ObstacleWidth;
        inflated_width = grid_resolution * gridSize_to_InflatedWidth;

        x = floor(x / grid_resolution) * grid_resolution + grid_resolution / 2.0;
        y = floor(y / grid_resolution) * grid_resolution + grid_resolution / 2.0;

        // TODO: Reuse this block to avoid obstacle generated too close to entities and their path
        if (x - _x_l <= 2.5 || _x_h - x <= 2.5) {
            --i;
            continue;
        }

        if (y - _y_l <= 2.5 || _y_h - y <= 2.5) {
            --i;
            continue;
        }

        // base area
        if (x <= 1.5 && x >= -7.5 && y <= -12.5) {
            --i;
            continue;
        }

        // car0
        if (fabs(x - 12.5) <= 2.5 && fabs(y - 12.5) <= 2.5) {
            --i;
            continue;
        }

        // car1
        if (fabs(x + 12.5) <= 2.5 && fabs(y - 12.5) <= 2.5) {
            --i;
            continue;
        }

        curr_random_obstacle_locs.emplace_back(x, y);

        // Generate real point cloud of obstacles
        int obstacle_widNum = floor(obstacle_width / map_resolution);
        for (int r = -obstacle_widNum / 2.0; r < obstacle_widNum / 2.0; r++) {
            for (int s = -obstacle_widNum / 2.0; s < obstacle_widNum / 2.0; s++) {
                h = _h_h;
                int heiNum = ceil(h / map_resolution);
                for (int t = -5; t < heiNum; t++) {
                    pt_random.x = x + r * map_resolution - 1e-2;
                    pt_random.y = y + s * map_resolution - 1e-2;
                    pt_random.z = t * map_resolution - 1e-2;
                    cloudMap.points.push_back(pt_random);
                }
            }
        }

        // Generate point cloud of inflated obstacles
        int inflated_widNum = floor(inflated_width / map_resolution);
        for (int r = -inflated_widNum / 2.0; r < inflated_widNum / 2.0; r++) {
            for (int s = -inflated_widNum / 2.0; s < inflated_widNum / 2.0; s++) {
                h = _h_h * 1.05;
                int heiNum = ceil(h / map_resolution);
                for (int t = -5; t < heiNum; t++) {
                    pt_random.x = x + r * map_resolution - 1e-2;
                    pt_random.y = y + s * map_resolution - 1e-2;
                    pt_random.z = t * map_resolution - 1e-2;
                    inflated_cloudMap.points.push_back(pt_random);
                }
            }
        }

    }

    // generate circle obs
    for (int i = 0; i < circle_num_; ++i) {
        double x, y, z;
        x = rand_x(eng);
        y = rand_y(eng);
        z = rand_z_(eng);


        // TODO: Reuse this block to avoid obstacle generated too close to entities and their path
        if (sqrt(pow(x - _init_x, 2) + pow(y - _init_y, 2)) < 2.0) {
            i--;
            continue;
        }

        if (sqrt(pow(x - 19.0, 2) + pow(y - 0.0, 2)) < 2.0) {
            i--;
            continue;
        }

        x = floor(x / map_resolution) * map_resolution + map_resolution / 2.0;
        y = floor(y / map_resolution) * map_resolution + map_resolution / 2.0;
        z = floor(z / map_resolution) * map_resolution + map_resolution / 2.0;

        Eigen::Vector3d translate(x, y, z);

        double theta = rand_theta_(eng);
        Eigen::Matrix3d rotate;
        rotate << cos(theta), -sin(theta), 0.0, sin(theta), cos(theta), 0.0, 0, 0,
                1;

        double radius1 = rand_radius_(eng);
        double radius2 = rand_radius2_(eng);

        // draw a circle centered at (x,y,z)
        Eigen::Vector3d cpt;
        for (double angle = 0.0; angle < 6.282; angle += map_resolution / 2) {
            cpt(0) = 0.0;
            cpt(1) = radius1 * cos(angle);
            cpt(2) = radius2 * sin(angle);

            // inflate
            Eigen::Vector3d cpt_if;
            for (int ifx = -0; ifx <= 0; ++ifx)
                for (int ify = -0; ify <= 0; ++ify)
                    for (int ifz = -0; ifz <= 0; ++ifz) {
                        cpt_if = cpt + Eigen::Vector3d(ifx * map_resolution, ify * map_resolution,
                                                       ifz * map_resolution);
                        cpt_if = rotate * cpt_if + Eigen::Vector3d(x, y, z);
                        pt_random.x = cpt_if(0);
                        pt_random.y = cpt_if(1);
                        pt_random.z = cpt_if(2);
                        cloudMap.push_back(pt_random);
                    }
        }
    }

    cloudMap.width = cloudMap.points.size();
    cloudMap.height = 1;
    cloudMap.is_dense = true;

    inflated_cloudMap.width = inflated_cloudMap.points.size();
    inflated_cloudMap.height = 1;
    inflated_cloudMap.is_dense = true;

    kdtreeLocalMap.setInputCloud(cloudMap.makeShared());

    _map_ok = true;
}

void ReadMapGenerate() {
    cloudMap.clear();
    inflated_cloudMap.clear();

    if (_obs_num == 0) {
        // Avoid empty point cloud, put a single point up in the sky
        pcl::PointXYZ pt;
        pt.x = pt.y = 0;
        pt.z = 10.0;

        cloudMap.points.push_back(pt);

        kdtreeLocalMap.setInputCloud(cloudMap.makeShared());

        inflated_cloudMap.points.push_back(pt);
    }

    pcl::PointXYZ pt_random;

    // generate polar obs
    for (int i = 0; i < _obs_num; i++) {
        double x, y, obstacle_width, inflated_width, h;
        x = rand_x(eng);
        y = rand_y(eng);
//        obstacle_width = rand_w(eng);
        obstacle_width = grid_resolution * gridSize_to_ObstacleWidth;
        inflated_width = grid_resolution * gridSize_to_InflatedWidth;
        x = curr_random_obstacle_locs[i].first;
        y = curr_random_obstacle_locs[i].second;

        // Generate real point cloud of obstacles
        int obstacle_widNum = floor(obstacle_width / map_resolution);
        for (int r = -obstacle_widNum / 2.0; r < obstacle_widNum / 2.0; r++) {
            for (int s = -obstacle_widNum / 2.0; s < obstacle_widNum / 2.0; s++) {
                h = _h_h;
                int heiNum = ceil(h / map_resolution);
                for (int t = -5; t < heiNum; t++) {
                    pt_random.x = x + r * map_resolution - 1e-2;
                    pt_random.y = y + s * map_resolution - 1e-2;
                    pt_random.z = t * map_resolution - 1e-2;
                    cloudMap.points.push_back(pt_random);
                }
            }
        }

        // Generate point cloud of inflated obstacles
        int inflated_widNum = floor(inflated_width / map_resolution);
        for (int r = -inflated_widNum / 2.0; r < inflated_widNum / 2.0; r++) {
            for (int s = -inflated_widNum / 2.0; s < inflated_widNum / 2.0; s++) {
                h = _h_h * 1.05;
                int heiNum = ceil(h / map_resolution);
                for (int t = -5; t < heiNum; t++) {
                    pt_random.x = x + r * map_resolution - 1e-2;
                    pt_random.y = y + s * map_resolution - 1e-2;
                    pt_random.z = t * map_resolution - 1e-2;
                    inflated_cloudMap.points.push_back(pt_random);
                }
            }
        }

    }

    cloudMap.width = cloudMap.points.size();
    cloudMap.height = 1;
    cloudMap.is_dense = true;

    inflated_cloudMap.width = inflated_cloudMap.points.size();
    inflated_cloudMap.height = 1;
    inflated_cloudMap.is_dense = true;

    kdtreeLocalMap.setInputCloud(cloudMap.makeShared());

    pcl::toROSMsg(cloudMap, globalMap_pcd);
    pcl::toROSMsg(inflated_cloudMap, inflated_globalMap_pcd);

    _map_ok = true;
}

void rcvOdometryCallbck(const nav_msgs::Odometry odom) {
    if (odom.child_frame_id == "X" || odom.child_frame_id == "O") return;
    _has_odom = true;

    _state = {odom.pose.pose.position.x,
              odom.pose.pose.position.y,
              odom.pose.pose.position.z,
              odom.twist.twist.linear.x,
              odom.twist.twist.linear.y,
              odom.twist.twist.linear.z,
              0.0,
              0.0,
              0.0};
}

int i = 0;

void pubSensedPoints() {
    pcl::toROSMsg(cloudMap, globalMap_pcd);
    globalMap_pcd.header.frame_id = "world";
    pub_global_map.publish(globalMap_pcd);

    pcl::toROSMsg(inflated_cloudMap, inflated_globalMap_pcd);
    inflated_globalMap_pcd.header.frame_id = "world";
    pub_inflated_global_map.publish(inflated_globalMap_pcd);

    return;

    /* ---------- only publish points around current position ---------- */
    if (!_map_ok || !_has_odom) return;

    pcl::PointCloud<pcl::PointXYZ> localMap;

    pcl::PointXYZ searchPoint(_state[0], _state[1], _state[2]);
    pointIdxRadiusSearch.clear();
    pointRadiusSquaredDistance.clear();

    pcl::PointXYZ pt;

    if (isnan(searchPoint.x) || isnan(searchPoint.y) || isnan(searchPoint.z))
        return;

    if (kdtreeLocalMap.radiusSearch(searchPoint, _sensing_range,
                                    pointIdxRadiusSearch,
                                    pointRadiusSquaredDistance) > 0) {
        for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i) {
            pt = cloudMap.points[pointIdxRadiusSearch[i]];
            localMap.points.push_back(pt);
        }
    } else {
        ROS_ERROR("[Map server] No obstacles .");
        return;
    }

    localMap.width = localMap.points.size();
    localMap.height = 1;
    localMap.is_dense = true;

    pcl::toROSMsg(localMap, localMap_pcd);
    localMap_pcd.header.frame_id = "world";
    _local_map_pub.publish(localMap_pcd);
}


// TODO: Reuse this to perform dynamic experiment
void clickPointCallback(const geometry_msgs::PoseStamped &msg) {
    // Click to add obstacle
    ROS_INFO("[map_generator] click callback called");
    sensor_msgs::PointCloud2 click_globalMap_pcd;
    pcl::PointCloud<pcl::PointXYZ> click_cloudMap;
    sensor_msgs::PointCloud2 click_inflated_globalMap_pcd;
    pcl::PointCloud<pcl::PointXYZ> click_inflated_cloudMap;

    double x = msg.pose.position.x;
    double y = msg.pose.position.y;
    double h;
    pcl::PointXYZ pt_random;
    double obstacle_width, inflated_width;
    obstacle_width = grid_resolution * gridSize_to_ObstacleWidth;
    inflated_width = grid_resolution * gridSize_to_InflatedWidth;

    x = floor(x / grid_resolution) * grid_resolution + grid_resolution / 2.0;
    y = floor(y / grid_resolution) * grid_resolution + grid_resolution / 2.0;

    // Generate real point cloud of obstacles
    int obstacle_widNum = floor(obstacle_width / map_resolution);
    for (int r = -obstacle_widNum / 2.0; r < obstacle_widNum / 2.0; r++) {
        for (int s = -obstacle_widNum / 2.0; s < obstacle_widNum / 2.0; s++) {
            h = _h_h;
            int heiNum = ceil(h / map_resolution);
            for (int t = -5; t < heiNum; t++) {
                pt_random.x = x + r * map_resolution - 1e-2;
                pt_random.y = y + s * map_resolution - 1e-2;
                pt_random.z = t * map_resolution - 1e-2;
                click_cloudMap.points.push_back(pt_random);

                cloudMap.points.push_back(pt_random);
            }
        }
    }

    // Generate point cloud of inflated obstacles
    int inflated_widNum = floor(inflated_width / map_resolution);
    for (int r = -inflated_widNum / 2.0; r < inflated_widNum / 2.0; r++) {
        for (int s = -inflated_widNum / 2.0; s < inflated_widNum / 2.0; s++) {
            h = _h_h * 1.05;
            int heiNum = ceil(h / map_resolution);
            for (int t = -5; t < heiNum; t++) {
                pt_random.x = x + r * map_resolution - 1e-2;
                pt_random.y = y + s * map_resolution - 1e-2;
                pt_random.z = t * map_resolution - 1e-2;
                click_inflated_cloudMap.points.push_back(pt_random);

                inflated_cloudMap.points.push_back(pt_random);
            }
        }
    }

    click_cloudMap.width = click_cloudMap.points.size();
    click_cloudMap.height = 1;
    click_cloudMap.is_dense = true;

    click_inflated_cloudMap.width = click_inflated_cloudMap.points.size();
    click_inflated_cloudMap.height = 1;
    click_inflated_cloudMap.is_dense = true;

    pcl::toROSMsg(click_cloudMap, click_globalMap_pcd);
    click_globalMap_pcd.header.frame_id = "world";

    pcl::toROSMsg(click_inflated_cloudMap, click_inflated_globalMap_pcd);
    click_inflated_globalMap_pcd.header.frame_id = "world";

    click_map_pub_.publish(click_globalMap_pcd);

    cloudMap.width = cloudMap.points.size();
    cloudMap.height = 1;
    cloudMap.is_dense = true;

    inflated_cloudMap.width = inflated_cloudMap.points.size();
    inflated_cloudMap.height = 1;
    inflated_cloudMap.is_dense = true;

    pcl::toROSMsg(cloudMap, globalMap_pcd);
    globalMap_pcd.header.frame_id = "world";

    pcl::toROSMsg(inflated_cloudMap, inflated_globalMap_pcd);
    inflated_globalMap_pcd.header.frame_id = "world";

    ROS_INFO("[map_generator] click generation finished");
}

sensor_msgs::PointCloud2 real_map;

void storeRealMap(const sensor_msgs::PointCloud2 &real_map_) {
    real_map = real_map_;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "random_map_sensing");
    ros::NodeHandle n("~");

    _local_map_pub = n.advertise<sensor_msgs::PointCloud2>("/map_generator/local_cloud", 1);
    pub_global_map = n.advertise<sensor_msgs::PointCloud2>("/map_generator/global_cloud", 1);
    pub_inflated_global_map = n.advertise<sensor_msgs::PointCloud2>("/map_generator/inflated_global_cloud", 1);

    _odom_sub = n.subscribe("odom", 50, rcvOdometryCallbck);

    ros::Subscriber sub_real_map = n.subscribe("/real_map", 1, storeRealMap);

     click_map_pub_ = n.advertise<sensor_msgs::PointCloud2>("/click_map", 1);
//    ros::Subscriber click_sub = n.subscribe("/goal", 10, clickCallback);
     ros::Subscriber clicked_point_sub = n.subscribe("/move_base_simple/goal", 10, clickPointCallback);

    n.param("init_state_x", _init_x, 0.0);
    n.param("init_state_y", _init_y, 0.0);

    n.param("map/x_size", _x_size, 50.0);
    n.param("map/y_size", _y_size, 50.0);
    n.param("map/z_size", _z_size, 5.0);
    n.param("map/obs_num", _obs_num, 0);
    n.param("map/resolution", map_resolution, 0.1);
    n.param("grid_resolution", grid_resolution, 1.0);
    n.param("map/circle_num", circle_num_, 0);

    n.param("gridSize_to_ObstacleWidth", gridSize_to_ObstacleWidth, 0.8);
    n.param("gridSize_to_InflatedWidth", gridSize_to_InflatedWidth, 0.99);

    n.param("ObstacleShape/lower_rad", _w_l, 0.3);
    n.param("ObstacleShape/upper_rad", _w_h, 0.8);
    n.param("ObstacleShape/lower_hei", _h_l, 3.0);
    n.param("ObstacleShape/upper_hei", _h_h, 7.0);

    n.param("ObstacleShape/radius_l", radius_l_, 7.0);
    n.param("ObstacleShape/radius_h", radius_h_, 7.0);
    n.param("ObstacleShape/z_l", z_l_, 7.0);
    n.param("ObstacleShape/z_h", z_h_, 7.0);
    n.param("ObstacleShape/theta", theta_, 7.0);

    n.param("sensing/radius", _sensing_range, 10.0);
    n.param("sensing/rate", _sense_rate, 10.0);

    _x_l = -_x_size / 2.0;
    _x_h = +_x_size / 2.0;

    _y_l = -_y_size / 2.0;
    _y_h = +_y_size / 2.0;

    _obs_num = min(_obs_num, (int) _x_size * 10);
    _z_limit = _z_size;

    bool use_real_map = n.param("use_real_map", true);
    bool read_map = n.param("read_map", true);

    if (use_real_map) {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        std::string map_path = ros::package::getPath(ROS_PACKAGE_NAME) + "/map/filtered_street.pcd";
        if (pcl::io::loadPCDFile<pcl::PointXYZ>(map_path, *cloud) == -1) {
            PCL_ERROR("Couldn't read file .pcd\n");
            return (-1);
        }
        pcl::toROSMsg(*cloud, real_map);
        real_map.header.frame_id = "world";
    } else if (!read_map) {
        RandomMapGenerate();

        pcl::toROSMsg(cloudMap, globalMap_pcd);
        globalMap_pcd.header.frame_id = "world";

        pcl::toROSMsg(inflated_cloudMap, inflated_globalMap_pcd);
        inflated_globalMap_pcd.header.frame_id = "world";

        ofstream writeFile;
        // TODO: more formatted file name
        int seq = n.param("/simulation_seq", 1);
        std::string path =
                ros::package::getPath(ROS_PACKAGE_NAME) + "/map/examples/episode_" + std::to_string(seq) + "/";
        if (!boost::filesystem::exists(path)) {
            boost::filesystem::create_directories(path);
        }
        writeFile.open(path + "obstacles");
        for (auto [x, y]: curr_random_obstacle_locs) {
            writeFile << x << " " << y << endl;
        }
        writeFile.close();
    } else {
        ifstream readFile;
        int seq = n.param("/simulation_seq", 1);
        std::string path =
                ros::package::getPath(ROS_PACKAGE_NAME) + "/map/examples/episode_" + std::to_string(seq) + "/";
        readFile.open(path + "obstacles", std::ios::in);
        if (!readFile.is_open()) {
            ROS_WARN("Could not open map file %s", path.c_str());
            return 1;
        }
        string location;
        while (getline(readFile, location)) {
            int spaceLocation = location.find(" ");
            curr_random_obstacle_locs.emplace_back(stod(location.substr(0, spaceLocation)),
                                                   stod(location.substr(spaceLocation + 1)));
        }
        readFile.close();
        ReadMapGenerate();

        pcl::toROSMsg(cloudMap, globalMap_pcd);
        globalMap_pcd.header.frame_id = "world";

        pcl::toROSMsg(inflated_cloudMap, inflated_globalMap_pcd);
        inflated_globalMap_pcd.header.frame_id = "world";
    }

    ros::Rate loop_rate(_sense_rate);

    while (ros::ok()) {
        ros::spinOnce();
        if (use_real_map) {
            pub_global_map.publish(real_map);
        } else {
            pub_global_map.publish(globalMap_pcd);
            pub_inflated_global_map.publish(inflated_globalMap_pcd);
        }

        loop_rate.sleep();
    }
}