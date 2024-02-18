/*
    一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
    'A' -> "1"
    'B' -> "2"
    ...
    'Z' -> "26"
    要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"11106" 可以映射为：
        "AAJF" ，将消息分组为 (1 1 10 6)
        "KJF" ，将消息分组为 (11 10 6)
    注意，消息不能分组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价。
    给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数 。
    题目数据保证答案肯定是一个 32 位 的整数。
*/
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#if 1
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        s = " " + s;
        int f[3];
        memset(f, 0, sizeof(f));
        f[0] = 1;
        for(int i = 1; i <= n; i++) {
            f[i % 3] = 0;
            int a = s[i] - '0', b = (s[i - 1] - '0') * 10 + s[i] - '0';
            if(1 <= a && a <= 9) f[i % 3] = f[(i - 1) % 3];
            if(10 <= b && b <= 26) f[i % 3] += f[(i - 2) % 3];
        }
        return f[n % 3];
    }
};
#endif
#if 0
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> f(n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] != '0') {
                f[i] += f[i - 1];
            }
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
                f[i] += f[i - 2];
            }
        }
        return f[n];
    }
};
#endif
int main(){
    string s="226";
    Solution abc;
    int result;
    result=abc.numDecodings(s);
    return 0;
}