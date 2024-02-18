/*
给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。
*/
#include "vectorPrint.h"
#if 1
class Solution {
public:
    int commpute_next(string pattern){
        vector<int> next(pattern.size()+1,0);
        next[0]=-1;
        next[1]=0;
        int i=2;
        int k=0;
        while(i<next.size()){
            cout<<"i:"<<i<<endl;
            if(pattern[i-1]==pattern[k]){
                next[i]=k+1;
                k=k+1;
                ++i;
            }else if(k==0){
                next[i]=0;
                ++i;
            }else{
                k=next[k];
            }
            cout<<"k:"<<k<<endl;
        
        }
        vectorcoutAuto(next);
        return next[next.size()-1];
    }
    string shortestPalindrome(string s) {
        if(s=="") return "";
        string reverse_str(s.rbegin(),s.rend());
        string pattern=s+'#'+reverse_str;
        cout<<pattern<<endl;
        int max_len=commpute_next(pattern);
        cout<<max_len<<endl;
        return reverse_str.substr(0,reverse_str.size()-max_len)+s;
    }
};
#endif
int main(){
    Solution abc;
    string s="ABADFBA";
    string result;
    result=abc.shortestPalindrome(s);
    cout<<result<<endl;
    return 0;
}