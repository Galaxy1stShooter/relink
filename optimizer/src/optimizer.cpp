#include "optimizer/optimizer.hpp"

void StarConvexOptimizer::init(ros::NodeHandle &nh)
{

    m_nh = nh;

    double ball_radius, ball_radius_multiplier;
    m_nh.param("optimizer/ball_radius", ball_radius, 5.0);
    m_nh.param("optimizer/ball_radius_multiplier", ball_radius_multiplier, 30.0);
    m_r_ball = ball_radius * ball_radius_multiplier;

    m_nh.param("optimizer/approximation_quality", m_alpha, 1.0);
    m_nh.param("optimizer/safe_margin", m_d_min, 3.0);
    m_nh.param("optimizer/penalty_weight", m_lambda, 800000.0);
    m_nh.param("optimizer/height_min", m_height_min, -1.0);
    ROS_ERROR("[debug]: lambda: %f", m_lambda);
    // Set the minimization parameters
    // TODO: Should get from parameter configuration
    params.g_epsilon = 1.0e-1;
    params.past = 3;
    params.delta = 1.0e-1;
    params.max_linesearch = 16;
    params.cautious_factor = 1.0e-3;
    params.max_iterations = 4;
    // params.f_dec_coeff = 1.0e-6;
    // params.s_curv_coeff = 0.1;
    memset(m_has_reached_goal, 1, sizeof(m_has_reached_goal));

    k_energy = m_nh.param("optimizer/k_energy", 1.0);
    k_comm = m_nh.param("optimizer/k_comm", 1.0);
    k_goal = m_nh.param("optimizer/k_goal", 1.0);

    m_reach_sub = m_nh.subscribe("/planning/reach", 1, &StarConvexOptimizer::rcvReachingSignalCallback, this);
    // m_scp_sub = m_nh.subscribe<message_files::StarConvexPolytopesStamped>("/star_convex/star_convex", 1, &StarConvexOptimizer::scpCallback, this);

    m_cur_pos_pub = m_nh.advertise<geometry_msgs::PointStamped>("/cur_pos", 10);
    m_goal_pub = m_nh.advertise<geometry_msgs::PointStamped>("/goal_point", 10);
    m_flipped_goal_pub = m_nh.advertise<geometry_msgs::PointStamped>("/flipped_goal_point", 10);

    // optimize_srv = m_nh.advertiseService("/optimizer/optimize", &StarConvexOptimizer::solveOnceCallback, this);

    // m_opt_timer = m_nh.createTimer(ros::Duration(1.0), &StarConvexOptimizer::optCallback, this);

    // m_polytopes.resize(m_tar_num);
    m_curr_solutions.resize(50);
    // for (auto solution : m_curr_solutions)
    // {
    //     solution << 10000, 10000, 10000;
    // }
    m_goal_pos.setZero();

}


void StarConvexOptimizer::optCallback(const ros::TimerEvent &e)
{
    ros::Time start = ros::Time::now();

    run(m_current_pos);

    ros::Time end = ros::Time::now();
    // std::cout << "The duration of the optimization: " << (end - start).toSec() << std::endl;
    ROS_INFO("[optimizer] The duration of the optimization: %.5fs\n", (end - start).toSec());
}

// Function rcvReachingSignalCallback
// Receives the signal if the uav reach its goal.
void StarConvexOptimizer::rcvReachingSignalCallback(const std_msgs::Header& msg)
{
    // ROS_INFO("[optimizer] The id is %d\n", msg.seq);
    if (msg.seq == -1)
    {
        return;
    }
    m_has_reached_goal[msg.seq] = true;
}

