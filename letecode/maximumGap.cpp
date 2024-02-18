/*
给定一个无序的数组 nums，返回 数组在排序之后，相邻元素之间最大的差值 。如果数组元素个数小于 2，则返回 0 。

您必须编写一个在「线性时间」内运行并使用「线性额外空间」的算法。
*/
#include "vectorPrint.h"
#include <algorithm>
#if 0
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n=nums.size();
        if(n<2) return 0;
        int exp=1;
        vector<int> buf(n);
        int maxVal=*max_element(nums.begin(),nums.end());
        while(maxVal>=exp){
            vector<int> cnt(10);
            for(int i=0;i<n;i++){
                int digit=(nums[i]/exp)%10;
                cnt[digit]++;
            }
            vectorcoutAuto(cnt);
            for(int i=1;i<10;i++){
                cnt[i]+=cnt[i-1];
            }
            vectorcoutAuto(cnt);
            for(int i=n-1;i>=0;i--){
                int digit=(nums[i]/exp)%10;
                buf[cnt[digit]-1]=nums[i];
                cnt[digit]--;
            }
            vectorcoutAuto(cnt);
            vectorcoutAuto(buf);
            
            copy(buf.begin(),buf.end(),nums.begin());
            exp*=10;
        }
        int ret=0;
        for(int i=1;i<n;i++) ret=max(ret,nums[i]-nums[i-1]);
        return ret;
    }
};
#endif
#if 1
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return 0;
        }
        int minVal = *min_element(nums.begin(), nums.end());
        int maxVal = *max_element(nums.begin(), nums.end());
        int d = max(1, (maxVal - minVal) / (n - 1));
        int bucketSize = (maxVal - minVal) / d + 1;

        vector<pair<int, int>> bucket(bucketSize, {-1, -1});  // 存储 (桶内最小值，桶内最大值) 对，(-1, -1) 表示该桶是空的
        for (int i = 0; i < n; i++) {
            int idx = (nums[i] - minVal) / d;
            if (bucket[idx].first == -1) {
                bucket[idx].first = bucket[idx].second = nums[i];
            } else {
                bucket[idx].first = min(bucket[idx].first, nums[i]);
                bucket[idx].second = max(bucket[idx].second, nums[i]);
            }
            cout<<"i:"<<i<<" idx:"<<idx<<" bucket[idx].first:"<<bucket[idx].first<<" bucket[idx].second:"<<bucket[idx].second<<endl;
        }

        int ret = 0;
        int prev = -1;
        for (int i = 0; i < bucketSize; i++) {
            if (bucket[i].first == -1) continue;
            if (prev != -1) {
                ret = max(ret, bucket[i].first - bucket[prev].second);
                cout<<ret<<endl;
            }
            prev = i;
        }
        return ret;
    }
};
#endif
int main(){
    vector<int> nums={12,234,66,55,4,58,1233,5,1,2,3,66};
    int result;
    Solution abc;
    result=abc.maximumGap(nums);
    cout<<result<<endl;
    return 0;
}