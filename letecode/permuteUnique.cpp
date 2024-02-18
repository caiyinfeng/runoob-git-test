#include "vectorPrint.h"
#include<algorithm>
#if 1
class Solution {
    vector<vector<int>> ans;

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        perm(nums, 0, nums.size() - 1);
        return ans;
    }
    
    void perm(vector<int> nums, int left, int right) {
        //cout<<"循环外"<<endl;
        cout<<"left:"<<left<<endl;
        if (left == right){
            ans.push_back(nums);
            PrintVecofVec2(ans);
        }
        else {
            for (int i = left; i <= right; i++) {
                cout<<"i:"<<i<<endl;
                if (i != left && nums[left] == nums[i]) {
                    //cout<<"continue"<<endl;
                    continue;  // 去重
                }
                //cout<<"循环内"<<endl;
                swap(nums[left], nums[i]);
                vectorcoutInt(nums);
                perm(nums, left + 1, right);
            }
        }
    }
};
#endif
int main()
{
    vector<int> abc={1,1,2,2};
    vector<vector<int>> ab;
    Solution ee;
    ab=ee.permuteUnique(abc);
    return 0;
}