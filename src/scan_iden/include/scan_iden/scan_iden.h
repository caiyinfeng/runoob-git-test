#ifndef __SCAN_IDEN_H__
#define __SCAN_IDEN_H__
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/PointStamped.h"
typedef struct Point{
    double x;
    double y;
}Point;
class Scan_Iden
{
public:
    Scan_Iden(ros::NodeHandle& nh, ros::NodeHandle& pnh);
    ~Scan_Iden(){};

    void init();
    void laser_callback(sensor_msgs::LaserScan::ConstPtr msg);
    Point laser_segmentation2(std::vector<Point> point);//支架跟檩条
    Point laser_segmentation1(std::vector<Point> point);//檩条
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    ros::Subscriber laser_sub;
    sensor_msgs::LaserScan laser;
    ros::Publisher laser_pub;
    ros::Publisher point_change;
    double save_x=1.30;
};


#endif