/*
	Given a linked list, swap every two adjacent nodes and return its head.
*/
#include <iostream>
 /* Definition for singly-linked list.*/
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
         if (!head || !head->next)//小于等于1个结点
			  return head;
		  ListNode* ret=new ListNode(0);// new a temp node
		  ListNode* pre = ret;
		  pre->next = head;
		  while (pre->next&&pre->next->next)
		  {
			  ListNode* pa = pre->next;
			  ListNode* pb = pa->next;
			  pre->next = pb;
			  pa->next = pb->next;
			  pb->next = pa;
			  pre = pa;
		  }
		  return ret->next;
    }
};