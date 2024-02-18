/*
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。 
*/
#include "LisNode.h"
#if 1
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int l, int r) {
        ListNode* dummyHead=new ListNode(0);
        dummyHead->next=head;
        r-=l;
        ListNode* hh=dummyHead;
        while(l-->1)
            hh=hh->next;
        ListNode* prv=hh->next;
        //ListNode* cur=prv->next;
        while(r-->0){
            ListNode* nxt=prv->next;
            prv->next=nxt->next;
            nxt->next=hh->next;
            hh->next=nxt;
            
        }
        //hh->next->next=cur;
        //hh->next=prv;
        return dummyHead->next;
    }
};
#endif
int main(){
    int l,r;
    cout<<"left:"<<endl;
    cin>>l;
    cout<<"right"<<endl;
    cin>>r;
    ListNode* head;
    head=CreateList();
    PrintList(head);
    Solution abc;
    ListNode* result;
    result=abc.reverseBetween(head,l,r);
    PrintList(result);
    return 0;
}