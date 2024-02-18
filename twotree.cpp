#include <stack>
#include <queue>
#include <iostream>
using namespace std;
typedef int Element;
 
//定义结点
struct BTNode {
	Element data;
	BTNode* lchild;
	BTNode* rchild;
	//结构体的构造函数
	BTNode(Element number) {
		data = number;
		lchild = NULL;
		rchild = NULL;
	}
};
 
//定义二叉树类
class Btree {
public:
	BTNode* Root;
	//初始化创建树头
	void Init() {
		Root = CreatBTree();
		cout << "树创建成功" << endl;
	}
 
	//创建树(前序)
	BTNode* CreatBTree() {
		BTNode* p;
		Element number;
		cin >> number;
		if (number == 0)
			p = NULL;
		else {
			cout << "树创建中" << endl;
			p = new BTNode(number);
			p->lchild = CreatBTree();
			p->rchild = CreatBTree();
		}
		return p;
	}
	
	//前序遍历
	void preOrderTraverse(BTNode *root) {
		if (root) {
			cout << root->data << " ";
			preOrderTraverse(root->lchild);
			preOrderTraverse(root->rchild);
		}
	}
 
	//中序遍历
	void inOrderTraverse(BTNode* root) {
		if (root) {
			inOrderTraverse(root->lchild);
			cout << root->data << " ";
			inOrderTraverse(root->rchild);
		}
	}
 
	//后序遍历
	void lastOrderTraverse(BTNode* root) {
		if (root) {
			lastOrderTraverse(root->lchild);
			lastOrderTraverse(root->rchild);
			cout << root->data << " ";
		}
	}
 
	//求叶子结点个数
	int LeafNum(BTNode* root) {
		if (root == NULL) {
			return 0;
		}
		else if (root->lchild == NULL && root->rchild == NULL)
			return 1;
		else
			return LeafNum(root->lchild) + LeafNum(root->rchild);
	}
 
	//求树的结点个数
	int BTNodeNum(BTNode* root) {
		if (root == NULL)
			return 0;
		else
			return BTNodeNum(root->lchild) + BTNodeNum(root->rchild) + 1;
	}
 
	//求树的深度
	int TreeDepth(BTNode* root) {
		if (root == NULL)
			return 0;
		int left = TreeDepth(root->lchild);
		int right = TreeDepth(root->rchild);
		return left > right ? left + 1 : right + 1;
	}
 
	//中序遍历非递归
	void Traverse(BTNode* root) {
		//创建栈
		stack<BTNode*>s;
		BTNode* p = root;
		BTNode* q = NULL;
		while (p || !s.empty()) {
			if (p) {
				s.push(p);
				p = p->lchild;
			}
			else {
				q = s.top();
				cout << q->data << " ";
				s.pop();
				p = q->rchild;
			}
		}
 
	}
 
	//二叉树层次遍历算法
	void LevelOrder(BTNode* root) {
		//创建队列
		queue<BTNode*>q;
		BTNode* p;
		//先入队头结点
		q.push(root);
		//队不为空
		while (!q.empty()) {
			//取队头
			p = q.front();
			q.pop();
			cout << p->data << " ";
			//左孩子不为空
			if (p->lchild != NULL) {
				q.push(p->lchild);
			}
			//右孩子不为空
			if (p->rchild != NULL) {
				q.push(p->rchild);
			}
		}
	}
};
 
int main()
{
 
	Btree T;
 
	//初始化
	T.Init();
 
	//遍历
	cout << "前序遍历为：" << endl;
	T.preOrderTraverse(T.Root);
	cout << endl;
	cout << "中序遍历为：" << endl;
	T.inOrderTraverse(T.Root);
	cout << endl;
	cout << "后序遍历为：" << endl;
	T.lastOrderTraverse(T.Root);
	cout << endl;
 
	//树的结点个数
	cout << "树的结点个数为：";
	int nodenum = T.BTNodeNum(T.Root);
	cout << nodenum << endl;
 
	//树的叶子个数
	cout << "树的叶子个数为：";
	int leaves = T.LeafNum(T.Root);
	cout << leaves << endl;
 
	//树的深度为：
	cout << "树的深度为：";
	int depth = T.TreeDepth(T.Root);
	cout << depth << endl;
 
	//树的中序非递归遍历
	cout << "树的中序非递归遍历：" << endl;
	T.Traverse(T.Root);
	cout << endl;
 
	//树的层次遍历算法
	cout << "树的层次遍历算法：" << endl;
	T.LevelOrder(T.Root);
	cout << endl;
	system("pause");
	cout << endl;
}