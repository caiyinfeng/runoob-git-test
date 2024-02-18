#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

void dijkstar( )
{
   int n = 6;
    vector<vector<int>> times{ {0,1,1},{0,2,12},{1,2,9},{1,3,3},{2,4,5},{3,5,15},{3,4,13},{3,2,4},{4,5,4} };//图
    int INF = 1e9;
    unordered_map<int, vector<pair<int, int>>> e;
    for (auto v : times)
    {
        int x = v[0], y = v[1], cost = v[2];
        e[x].push_back({ y, cost });
    }
    int start = 0;
    vector<int> cost(n, INF);
    cost[start] = 0;//初始化cost
    //定义优先队列,每次将距离start point最近的点放到队列最前端
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > minHeap;
    minHeap.push({ 0, start });//{到0的最小距离，0到第几个点}
    while (!minHeap.empty())
    {
        auto dd = minHeap.top();
        minHeap.pop();
        if (dd.first > cost[dd.second] || cost[dd.second] == INF)
            continue;
        for (auto yy : e[dd.second])
        {
            if (cost[dd.second] + yy.second < cost[yy.first])
            {
                cost[yy.first] = cost[dd.second] + yy.second;
                minHeap.push({ cost[yy.first], yy.first });
            }
        }
    }
    //打印更新过的结果
    for (auto d : cost)
    {
        cout << d << endl;
    }
}
int main(){
    dijkstar();
    return 0;
}