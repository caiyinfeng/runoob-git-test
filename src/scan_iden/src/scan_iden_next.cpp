#include "scan_iden/scan_iden.h"
#include <inttypes.h>
#include "math.h"
#include <algorithm>
Point Scan_Iden::laser_segmentation2(std::vector<Point> point)
{
    std::vector<double> dx, dy, dx_qian10, dy_qian10, dx_hou10, dy_hou10;
    Point point_chu;
    std::vector<Point> point_jin_qian,point_jin_hou;
    double qian_dis,hou_dis;
    for (int i = 0; i < point.size(); i++)
    {
        if (i < 15)
        {
            dx_qian10.push_back(point[i].x);
            dy_qian10.push_back(point[i].y);
            point_chu.x=point[i].x;
            point_chu.y=point[i].y;
            point_jin_qian.push_back(point_chu);
        }
        else if (i > point.size() - 15)
        {
            dx_hou10.push_back(point[i].x);
            dy_hou10.push_back(point[i].y);
            point_chu.x=point[i].x;
            point_chu.y=point[i].y;
            point_jin_hou.push_back(point_chu);
        }
        else
        {
            dx.push_back(point[i].x);
            dy.push_back(point[i].y);
        }
    }
    point_chu=laser_segmentation1(point_jin_qian);
    Point laser_seg_hou=laser_segmentation1(point_jin_hou);            
    point_chu=(laser_seg_hou.y<point_chu.y&&laser_seg_hou.y)||point_chu.y==0?laser_seg_hou:point_chu;              
    if(!point_chu.x){
        point_chu.x=0;
        point_chu.y=0;
    }
    return point_chu;
}
Scan_Iden::Scan_Iden(ros::NodeHandle &nh, ros::NodeHandle &pnh) : nh_(nh), pnh_(pnh)
{
    init();
}
void Scan_Iden::init()
{
    laser_sub = nh_.subscribe("/scan1", 10, &Scan_Iden::laser_callback, this);
    laser_pub = nh_.advertise<sensor_msgs::LaserScan>("/scan_change1", 10);
    point_change = nh_.advertise<geometry_msgs::PointStamped>("/point_change1", 10, true);
}

