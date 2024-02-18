/*
给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。
*/
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int countDigitOne(int n) {
        long long mulk=1;
        int ans=0;
        for(int k=0;n>=mulk;++k){
            ans+=(n/(mulk*10))*mulk+min(max(n%(mulk*10)-mulk+1,0LL),mulk);
            cout<<ans<<endl;
            mulk*=10;
        }
        return ans;
    }
};
int main(){
    int n=222;
    Solution abc;
    int result;
    result=abc.countDigitOne(n);
    return 0;
}