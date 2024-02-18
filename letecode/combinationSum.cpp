#include "vectorPrint.h"
//#include <stdio.h>
//#include <string.h>
int count=0;

class Solution {
public:
    void dfs(vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& combine, int idx) {
        count++;
        cout<<"count: "<<count<<" idx: "<<idx<<endl;
        if (idx == candidates.size()) {
            cout<<"idx == candidates.size() "<<count<<" "<<idx<<endl;
            return;
        }
        if (target == 0) {
            ans.emplace_back(combine);
            cout<<idx<<" 30"<<endl;
           vectorcoutInt(combine);
            return;
        }
        // 直接跳过
        dfs(candidates, target,ans, combine, idx + 1);
        // 选择当前数
        if (target - candidates[idx] >=0) {
            combine.emplace_back(candidates[idx]);
            dfs(candidates, target - candidates[idx], ans, combine, idx);
            cout<<idx<<" 40"<<endl;
            vectorcoutInt(combine);
            combine.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combine;
        dfs(candidates, target, ans, combine, 0);
        return ans;
    }
};
int main()
{
    vector<int> abc;
    int a[]={2,3,6,7};
//    memset(a,0,sizeof(a));
    int length = sizeof(a) / sizeof(a[0]);
//    cout<<length<<endl;
    for(int i=0;i<length;i++)
    {
        abc.emplace_back(a[i]);
    }
    //vectorcoutInt(abc);
    int ab=7;
    Solution aa;
    vector<vector<int>> ac=aa.combinationSum(abc,ab);
//    cout<<"a:"<<a<<endl;
    //PrintVecofVec2(ac);
    return 0;
}