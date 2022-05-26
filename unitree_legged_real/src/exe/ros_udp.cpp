#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <unitree_legged_msgs/HighCmd.h>
#include <unitree_legged_msgs/HighState.h>
#include <unitree_legged_msgs/LowCmd.h>
#include <unitree_legged_msgs/LowState.h>
#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include "convert.h"
#include <chrono>
#include <pthread.h>

Custom custom;

ros::Subscriber sub_cmd_vel;
ros::Subscriber sub_high;
ros::Subscriber sub_low;

ros::Publisher pub_high;
ros::Publisher pub_low;

long high_count = 0;
long low_count = 0;

bool floatSimilarTo(float a, float b, float diff)
{
  float difference = a - b;

  return (difference < diff) && (-difference < diff);
}

void cmdVelCallback(const geometry_msgs::Twist::ConstPtr &vel_msg)
{
    //printf("tomeu\n");

    unitree_legged_msgs::HighCmd cmd_vel;

    float vel_x = vel_msg -> linear.x;
    float vel_y = vel_msg -> linear.y;
    float yaw = vel_msg -> angular.z;

    cmd_vel.head[0] = 0xFE;
    cmd_vel.head[1] = 0xEF;
    cmd_vel.levelFlag = 0;
    cmd_vel.mode = 0;
    cmd_vel.gaitType = 0;
    cmd_vel.speedLevel = 0;
    cmd_vel.footRaiseHeight = 0;
    cmd_vel.bodyHeight = 0;
    cmd_vel.euler[0] = 0;
    cmd_vel.euler[1] = 0;
    cmd_vel.euler[2] = 0;
    cmd_vel.velocity[0] = 0.0f;
    cmd_vel.velocity[1] = 0.0f;
    cmd_vel.yawSpeed = 0.0f;
    cmd_vel.reserve = 0;

    if(floatSimilarTo(vel_x, 0.0, 0.001) && floatSimilarTo(vel_y, 0.0, 0.001) && floatSimilarTo(yaw, 0.0, 0.001))
    {
        cmd_vel.mode = 1;
        cmd_vel.bodyHeight = 0.0;
        cmd_vel.velocity[0] = 0.0f;
        cmd_vel.velocity[1] = 0.0f;
        cmd_vel.yawSpeed = 0.0f;
        printf("Robot stops\n");

    } else {
        
        if(floatSimilarTo(yaw, 0.0, 0.001)){ // Linear
            cmd_vel.mode = 2;
            cmd_vel.gaitType = 2;
            cmd_vel.velocity[0] = (float)vel_x;
            cmd_vel.velocity[1] = (float)vel_y;
            cmd_vel.yawSpeed = 0.0f;
            cmd_vel.footRaiseHeight = 0.1;
            printf("Robot moves\n");
        } else {
            cmd_vel.mode = 2;
            cmd_vel.gaitType = 2;
            cmd_vel.velocity[0] = 0.4f/*float(0.2*yaw)*/;
            cmd_vel.velocity[1] = 0.0f;
            cmd_vel.yawSpeed = (float)yaw;
            cmd_vel.footRaiseHeight = 0.1;
            printf("Robot turns\n");
        }
        
        
    }   

    custom.cmdAssignment(cmd_vel);

    unitree_legged_msgs::HighState high_state_ros;
    //printf("velocity: %f\n", custom.high_cmd.velocity[0]);

    custom.stateAssignment(high_state_ros);

    pub_high.publish(high_state_ros);

    //printf("highCmdCallback ending !\t%ld\n\n", ::high_count++);
}

void highCmdCallback(const unitree_legged_msgs::HighCmd::ConstPtr &msg)
{
    //printf("highCmdCallback is running !\t%ld\n", ::high_count);

    custom.cmdAssignment(msg);

    unitree_legged_msgs::HighState high_state_ros;

    custom.stateAssignment(high_state_ros);

    pub_high.publish(high_state_ros);

    //printf("highCmdCallback ending !\t%ld\n\n", ::high_count++);
}

void lowCmdCallback(const unitree_legged_msgs::LowCmd::ConstPtr &msg)
{

    printf("lowCmdCallback is running !\t%ld\n", low_count);

    custom.cmdAssignment(msg);

    unitree_legged_msgs::LowState low_state_ros;

    custom.stateAssignment(low_state_ros);

    pub_low.publish(low_state_ros);

    printf("lowCmdCallback ending!\t%ld\n\n", ::low_count++);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ros_udp");

    ros::NodeHandle nh;

    if (strcasecmp(argv[1], "LOWLEVEL") == 0)
    {
        sub_low = nh.subscribe("low_cmd", 1, lowCmdCallback);
        pub_low = nh.advertise<unitree_legged_msgs::LowState>("low_state", 1);

        LoopFunc loop_udpSend("low_udp_send", 0.002, 3, boost::bind(&Custom::lowUdpSend, &custom));
        LoopFunc loop_udpRecv("low_udp_recv", 0.002, 3, boost::bind(&Custom::lowUdpRecv, &custom));

        loop_udpSend.start();
        loop_udpRecv.start();

        ros::spin();

        printf("low level runing!\n");
    }
    else if (strcasecmp(argv[1], "HIGHLEVEL") == 0)
    {
        sub_cmd_vel = nh.subscribe("cmd_vel", 10, cmdVelCallback);
        sub_high = nh.subscribe("high_cmd", 1, highCmdCallback);
        pub_high = nh.advertise<unitree_legged_msgs::HighState>("high_state", 1);

        LoopFunc loop_udpSend("high_udp_send", 0.002, 3, boost::bind(&Custom::highUdpSend, &custom));
        LoopFunc loop_udpRecv("high_udp_recv", 0.002, 3, boost::bind(&Custom::highUdpRecv, &custom));

        loop_udpSend.start();
        loop_udpRecv.start();

        ros::spin();

        printf("high level runing!\n");
    }
    else
    {
        std::cout << "Control level name error! Can only be highlevel or lowlevel(not case sensitive)" << std::endl;
        exit(-1);
    }

    return 0;
}
