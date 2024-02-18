#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

 void PrintList(ListNode* head){
	ListNode* phead = new ListNode(0);
	phead = head;
	cout<<"链表元素如下: "<<endl;
	while(phead!=NULL){
		cout<<phead->val<<"->";
		head = phead;
		phead = phead->next;  //phead按序往后遍历整个链表
		if(!phead) cout<<"NULL"<<endl;
	}
}
ListNode* CreateList(){
    int n;
	cout<<"请输入初始链表元素个数: "<<endl;
	cin>>n;
	int a[n];
	cout<<"请依次输入链表元素: ";
	for(int i = 0;i<n;i++) cin>>a[i];
	ListNode* head;
    ListNode* phead = new ListNode(0);
	if(!phead) return NULL;
	phead->val = a[0];
	head = phead;
	for(int i = 1;i<n;i++){
		ListNode* newnode = new ListNode(0);
		newnode->val = a[i];
		newnode->next = NULL;
		phead->next = newnode;
		phead = phead->next;
	}
	return head;
}