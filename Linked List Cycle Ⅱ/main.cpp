#include <iostream>
  /*Definition for singly-linked list.
  Given a linked list, return the node where the cycle begins.
  If there is no cycle, return null.
  */
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if (!head || !head->next)
			return nullptr;
		ListNode* fast = head;
		ListNode* slow = head;
		while (slow&&fast&&fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)//find the meeting pointer
			{
				slow = head;//let the slow point to head
				while (slow != fast)//get the Node when they meet again,that's is a entrance
				{
					slow = slow->next;
					fast = fast->next;
				}
				return fast;
			}
		}
		return nullptr;
	}
};