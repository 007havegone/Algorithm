typedef int ElementType;
#ifndef SKEWHEAP_H_
/*
	斜堆(SkewHeap)是左式堆的自调节形式，实现起来很简单。
	类似伸展树和AVL树间的关系。
	斜堆是具有堆序的二叉树，但是不存在对树的结构限制。
	不同于左式堆，关于任意节点的零路径长(NPL)的任何信息不保留。
	斜堆的右路径任何时刻都可以任意长，因此，所有操作的最坏情况时间复杂度为O（N），
	然而如同伸展树一样，跨必须有M次操作，总的最坏时间复杂度为O（MlogN)。
	因此，斜堆的每次操作的摊还时间为O（lgN）
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