/**
 * Function scpCallback
 * Receives the SCP messages and operates the assignment.
 * In practice, everytime this function called, new set of star convex has been created,
 * the number of SCPs and meshes in them may have changed, so just re-store them.
 * TODO: Some way to tell this function which part of SCPs changed and which not, to accelarate 
 * (eliminate the operation 'm_polytopes.clear();')
*/
void StarConvexOptimizer::scpCallback(const message_files::StarConvexPolytopesStampedConstPtr& msg)
{ 

    // int index = msg->header.seq;

    // m_polytopes[index].center(0) = msg->center.x;
    // m_polytopes[index].center(1) = msg->center.y;
    // m_polytopes[index].center(2) = msg->center.z;

    // m_polytopes[index].polygons.clear();
    // std::vector<Eigen::Vector3d> polygon_tmp;
    // Eigen::Vector3d point_tmp;
    // for (unsigned int i = 0; i < msg->polygons.size(); i++)
    // {
    //     polygon_tmp.clear();
    //     for (unsigned int j = 0; j < msg->polygons[i].points.size(); j++)
    //     {
    //         point_tmp(0) = msg->polygons[i].points[j].x - msg->center.x;
    //         point_tmp(1) = msg->polygons[i].points[j].y - msg->center.y;
    //         point_tmp(2) = msg->polygons[i].points[j].z - msg->center.z;

    //         polygon_tmp.push_back(point_tmp);
    //     }

    //     // temporary handle: delete the polygon under the ground
    //     if (polygon_tmp[0](2) < 0.1 || polygon_tmp[1](2) < 0.1 || polygon_tmp[2](2) < 0.1) continue;

    //     m_polytopes[index].polygons.push_back(polygon_tmp);
    // }

    // // temporary handle: add a polygon that represents the ground
    // polygon_tmp.clear();
    // point_tmp = {1.0, 0.0, -0.1};
    // polygon_tmp.push_back(pointTransform(point_tmp));
    // point_tmp = {0.0, -1.0, -0.1};
    // polygon_tmp.push_back(pointTransform(point_tmp));
    // point_tmp = {-1.0, 0.0, -0.1};
    // polygon_tmp.push_back(pointTransform(point_tmp));
    // m_polytopes[index].polygons.push_back(polygon_tmp);

    // run(m_current_pos);

    m_polytopes.clear();
    for (unsigned int polytope_idx = 0; polytope_idx < msg->SCPs.size(); polytope_idx++)
    {
        Polytope curr_polypote;
        curr_polypote.center(0) = msg->SCPs[polytope_idx].center.x;
        curr_polypote.center(1) = msg->SCPs[polytope_idx].center.y;
        curr_polypote.center(2) = msg->SCPs[polytope_idx].center.z;

        curr_polypote.polygons.clear();
        std::vector<Eigen::Vector3d> polygon_tmp;
        Eigen::Vector3d point_tmp;
        for (unsigned int polygon_idx = 0; polygon_idx < msg->SCPs[polytope_idx].polygons.size(); polygon_idx++)
        {
            polygon_tmp.clear();
            for (unsigned int point_idx = 0; point_idx < msg->SCPs[polytope_idx].polygons[polygon_idx].points.size(); point_idx++)
            {
                point_tmp(0) = msg->SCPs[polytope_idx].polygons[polygon_idx].points[point_idx].x - msg->SCPs[polytope_idx].center.x;
                point_tmp(1) = msg->SCPs[polytope_idx].polygons[polygon_idx].points[point_idx].y - msg->SCPs[polytope_idx].center.y;
                point_tmp(2) = msg->SCPs[polytope_idx].polygons[polygon_idx].points[point_idx].z - msg->SCPs[polytope_idx].center.z;

                polygon_tmp.push_back(point_tmp);
            }

            // temporary handle: delete the polygon under the ground
            if (polygon_tmp[0](2) < 0.1 || polygon_tmp[1](2) < 0.1 || polygon_tmp[2](2) < 0.1) continue;

            curr_polypote.polygons.push_back(polygon_tmp);
        }

        // // temporary handle: add a polygon that represents the ground
        // polygon_tmp.clear();
        // point_tmp = {1.0, 0.0, -0.1};
        // polygon_tmp.push_back(pointTransform(point_tmp));
        // point_tmp = {0.0, -1.0, -0.1};
        // polygon_tmp.push_back(pointTransform(point_tmp));
        // point_tmp = {-1.0, 0.0, -0.1};
        // polygon_tmp.push_back(pointTransform(point_tmp));
        // curr_polypote.polygons.push_back(polygon_tmp);

        m_polytopes.push_back(curr_polypote);
    }

    ros::Time start = ros::Time::now();

    run(m_current_pos);

    ros::Time end = ros::Time::now();
    // std::cout << "The duration of the optimization: " << (end - start).toSec() << std::endl;
    ROS_INFO("[optimizer] The duration of the optimization for UAV %d: %.5fs\n", msg->header.seq, (end - start).toSec());
}


Polytope StarConvexOptimizer::transformStarConvexPolytopeType(const message_files::StarConvexPolytope& SCP) {
    Polytope curr_polypote;
    curr_polypote.center(0) = SCP.center.x;
    curr_polypote.center(1) = SCP.center.y;
    curr_polypote.center(2) = SCP.center.z;

    curr_polypote.polygons.clear();
    std::vector<Eigen::Vector3d> polygon_tmp;
    Eigen::Vector3d point_tmp;
    for (unsigned int polygon_idx = 0; polygon_idx < SCP.polygons.size(); polygon_idx++)
    {
        polygon_tmp.clear();
        for (unsigned int point_idx = 0; point_idx < SCP.polygons[polygon_idx].points.size(); point_idx++)
        {
            point_tmp(0) = SCP.polygons[polygon_idx].points[point_idx].x - curr_polypote.center(0);
            point_tmp(1) = SCP.polygons[polygon_idx].points[point_idx].y - curr_polypote.center(1);
            point_tmp(2) = SCP.polygons[polygon_idx].points[point_idx].z - curr_polypote.center(2);

            polygon_tmp.push_back(point_tmp);
        }

        // temporary handle: delete the polygon under the ground
        if (polygon_tmp[0](2) < 0.1 || polygon_tmp[1](2) < 0.1 || polygon_tmp[2](2) < 0.1) continue;

        curr_polypote.polygons.push_back(polygon_tmp);
    }

    // temporary handle: add a polygon that represents the ground
    polygon_tmp.clear();
    point_tmp = {1.0, 0.0, 2.0};
    polygon_tmp.push_back(pointTransform(point_tmp));
    point_tmp = {0.0, -1.0, 2.0};
    polygon_tmp.push_back(pointTransform(point_tmp));
    point_tmp = {-1.0, 0.0, 2.0};
    polygon_tmp.push_back(pointTransform(point_tmp));
    curr_polypote.polygons.push_back(polygon_tmp);

    return curr_polypote;
}


