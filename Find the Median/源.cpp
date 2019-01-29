#include <iostream>
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	int FindTheMedian(ListNode* head) {
		if (!head)//not node return 0
			return 0;
		if (!head->next)
			return head->val;//one node return it's val
		ListNode* fast = head;
		ListNode* slow = head;
		while (slow&&fast)
		{
			if (!fast->next)//odd number 
				return slow->val;
			else if (!fast->next->next)//even number
				return (slow->val + slow->next->val) / 2;
			else {
				slow = slow->next;
				fast = fast->next->next;
			}
		}
	}
};