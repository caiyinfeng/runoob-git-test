/*
给定一个非负整数数组 nums 和一个整数 k ，你需要将这个数组分成 k 个非空的连续子数组。

设计一个算法使得这 k 个子数组各自和的最大值最小。
*/
#include "vectorPrint.h"
#include <limits.h>
#if 1
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        long l=nums[0],h=0;
        for(auto i:nums){
            h+=i;
            l=l>i?l:i;
        }
        while(l<h){
            long mid=(l+h)/2;
            long temp=0;
            int cnt=1;
            for(auto i:nums){
                temp+=i;
                if(temp>mid){
                    temp=i;
                    ++cnt;
                }
            }
            if(cnt>m) l=mid+1;
            else h=mid;
        }
        return l;
    }
};
#endif
#if 0
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
       int n=nums.size();
       vector<vector<long long>> f(n+1,vector<long long>(m+1,LLONG_MAX));
       vector<long long> sub(n+1,0);
       for(int i=0;i<n;i++) sub[i+1]=sub[i]+nums[i];
       f[0][0]=0; 
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, m); j++) {
                for (int k = 0; k < i; k++) {
                    f[i][j] = min(f[i][j], max(f[k][j - 1], sub[i] - sub[k]));
                }
            }
        }
        return (int)f[n][m];
    }
};
#endif
int main() {
    Solution sol;

    // Test Case 1: Basic test case
    vector<int> nums1 = {7, 2, 5, 10, 8};
    int k1 = 2;
    cout << "Test Case 1: " << sol.splitArray(nums1, k1) << " (Expected: 18)" << endl;

    // Test Case 2: Larger array with more partitions
    vector<int> nums2 = {1, 2, 3, 4, 5};
    int k2 = 2;
    cout << "Test Case 2: " << sol.splitArray(nums2, k2) << " (Expected: 9)" << endl;

    // Test Case 3: All elements are the same
    vector<int> nums3 = {6, 6, 6, 6, 6};
    int k3 = 3;
    cout << "Test Case 3: " << sol.splitArray(nums3, k3) << " (Expected: 12)" << endl;

    // Test Case 4: Single-element array
    vector<int> nums4 = {9};
    int k4 = 1;
    cout << "Test Case 4: " << sol.splitArray(nums4, k4) << " (Expected: 9)" << endl;

    return 0;
}