Eigen::Vector3d StarConvexOptimizer::solveOptimalPose(const Eigen::Vector3d& curr_pos, const Eigen::Vector3d& goal_pos, const message_files::StarConvexPolytopesStamped& SCPs)
{
    int uav_id = SCPs.header.seq;

    // judge if reaching goal here
    // if ((m_curr_solutions[uav_id] - curr_pos).norm() > 0.5)
    // {
    //     return m_curr_solutions[uav_id];
    // }

    // judge if reaching goal in fast-planner
    if (!m_has_reached_goal[uav_id])
    {
        return m_curr_solutions[uav_id];
    }
    m_has_reached_goal[uav_id] = false;

    m_current_pos = curr_pos;
    // m_goal_pos = goal_pos;
    m_polytopes.clear();
    for (unsigned int polytope_idx = 0; polytope_idx < SCPs.SCPs.size(); polytope_idx++)
    {
        Polytope curr_polypote;
        curr_polypote.center(0) = SCPs.SCPs[polytope_idx].center.x;
        curr_polypote.center(1) = SCPs.SCPs[polytope_idx].center.y;
        curr_polypote.center(2) = SCPs.SCPs[polytope_idx].center.z;

        curr_polypote.polygons.clear();
        std::vector<Eigen::Vector3d> polygon_tmp;
        Eigen::Vector3d point_tmp;
        for (unsigned int polygon_idx = 0; polygon_idx < SCPs.SCPs[polytope_idx].polygons.size(); polygon_idx++)
        {
            polygon_tmp.clear();
            for (unsigned int point_idx = 0; point_idx < SCPs.SCPs[polytope_idx].polygons[polygon_idx].points.size(); point_idx++)
            {
                point_tmp(0) = SCPs.SCPs[polytope_idx].polygons[polygon_idx].points[point_idx].x - SCPs.SCPs[polytope_idx].center.x;
                point_tmp(1) = SCPs.SCPs[polytope_idx].polygons[polygon_idx].points[point_idx].y - SCPs.SCPs[polytope_idx].center.y;
                point_tmp(2) = SCPs.SCPs[polytope_idx].polygons[polygon_idx].points[point_idx].z - SCPs.SCPs[polytope_idx].center.z;

                polygon_tmp.push_back(point_tmp);
            }

            // temporary handle: delete the polygon under the ground
            if (polygon_tmp[0](2) < 0.1 || polygon_tmp[1](2) < 0.1 || polygon_tmp[2](2) < 0.1) continue;

            curr_polypote.polygons.push_back(polygon_tmp);
        }

        // temporary handle: add a polygon that represents the ground
        polygon_tmp.clear();
        point_tmp = {1.0, 0.0, 2.0};
        polygon_tmp.push_back(pointTransform(point_tmp));
        point_tmp = {0.0, -1.0, 2.0};
        polygon_tmp.push_back(pointTransform(point_tmp));
        point_tmp = {-1.0, 0.0, 2.0};
        polygon_tmp.push_back(pointTransform(point_tmp));
        curr_polypote.polygons.push_back(polygon_tmp);

        m_polytopes.push_back(curr_polypote);
    }

    ros::Time start = ros::Time::now();

    double final_cost;
    Eigen::VectorXd x;

    // Set the initial position by myself
    if ((m_goal_pos - goal_pos).norm() > 0.5)
    {
        // Use new goal position as the initial value
        m_goal_pos = goal_pos;
        m_goal_pos(2) += 1.0;
        x = m_goal_pos;
    }
    else
    {
        // Use last solution as the initial value
        x = m_curr_solutions[uav_id];
    }
    // m_goal_pos(2) += 0.5;
    // Eigen::VectorXd x(m_goal_pos);

    // Start optimization
    int ret = lbfgs::lbfgs_optimize(x,
                                    final_cost,
                                    costFunction,
                                    nullptr,
                                    monitorProgress,
                                    this,
                                    this->params);

    m_curr_solutions[uav_id] = x;
    m_is_first_solution = false;

    // std::cout << std::setprecision(4)
    //           << "================================" << std::endl
    //           << "L-BFGS Optimization Returned: " << ret << std::endl
    //           << "Minimized Cost: " << final_cost << std::endl
    //           << "Optimal Variables: " << std::endl
    //           << x.transpose() << std::endl;

    ros::Time end = ros::Time::now();
//    ROS_INFO("[optimizer] Optimization for UAV %d: status code %d, used %.5fs\n", SCPs.header.seq, ret, (end - start).toSec());
//    std::cout << x.transpose() << std::endl;
    if (ret != 0) ROS_WARN("[optimizer] Optimization for UAV %d status %d, used %.5fs\n", SCPs.header.seq, ret, (end - start).toSec());

    return x;
}


