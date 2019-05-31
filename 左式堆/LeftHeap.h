#pragma once
/*
	��ʽ�ѣ��ֳ�Ϊ��ƫ�����������
	�ڴ�ͳ������С���ںϲ�������
	�ýṹ�ϲ������ֻ��ҪO��logN��
*/
struct TreeNode;
typedef TreeNode *PriorityQueue;
typedef int ElementType;
PriorityQueue Initialize();
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

#define Insert(X,H) (H=Insert1( (X), H));
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin(PriorityQueue H);

struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;//null path length,��һ��û���������ӵĽڵ����̾���
};

