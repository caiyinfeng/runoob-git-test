#include "vectorPrint.h"
#include <queue>
typedef pair<int,int> pii;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {  
        if (heightMap.size() <= 2 || heightMap[0].size() <= 2) {
            return 0;
        }  
        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    pq.push({heightMap[i][j], i * n + j});
                    visit[i][j] = true;
                }
            }
        }

        int res = 0;
        int dirs[] = {-1, 0, 1, 0, -1};
        while (!pq.empty()) {
            pii curr = pq.top();
            pq.pop();            
            for (int k = 0; k < 4; ++k) {
                int nx = curr.second / n + dirs[k];
                int ny = curr.second % n + dirs[k + 1];
                if( nx >= 0 && nx < m && ny >= 0 && ny < n && !visit[nx][ny]) {
                    if (heightMap[nx][ny] < curr.first) {
                        res += curr.first - heightMap[nx][ny]; 
                    }
                    visit[nx][ny] = true;
                    pq.push({max(heightMap[nx][ny], curr.first), nx * n + ny});
                }
            }
        }
        
        return res;
    }
};
int main() {
    // 边界情况：空矩阵
    Solution abc;
    vector<vector<int>> testCase1 = {};
    cout << "Test Case 1: " << abc.trapRainWater(testCase1) << " (Expected: 0)" << endl;

    // 边界情况：矩阵大小为 1x1
    vector<vector<int>> testCase2 = {{1}};
    cout << "Test Case 2: " << abc.trapRainWater(testCase2) << " (Expected: 0)" << endl;

    // 一般情况：3x3 矩阵
    vector<vector<int>> testCase3 = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };
    cout << "Test Case 3: " << abc.trapRainWater(testCase3) << " (Expected: 0)" << endl;

    // 一般情况：4x4 矩阵
    vector<vector<int>> testCase4 = {
        {1, 4, 3, 1},
        {3, 2, 1, 3},
        {2, 3, 3, 2},
        {1, 2, 1, 4}
    };
    cout << "Test Case 4: " << abc.trapRainWater(testCase4) << " (Expected: 7)" << endl;

    // 特殊情况：高度都相同的矩阵
    vector<vector<int>> testCase5 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    cout << "Test Case 5: " << abc.trapRainWater(testCase5) << " (Expected: 0)" << endl;

    // 特殊情况：高度递增的矩阵
    vector<vector<int>> testCase6 = {
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 5}
    };
    cout << "Test Case 6: " << abc.trapRainWater(testCase6) << " (Expected: 0)" << endl;

    return 0;
}