/*
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
*/
#include "vectorPrint.h"

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        vector<bool> dp(s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++)
        {
            for (auto &word : wordDict)
            {
                int sz = word.size();
                if (i - sz >= 0 && s.substr(i - sz, sz) == word)
                {
                    cout<<"17 "<<dp[i]<<endl;
                    dp[i] = dp[i] || dp[i - sz];
                    cout<<"19 "<<dp[i]<<" "<<s.substr(i - sz, sz)<<endl;
                }
            }
        }
        return dp[s.size()];
    }
};
int main()
{
    string s = "catsandog";
    vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};
    Solution abc;
    bool result;
    result = abc.wordBreak(s, wordDict);
    return 0;
}