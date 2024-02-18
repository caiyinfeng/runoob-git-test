#include <iostream>
#include <unordered_map>
#include <climits>
using namespace std;
#if 0
class Solution {
public:
    unordered_map<char,int> ori,cnt;
    bool check(){
        for(const auto &p:ori){
            if(cnt[p.first]<p.second){
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t) {
        for(const auto &c:t){
            ++ori[c];
        }
        int l=0,r=-1;
        int len=INT_MAX,ansL=-1,ansR=-1;
        while(r<int(s.size())){
            if(ori.find(s[++r])!=ori.end()){
                ++cnt[s[r]];
            }
            while(check()&&l<=r){
                if(r-l+1<len){
                    len=r-l+1;
                    ansL=l;
                }
                if(ori.find(s[l])!=ori.end()){
                    --cnt[s[l]];
                }
                ++l;
            }

        }
        return ansL==-1?string():s.substr(ansL,len);
    }
};
#endif
#if 1
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> need;
        int Len=t.size(),correct=0;
        for(char c:t)
            need[c]++;  //  s需要包含的字符
        int left=0,right=0,min_len=s.size()+1,start=0;
        string res;
        for(;right<s.size();right++)
        {
            if(need[s[right]]>0) correct++; // 是t中的字符  有效添加
            need[s[right]]--;  // 需要包含的 当前字符 数目--， 对于非t的字符也直接--，并不关心
            cout<<"57"<<" right:"<<right<<" s[right]:"<<s[right]<<" need[s[right]]:"<<need[s[right]]<<" correct:"<<correct<<endl;
            while(correct==Len)
            {
                if(min_len>right-left+1)  // 满足包含t时记录一下最短字符串
                {
                    min_len=right-left+1;
                    // res=s.substr(left,min_len); // 当输入用例中冗余过长时 频繁的字符串截取操作会超时 最好直接记录一下start
                    start=left;
                }
                if(need[s[left]]==0) correct--; // 不属于t的字符一开始need中就为0 添加过程中可能--，left左移遇到再++回来 不可能满足该if条件
                need[s[left]]++;
                left++;
                cout<<"69"<<" left:"<<left<<" s[left]:"<<s[left]<<" need[s[left]]:"<<need[s[left]]<<" correct:"<<correct<<endl;
            }
            /* 另一种写法： 先while去除左侧冗余字符 */
            // while(need[s[left]]<0)  // 如果left对应的字符是冗余的，那么进行右移删除
            // {
            //     need[s[left]]++;
            //     left++;
            // }
            // if(correct==Len)
            //     if(min_len>right-left+1)  // 满足包含t时记录一下最短字符串
            //     {
            //         min_len=right-left+1;
            //         res=s.substr(left,min_len);
            //         start=left;
            //     }
        }
        return min_len==s.size()+1?"":s.substr(start,min_len);
        // return res;
    }
};
#endif
int main()
{
    string s="ADOBECODEBANC";
    string t="ABC";
    Solution abc;
    string result;
    result=abc.minWindow(s,t);
    cout<<result<<endl;
    return 0;
}