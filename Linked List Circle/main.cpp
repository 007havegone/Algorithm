/*Given a linked list, determine if it has a cycle in it.

	empty or one Node is not a circle
*/

#include <iostream>
#include <set>
using namespace std;
 /* Definition for singly-linked list.*/
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
	//use the fast pointer and slow pointer
	bool hasCycle(ListNode *head) {
		if (!head||!head->next)
			return false;	
		ListNode* fast = head;
		ListNode* slow = head;
		while (slow&&fast&&fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
				return true;
		}
		return false;
	}
	/*use the hash set
	  room O(1), run_time O(n)
	通过使用具有 不同速度 的快、慢两个指针遍历链表，空间复杂度可以被降低至O(1)。慢指针每次移动一步，而快指针每次移动两步。
	如果列表中不存在环，最终快指针将会最先到达尾部，此时我们可以返回 false。
	现在考虑一个环形链表，把慢指针和快指针想象成两个在环形赛道上跑步的运动员（分别称之为慢跑者与快跑者）。而快跑者最终一定会追上慢跑者。
	这是为什么呢？
	考虑下面这种情况（记作情况 A）- 假如快跑者只落后慢跑者一步，在下一次迭代中，它们就会分别跑了一步或两步并相遇。
	其他情况又会怎样呢？例如，我们没有考虑快跑者在慢跑者之后两步或三步的情况。
	但其实不难想到，因为在下一次或者下下次迭代后，又会变成上面提到的情况 A。
	可理解为速度差为1，每进行一次距离减一，环形上最后一定会相遇
	*/
	bool hasCycle(ListNode* head) {
		set<ListNode*> s;
		ListNode* p = head;
		while (p) {
			if (s.find(p) != s.end())
				return true;
			s.insert(p);
			p = p->next;
		}
		return false;
	}

};