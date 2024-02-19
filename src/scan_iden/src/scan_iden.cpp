#include "scan_iden/scan_iden.h"
#include <inttypes.h>
#include <vector>
#include "ceres/ceres.h"
#include "math.h"

struct CURVE_FITTING_COST {
    CURVE_FITTING_COST(double x, double y) : x_(x), y_(y) {}

    template <typename T>
    bool operator()(const T* ab, T* residual) const {
        residual[0] = T(y_) - (ab[0] * T(x_) + ab[1]);
        return true;
    }

    const double x_;
    const double y_;
};
void CeresLineFit(std::vector<double> data_x, std::vector<double> data_y, unsigned long data_n, std::vector<double>& vResult) {
    double ab[2] = {0, 0};
    ceres::Problem problem;

    for (unsigned long i = 0; i < data_n; i++) {
        problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 2>(
                new CURVE_FITTING_COST(data_x[i], data_y[i])
            ),
            nullptr,
            ab
        );
    }

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = false;

    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    vResult.push_back(ab[0]); // 斜率
    vResult.push_back(ab[1]); // 截距
}
//求点到直线的距离
double get_distance(double k,double d,double x,double y){
    return fabs((k*x-y+d)/sqrt(k*k+1));
}

Scan_Iden::Scan_Iden(ros::NodeHandle &nh, ros::NodeHandle &pnh) :
    nh_(nh), pnh_(pnh)
{
    init();
}

void Scan_Iden::init()
{
    laser_sub = nh_.subscribe("/scan", 10, &Scan_Iden::laser_callback, this);
    laser_pub = nh_.advertise<sensor_msgs::LaserScan>("/scan_change",10);
    point_change= nh_.advertise<geometry_msgs::PointStamped>("/point_change",10,true);
}

void Scan_Iden::laser_callback(sensor_msgs::LaserScan::ConstPtr msg)
{
    sensor_msgs::LaserScan change;
    change.header=msg->header;
    change.angle_increment=msg->angle_increment;
    change.angle_max=msg->angle_max;
    change.angle_min=msg->angle_min;
    change.intensities=msg->intensities;
    change.range_max=msg->range_max;
    change.range_min=msg->range_min;
    change.scan_time=msg->scan_time;
    change.time_increment=msg->time_increment;
    //ROS_INFO("SUCESS!");
    std::vector<float> changes(msg->ranges.size()+1,NAN);
    double x_qian,y_qian,x_save,y_save,x_;//
    int count1=0,count2=0;
    int save_i=0;
    double k1,k2,d1,d2;
    double k3=0,d3=0;
    bool change_line=false;
    std::vector<double> dx,dy,dk,dd;
    std::vector<Point> point;
    std::vector<std::vector<Point>> save_points;
    //ROS_INFO("SUCESS!2");
    for(int i=0.1*msg->ranges.size();i<=msg->ranges.size();++i){
        if((i-save_i==10||i==msg->ranges.size())&&dy.size()>2&&change_line==true){
            //ROS_INFO("i-save_i==5||i==msg->ranges.size())&&dy.size()>2");
            std::vector<double> result;
            CeresLineFit(dx,dy,dy.size(),result);
            k3=result[0],d3=result[1];
            dk.push_back(k3);
            dd.push_back(d3);
            change_line=false;
            dx.clear();
            dy.clear();
            k3=0;
            d3=0;
        }
        if(msg->ranges[i]>2.0){
            changes[i]=NAN;
        }else if(msg->ranges[i]>0.1){
            count1++;
            changes[i]=msg->ranges[i];
            //std::cout<<msg->ranges[i]<<std::endl;
            double angle = msg->angle_min + msg->angle_increment * (i - 1);
            double x=changes[i]*cos(angle),y=changes[i]*sin(angle);
            //ROS_INFO("SUCESS!3");
            if(!x_qian&&!y_qian){
                x_qian=x;
                y_qian=y;
                continue;
            }
            if(x-x_qian==0) x_qian-=0.0001;
            k1=(y-y_qian)/(x-x_qian);
            //d1=(x*y_qian-x_qian*y)/(x-x_qian);
            double s=atan(fabs(k1-k2)/(1+k1*k2))*90/1.57;//求3个点形成的直线夹角
            //double dis=(x-x_save)*(x-x_save)+(y-y_save)*(y-y_save);//求2点之间的距离
            double dis=(x-x_qian)*(x-x_qian)+(y-y_qian)*(y-y_qian);//求2点之间的距离
            if(dy.size()>2){
                std::vector<double> result;
                CeresLineFit(dx,dy,dy.size(),result);
                k3=result[0],d3=result[1];
            }
            // if(dis>0.03*0.03){
            //     std::cout<<x_save<<" "<<y_save<<" "<<dis<<std::endl;
            // }
            //x_save=x;
            //y_save=y;
            if(dis>0.03*0.03&&y>0.5*x&&y<-0.5*x){
                
                //std::cout<<x<<" "<<y<<" "<<dis<<std::endl;
                x_qian=x;
                y_qian=y;                
                count2++;
                continue;
            }
            if(get_distance(k3,d3,x,y)>0.01&&k3&&d3){
                std::vector<double>::const_iterator fist1 = dx.end() - 2; // 第三个迭代器
                std::vector<double>::const_iterator last1 = dx.end() ; // 倒数第二个迭代器
                std::vector<double> dx_save(fist1, last1);
                std::vector<double>::const_iterator fist2 = dy.end() - 2; // 第三个迭代器
                std::vector<double>::const_iterator last2 = dy.end() ; // 倒数第二个迭代器
                std::vector<double> dy_save(fist2, last2);
                dx.clear();
                dy.clear();
                dk.push_back(k3);
                dd.push_back(d3);
                //ROS_INFO("SUCESS!8");
                dx=dx_save;
                dy=dy_save;
                //ROS_INFO("SUCESS!9");
                if(!dx.empty()){
                    geometry_msgs::PointStamped point1;
                    point1.header=msg->header;
                    point1.point.x=dx[0];
                    point1.point.y=dy[0];
                    point1.point.z=0.02;
                    Point corner_point;
                    corner_point.x=dx[0];
                    corner_point.y=dy[0];
                    //ROS_INFO("corner_point.x:%2f,corner_point.y:%2f",corner_point.x,corner_point.y);
                    //ROS_INFO("dy:%ld",dy.size());
                    point.push_back(corner_point); 
                    point_change.publish(point1);
                }
                k3=0;
                d3=0;
                change_line=true;
            }
            //ROS_INFO("SUCESS!10");
            dx.push_back(x);
            dy.push_back(y);
            x_qian=x;
            y_qian=y;
            k2=k1;
            //d2=d1;
            save_i=i; 
            //ROS_INFO("X:%2f,Y:%2f",p.x,p.y);
        }            
    }
    ROS_INFO("point:%ld",point.size());
    ROS_INFO("dk:%ld",dk.size());
    ROS_INFO("count1:%d,count2:%d",count1,count2);
    point.clear();
    change.ranges=changes;
    laser_pub.publish(change);
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