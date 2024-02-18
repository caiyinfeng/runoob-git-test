#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
//#include "ros/ros.h"
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

void chassis_set_speed(short v_l, short v_r)
{
    short l_v = -1.0 * v_l;
    short r_v = -1.0 * v_r;
    printf("speed_msg.r_v: %d ,speed_msg.l_v: %d \n", r_v, l_v);
}
int main()
{
    double cam_angle_value = 5;
    double cam_length = 88;
    short v_max = 150;           //速度设定上限值
    short v_min = 50;            //速度设定下限值
    std::string cam_mode = "B2"; // Bl,Br,B2,C1,None
#if 1
    if (cam_angle_value < 4 && cam_angle_value > -4)
    {
        chassis_set_speed(-100, -100);
    }
    else if (cam_angle_value > 4)
    {
        short v_r = -100;
        short v_l = (short)((abs(cam_length - 1) * v_r) / 45);
        if (abs(v_l) >= v_max)
            v_l = -v_max;
        if (abs(v_l) <= v_min)
            v_l = -v_min;
        chassis_set_speed(v_r, v_l);
    }
    else if (cam_angle_value < -4)
    {
        short v_r = -100;
        short v_l = (short)((abs(cam_length - 1) * v_r) / 45);
        if (abs(v_l) >= v_max)
            v_l = -v_max;
        if (abs(v_l) <= v_min)
            v_l = -v_min;
        chassis_set_speed(v_l, v_r);
    }
#endif
#if 0
    if (cam_angle_value > 0)
    {
        //ROS_INFO("go in angle>0");
        // qDebug() << "go in angle>0";
        short v_l = -100;
        short v_r = (short)((abs(cam_length - 1) * v_l) / 45);
        // ROS_INFO("cam_length:%f,vr:%f",cam_length,v_r);
        if (abs(v_r) >= v_max)
            v_r = -v_max;
        if (abs(v_r) <= v_min)
            v_r = -v_min;
        // ROS_INFO("v_l: %d ,v_r: %d", v_l, v_r);
        //  qDebug() << "v_l:" << v_l << "v_r:" << v_r;
        if ((cam_mode.find("B2") != std::string::npos) || (cam_mode.find("C1") != std::string::npos))
        {
            chassis_set_speed(v_r, v_l);
            // qDebug() << "v_l:" << v_l << "v_r:" << v_r;
            // ROS_INFO("v_l: %d ,v_r: %d", v_l, v_r);
        }
        else if (cam_mode.find("BR") != std::string::npos)
        {
            chassis_set_speed(v_l, v_r);
            //ROS_INFO_STREAM("cam_mode 1:" << cam_mode);

            // qDebug() << "cam_mode 1:" << cam_mode;
        }
        else if (cam_mode.find("BL") != std::string::npos)
        {
            chassis_set_speed(v_r, v_l);
            //ROS_INFO_STREAM("cam_mode 2:" << cam_mode);
            // qDebug() << "cam_mode 2:" << cam_mode;
        }
    }
    else if (cam_angle_value < 0)
    {
        //ROS_INFO("go in angle<0");

        // qDebug() << "go in angle<0";
        short v_r = -100;
        short v_l = (short)((abs(cam_length - 1) * v_r) / 45);

        if (abs(v_l) >= v_max)
            v_l = -v_max;
        if (abs(v_l) <= v_min)
            v_l = -v_min;
        // ROS_INFO("v_l: %d ,v_r: %d", v_l, v_r);
        //  qDebug() << "v_l:" << v_l << "v_r:" << v_r;
        if ((cam_mode.find("B2") != std::string::npos) || (cam_mode.find("C1") != std::string::npos))
        {
            chassis_set_speed(v_r, v_l);
            // ROS_INFO("v_l: %d ,v_r: %d", v_l, v_r);
        }
        else if (cam_mode.find("BL") != std::string::npos)
        {
            chassis_set_speed(v_l, v_r);
            //ROS_INFO_STREAM("cam_mode 3:" << cam_mode);
        }
        else if (cam_mode.find("BR") != std::string::npos)
        {
            chassis_set_speed(v_r, v_l);
            //ROS_INFO_STREAM("cam_mode 7:" << cam_mode);
        }
    }
#endif

}