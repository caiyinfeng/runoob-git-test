/*
给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
*/
#include "vectorPrint.h"
#include <algorithm>
#include <limits.h>
#if 0
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.empty()) return 0;
        int n=prices.size();
        k=min(k,n/2);
        vector<vector<int>> buy(n,vector<int>(k+1));
        vector<vector<int>> sell(n,vector<int>(k+1));
        buy[0][0]=-prices[0];
        sell[0][0]=0;
        for(int i=1;i<=k;++i) buy[0][i]=sell[0][i]=INT_MIN/2;
        for(int i=1;i<n;++i){
            buy[i][0]=max(buy[i-1][0],sell[i-1][0]-prices[i]);
            for(int j=1;j<=k;++j){
                buy[i][j]=max(buy[i-1][j],sell[i-1][j]-prices[i]);
                sell[i][j]=max(sell[i-1][j],buy[i-1][j-1]+prices[i]);
            }
        }
        return *max_element(sell[n-1].begin(),sell[n-1].end());
    }
};
#endif
#if 0
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.empty()) return 0;
        int n=prices.size();
        k=min(k,n/2);
        vector<int> buy(k+1);
        vector<int> sell(k+1);
        buy[0]=-prices[0];
        sell[0]=0;
        for(int i=1;i<=k;++i) buy[i]=sell[i]=INT_MIN/2;
        for(int i=1;i<n;++i){
            buy[0]=max(buy[0],sell[0]-prices[i]);
            for(int j=1;j<=k;++j){
                buy[j]=max(buy[j],sell[j]-prices[i]);
                sell[j]=max(sell[j],buy[j-1]+prices[i]);
            }
        }
        return *max_element(sell.begin(),sell.end());
    }
};
#endif
#if 1
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();
        // 二分查找的上下界
        int left = 1, right = *max_element(prices.begin(), prices.end());
        // 存储答案，如果值为 -1 表示二分查找失败
        int ans = -1;
        while (left <= right) {
            // 二分得到当前的斜率（手续费）
            int c = (left + right) / 2;

            // 使用与 714 题相同的动态规划方法求解出最大收益以及对应的交易次数
            int buyCount = 0, sellCount = 0;
            int buy = -prices[0], sell = 0;

            for (int i = 1; i < n; ++i) {
                if (sell - prices[i] >= buy) {
                    buy = sell - prices[i];
                    buyCount = sellCount;
                }
                if (buy + prices[i] - c >= sell) {
                    sell = buy + prices[i] - c;
                    sellCount = buyCount + 1;
                }
            }

            // 如果交易次数大于等于 k，那么可以更新答案
            // 这里即使交易次数严格大于 k，更新答案也没有关系，因为总能二分到等于 k 的
            if (sellCount >= k) {
                // 别忘了加上 kc
                ans = sell + k * c;
                left = c + 1;
            }
            else {
                right = c - 1;
            }
        }

        // 如果二分查找失败，说明交易次数的限制不是瓶颈
        // 可以看作交易次数无限，直接使用贪心方法得到答案
        if (ans == -1) {
            ans = 0;
            for (int i = 1; i < n; ++i) {
                ans += max(prices[i] - prices[i - 1], 0);
            }
        }

        return ans;
    }
};
#endif
int main(){
    vector<int> nums={3,2,6,5,0,3};
    int k=9000;
    Solution abc;
    int result;
    result=abc.maxProfit(k,nums);
    return 0;
}