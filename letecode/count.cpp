/*
给你两个数字字符串 num1 和 num2 ，以及两个整数 max_sum 和 min_sum 。如果一个整数 x 满足以下条件，我们称它是一个好整数：

    num1 <= x <= num2
    min_sum <= digit_sum(x) <= max_sum.

请你返回好整数的数目。答案可能很大，请返回答案对 109 + 7 取余后的结果。

注意，digit_sum(x) 表示 x 各位数字之和。
*/
#include "vectorPrint.h"
#include <functional>
#if 1
class Solution
{
    const int MOD = 1000000007;
    int calc(string &s, int min_sum, int max_sum)
    {
        int n = s.length();
        vector<vector<int>> memo(n, vector<int>(min(9 * n, max_sum) + 1, -1));
        function<int(int, int, bool)> dfs = [&](int i, int sum, bool is_limit) -> int
        {
            if (sum > max_sum)
                return 0;
            if (i == n)
                return sum >= min_sum ? 1 : 0;
            if (!is_limit && memo[i][sum] != -1)
                return memo[i][sum];
            int up = is_limit ? s[i] - '0' : 9;
            int res = 0;
            for (int d = 0; d <= up; d++)
                res = (res + dfs(i + 1, sum + d, is_limit && d == up)) % MOD;
            if (!is_limit)
                memo[i][sum] = res;
            return res;
        };
        cout<<"calc:"<<dfs(0,0,true)<<endl;
        return dfs(0, 0, true);
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum)
    {
        int ans = calc(num2, min_sum, max_sum) - calc(num1, min_sum, max_sum) + MOD;
        int sum = 0;
        for (char c : num1)
            sum += c - '0';
        ans += min_sum <= sum && sum <= max_sum;
        return ans % MOD;
    }
};
#endif
#if 0
class Solution {

public:

    int count(string num1, string num2, int min_sum, int max_sum) {

        int n = num2.length();
        num1 = string(n - num1.length(), '0') + num1; // 补前导零，和 num2 对齐
        vector<vector<int>> memo(n, vector<int>(min(9 * n, max_sum) + 1, -1));
        function<int(int, int, bool, bool)> dfs = [&](int i, int sum, bool limit_low, bool limit_high) -> int {
            if (sum > max_sum) { // 非法
                return 0;
            }
            if (i == n) {
                return sum >= min_sum;
            }
            if (!limit_low && !limit_high && memo[i][sum] != -1) {
                return memo[i][sum];
            }
            int lo = limit_low ? num1[i] - '0' : 0;
            int hi = limit_high ? num2[i] - '0' : 9;
            int res = 0;
            for (int d = lo; d <= hi; d++) { // 枚举当前数位填 d
                res = (res + dfs(i + 1, sum + d, limit_low && d == lo, limit_high && d == hi)) % 1'000'000'007;
            }
            if (!limit_low && !limit_high) {
                memo[i][sum] = res;
            }
            return res;
        };
        return dfs(0, 0, true, true);
    }
};
#endif
void runTest(string num1, string num2, int min_sum, int max_sum)
{
    Solution solution;
    int result = solution.count(num1, num2, min_sum, max_sum);
    cout << "num1: " << num1 << ", num2: " << num2 << ", min_sum: " << min_sum
         << ", max_sum: " << max_sum << " => Result: " << result << endl;
}

int main()
{
    // Test Case 1
    runTest("123", "456", 5, 10);

    // Test Case 2
    //runTest("123456789", "987654321", 30, 50);

    // Test Case 3
    runTest("1", "9", 1, 9);

    // Test Case 4
    //runTest("12345", "12345", 15, 15);
    return 0;
}