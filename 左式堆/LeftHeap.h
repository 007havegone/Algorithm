typedef int ElementType;

#ifndef LEFTHEAP_H_
/*
	��ʽ�ѣ��ֳ�Ϊ��ƫ�����������
	�ڴ�ͳ������С���ںϲ�������
	�ýṹ�ϲ������ֻ��ҪO��logN��
*/
struct TreeNode;
typedef struct TreeNode *PriorityQueue;
PriorityQueue Initialize();
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

#define Insert(X,H) (H=Insert1( (X), H))
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin(PriorityQueue H);

#endif // !LEFTHEAP_H_


