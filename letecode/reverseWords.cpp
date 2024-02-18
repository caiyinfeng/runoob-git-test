#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

#if 0
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(),s.end());
        int n=s.size();
        int idx=0;
        for(int start=0;start<n;++start){
            if(s[start]!=' '){
                cout<<"start: "<<start<<endl;
                if(idx!=0) s[idx++]=' ';
                cout<<"s:16 "<<s<<" "<< idx<<endl;
                int end=start;
                while(end<n&&s[end]!=' ') s[idx++]=s[end++];
                cout<<"s:19 "<<s<<" "<< idx<<endl;
                reverse(s.begin()+idx-(end-start),s.begin()+idx);
                cout<<"s:20 "<<s<<" "<< idx<<endl;
                start=end;
            }
        }
        s.erase(s.begin()+idx,s.end());
        return s;
    }
};
#endif
#if 1
class Solution {
public:
    string reverseWords(string s) {
        int left=0,right=s.size()-1;
        while(left<=right&&s[left]==' ') ++left;
        while(left<=right&&s[right]==' ') --right;
        deque<string> d;
        string word;
        while(left<=right){
            char c=s[left];
            if(word.size()&&c==' '){
                d.push_front(move(word));
                word="";
            }else if(c!=' '){
                word+=c;
            }
            ++left;
        }
        d.push_front(move(word));
        string ans;
        while(!d.empty()){
            ans+=d.front();
            d.pop_front();
            if(!d.empty()) ans+=' ';
        }
        return ans;
    }
};
#endif
int main(){
    string s="  the sky is blue  ";
    string result;
    Solution abc;
    result=abc.reverseWords(s);
    cout<<result<<endl;
    return 0;
}