Eigen::VectorXd StarConvexOptimizer::solveOptimalPoseArray(const std::vector<Agent>& uav_data_array)
{
    int agent_num = uav_data_array.size();
    // judge if reaching goal in fast-planner
    for (int agent_id = 0; agent_id < agent_num; agent_id++) {
        // ignore the agent without missions
        if (uav_data_array[agent_id].SCPs.SCPs.empty()) continue;
        if (!m_has_reached_goal[agent_id]) return m_curr_solution;
    }
    // std::cout << "[debug] has reach goal: ";
    // for (int i = 0; i < agent_num; i++) {
    //     std::cout << m_has_reached_goal[i] << ", ";
    // }
    // std::cout << std::endl;
    memset(m_has_reached_goal, 0, sizeof(m_has_reached_goal));

    m_agents.clear();
    m_agents.resize(agent_num);
    Eigen::VectorXd x(3 * agent_num);
    for (size_t agent_index = 0; agent_index < agent_num; agent_index++) {
        m_agents[agent_index].current_position = uav_data_array[agent_index].current_position;
        m_agents[agent_index].goal_position    = uav_data_array[agent_index].goal_position;

        for (auto polytope : uav_data_array[agent_index].SCPs.SCPs) {
            Polytope curr_polypote = transformStarConvexPolytopeType(polytope);
            m_agents[agent_index].polytopes.push_back(curr_polypote);
        }

        // Set the initial position
        x.segment(3 * agent_index, 3) = m_agents[agent_index].goal_position;
    }

    if (!m_is_first_solution && m_goal_pos == uav_data_array[0].goal_position) {
        if (m_goal_pos != uav_data_array[0].goal_position) {
            m_goal_pos = uav_data_array[0].goal_position;
        }
        else {
            x = m_curr_solution;
        }
    }

    ros::Time start = ros::Time::now();
    double final_cost;
    // // Start optimization
    // int ret = lbfgs::lbfgs_optimize(x,
    //                                 final_cost,
    //                                 costFunctionCentralized,
    //                                 nullptr,
    //                                 monitorProgress,
    //                                 this,
    //                                 this->params);

    // Start optimization. Silent
    int ret = lbfgs::lbfgs_optimize(x,
                                    final_cost,
                                    costFunctionCentralized,
                                    nullptr,
                                    nullptr,
                                    this,
                                    this->params);

    // std::cout << std::setprecision(4)
    //           << "================================" << std::endl
    //           << "L-BFGS Optimization Returned: " << ret << std::endl
    //           << "Minimized Cost: " << final_cost << std::endl
    //           << "Optimal Variables: " << std::endl
    //           << x.transpose() << std::endl;

    ros::Time end = ros::Time::now();
    if (ret != 0 || ret != 1) ROS_WARN("[optimizer] Optimization for all UAVs status %d, used %.5fs\n", ret, (end - start).toSec());

    m_curr_solution = x;
    // m_is_first_solution = false;
    // std::cout << "[debug] current solution: " << m_curr_solution.transpose() << std::endl;
    return x;
}


void StarConvexOptimizer::goalPublish(const Eigen::Vector3d& x)
{

    geometry_msgs::PointStamped msg;
    msg.header.frame_id = std::string("world");
    msg.header.stamp = ros::Time::now();

    // Publish the goal point
    // msg.point.x = x(0) + m_center(0);
    // msg.point.y = x(1) + m_center(1);
    // msg.point.z = x(2) + m_center(2);
    msg.point.x = x(0);
    msg.point.y = x(1);
    msg.point.z = x(2);

    m_goal_pub.publish(msg);

    // // Publish the flipped goal point
    // Eigen::Vector3d x_flip = pointTransform(x - m_polytopes[0].center);
    // msg.point.x = x_flip(0) + m_polytopes[0].center(0);
    // msg.point.y = x_flip(1) + m_polytopes[0].center(1);
    // msg.point.z = x_flip(2) + m_polytopes[0].center(2);

    // m_flipped_goal_pub.publish(msg);

    // Publish the current position
    msg.point.x = m_current_pos(0);
    msg.point.y = m_current_pos(1);
    msg.point.z = m_current_pos(2);

    m_cur_pos_pub.publish(msg);

}


