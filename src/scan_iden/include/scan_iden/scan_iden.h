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