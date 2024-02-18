/*
n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

    每个孩子至少分配到 1 个糖果。
    相邻两个孩子评分更高的孩子会获得更多的糖果。

请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。
*/
#include "vectorPrint.h"
//#include <algorithm>
#if 1
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        vector<int> left(n);
        for(int i=0;i<n;i++){
            if(i>0&&ratings[i]>ratings[i-1]) left[i]=left[i-1]+1;
            else left[i]=1;
        }
        int right=0,ret=0;
        for(int i=n-1;i>=0;i--){
            if(i<n-1&&ratings[i]>ratings[i+1]) right++;
            else right=1;
            ret+=max(left[i],right);
        }
        return ret;
    }
};
#endif
#if 0
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        int ret=1;
        int inc=1,dec=0,pre=1;
        for(int i=1;i<n;i++){
            if(ratings[i]>=ratings[i-1]){
                dec=0;
                pre=ratings[i]==ratings[i-1]?1:pre+1;
                ret+=pre;
                inc=pre;
            }else{
                dec++;
                if(dec==inc) dec++;
                ret+=dec;
                pre=1;
            }
        }
        return ret;
    }
};
#endif
int main(){
    vector<int> ratings={1,3,5,3,2,1};
    int result;
    Solution abc;
    result=abc.candy(ratings);
    return 0;
}