/* Function heightConstraint
calculates the height constraint of a variable. */
double StarConvexOptimizer::heightConstraint(const Eigen::Vector3d& x)
{

    // std::cout << m_height_min << std::endl;
    return 0 < m_height_min - x(2) ? pow(m_height_min - x(2), 2) : 0;

}


double StarConvexOptimizer::gradOfHeight(const Eigen::Vector3d& x)
{

    return 0 < m_height_min - x(2) ? 2 * m_lambda * (x(2) - m_height_min) : 0;
}


/* Function starConvexConstraint
calculates the star convex constraint of a variable in DISTRIBUTED optimization. */
double StarConvexOptimizer::starConvexConstraint(const Eigen::Vector3d& x, int index)
{

    // Operate point transformation
    Eigen::Vector3d x_cap = pointTransform(x - m_polytopes[index].center);
    // x_cap += m_polytopes[index].center; // 为什么不给人加回去？？因为前面有人负重前行

    // Calculate the distances from x_cap to all polygons
    int n = m_polytopes[index].polygons.size();
    // Eigen::ArrayXd distances(n);
    Eigen::Array<long double, -1, 1> distances(n);
    for (int i = 0; i < n; i++)
    {
        distances(i) = getPoint2PlaneDistance(x_cap, m_polytopes[index].polygons[i], m_polytopes[index].center);
    }
    // if (distances(0) != distances(0)) {
    //     std::cout << distances.transpose() << std::endl;
    //     std::cout << x_cap.transpose() << std::endl;
    //     std::cout << x.transpose() << std::endl;
    //     std::cout << m_polytopes[index].center.transpose() << std::endl;
    //     // while (1);
    // }

    double J_constraint = logSumExpCap(distances);

    if (J_constraint > 0)
    {
        return J_constraint;
    }
    else
    {
        return 0;
    }

}


/* Function starConvexConstraint
calculates the star convex constraint of a variable in CENTRALIZED optimization. */
double StarConvexOptimizer::starConvexConstraint(const Eigen::Vector3d& x, int agent_index, int neighbor_index) {
    // Operate point transformation
    Eigen::Vector3d x_cap = pointTransform(x - m_agents[agent_index].polytopes[neighbor_index].center);
    // x_cap += m_polytopes[index].center; // 为什么不给人加回去？？因为前面有人负重前行

    // Calculate the distances from x_cap to all polygons
    int n = m_agents[agent_index].polytopes[neighbor_index].polygons.size();
    // Eigen::ArrayXd distances(n);
    Eigen::Array<long double, -1, 1> distances(n);
    for (int i = 0; i < n; i++)
    {
        distances(i) = getPoint2PlaneDistance(x_cap, 
                                              m_agents[agent_index].polytopes[neighbor_index].polygons[i], 
                                              m_agents[agent_index].polytopes[neighbor_index].center);
    }
    // if (distances(0) != distances(0)) {
    //     std::cout << distances.transpose() << std::endl;
    //     std::cout << x_cap.transpose() << std::endl;
    //     std::cout << x.transpose() << std::endl;
    //     std::cout << m_polytopes[index].center.transpose() << std::endl;
    //     // while (1);
    // }

    double J_constraint = logSumExpCap(distances);

    if (J_constraint > 0)
    {
        return J_constraint;
    }
    else
    {
        return 0;
    }
}


/* Function gradOfConstraintTerm
calculates the gradient of the constraint term of a variable in DISTRIBUTED optimization. */
Eigen::Vector3d StarConvexOptimizer::gradOfConstraintTerm(const Eigen::Vector3d& x, double J_constraint, int index)
{

    // Operate point transformation
    Eigen::Vector3d x_cap = pointTransform(x - m_polytopes[index].center);
    // x_cap += m_polytopes[index].center; // 为什么不给人加回去？？
    // Eigen::Vector3d x_cap = pointTransform(x);

    int n = m_polytopes[index].polygons.size();
    Eigen::Matrix<double, -1, 3> outer_normal_factors(n, 3);
    Eigen::ArrayXd distances(n);
    for (int i = 0; i < n; i++)
    {
        Eigen::Vector3d center_tmp = m_polytopes[index].center;
        outer_normal_factors.block(i, 0, 1, 3) = getOuterNormalFactor(m_polytopes[index].polygons[i], center_tmp).transpose();
        distances(i) = getPoint2PlaneDistance(x_cap, m_polytopes[index].polygons[i], center_tmp);
    }

    Eigen::Vector3d g_scp = Eigen::Vector3d::Zero();
    if (J_constraint > 0)
    {
        g_scp = (3 * m_lambda * std::pow(J_constraint, 2) *
                (m_alpha * distances).exp().matrix().transpose() * outer_normal_factors /
                (m_alpha * distances).exp().sum());

        // Eigen::VectorXd::Index row, col;
        // double d_max = distances.matrix().maxCoeff(&row, &col);
        // g_scp = 3 * m_lambda * std::pow(J_constraint, 2) *
        //         outer_normal_factors.block(row, 0, 1, 3).transpose();
    }

    // for test
    // std::cout << "MAXIMUM DISTANCE: " << distances.maxCoeff() << std::endl;
    // std::cout << "APPROXIMATE MAXIMUM DISTANCE: " << (std::log((m_alpha * distances).exp().sum()) / m_alpha) << std::endl;
    // std::cout << "GRADIENT OF SCP: " << g_scp.transpose() << std::endl;
    // for (unsigned int i = 0; i < distances.size(); i++)
    // {
    //     std::cout << std::log
    // }

    return g_scp;

}


