/*
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
*/
#include "vectorPrint.h"
#if 0
class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;
    vector<vector<int>> subsets(vector<int>& nums) {
        int n=nums.size();
        for(int mask=0;mask<(1<<n);++mask)
        {
            t.clear();
            for(int i=0;i<n;i++)
            {
                if(mask&(1<<i)){
                    t.push_back(nums[i]);

                }
            }
            ans.push_back(t);
            PrintVecofVec2(ans);
        }
        return ans;
    }
};
#endif
#if 1
class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;    
    void dfs(int cur,vector<int>& nums)
    {
        if(cur==nums.size()){
            ans.push_back(t);
            PrintVecofVec2(ans);
            return;
        }
        t.push_back(nums[cur]);
        dfs(cur+1,nums);
        t.pop_back();
        dfs(cur+1,nums);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(0,nums);
        return ans;
    }
};
#endif
int main()
{
    vector<int> nums={5,2,9};
    vector<vector<int>> result;
    Solution abc;
    result=abc.subsets(nums);
    return 0;
}