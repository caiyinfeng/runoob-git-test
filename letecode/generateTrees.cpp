/*
给你一个整数 n ，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树 。可以按 任意顺序 返回答案。

*/
#include <iostream>
#include "vectorPrint.h"
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#if 0
class Solution {
public:
    vector<TreeNode*> dfs(int start,int end){
        if(start>end){
            return {nullptr};
        }
        vector<TreeNode*> allTrees;
        for(int i=start;i<=end;i++)
        {
            vector<TreeNode*> leftTrees=dfs(start,i-1);
            vector<TreeNode*> rightTrees=dfs(i+1,end);
            for(auto& left:leftTrees){
                for(auto& right:rightTrees){
                    TreeNode* currTree=new TreeNode(i);
                    currTree->left=left;
                    currTree->right=right;
                    allTrees.emplace_back(currTree);
                }
            }
        }
        return allTrees;
    }
    vector<TreeNode*> generateTrees(int n) {
            if(!n){
                return {};        
        }
        return dfs(1,n);
    }
};
#endif
#if 1
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        //用动态规划记录树的结构
        vector<vector<TreeNode*>> dp(n+1);
        dp[0].push_back(NULL);
        //动态规划
        for(int len=1;len<=n;++len){
            for(int i=1;i<=len;++i){
                for(auto l:dp[i-1]){
                    for(auto r:dp[len-i]){
                        TreeNode* root=new TreeNode(i);
                        root->left=l;
                        root->right=clone(r,i);
                        dp[len].push_back(root);
                    }
                }
            }
        }
        return dp[n];       
    }
    //复制树的结构并加上偏置
    TreeNode* clone(TreeNode* root,int offset){
        if(!root) return NULL;
        TreeNode* r=new TreeNode(root->val+offset);
        r->left=clone(root->left,offset);
        r->right=clone(root->right,offset);
        return r;
    }
};
#endif
int main(){
    int n=3;
    Solution abc;
    vector<TreeNode*> allTrees;
    allTrees=abc.generateTrees(n);
    return 0;
}