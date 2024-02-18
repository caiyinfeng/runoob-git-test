/*
给你三个点，怎么计算三个夹角的角度？
*/

#include <cmath>
#include <iostream>
#include <vector>

struct Point {
    double x, y, z;
};

double dot_product(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross_product(Point a, Point b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};

}

double norm(Point a) {
    return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double angle_between(Point a, Point b) {
    double cosang = dot_product(a, b);
    double sinang = norm(cross_product(a, b));
    return std::atan2(sinang, cosang);
}

Point subtract(Point a, Point b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

double calculate_angle(Point p1, Point p2, Point p3) {
    Point v1 = subtract(p1, p2);
    Point v2 = subtract(p3, p2);
    return angle_between(v1, v2);
}

int main() {
    Point p1 = {1, 0, 0};
    Point p2 = {0, 0, 0};
    Point p3 = {0, 1, 0};

    std::cout << calculate_angle(p1, p2, p3) << std::endl;

    return 0;
}