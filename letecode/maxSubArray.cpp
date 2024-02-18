#include <iostream>
#include <vector>
using namespace std;
#if 0
//动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
            cout<<"pre:"<<pre<<" maxAns:"<<maxAns<<endl;
        }
        return maxAns;
    }
};
#endif
//分治法 线段树
class Solution {
public:
    struct Status {
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status l, Status r,int lr) {
        //cout<<"开始:"<<count<<endl;
        int iSum = l.iSum + r.iSum;
        int lSum = max(l.lSum, l.iSum + r.lSum);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
        cout<<"iSum:"<<iSum<<" lSum:"<<lSum<<" rSum:"<<rSum<<" mSum:"<<mSum<<endl;
        cout<<"left or rignt:"<<lr<<endl;
        return (Status) {lSum, rSum, mSum, iSum};
    };

    Status get(vector<int> &a, int l, int r,int lr) {
        cout<<l<<" "<<r<<endl;
        if (l == r) {
            return (Status) {a[l], a[l], a[l], a[l]};
        }
        int m = (l + r) >> 1;
        cout<<"l:"<<l<<" r:"<<r<<" m:"<<m<<endl;
        Status lSub = get(a, l, m,0);
        Status rSub = get(a, m + 1, r,1);
        cout<<lSub.iSum<<" "<<lSub.lSum<<" "<<lSub.rSum<<" "<<lSub.mSum<<" "<<endl;
        cout<<rSub.iSum<<" "<<rSub.lSum<<" "<<rSub.rSum<<" "<<rSub.mSum<<" "<<endl;
        return pushUp(lSub, rSub,lr);
    }

    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1,2).mSum;
    }
protected:
    int count=0;
};

int main(){
    vector<int> ab={-2,1,-3,4,-1,2,1,-5,4};
    //vector<int> ab={5,4,-1,7,8};
    Solution abc;
    int result;
    result=abc.maxSubArray(ab);
    return 0;
}
