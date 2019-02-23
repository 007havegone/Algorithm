/*
Given a linked list, rotate the list to the right by k places, where k is non-negative.
Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
*/
//  Definition for singly-linked list.
#include <iostream>
  struct ListNode {
	  int val;
	  ListNode *next;
	  ListNode(int x) : val(x), next(NULL) {}
  };
class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head || !head->next)
			return head;
		ListNode* t = head;
		ListNode* p;
		ListNode* ed;
		int len = 0;
		///��ȡ����
		while (t){
			len++;
			t = t->next;
		}
		k = k % len;//���ƶ���������
		if (k == 0)return head;//Ϊ0�����ƶ�ֱ�ӷ���
		k = len - k-1;//Ҫָ���len-k,��ʼָ���һ����㣬���ƶ�len-k-1��
		t = head;
		while (t) {
			if (!k--) {
				p = t;//ָ���len-k�����
			}
			if (!t->next)//��¼β�ڵ�
				ed = t;
			t = t->next;
		}//�Ա������ת
		ed->next = head;
		t = p->next;//��¼�µ�ͷ���
		p->next = nullptr;
		return t;
	}
};