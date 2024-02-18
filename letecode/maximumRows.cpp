/*
给你一个下标从 0 开始、大小为 m x n 的二进制矩阵 matrix ；另给你一个整数 numSelect，表示你必须从 matrix 中选择的 不同 列的数量。

如果一行中所有的 1 都被你选中的列所覆盖，则认为这一行被 覆盖 了。

形式上，假设 s = {c1, c2, ...., cnumSelect} 是你选择的列的集合。对于矩阵中的某一行 row ，如果满足下述条件，则认为这一行被集合 s 覆盖：

    对于满足 matrix[row][col] == 1 的每个单元格 matrix[row][col]（0 <= col <= n - 1），col 均存在于 s 中，或者
    row 中 不存在 值为 1 的单元格。

你需要从矩阵中选出 numSelect 个列，使集合覆盖的行数最大化。

返回一个整数，表示可以由 numSelect 列构成的集合 覆盖 的 最大行数 。
*/
#include "vectorPrint.h"
class Solution {

public:

    int maximumRows(vector<vector<int>> &mat, int numSelect) {

        int m = mat.size(), n = mat[0].size();

        vector<int> mask(m);

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                mask[i] |= mat[i][j] << j;

            }

        }



        int ans = 0;

        int subset = (1 << numSelect) - 1;

        while (subset < (1 << n)) {

            int coveredRows = 0;

            for (int row : mask) {

                if ((row & subset) == row) {

                    coveredRows++;

                }

            }

            ans = max(ans, coveredRows);

            int lb = subset & -subset;

            int x = subset + lb;

            subset = ((subset ^ x) / lb >> 2) | x;

        }

        return ans;

    }

};

int main() {
    Solution sol;

    // Test Case 1: Basic test case
    vector<vector<int>> mat1 = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
    int numSelect1 = 2;
    cout << "Test Case 1: " << sol.maximumRows(mat1, numSelect1) << " (Expected: 3)" << endl;

    // Test Case 2: Larger matrix
    vector<vector<int>> mat2 = {{0, 1, 0, 1}, {1, 1, 1, 0}, {0, 0, 1, 1}};
    int numSelect2 = 3;
    cout << "Test Case 2: " << sol.maximumRows(mat2, numSelect2) << " (Expected: 2)" << endl;

    // Test Case 3: Empty matrix
    // vector<vector<int>> mat3 = {};
    // int numSelect3 = 1;
    // cout << "Test Case 3: " << sol.maximumRows(mat3, numSelect3) << " (Expected: 0)" << endl;

    // Test Case 4: All-zero row
    vector<vector<int>> mat4 = {{0, 0, 0}, {1, 0, 1}, {0, 0, 0}};
    int numSelect4 = 2;
    cout << "Test Case 4: " << sol.maximumRows(mat4, numSelect4) << " (Expected: 1)" << endl;

    // Test Case 5: numSelect is zero
    // vector<vector<int>> mat5 = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
    // int numSelect5 = 0;
    // cout << "Test Case 5: " << sol.maximumRows(mat5, numSelect5) << " (Expected: 0)" << endl;

    return 0;
}

