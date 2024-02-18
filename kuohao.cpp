#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxans = 0, n = s.length();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++) {
            //cout<<i<<"first "<<dp[i]<<endl;
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                    cout<<"sucess"<<endl;
                }
                maxans = max(maxans, dp[i]);
            }
            cout<<i<<" "<<dp[i]<<endl;
        }
        return maxans;
    }
};

int main()
{
    string abc="())";
    Solution aa;
    int a;
    a=aa.longestValidParentheses(abc);
    printf("a:%d\n",a);
    return 0;
}