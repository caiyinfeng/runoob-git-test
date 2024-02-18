#include <iostream>
#include <vector>
#include <stack>
using namespace std;
 
//定义结构体
struct ListNode{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class operateList
{
public:
	/*创建单链表*/
	void createList(ListNode *head)
	{
		int i;
		int a[]={1,1,1,1,2,3,4,4,4,5,5};
		head->val=a[0];
		head->next=nullptr;
		ListNode* phead=head; //不破坏头指针
		for(i=1;i<10;i++){
			ListNode* node=new ListNode;
			node->val=a[i];
			node->next=NULL;
			phead->next=node;
			phead=node;
		}
		cout<<"链表创建成功!\n";
	}
	
	/*打印链表*/
	void printList(ListNode* head)
	{
		ListNode* phead=head;
		while(phead->next!=NULL)
		{
			cout<<phead->val<<" ";
			phead=phead->next;
		}
		cout<<phead->val<<"\n";
	}		
	
	/*利用栈先进后出的思想*/
	vector<int> printListInverseByStack(ListNode* head){
		vector<int> result;
		stack<int> arr;
		int i;
		ListNode* phead=head;
		while(phead->next!=NULL)
		{
			arr.push(phead->val);
			phead=phead->next;
		}
		arr.push(phead->val); //最后一个元素
		while(!arr.empty())
		{
			result.push_back(arr.top());
			arr.pop();
		}
		return result;
	}
	
	void printVector(vector<int> result)
	{
		int i;
		for(i=0;i<result.size();i++)
			cout<<result[i]<<" ";
		cout<<"\n";
	}
	ListNode* deleteDuplicates(ListNode* head) {
        if(!head) return head;
        ListNode* dummy=new ListNode(0,head);
        ListNode* cur=dummy;
        while(cur->next&&cur->next->next){
            if(cur->next->val==cur->next->next->val){
                int x=cur->next->val;
                while(cur->next&&cur->next->val==x)
                {
                    cur->next=cur->next->next;
					cout<<"删除列表中的值"<<endl;
                }
            }else{
                cur=cur->next;
				cout<<"保存正确的值"<<endl;
            }
				printList(cur);
				printList(dummy);
        }
        return dummy->next;
    }
};
 
int main()
{
	ListNode* head=new ListNode;
	vector<int> result;
	operateList ll;
	ll.createList(head);
	ll.printList(head);
	//利用栈逆序
	result=ll.printListInverseByStack(head); 
	cout<<"利用栈逆序的结果为：\n";
	ll.printVector(result);
	ListNode* okben=new ListNode;
	okben=ll.deleteDuplicates(head);
	ll.printList(okben);
	return 0;
}