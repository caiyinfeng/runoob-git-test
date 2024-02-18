/*
给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。

注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。
*/
#include "vectorPrint.h"
#include <algorithm>
#include <sstream>
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> str;
        for(auto i:nums){
            str.push_back(to_string(i));
        }
        auto cmp=[](string left,string right){
            return left+right>right+left;
        };
        sort(str.begin(),str.end(),cmp);
        stringstream ss;
        for(auto c:str){
            ss<<c;
        }
        string ans=ss.str();
        if(ans[0]=='0') return "0";
        return ans;
    }
};
int main(){
    vector<int> nums={3,30,34,5,9};
    string result;
    Solution abc;
    result=abc.largestNumber(nums);
    cout<<result<<endl;
    return 0;
}