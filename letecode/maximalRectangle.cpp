#include <iostream>
#include <vector>
using namespace std;
#if 1
class Solution {
public:
    int maximalRectangle(vector<vector<string>>& matrix) {
        if (matrix.empty()) return 0;
        int ans = 0;
        vector<int> line(matrix[0].size() + 2, 0);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                line[j + 1] = (matrix[i][j] == "0") ? 0 : line[j + 1] + 1;
            }
            ans = max(ans, largestRectangleArea(line));
        }
        return ans;
    }
    
    int largestRectangleArea(vector<int>& heights) {
        int ans = 0;
        vector<int> st;
        // heights.insert(heights.begin(), 0);
        // heights.push_back(0);
        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[st.back()] > heights[i]) {
                int cur = st.back();
                st.pop_back();
                int left = st.back() + 1;
                int right = i - 1;
                ans = max(ans, (right - left + 1) * heights[cur]);
            }
            st.push_back(i);
        }
        return ans;
    }
};
#endif
#if 0
//动态规划
class Solution {
public:
	int maximalRectangle(vector<vector<string>>& matrix) {
		int n = matrix.size();
		int m = 0;
		if (n > 0) { m = matrix[0].size(); }
		vector<vector<int>> heights(n + 1,vector<int>(m + 1,0));
		vector<vector<vector<int>>> dp(n + 1,vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (matrix[i-1][j-1] == "0") { continue; }
				heights[i][j] = heights[i-1][j] + 1;
				for (int k = 1; k <= heights[i][j]; k++) {
					dp[i][j][k] = dp[i][j-1][k] + k;
					ans = max(ans, dp[i][j][k]);
				}
			}
		}
		return ans;
	}
};
#endif
int main(){
    vector<vector<string>> matrix={{"1","0","1","0","0"},{"1","0","1","1","1"},{"1","1","1","1","1"},{"1","0","0","1","0"}};
    Solution abc;
    int result;
    result=abc.maximalRectangle(matrix);
    return 0;
}