#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;
    bool visited;
    int cluster;

    Point(double _x, double _y) : x(_x), y(_y), visited(false), cluster(-1) {}
};

class DBSCAN {
private:
    std::vector<Point> points;
    double epsilon;  // 邻域半径
    int minPts;      // 最小邻域点数

public:
    DBSCAN(std::vector<Point> _points, double _epsilon, int _minPts)
        : points(std::move(_points)), epsilon(_epsilon), minPts(_minPts) {}

    void run() {
        int clusterId = 0;
        for (auto& point : points) {
            if (!point.visited) {
                point.visited = true;

                std::vector<Point*> neighbors = getNeighbors(&point);

                if (neighbors.size() >= minPts) {
                    expandCluster(&point, neighbors, clusterId);
                    clusterId++;
                } else {
                    point.cluster = -1;  // Noise point
                }
            }
        }
    }

    std::vector<Point*> getNeighbors(Point* point) {
        std::vector<Point*> neighbors;

        for (auto& other : points) {
            if (calculateDistance(point, &other) <= epsilon) {
                neighbors.push_back(new Point(other.x, other.y));
            }
        }

        return neighbors;
    }

    void expandCluster(Point* point, std::vector<Point*>& neighbors, int clusterId) {
        point->cluster = clusterId;

        for (auto& neighbor : neighbors) {
            if (!neighbor->visited) {
                neighbor->visited = true;

                std::vector<Point*> neighborNeighbors = getNeighbors(neighbor);

                if (neighborNeighbors.size() >= minPts) {
                    neighbors.insert(neighbors.end(), neighborNeighbors.begin(), neighborNeighbors.end());
                }
            }

            if (neighbor->cluster == -1) {
                neighbor->cluster = clusterId;
            }
        }

        // 释放动态分配的内存
        for (auto& neighbor : neighbors) {
            delete neighbor;
        }
    }

    double calculateDistance(const Point* p1, const Point* p2) {
        return std::sqrt(std::pow(p1->x - p2->x, 2) + std::pow(p1->y - p2->y, 2));
    }

    void printClusters() {
        for (const auto& point : points) {
            std::cout << "Point (" << point.x << ", " << point.y << ") - Cluster: " << point.cluster << std::endl;
        }
    }
};
/*

您提供的代码是一个实现 DBSCAN（Density-Based Spatial Clustering of Applications with Noise）算法的 C++ 实现。DBSCAN 是一种基于密度的聚类算法，通过识别数据空间中的高密度区域，并将其划分为簇。以下是代码的解析：

cpp
Copy code
struct Point {
    double x, y;    // 二维空间中的坐标
    bool visited;   // 标记点是否已被访问
    int cluster;    // 簇的标识，-1 表示噪声点

    Point(double _x, double _y) : x(_x), y(_y), visited(false), cluster(-1) {}
};
定义了一个结构体 Point，表示二维空间中的点。每个点有 x 和 y 坐标，以及一个表示是否被访问的标志 (visited) 和一个簇的标识 (cluster)。

cpp
Copy code
class DBSCAN {
private:
    std::vector<Point> points;   // 存储点的向量
    double epsilon;              // 邻域半径
    int minPts;                  // 最小邻域点数

public:
    // 构造函数，初始化点、邻域半径和最小邻域点数
    DBSCAN(std::vector<Point> _points, double _epsilon, int _minPts)
        : points(std::move(_points)), epsilon(_epsilon), minPts(_minPts) {}

    // 主要运行函数，执行 DBSCAN 算法
    void run() {
        int clusterId = 0;
        for (auto& point : points) {
            if (!point.visited) {
                point.visited = true;

                // 获取当前点的邻域
                std::vector<Point*> neighbors = getNeighbors(&point);

                if (neighbors.size() >= minPts) {
                    // 扩展簇
                    expandCluster(&point, neighbors, clusterId);
                    clusterId++;
                } else {
                    // 标记为噪声点
                    point.cluster = -1;
                }
            }
        }
    }

    // 获取当前点的邻域
    std::vector<Point*> getNeighbors(Point* point) {
        std::vector<Point*> neighbors;

        for (auto& other : points) {
            if (calculateDistance(point, &other) <= epsilon) {
                neighbors.push_back(&other);
            }
        }

        return neighbors;
    }

    // 扩展簇
    void expandCluster(Point* point, std::vector<Point*>& neighbors, int clusterId) {
        point->cluster = clusterId;

        for (auto& neighbor : neighbors) {
            if (!neighbor->visited) {
                neighbor->visited = true;

                // 获取邻居的邻域
                std::vector<Point*> neighborNeighbors = getNeighbors(neighbor);

                if (neighborNeighbors.size() >= minPts) {
                    // 扩展邻居的邻域
                    neighbors.insert(neighbors.end(), neighborNeighbors.begin(), neighborNeighbors.end());
                }
            }

            if (neighbor->cluster == -1) {
                neighbor->cluster = clusterId;
            }
        }
    }

    // 计算两点之间的欧几里得距离
    double calculateDistance(const Point* p1, const Point* p2) {
        return std::sqrt(std::pow(p1->x - p2->x, 2) + std::pow(p1->y - p2->y, 2));
    }

    // 打印簇的信息
    void printClusters() {
        for (const auto& point : points) {
            std::cout << "Point (" << point.x << ", " << point.y << ") - Cluster: " << point.cluster << std::endl;
        }
    }
};
定义了一个 DBSCAN 类，包含了执行 DBSCAN 算法所需的功能。主要函数有：

run: 运行 DBSCAN 算法的主要函数。
getNeighbors: 获取给定点的邻域。
expandCluster: 扩展簇的函数。
calculateDistance: 计算两个点之间的欧几里得距离。
printClusters: 打印簇的信息。
*/
int main() {
    std::vector<Point> points = {
        {1.0, 2.0},
        {2.0, 3.0},
        {5.0, 5.0},
        {6.0, 6.0},
        {10.0, 10.0},
        {11.0, 11.0}
    };

    double epsilon = 2.0;
    int minPts = 2;

    DBSCAN dbscan(points, epsilon, minPts);
    dbscan.run();
    dbscan.printClusters();

    return 0;
}
