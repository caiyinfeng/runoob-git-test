/*
按字典 wordList 完成从单词 beginWord 到单词 endWord 转化，一个表示此过程的 转换序列 是形式上像 beginWord -> s1 -> s2 -> ... -> sk 这样的单词序列，并满足：

    每对相邻的单词之间仅有单个字母不同。
    转换过程中的每个单词 si（1 <= i <= k）必须是字典 wordList 中的单词。注意，beginWord 不必是字典 wordList 中的单词。
    sk == endWord

给你两个单词 beginWord 和 endWord ，以及一个字典 wordList 。请你找出并返回所有从 beginWord 到 endWord 的 最短转换序列 ，如果不存在这样的转换序列，返回一个空列表。每个序列都应该以单词列表 [beginWord, s1, s2, ..., sk] 的形式返回。
*/
#include "vectorPrint.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
class Solution
{
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        vector<vector<string>> res;
        // 因为需要快速判断扩展出的单词是否在 wordList 里，因此需要将 wordList 存入哈希表，这里命名为「字典」
        unordered_set<string> dict = {wordList.begin(), wordList.end()};
        // 修改以后看一下，如果根本就不在 dict 里面，跳过
        if (dict.find(endWord) == dict.end())
        {
            return res;
        }
        // 特殊用例处理
        dict.erase(beginWord);

        // 第 1 步：广度优先搜索建图
        // 记录扩展出的单词是在第几次扩展的时候得到的，key：单词，value：在广度优先搜索的第几层
        unordered_map<string, int> steps = {{beginWord, 0}};
        // 记录了单词是从哪些单词扩展而来，key：单词，value：单词列表，这些单词可以变换到 key ，它们是一对多关系
        unordered_map<string, set<string>> from = {{beginWord, {}}};
        int step = 0;
        bool found = false;
        queue<string> q = queue<string>{{beginWord}};
        int wordLen = beginWord.length();
        while (!q.empty())
        {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                const string currWord = move(q.front());
                string nextWord = currWord;
                q.pop();
                // 将每一位替换成 26 个小写英文字母
                for (int j = 0; j < wordLen; ++j)
                {
                    const char origin = nextWord[j];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        nextWord[j] = c;
                        if (steps[nextWord] == step)
                        {
                            from[nextWord].insert(currWord);
                        }
                        if (dict.find(nextWord) == dict.end())
                        {
                            continue;
                        }
                        // 如果从一个单词扩展出来的单词以前遍历过，距离一定更远，为了避免搜索到已经遍历到，且距离更远的单词，需要将它从 dict 中删除
                        dict.erase(nextWord);
                        // 这一层扩展出的单词进入队列
                        q.push(nextWord);
                        // 记录 nextWord 从 currWord 而来
                        from[nextWord].insert(currWord);
                        // 记录 nextWord 的 step
                        steps[nextWord] = step;
                        if (nextWord == endWord)
                        {
                            found = true;
                        }
                    }
                    nextWord[j] = origin;
                }
            }
            if (found)
            {
                break;
            }
        }
        // 第 2 步：回溯找到所有解，从 endWord 恢复到 beginWord ，所以每次尝试操作 path 列表的头部
        if (found)
        {
            vector<string> Path = {endWord};
            backtrack(res, endWord, from, Path);
        }
        return res;
    }

    void backtrack(vector<vector<string>> &res, const string &Node, unordered_map<string, set<string>> &from,
                   vector<string> &path)
    {
        if (from[Node].empty())
        {
            res.push_back({path.rbegin(), path.rend()});
            return;
        }
        for (const string &Parent : from[Node])
        {
            path.push_back(Parent);
            backtrack(res, Parent, from, path);
            path.pop_back();
        }
    }
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> dict = {wordList.begin(), wordList.end()};
        if (dict.find(endWord) == dict.end())
            return 0;
        dict.erase(beginWord);
        int step = 1;
        queue<string> q = queue<string>{{beginWord}};
        int wordLen = beginWord.length();
        while (!q.empty())
        {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                const string currWord = move(q.front());
                string nextWord = currWord;
                q.pop();
                for (int j = 0; j < wordLen; ++j)
                {
                    const char origin = nextWord[j];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        nextWord[j] = c;
                        if (dict.find(nextWord) == dict.end()) continue;
                        dict.erase(nextWord);
                        q.push(nextWord);
                        if (nextWord == endWord)
                        {
                            cout<<step<<endl;
                            return step;
                        }
                    }
                    nextWord[j]=origin;
                }
            }
        }
    }
};

int main()
{
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    Solution abc;
    vector<vector<string>> result;
    int step;
    result = abc.findLadders(beginWord, endWord, wordList);
    step=abc.ladderLength(beginWord, endWord, wordList);
    cout<<step<<endl;
    //PrintVecofVec2(result);
    return 0;
}