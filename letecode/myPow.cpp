#include <iostream>
using namespace std;
class Solution{
public:
    double quickMul(double x,long long N){
        if(N==0){
            return 1.0;
        }
        //cout<<"N:"<<N<<endl;
        double y=quickMul(x,N/2);
        //cout<<"y:"<<y<<endl;
        return N%2==0?y*y:y*y*x;
    }
    double mypow(double x,int n){
        long long N=n;
        return N>=0?quickMul(x,N):1.0/quickMul(x,-N);
    }
};

int main()
{
    double quick;
    Solution a;
    quick=a.mypow(2.0,37);
    cout<<"quick:"<<quick<<endl;
    return 0;
}