/* Function gradOfConstraintTerm
calculates the gradient of the constraint term of a variable in CENTRALIZED optimization. */
Eigen::Vector3d StarConvexOptimizer::gradOfConstraintTerm(const Eigen::Vector3d& x, double J_constraint, 
                                                          int agent_index, int neighbor_index)
{

    // Operate point transformation
    Eigen::Vector3d x_cap = pointTransform(x - m_agents[agent_index].polytopes[neighbor_index].center);
    // x_cap += m_polytopes[index].center; // 为什么不给人加回去？？
    // Eigen::Vector3d x_cap = pointTransform(x);

    int n = m_agents[agent_index].polytopes[neighbor_index].polygons.size();
    Eigen::Matrix<double, -1, 3> outer_normal_factors(n, 3);
    Eigen::ArrayXd distances(n);
    for (int i = 0; i < n; i++)
    {
        Eigen::Vector3d center_tmp = m_agents[agent_index].polytopes[neighbor_index].center;
        outer_normal_factors.block(i, 0, 1, 3) = getOuterNormalFactor(m_agents[agent_index].polytopes[neighbor_index].polygons[i], center_tmp).transpose();
        distances(i) = getPoint2PlaneDistance(x_cap, m_agents[agent_index].polytopes[neighbor_index].polygons[i], center_tmp);
    }

    Eigen::Vector3d g_scp = Eigen::Vector3d::Zero();
    if (J_constraint > 0)
    {
        g_scp = (3 * m_lambda * std::pow(J_constraint, 2) *
                (m_alpha * distances).exp().matrix().transpose() * outer_normal_factors /
                (m_alpha * distances).exp().sum());

        // Eigen::VectorXd::Index row, col;
        // double d_max = distances.matrix().maxCoeff(&row, &col);
        // g_scp = 3 * m_lambda * std::pow(J_constraint, 2) *
        //         outer_normal_factors.block(row, 0, 1, 3).transpose();
    }

    // for test
    // std::cout << "MAXIMUM DISTANCE: " << distances.maxCoeff() << std::endl;
    // std::cout << "APPROXIMATE MAXIMUM DISTANCE: " << (std::log((m_alpha * distances).exp().sum()) / m_alpha) << std::endl;
    // std::cout << "GRADIENT OF SCP: " << g_scp.transpose() << std::endl;
    // for (unsigned int i = 0; i < distances.size(); i++)
    // {
    //     std::cout << std::log
    // }

    return g_scp;

}


/* Function pointTransform
operates point transformation that flips the point x to outside of the
sphere boundary, whose radius is m_r_ball. */
Eigen::Vector3d StarConvexOptimizer::pointTransform(const Eigen::Vector3d& x)
{

    return x + 2 * (m_r_ball - x.norm()) * x.normalized();

}


/* Function getOuterNormalFactor
calculates the outer normal factor of a plane using 3 points, 
which are sorted counterclockwise. */
inline Eigen::Vector3d StarConvexOptimizer::getOuterNormalFactor(const std::vector<Eigen::Vector3d>& plane, const Eigen::Vector3d& center)
{

    Eigen::Vector3d x, y, n;
    x = plane[1] - plane[0];
    y = plane[2] - plane[0];
    n = x.cross(y);

    // check if it is outer
    // if (n.dot(plane[0] - center) < 0)
    if (n.dot(plane[0]) < 0)
    {
        n = -n;
    }

    return n.normalized();

}


/* Function getPoint2PlaneDistance
calculates the signed distance from a point to a plane. */
inline double StarConvexOptimizer::getPoint2PlaneDistance(const Eigen::Vector3d& point, 
                                                          const std::vector<Eigen::Vector3d>& plane, 
                                                          const Eigen::Vector3d& center)
{

    return getOuterNormalFactor(plane, center).dot(point - plane[0]);

}


