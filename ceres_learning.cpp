#include <iostream>
#include <vector>
#include <cmath>
#include "ceres/ceres.h"

// 定义曲线拟合的成本函数
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

int main() {
    // 生成模拟数据
    std::vector<double> true_slope_intercept = {2.0, 3.0}; // 真实的斜率和截距
    unsigned long num_data_points = 100;
    std::vector<double> data_x;
    std::vector<double> data_y;

    for (unsigned long i = 0; i < num_data_points; i++) {
        double x = i / static_cast<double>(num_data_points); // 0 到 1 之间的 x 值
        double y = true_slope_intercept[0] * x + true_slope_intercept[1] + 0.1 * ((rand() % 100) / 100.0 - 0.5); // 添加少量噪音
        data_x.push_back(x);
        data_y.push_back(y);
    }

    // 使用 Ceres 进行拟合
    std::vector<double> vResult;
    CeresLineFit(data_x, data_y, num_data_points, vResult);

    // 输出拟合结果
    std::cout << "True Slope: " << true_slope_intercept[0] << ", True Intercept: " << true_slope_intercept[1] << std::endl;
    std::cout << "Fitted Slope: " << vResult[0] << ", Fitted Intercept: " << vResult[1] << std::endl;

    return 0;
}
