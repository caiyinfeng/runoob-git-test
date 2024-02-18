/*
给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
*/
#include "vectorPrint.h"
#include <stack>
#include "TreeNode.h"
#include <algorithm>


#if 0
class Solution {
public:
    void postorder(TreeNode* root,vector<int>& res){
        if(root==nullptr) return;
        postorder(root->left,res);
        postorder(root->right,res);
        res.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        postorder(root,res);
        return res;
    }
};
#endif
#if 0
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root==nullptr) return res;
        stack<TreeNode*> stk;
        TreeNode* prev=nullptr;
        while(root!=nullptr||!stk.empty()){
            while(root!=nullptr){
                stk.emplace(root);
                root=root->left;
            }
            root=stk.top();
            stk.pop();
            if(root->right==nullptr||root->right==prev){
                res.emplace_back(root->val);
                prev=root;
                root=nullptr;
            }else{
                stk.emplace(root);
                root=root->right;
            }
        }
        return res;
    }
};
#endif
#if 1
class Solution
{
public:
    void addPath(vector<int> &vec, TreeNode *node)
    {
        int count = 0;
        while (node != nullptr)
        {
            ++count;
            vec.emplace_back(node->val);
            node = node->right;
        }
        cout<<"before:"<<count<<endl;
        vectorcoutAuto(vec);
        reverse(vec.end() - count, vec.end());
        cout<<"reverse:"<<endl;
        vectorcoutAuto(vec);
    }

    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> res;
        if (root == nullptr)
        {
            return res;
        }

        TreeNode *p1 = root, *p2 = nullptr;

        while (p1 != nullptr)
        {
            p2 = p1->left;
            if (p2 != nullptr)
            {
                while (p2->right != nullptr && p2->right != p1)
                {
                    p2 = p2->right;
                }
                if (p2->right == nullptr)
                {
                    p2->right = p1;
                    p1 = p1->left;
                    continue;
                }
                else
                {
                    p2->right = nullptr;
                    addPath(res, p1->left);
                }
            }
            p1 = p1->right;
        }
        addPath(res, root);
        return res;
    }
};
#endif
int main(){
    Btree T;
    T.Init();
    vector<int> result;
    Solution abc;
    result=abc.postorderTraversal(T.root);
//    vectorcoutAuto(result);
    return 0;
}