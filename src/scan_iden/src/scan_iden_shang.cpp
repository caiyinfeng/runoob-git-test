#include "scan_iden/scan_iden.h"
#include <inttypes.h>
#include <vector>
#include "ceres/ceres.h"
#include "math.h"
#include <algorithm>

struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST(double x, double y) : x_(x), y_(y) {}

    template <typename T>
    bool operator()(const T *ab, T *residual) const
    {
        residual[0] = T(y_) - (ab[0] * T(x_) + ab[1]);
        return true;
    }

    const double x_;
    const double y_;
};
void CeresLineFit(std::vector<double> data_x, std::vector<double> data_y, unsigned long data_n, std::vector<double> &vResult)
{
    double ab[2] = {0, 0};
    ceres::Problem problem;

    for (unsigned long i = 0; i < data_n; i++)
    {
        problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 2>(
                new CURVE_FITTING_COST(data_x[i], data_y[i])),
            nullptr,
            ab);
    }

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = false;

    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    vResult.push_back(ab[0]); // 斜率
    vResult.push_back(ab[1]); // 截距
}
// 求点到直线的距离
double get_distance(double x1, double y1, double x2, double y2,double x3,double y3)
{
    return abs((y1-y2)*x3+(x2-x1)*y3+x1*y2-y1*x2)/sqrt((y1-y2) *(y1-y2)+(x1-x2)*(x1-x2));
}
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
    point_chu=(laser_seg_hou.y>point_chu.y&&laser_seg_hou.y)||point_chu.y==0?laser_seg_hou:point_chu;              
    if(!point_chu.x){
        point_chu.x=0;
        point_chu.y=0;
    }
    return point_chu;
}
Point Scan_Iden::laser_segmentation1(std::vector<Point> point)
{
    std::vector<double> dx, dy, dx_qian3, dy_qian3, dx_hou3, dy_hou3;
    Point point_chu;
    point_chu.y=10000;
    for (int i = 0; i < point.size(); i++)
    {
        if (i < 3)
        {
            dx_qian3.push_back(point[i].x);
            dy_qian3.push_back(point[i].y);
        }
        else if (i > point.size() - 4)
        {
            dx_hou3.push_back(point[i].x);
            dy_hou3.push_back(point[i].y);
        }
        else
        {
            dx.push_back(point[i].x);
            dy.push_back(point[i].y);
        }
    }
    std::vector<double> result,result_qian,result_hou;
    CeresLineFit(dx, dy, dy.size(), result);
    double k = result[0];
    CeresLineFit(dx_qian3, dy_qian3, dx_qian3.size(), result_qian);
    double k_qian = result_qian[0];
    CeresLineFit(dx_hou3, dy_hou3, dy_hou3.size(), result_hou);
    double k_hou = result_hou[0];
    double s_hou = atan(fabs(k - k_hou) / (1 + k * k_hou)) * 90 / 1.57, s_qian = atan(fabs(k - k_qian) / (1 + k * k_qian)) * 90 / 1.57,s_qian_hou=atan(fabs(k_hou - k_qian) / (1 + k * k_hou)) * 90 / 1.57;
    std::cout<<"s_hou_qian:"<<s_hou<<"  "<<s_qian<<" "<<s_qian_hou<<std::endl;
    if(abs(s_qian_hou)>60&&abs(s_hou) <=50&&abs(s_qian) <=50){
        s_hou=70;
        s_qian=70;
    }
    if(abs(s_hou) < 50&&abs(s_qian) <50)
    {
        point_chu.x = 0;
        point_chu.y = 0;
        return point_chu;
    }
    if (abs(s_qian) > 50)
    {
        
        point_chu.x = dx[0];
        point_chu.y = dy[0];
        while (true)
        {
            dx_qian3.push_back(dx[0]);
            dy_qian3.push_back(dy[0]);
            dx.erase(dx.begin());
            dy.erase(dy.begin());
            dx.insert(dx.end(), dx_hou3.begin(), dx_hou3.end());
            dy.insert(dy.end(), dy_hou3.begin(), dy_hou3.end());
            CeresLineFit(dx_qian3, dy_qian3, dx_qian3.size(), result);
            k_qian = result[0];
            CeresLineFit(dx, dy, dy.size(), result);
            k = result[0];
            s_qian = atan(fabs(k - k_qian) / (1 + k * k_qian)) * 90 / 1.57;
            if (abs(s_qian) < 75)
            {
                break;
            }
            point_chu.x = dx[0];
            point_chu.y = dy[0];
        }
    }
    //std::cout<<"point_chu:"<<point_chu.x<<"  "<<point_chu.y<<std::endl;
    if (abs(s_hou) > 50&&point_chu.y>dy.back())
    {
        //ROS_INFO("abs(s_hou > 60");
        point_chu.x = dx.back();
        point_chu.y = dy.back();
        while (true)
        {
            dx_hou3.push_back(dx.back());
            dy_hou3.push_back(dy.back());
            dx.erase(dx.end() - 1);
            dy.erase(dy.end() - 1);
            dx.insert(dx.end(), dx_qian3.begin(), dx_qian3.end());
            dy.insert(dy.end(), dy_qian3.begin(), dy_qian3.end());
            CeresLineFit(dx_hou3, dy_hou3, dx_hou3.size(), result);
            k_hou = result[0];
            CeresLineFit(dx, dy, dy.size(), result);
            k = result[0];
            s_hou = atan(fabs(k - k_hou) / (1 + k * k_hou)) * 90 / 1.57;
            if (abs(s_hou) < 75)
            {

                break;
            }
            point_chu.x = dx.back();
            point_chu.y = dy.back();
        }
    }
    //std::cout<<"point_chu:"<<point_chu.x<<"  "<<point_chu.y<<std::endl;
    return point_chu;
}
Scan_Iden::Scan_Iden(ros::NodeHandle &nh, ros::NodeHandle &pnh) : nh_(nh), pnh_(pnh)
{
    init();
}

