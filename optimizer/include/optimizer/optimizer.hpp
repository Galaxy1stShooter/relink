#include <iostream>
#include <iomanip>
#include <cmath>
#include <Eigen/Eigen>
#include <ros/ros.h>

#include "message_files/StarConvexPolytopesStamped.h"
#include "message_files/PolygonArrayStamped.h"
#include "message_files/StarConvexPolytope.h"
#include "message_files/Optimize.h"
#include "geometry_msgs/PointStamped.h"
#include "lbfgs/lbfgs.hpp"


struct Polytope
{

    std::string name_id;
    Eigen::Vector3d center;
    std::vector<std::vector<Eigen::Vector3d>> polygons;

};

struct Agent {
    Eigen::Vector3d current_position, goal_position;
    message_files::StarConvexPolytopesStamped SCPs;
    std::vector<Polytope> polytopes;

    Agent() = default;
};


class StarConvexOptimizer
{

    public:
        StarConvexOptimizer(){};
        ~StarConvexOptimizer(){};

        void init(ros::NodeHandle &nh);
        int run(const Eigen::Vector3d& pos);

    private:
        // ROS Utils
        ros::NodeHandle m_nh;
        ros::Subscriber m_scp_sub, m_reach_sub;
        ros::Publisher m_cur_pos_pub;
        ros::Publisher m_goal_pub;
        ros::Publisher m_flipped_goal_pub;
        ros::ServiceServer optimize_srv;
        ros::Timer m_opt_timer;

        // Centralized opimization
        std::vector<Agent> m_agents;

        Eigen::Vector3d m_current_pos, m_goal_pos;
        std::vector<Polytope> m_polytopes;
        std::vector<Eigen::Vector3d> m_curr_solutions;
        Eigen::VectorXd m_curr_solution;
        bool m_has_reached_goal[50], m_is_first_solution = true;
        double m_r_ball;
        double m_alpha;
        double m_d_min;
        double m_lambda;
        double k_energy, k_comm, k_goal;  // Weights of items in cost function
        double m_height_min;
        int m_tar_num;
        int m_iter_index;
        lbfgs::lbfgs_parameter_t params;

    public:
        void scpCallback(const message_files::StarConvexPolytopesStampedConstPtr& msg);
        void rcvReachingSignalCallback(const std_msgs::Header& msg);
        Polytope transformStarConvexPolytopeType(const message_files::StarConvexPolytope& SCP);
        Eigen::Vector3d solveOptimalPose(const Eigen::Vector3d& curr_pos, const Eigen::Vector3d& goal_pos, const message_files::StarConvexPolytopesStamped& SCPs);
        Eigen::VectorXd solveOptimalPoseArray(const std::vector<Agent>& uav_data_array);
        void optCallback(const ros::TimerEvent &e);
        void goalPublish(const Eigen::Vector3d& x);
        double heightConstraint(const Eigen::Vector3d& x);
        double gradOfHeight(const Eigen::Vector3d& x);
        double starConvexConstraint(const Eigen::Vector3d& x, int index);
        double starConvexConstraint(const Eigen::Vector3d& x, int agent_index, int neighbor_index);
        Eigen::Vector3d gradOfConstraintTerm(const Eigen::Vector3d& x, double J_constraint, int index);
        Eigen::Vector3d gradOfConstraintTerm(const Eigen::Vector3d& x, double J_constraint, 
                                             int agent_index, int neighbor_index);
        inline Eigen::Vector3d pointTransform(const Eigen::Vector3d& x);
        inline double getPoint2PlaneDistance(const Eigen::Vector3d& point, 
                                             const std::vector<Eigen::Vector3d>& plane, 
                                             const Eigen::Vector3d& center);
        inline Eigen::Vector3d getOuterNormalFactor(const std::vector<Eigen::Vector3d>& plane, const Eigen::Vector3d& center);
        inline double logSumExpCap(const Eigen::Array<long double, -1, 1>& distances);
        inline double penalty(double x);
        static double costFunction(void *instance,
                                   const Eigen::VectorXd &x,
                                   Eigen::VectorXd &g);
        static double costFunctionCentralized(void *instance,
                                   const Eigen::VectorXd &x,
                                   Eigen::VectorXd &g);
        static int monitorProgress(void *instance,
                                   const Eigen::VectorXd &x,
                                   const Eigen::VectorXd &g,
                                   const double fx,
                                   const double step,
                                   const int k,
                                   const int ls);

};