void Scan_Iden::laser_callback(sensor_msgs::LaserScan::ConstPtr msg)
{
    sensor_msgs::LaserScan change;
    change.header = msg->header;
    change.angle_increment = msg->angle_increment;
    change.angle_max = msg->angle_max;
    change.angle_min = msg->angle_min;
    change.intensities = msg->intensities;
    change.range_max = msg->range_max;
    change.range_min = msg->range_min;
    change.scan_time = msg->scan_time;
    change.time_increment = msg->time_increment;
    std::vector<float> changes(msg->ranges.size() + 1, NAN);
    double x_qian=0, y_qian=0, x_save=0, y_save=0; //
    int count1 = 0, count2 = 0, count3 = 0;
    int save_i = 0, dis_more_i = 0;
    bool change_line = false;
    bool dis_more = false;
    bool Photovoltaic_Panels = false;
    bool point_clean=false;
    Point Photovoltaic_Panels_Point;
    geometry_msgs::PointStamped Purlin_Point;
    std::vector<double> Photovoltaic_Panels_x, Photovoltaic_Panels_y;
    std::vector<Point> point;
    std::vector<std::vector<Point>> save_points;
    for (int i = 0.1 * msg->ranges.size(); i <= msg->ranges.size(); ++i)
    {
        if (i - save_i == 11 || i == msg->ranges.size() || count3 == 4||point_clean)
        {
            std::vector<Point> point_save;
            if (point.size() > 10)
            {
                save_points.push_back(point);
                std::cout << "point:" << point.size() << std::endl;
            }
            if (count3 == 4)
            {
                dis_more = false;
                if (point.size() > 3)
                {
                    point_save=prev_vector(point,3);
                }
            }
            count3 = 0;
            point.clear();
            point = point_save;
            Photovoltaic_Panels_x.clear();
            Photovoltaic_Panels_y.clear();
            Photovoltaic_Panels = false;
            if(point_clean){
                changes[i] = msg->ranges[i];
                Point corner_point;
                corner_point.x = x_qian;
                corner_point.y = y_qian;
                point.push_back(corner_point);
            }
            point_clean=false;
            point_save.clear();
            x_qian = 0;
            y_qian = 0;
        }
        if (msg->ranges[i] > 1.6)
        {
            changes[i] = NAN;
        }
        else if (msg->ranges[i] > 0.3)
        {
            count1++;
            double angle = msg->angle_min + msg->angle_increment * (i - 1);
            double x = msg->ranges[i] * cos(angle), y = msg->ranges[i] * sin(angle);
            if (!x_qian && !y_qian)
            {
                x_qian = x;
                y_qian = y;
                save_i = i;
                changes[i] = msg->ranges[i];
                Point corner_point;
                corner_point.x = x;
                corner_point.y = y;
                point.push_back(corner_point);
                continue;
            }
            double dis = (x - x_qian) * (x - x_qian) + (y - y_qian) * (y - y_qian); // 求2点之间的距离
            if(dis>0.08*0.08){point_clean=true;
                std::cout << "point:" << point.size() << std::endl;
                ROS_INFO("point_clean");
                x_qian = x;
                y_qian = y;
                save_i = i;
                continue;
            }
            if (dis <= 0.02 * 0.02 && i - save_i < 4)
            {
                Photovoltaic_Panels_x.push_back(x);
                Photovoltaic_Panels_y.push_back(y);
                if (Photovoltaic_Panels == true)
                {
                    Photovoltaic_Panels_Point.x = std::min(Photovoltaic_Panels_Point.x, x);
                    Photovoltaic_Panels_Point.y = std::min(Photovoltaic_Panels_Point.y, y);
                    continue;
                }
            }
            else if (Photovoltaic_Panels_x.size() < 100 && i - save_i > 4)
            {
                Photovoltaic_Panels_x.clear();
                Photovoltaic_Panels_y.clear();
            }
            if (i - save_i > 6 && Photovoltaic_Panels)
                break;
            if (Photovoltaic_Panels_x.size() > 100)
            {
                std::vector<double> point_save_x=prev_vector(Photovoltaic_Panels_x,15), point_save_y=prev_vector(Photovoltaic_Panels_y,15);
                std::vector<double> result;
                CeresLineFit(point_save_x, point_save_y, point_save_y.size(), result);
                double k = result[0], d = result[1];
                result.clear();
                CeresLineFit(Photovoltaic_Panels_x, Photovoltaic_Panels_y, Photovoltaic_Panels_y.size(), result);
                double s_hou = atan(fabs(k - result[0]) / (1 + k * result[0])) * 90 / 1.57;
                k = result[0], d = result[1];
                point_save_x.clear();point_save_y.clear();
                point_save_x.insert(point_save_x.begin(),Photovoltaic_Panels_x.begin(),Photovoltaic_Panels_x.begin()+15);
                point_save_y.insert(point_save_y.begin(),Photovoltaic_Panels_y.begin(),Photovoltaic_Panels_y.begin()+15);
                result.clear();
                CeresLineFit(point_save_x, point_save_y, point_save_y.size(), result);
                double s_qian=atan(fabs(k - result[0]) / (1 + k * result[0])) * 90 / 1.57;
                if (abs(s_hou) < 15&&abs(s_qian) < 15&&k<-0.3&&k>-2&&save_points.size()<=2)
                {
                    Photovoltaic_Panels = true;
                    if (Photovoltaic_Panels_x[0] < Photovoltaic_Panels_x.back())
                    {
                        Photovoltaic_Panels_Point.x = Photovoltaic_Panels_x[0];
                        Photovoltaic_Panels_Point.y = Photovoltaic_Panels_y[0];
                        break;
                    }
                    else
                    {
                        Photovoltaic_Panels_Point.x = Photovoltaic_Panels_x.back();
                        Photovoltaic_Panels_Point.y = Photovoltaic_Panels_y.back();
                    }
                }
            }
            if (dis <= 0.03 * 0.03 && i - save_i <= 10 && y < 0.5 * x && y > -0.5 * x)
            { //+-26度
                count2++;
                changes[i] = msg->ranges[i];
                Point corner_point;
                corner_point.x = x;
                corner_point.y = y;
                point.push_back(corner_point);
            }
            else if (dis > 0.03 * 0.03)
            {
                dis_more = true;
                if (i - dis_more_i >= 1 && i - dis_more_i < 4)
                {
                    count3 = 0;
                    if ((x - x_save) * (x - x_save) + (y - y_save) * (y - y_save) < 0.04 * 0.04)
                    {
                        changes[i] = msg->ranges[i];
                        Point corner_point;
                        corner_point.x = x;
                        corner_point.y = y;
                        point.push_back(corner_point);
                    }else{
                        changes[i] = msg->ranges[i];
                        Point corner_point;
                        corner_point.x = x;
                        corner_point.y = y;
                        point.pop_back();
                        if(point.size()) point.pop_back();
                        point.push_back(corner_point);
                    }
                }
                x_save = x_qian;
                y_save = y_qian;
                dis_more_i = i;
            }
            if (dis_more == true)
            {
                double dis_save = (x - x_save) * (x - x_save) + (y - y_save) * (y - y_save);
                //std::cout << "dis_save:" << dis_save<< std::endl;
                //std::cout << "x_save:" << x_save<<" y_save:"<<y_save<< std::endl;
                if (dis_save > 0.04 * 0.04)
                {
                    count3++;
                }else{
                    dis_more=false;
                }
            }
            save_i = i;
            x_qian = x;
            y_qian = y;
        }

    }
    change.ranges = changes;
    laser_pub.publish(change);
    Purlin_Point.header = msg->header;
    Purlin_Point.point.y=1000;
    if (Photovoltaic_Panels)
    {
        ROS_INFO("Photovoltaic_Panels");
        Purlin_Point.point.x = Photovoltaic_Panels_Point.x+0.3 ;
        Purlin_Point.point.y = Photovoltaic_Panels_Point.y- 0.28;
        if(abs(save_x-Purlin_Point.point.x)>0.1) Purlin_Point.point.x=save_x;
        Photovoltaic_Panels = false;
    }
    else
    {
        for (std::vector<Point> points : save_points)
        {
            Point point_chu;
            if (points.size() > 24)
            {
                point_chu=laser_segmentation2(points);
                ROS_INFO("point_chu.x:%2f,point_chu.y:%2f",point_chu.x,point_chu.y);
                Purlin_Point.point.x = point_chu.x != 0 &&abs(point_chu.x-save_x)<0.20&&point_chu.y<Purlin_Point.point.y? point_chu.x : Purlin_Point.point.x;
                Purlin_Point.point.y = point_chu.x != 0 &&abs(point_chu.x-save_x)<0.20&&point_chu.y<Purlin_Point.point.y? point_chu.y : Purlin_Point.point.y;
            }
            else if (points.size() <=24&&save_points.size()>0)
            {
                point_chu=laser_segmentation1(points);
                ROS_INFO("point_chu.x:%2f,point_chu.y:%2f",point_chu.x,point_chu.y);
                Purlin_Point.point.x = point_chu.x != 0&&abs(point_chu.x-save_x)<0.20&&point_chu.y<Purlin_Point.point.y? point_chu.x : Purlin_Point.point.x;
                Purlin_Point.point.y = point_chu.x != 0&&abs(point_chu.x-save_x)<0.20&&point_chu.y<Purlin_Point.point.y? point_chu.y : Purlin_Point.point.y;
            }
        }
    }
    std::cout << "save_points:" << save_points.size() << std::endl;
    // ROS_INFO("count1:%d,count2:%d",count1,count2);
    if(!Purlin_Point.point.x&&save_points.size()>0) ROS_ERROR("LOSS Purlin_Point"); 
    if(Purlin_Point.point.x) 
    {
        save_x=Purlin_Point.point.x;        
    }
    point_change.publish(Purlin_Point);
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "scan_iden");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    Scan_Iden da_ke(nh, pnh);
    ros::spin();
    return 0;
}