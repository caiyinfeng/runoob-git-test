#ifndef __SCAN_IDEN_H__
#define __SCAN_IDEN_H__
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/PointStamped.h"
#include <vector>
#include "ceres/ceres.h"
template<typename T>
std::vector<T> prev_vector(std::vector<T> prev_point,int count){
    std::vector<T> result;
    auto first_iterator = std::prev(prev_point.end(), 15); // 倒数第15个迭代器
    auto last_iterator = prev_point.end();
    result.assign(first_iterator, last_iterator);
    return result;
}
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
    Point laser_segmentation1(std::vector<Point> point)//檩条
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
        if (abs(s_hou) > 50&&point_chu.y>dy.back())
        {
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
        return point_chu;
    }
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