/* Function logSumExpCap
calculates the difference value between the safe margin and the maximum 
of distances. The maximum is approximated using log-sum-exp function. */
double StarConvexOptimizer::logSumExpCap(const Eigen::Array<long double, -1, 1>& distances)
{
    double d_max = std::log((m_alpha * distances).exp().sum()) / m_alpha;
    // double d_max = distances.matrix().maxCoeff();
    // std::cout << "[debug]: " << ans << " " << row << " " << col << std::endl;

    // double d_max = std::log((m_alpha * distances_normalized).exp().sum()) / m_alpha * distances_norm;
    // // std::cout << d_max << std::endl;
    // while (isinf(d_max) || isnan(d_max)) {
    //     // if (isinf(d_max)) ROS_ERROR("[optimizer]: LSE overflow!");
    //     // if (isnan(d_max)) ROS_ERROR("[optimizer]: LSE illegal operation!");
    //     alpha /= 2.0;
    //     d_max = std::log((alpha * distances).exp().sum()) / alpha;
    //     std::cout << distances.transpose() << std::endl;
    //     ROS_ERROR("[optimizer]: dmax: %f!", d_max);
    // }
    if (isinf(d_max)) ROS_ERROR("[optimizer]: LSE overflow!");
    if (isnan(d_max)) ROS_ERROR("[optimizer]: LSE illegal operation!");
    return m_d_min - d_max;

}


/* Function penalty
turns a hard constraint to a soft constraint. */
double StarConvexOptimizer::penalty(double x)
{

    return m_lambda * std::pow(std::max(x, 0.0), 3);

}


int StarConvexOptimizer::run(const Eigen::Vector3d& pos)
{

    double final_cost;
    Eigen::VectorXd x(3);
    m_current_pos = pos;

    // // Set the initial position at the center of SCP
    // for (int i = 0; i < 3; i++)
    // {
    //     x(i) = 0.01;
    // }

    // // Set the initial position at the position of agent
    // for (int i = 0; i < 3; i++)
    // {
    //     x(i) = pos(i) + 0.1;
    // }

    // Set the initial position by myself
    x(0) = 8.0;
    x(1) = 3.0;
    x(2) = 1.0;

    // Set the minimization parameters
    lbfgs::lbfgs_parameter_t params;
    params.g_epsilon = 1.0e-4;
    params.past = 0;
    params.delta = 1.0e-4;
    params.max_linesearch = 8;
    // params.cautious_factor = 1.0e-4;
    // params.f_dec_coeff = 1.0e-6;
    // params.s_curv_coeff = 0.1;

    // // Start optimization
    // int ret = lbfgs::lbfgs_optimize(x,
    //                                 final_cost,
    //                                 costFunction,
    //                                 nullptr,
    //                                 monitorProgress,
    //                                 this,
    //                                 params);
    // Start optimization. Silent
    int ret = lbfgs::lbfgs_optimize(x,
                                    final_cost,
                                    costFunction,
                                    nullptr,
                                    nullptr,
                                    this,
                                    params);

    // std::cout << std::setprecision(4)
    //           << "================================" << std::endl
    //           << "L-BFGS Optimization Returned: " << ret << std::endl
    //           << "Minimized Cost: " << final_cost << std::endl
    //           << "Optimal Variables: " << std::endl
    //           << x.transpose() << std::endl;

    goalPublish(x);

    return ret;

}


/* Function costFunction
calculates the values of the cost function itself 
and the gradients of its variables. */
double StarConvexOptimizer::costFunction(void *instance,
                                         const Eigen::VectorXd &x,
                                         Eigen::VectorXd &g)
{

    StarConvexOptimizer *opt = reinterpret_cast<StarConvexOptimizer *>(instance);
    double fx = 0.0;

    // energy term
    double J_energy = std::pow((opt->m_current_pos - x).norm(), 2);
    // goal term
    double J_goal = std::pow((opt->m_goal_pos - x).norm(), 2);
    // communication term
    double J_comm = 0.0;
    // constraint term
    double J_constraint = opt->heightConstraint(x);
    // the gradient of StarConvexConstraint
    Eigen::Vector3d g_scp = Eigen::Vector3d::Zero();
    g_scp(2) = opt->gradOfHeight(x);
    for (int i = 0; i < opt->m_polytopes.size(); i++)
    {
        J_comm += std::pow((opt->m_polytopes[i].center - x).norm(), 2);
        double constraint_tmp = opt->starConvexConstraint(x, i);
        J_constraint += constraint_tmp;
        g_scp += opt->gradOfConstraintTerm(x, constraint_tmp, i);
    }
    fx += opt->k_energy * J_energy + opt->k_comm * J_comm + opt->k_goal * J_goal + opt->penalty(J_constraint);

    std::cout << "[debug]J_constraint: " << J_constraint << std::endl;

    // the gradient of energy
    Eigen::Vector3d g_energy = 2 * (x - opt->m_current_pos);
    // the gradient of energy
    Eigen::Vector3d g_goal = 2 * (x - opt->m_goal_pos);
    // the gradient of communication
    Eigen::Vector3d g_comm = Eigen::Vector3d::Zero();
    // the gradient of StarConvexConstraint
    // Eigen::Vector3d g_scp = Eigen::Vector3d::Zero();
    // g_scp(2) = opt->gradOfHeight(x);
    for (size_t i = 0; i < opt->m_polytopes.size(); i++)
    {
        g_comm += 2 * (x - opt->m_polytopes[i].center);
        // g_scp += opt->gradOfConstraintTerm(x, J_constraint, i);
    }
    // g_scp.setZero();
    g = opt->k_energy * g_energy + opt->k_comm * g_comm + opt->k_goal * g_goal + g_scp;

    return fx;

}