void Scan_Iden::init()
{
    laser_sub = nh_.subscribe("/scan2", 10, &Scan_Iden::laser_callback, this);
    laser_pub = nh_.advertise<sensor_msgs::LaserScan>("/scan_change2", 10);
    point_change = nh_.advertise<geometry_msgs::PointStamped>("/point_change2", 10, true);
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
    // ROS_INFO("SUCESS!");
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
    // ROS_INFO("SUCESS!2");
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
                //ROS_INFO("count3 == 4");
                //std::cout << "point:" << point.size() << std::endl;
                dis_more = false;
                if (point.size() > 3)
                {
                    auto first_iterator = std::prev(point.end(), 3); // 倒数第三个迭代器
                    auto last_iterator = point.end();                // 倒数第二个迭代器
                    point_save.assign(first_iterator, last_iterator);
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
            // changes[i]=msg->ranges[i];
            // std::cout<<msg->ranges[i]<<std::endl;
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
                std::vector<double> point_save_x, point_save_y;
                auto first_iterator = std::prev(Photovoltaic_Panels_x.end(), 15); // 倒数第15个迭代器
                auto last_iterator = Photovoltaic_Panels_x.end();
                point_save_x.assign(first_iterator, last_iterator);
                first_iterator = std::prev(Photovoltaic_Panels_y.end(), 15);
                last_iterator = Photovoltaic_Panels_y.end();
                point_save_y.assign(first_iterator, last_iterator);
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
                if (abs(s_hou) < 15&&abs(s_qian)<15&&k>0.3&&k<2&&save_points.size()<=2)
                {
                    std::cout << "s_hou:" << s_hou<<" s_qian:"<<s_qian<< std::endl;
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
    Purlin_Point.point.y=-1000;
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
                Purlin_Point.point.x = point_chu.x != 0 &&abs(point_chu.x-save_x)<0.15&&point_chu.y>Purlin_Point.point.y? point_chu.x : Purlin_Point.point.x;
                Purlin_Point.point.y = point_chu.x != 0 &&abs(point_chu.x-save_x)<0.15&&point_chu.y>Purlin_Point.point.y? point_chu.y : Purlin_Point.point.y;
            }
            else if (points.size() <=24&&save_points.size()>0)
            {
                point_chu=laser_segmentation1(points);
                ROS_INFO("point_chu.x:%2f,point_chu.y:%2f",point_chu.x,point_chu.y);
                Purlin_Point.point.x = point_chu.x != 0&&abs(point_chu.x-save_x)<0.15&&point_chu.y>Purlin_Point.point.y? point_chu.x : Purlin_Point.point.x;
                Purlin_Point.point.y = point_chu.x != 0&&abs(point_chu.x-save_x)<0.15&&point_chu.y>Purlin_Point.point.y? point_chu.y : Purlin_Point.point.y;
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