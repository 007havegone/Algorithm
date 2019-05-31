typedef int ElementType;
#ifndef SKEWHEAP_H_
/*
	б��(SkewHeap)����ʽ�ѵ��Ե�����ʽ��ʵ�������ܼ򵥡�
	������չ����AVL����Ĺ�ϵ��
	б���Ǿ��ж���Ķ����������ǲ����ڶ����Ľṹ���ơ�
	��ͬ����ʽ�ѣ���������ڵ����·����(NPL)���κ���Ϣ��������
	б�ѵ���·���κ�ʱ�̶��������ⳤ����ˣ����в���������ʱ�临�Ӷ�ΪO��N����
	Ȼ����ͬ��չ��һ�����������M�β������ܵ��ʱ�临�Ӷ�ΪO��MlogN)��
	��ˣ�б�ѵ�ÿ�β�����̯��ʱ��ΪO��lgN��
*/

struct TreeNode;
typedef struct TreeNode *PriorityQueue;
typedef int ElementType;
PriorityQueue Initialize();
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

#define Insert(X,H)(H= Insert1(X,H))
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin(PriorityQueue H);
#endif // !SKEWHEAP_H_