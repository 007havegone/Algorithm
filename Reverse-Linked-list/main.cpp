#include <iostream>
//  Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
class Solution {
public:
	//non-recursion
	ListNode* reverseList(ListNode* head) {
		if (!head || !head->next)//empty or only one,return it
			return head;
		ListNode* ph = nullptr;
		ListNode* nex = head;
		while (nex)
		{
			ListNode* t = nex->next;
			nex->next = ph;
			ph = nex;
			nex = t;
		}
		return ph;
	}
	//recursion
	ListNode* reverseList2(ListNode* head) {
		if (!head || !head->next)//empty or a demarcation point
			return head;
		ListNode* curhead = head;
		ListNode* head_next = head->next;
		head = reverseList2(head->next);
		head_next->next = curhead;
		curhead->next = nullptr;
		return head;
	}
};