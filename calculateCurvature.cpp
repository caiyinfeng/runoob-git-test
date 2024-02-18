#include <iostream>
#include <vector>
#include <cmath>

// 定义一个结构体来表示激光扫描数据
struct LaserScan {
    std::vector<double> ranges; // 激光扫描数据
};

// 函数用于计算曲率
std::vector<double> calculateCurvature(const LaserScan& scan) {
    std::vector<double> curvature;

    // 假设激光扫描的角度范围是[-pi, pi]
    size_t num_points = scan.ranges.size();
    double angle_increment = 2 * M_PI / num_points;

    // 将极坐标转换为笛卡尔坐标系
    std::vector<double> x, y;
    for (size_t i = 0; i < num_points; ++i) {
        double angle = -M_PI + i * angle_increment;
        x.push_back(scan.ranges[i] * cos(angle));
        y.push_back(scan.ranges[i] * sin(angle));
    }

    // 计算一阶和二阶导数
    std::vector<double> dx, dy, d2x, d2y;
    for (size_t i = 0; i < num_points; ++i) {
        dx.push_back((i > 0) ? (x[i] - x[i - 1]) : 0.0);
        dy.push_back((i > 0) ? (y[i] - y[i - 1]) : 0.0);
        d2x.push_back((i > 0) ? (dx[i] - dx[i - 1]) : 0.0);
        d2y.push_back((i > 0) ? (dy[i] - dy[i - 1]) : 0.0);
    }

    // 计算曲率
    for (size_t i = 0; i < num_points; ++i) {
        double denom = pow((dx[i] * dx[i] + dy[i] * dy[i]), 1.5);
        curvature.push_back(denom > 0 ? (dx[i] * d2y[i] - dy[i] * d2x[i]) / denom : 0.0);
    }

    return curvature;
}

int main() {
    // 使用示例
    LaserScan laserScan;
    // 替换为实际的激光扫描数据
    laserScan.ranges = {1.0, 0.8, 0.5, 0.3, 0.9};

    std::vector<double> curvature = calculateCurvature(laserScan);

    // 打印曲率
    for (size_t i = 0; i < curvature.size(); ++i) {
        std::cout << "Curvature at point " << i << ": " << curvature[i] << std::endl;
    }

    return 0;
}
