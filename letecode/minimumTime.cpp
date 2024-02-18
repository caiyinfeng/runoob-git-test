/*
给你两个长度相等下标从 0 开始的整数数组 nums1 和 nums2 。每一秒，对于所有下标 0 <= i < nums1.length ，nums1[i] 的值都增加 nums2[i] 。操作 完成后 ，你可以进行如下操作：

    选择任一满足 0 <= i < nums1.length 的下标 i ，并使 nums1[i] = 0 。

同时给你一个整数 x 。

请你返回使 nums1 中所有元素之和 小于等于 x 所需要的 最少 时间，如果无法实现，那么返回 -1 。
*/
/*
解题思路：
https://leetcode.cn/problems/minimum-time-to-make-array-sum-at-most-x/solutions/2374920/jiao-ni-yi-bu-bu-si-kao-ben-ti-by-endles-2eho/?envType=daily-question&envId=2024-01-19
*/
#include "vectorPrint.h"
#include <numeric>
#include <algorithm>
class Solution {
public:
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int n=nums1.size();
        vector<int> ids(n);
        //根据nums2大小排序
        iota(ids.begin(),ids.end(),0);
        sort(ids.begin(),ids.end(),[&](const int i,const int j){return nums2[i]<nums2[j];});
        vector<int> f(n+1);
        //
        for(int i=0;i<n;i++){
            int a=nums1[ids[i]],b=nums2[ids[i]];
            for(int j=i+1;j;j--) f[j]=max(f[j],f[j-1]+a+b*j);
        }
        vectorcoutAuto(f);
        int s1=accumulate(nums1.begin(),nums1.end(),0);
        int s2=accumulate(nums2.begin(),nums2.end(),0);
        for(int t=0;t<=n;t++){
            if(s1+s2*t-f[t]<=x) return t;
        }
        return -1;
    }
};
int main() {
    Solution sol;

    // Test Case 1
    vector<int> nums1_1 = {1, 2, 3};
    vector<int> nums2_1 = {4, 5, 6};
    int x_1 = 10;
    cout << "Test Case 1: " << sol.minimumTime(nums1_1, nums2_1, x_1) << endl;

    // Test Case 2
    vector<int> nums1_2 = {2, 3, 1};
    vector<int> nums2_2 = {5, 4, 6};
    int x_2 = 15;
    cout << "Test Case 2: " << sol.minimumTime(nums1_2, nums2_2, x_2) << endl;

    // Add more test cases as needed...
    vector<int> nums1_3 = {1, 2, 3};
    vector<int> nums2_3 = {1, 2, 3};
    int x_3 = 4;
    cout << "Test Case 3: " << sol.minimumTime(nums1_3, nums2_3, x_3) << endl;
    return 0;
}