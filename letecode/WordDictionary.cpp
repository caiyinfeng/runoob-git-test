/*
请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。

实现词典类 WordDictionary ：
    WordDictionary() 初始化词典对象
    void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
    bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
*/
#include "vectorPrint.h"
#include <ctype.h>
#include <queue>
#include <array>
#include "string.h"
#if 1
const int M=1e6+50;
int idx,son[M][26];
bool vis[M];
class WordDictionary {
public:
    WordDictionary() {
        memset(son,0,sizeof(son));
        idx=0;
        memset(vis,false,sizeof(vis));
        cout<<"init success"<<endl;
    }
    
    void addWord(string word) {
        int p=0;
        for(auto x:word){
            int u=x-'a';
            if(!son[p][u]) son[p][u]=++idx;
            p=son[p][u];
        }
        vis[p]=true;
    }
    
    bool search(string word) {
        return dfs(word,0,0);
    }
    bool dfs(string word,int u,int cur){
        if(cur==word.size()) return vis[u];
        if(word[cur]=='.'){
            for(int i=0;i<26;++i){
                int p=son[u][i];
                if(p){
                    if(dfs(word,p,cur+1)) return true;
                }
            }
        }else{
            int c=word[cur]-'a';
            int p=son[u][c];
            if(p) return dfs(word,p,cur+1);
        }
        return false;
    }
};
#endif
#if 0
struct TrieNode{
    array<int,26> nex;
    bool ed=false;
    int& operator [](int x){
        return nex[x];
    }
};
class WordDictionary {
private:
    vector<TrieNode> trieNode;
public:
    WordDictionary() {
        trieNode.emplace_back();
    }
    
    void addWord(string word) {
        int cur=0;
        for(auto c:word){
            if(trieNode[cur][c-'a']<=0){
                trieNode[cur][c-'a']=trieNode.size();
                cout<<trieNode.size()<<endl;
                trieNode.emplace_back();
            }
            cur=trieNode[cur][c-'a'];
        }
        trieNode[cur].ed=true;
    }  
    bool search(string word) {
        queue<pair<int,int>> Q;
        Q.push({0,0});
        for(int i=0;i<word.size();++i){
            while(!Q.empty()and Q.front().second==i){
                auto it=Q.front();
                Q.pop();
                if(isalpha(word[i])){
                    if(trieNode[it.first][word[i]-'a']) Q.push({trieNode[it.first][word[i]-'a'],i+1});
                }else{
                    for(int j=0;j<26;++j){
                        if(trieNode[it.first][j]) Q.push({trieNode[it.first][j],i+1});
                    }
                }
            }
        }
        while(!Q.empty()){
            auto it=Q.front();
            Q.pop();
            if(trieNode[it.first].ed) return true;
        }
        return false;
    }
};
#endif
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
int main(){
    WordDictionary abc;
    bool result;
    abc.addWord("abc");
    abc.addWord("efg");
    abc.addWord("acd");
    result=abc.search(".bc");
    cout<<result<<endl;
    return 0;

}