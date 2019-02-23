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
	ͨ��ʹ�þ��� ��ͬ�ٶ� �Ŀ졢������ָ����������ռ临�Ӷȿ��Ա�������O(1)����ָ��ÿ���ƶ�һ��������ָ��ÿ���ƶ�������
	����б��в����ڻ������տ�ָ�뽫�����ȵ���β������ʱ���ǿ��Է��� false��
	���ڿ���һ��������������ָ��Ϳ�ָ������������ڻ����������ܲ����˶�Ա���ֱ��֮Ϊ������������ߣ���������������һ����׷�������ߡ�
	����Ϊʲô�أ�
	������������������������ A��- ���������ֻ���������һ��������һ�ε����У����Ǿͻ�ֱ�����һ����������������
	��������ֻ������أ����磬����û�п��ǿ�������������֮�������������������
	����ʵ�����뵽����Ϊ����һ�λ������´ε������ֻ��������ᵽ����� A��
	�����Ϊ�ٶȲ�Ϊ1��ÿ����һ�ξ����һ�����������һ��������
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