/* Function costFunctionCentralized
calculates the values of the cost function itself 
and the gradients of its variables. */
double StarConvexOptimizer::costFunctionCentralized(void *instance,
                                         const Eigen::VectorXd &x,
                                         Eigen::VectorXd &g)
{

    StarConvexOptimizer *opt = reinterpret_cast<StarConvexOptimizer *>(instance);
    double fx = 0.0;
    size_t agent_num = opt->m_agents.size();

    double J_energy = 0.0;
    double J_goal = 0.0;
    double J_comm = 0.0;
    double J_constraint = 0.0;
    Eigen::VectorXd g_energy(3 * agent_num);
    Eigen::VectorXd g_goal(3 * agent_num);
    Eigen::VectorXd g_comm(3 * agent_num);
    g_comm.setZero();
    Eigen::VectorXd g_scp(3 * agent_num);
    g_scp.setZero();

    for (size_t agent_index = 0; agent_index < agent_num; agent_index++) {
        Eigen::Vector3d x_tmp = x.segment(3*agent_index, 3);
        Agent agent = opt->m_agents[agent_index];

        J_energy += std::pow((agent.current_position - x_tmp).norm(), 2);
        g_energy.segment(3*agent_index, 3) = 2 * (x_tmp - agent.current_position);

        for (size_t neighbor_index = 0; neighbor_index < agent.polytopes.size(); ++neighbor_index) {
            auto& neighbor = agent.polytopes[neighbor_index];
            if (neighbor.name_id[0] == 'u') {
                int neighbor_id = std::stoi(neighbor.name_id.substr(4));
                Eigen::Vector3d x_neighbor = x.segment(3*neighbor_id, 3);

                J_comm += std::pow((x_neighbor - x_tmp).norm(), 2);
                g_comm.segment(3*agent_index, 3) += 2 * (x_tmp - x_neighbor);
            }
            else {
                J_comm += std::pow((neighbor.center - x_tmp).norm(), 2);
                g_comm.segment(3*agent_index, 3) += 2 * (x_tmp - neighbor.center);
            }

            double constraint_tmp = opt->starConvexConstraint(x_tmp, agent_index, neighbor_index);
            // if (constraint_tmp > 5.0) penalty = 5.0;
            J_constraint += constraint_tmp;
            g_scp.segment(3*agent_index, 3) += opt->gradOfConstraintTerm(x_tmp, constraint_tmp, agent_index, neighbor_index);
        }

        J_goal   += std::pow((agent.goal_position    - x_tmp).norm(), 2);
        g_goal.segment(3*agent_index, 3)   = 2 * (x_tmp - agent.goal_position);
    }

    J_constraint = 0.0;
    g_scp.setZero();
    fx = opt->k_energy * J_energy + opt->k_comm * J_comm + opt->k_goal * J_goal + opt->penalty(J_constraint);
    g  = opt->k_energy * g_energy + opt->k_comm * g_comm + opt->k_goal * g_goal + g_scp;

    // std::cout << "[debug]J_constraint: " << J_constraint << std::endl;

    return fx;

}


/* Function monitorProgress
monitors the progress of the optimization. */
int StarConvexOptimizer::monitorProgress(void *instance,
                                         const Eigen::VectorXd &x,
                                         const Eigen::VectorXd &g,
                                         const double fx,
                                         const double step,
                                         const int k,
                                         const int ls)
{
    // return 0; // IF NEED MONITOR, UNCOMMENT
    std::cout << std::setprecision(4)
                  << "================================" << std::endl
                  << "Iteration: " << k << std::endl
                  << "Function Value: " << fx << std::endl
                  << "Gradient: " << g.transpose() << std::endl
                  << "Variables: " << std::endl
                  << x.transpose() << std::endl;

    return 0;

}


// int main(int argc, char **argv)
// {

//     ros::init(argc, argv, "optimizer");
//     ros::NodeHandle nh("~");
//     StarConvexOptimizer opt;
//     opt.init(nh);
    
//     ros::spin();

//     return 0;

// }