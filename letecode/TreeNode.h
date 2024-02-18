#include <iostream>
using namespace std;
typedef int Element;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Btree{
public:
    TreeNode* root;
	void Init() {
        cout << "输入树的值：" << endl;
		root = CreatBTree();
		cout << "树创建成功" << endl;
	}
 
	//创建树(前序)
	TreeNode* CreatBTree() {
		TreeNode* p;
		Element number;
		cin >> number;
		if (number == 0)
			p = nullptr;
		else {
			p = new TreeNode(number);
			p->left = CreatBTree();
			p->right = CreatBTree();
		}
		return p;
	}
};