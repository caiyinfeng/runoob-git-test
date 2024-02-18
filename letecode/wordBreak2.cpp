/*
给定一个字符串 s 和一个字符串字典 wordDict ，在字符串 s 中增加空格来构建一个句子，使得句子中所有的单词都在词典中。以任意顺序 返回所有这些可能的句子。

注意：词典中的同一个单词可能在分段中被重复使用多次。
*/
#include "vectorPrint.h"
#include <unordered_map>
#include <unordered_set>
class Solution {
private:
    unordered_map<int,vector<string>> ans;
    unordered_set<string> wordSet;
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        wordSet=unordered_set<string>(wordDict.begin(),wordDict.end());
        backtrack(s,0);
        return ans[0];
    }
    void backtrack(const string& s,int index){
        if(!ans.count(index)){
            if(index==s.size()){
                ans[index]={""};
                return;
            }
            ans[index]={};
            for(int i=index+1;i<=s.size();++i){
                string word=s.substr(index,i-index);
                if(wordSet.count(word)){
                    backtrack(s,i);
                    for(const string& succ:ans[i]){
                        ans[index].push_back(succ.empty()?word:word+" "+succ);
                        cout<<i<<endl;
                        vectorcoutAuto(ans[i]);
                        vectorcoutAuto(ans[0]);
                    }
                }
            }
        }
    }
};
int main(){
    string s = "catsanddog";
    vector<string> wordDict = {"cat","cats","and","sand","dog"};
    Solution abc;
    vector<string> result;
    result = abc.wordBreak(s, wordDict);
    //vectorcoutAuto(result);
    return 0;
}