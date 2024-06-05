/* This file controls starting and resetting of episodes
 * which means reset locations of targets and UAVs,
 * and send message to tell other nodes
 * */

#include <ros/ros.h>
#include <std_msgs/UInt32.h>
#include <termios.h>
#include <sensor_msgs/PointCloud2.h>

#include "backward-cpp/backward.hpp"

int getCharNoInterrupt()
{
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);           // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);                 // disable buffering
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

    int c = getchar();  // read character (non-blocking)

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
    return c;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "commander");
    ros::NodeHandle n("~");
    // ros::Duration(1).sleep();  // Waiting for other nodes
    ros::Publisher commander_pub = n.advertise<std_msgs::UInt32>("episode_seq", 1, true);

    std_msgs::UInt32 episode_seq;
    episode_seq.data = 1;
    while (ros::ok())
    {
        ROS_INFO("Started episode %d\n", episode_seq.data);
        commander_pub.publish(episode_seq);

        // Waiting predefined duration until next episode
        // ROS_INFO("Started episode %d, duration %f\n", episode_seq.data, n.param("episode_len", 5.0));
        // ++episode_seq.data;
        // ros::Duration(n.param("episode_len", 5.0)).sleep();

        // Command line control to next episode
        int c = getchar();
//        int c = getchar_unlocked();
//        int c = getCharNoInterrupt();   // call your non-blocking input function
        while (c == '\n') c = getchar();
        if (c == 'n') {
            ++episode_seq.data;
            // ROS_INFO("Finished episode %d, start next\n", episode_seq.data);
        }
    }

    return 0;
}
