#include <iostream>
#include <vector>
#include "math.h"
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        int maxPos = 0, n = nums.size(), end = 0, step = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (maxPos >= i) {
                maxPos = max(maxPos, i + nums[i]);
                if (i == end) {
                    end = maxPos;
                    ++step;
                }
            }
        }
        return step;
    }
};
int main()
{
    vector<int> ab={2,3,1,1,4,3,1,1,1};
    int result;
    Solution abc;
    result=abc.jump(ab);
    cout<<result<<endl;
    return 0;
}