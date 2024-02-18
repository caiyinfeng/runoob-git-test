/*
给你一个整数 n ，请你在无限的整数序列 [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...] 中找出并返回第 n 位上的数字。
示例 1：
输入：n = 3
输出：3
示例 2：
输入：n = 11
输出：0
解释：第 11 位数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 0 ，它是 10 的一部分。

*/
#include <iostream>
#include <cmath>
using namespace std;
class Solution {
public:
    int findNthDigit(int n) {
        int d=1,count=9;
        while(n>(long)d*count){
            n-=d*count;
            d++;
            count*=10;
        }
        cout<<"d:"<<d<<endl;
        cout<<"n:"<<n<<endl;
        int index=n-1;
        int start=(int)pow(10,d-1);
        int num=start+index/d;
        int digitIndex=index%d;
        int digit=(num/(int)(pow(10,d-digitIndex-1)))%10;
        cout<<"num:"<<num<<" digitIndex:"<<digitIndex<<endl;
        return digit;
    }
};
int main(){
    int n=8999;
    Solution abc;
    int c=abc.findNthDigit(n);
    return 0;
}