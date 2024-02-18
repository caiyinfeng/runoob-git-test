#include <iostream>
class Solution {
public:
    bool isPalindrome(int x) {
        std::string c;
        c=std::to_string(x);
        int count=c.size();
        int i=0;
        bool back=x<0?false:true;
        while((i*2)<=count&&back==true)
        {
            back=back&&(c[i]==c[count-i-1]?true:false);
            i++;
            
        }
        return back;
    }
};

int main()
{
    int abc=12;
    Solution aa;
    bool a;
    a=aa.isPalindrome(abc);
    printf("length:%d\n",a);
    return 0;
}
    