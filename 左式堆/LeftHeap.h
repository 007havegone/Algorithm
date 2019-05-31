#pragma once
/*
	左式堆，又称为左偏树、左高树等
	在传统最大堆最小堆在合并的困难
	该结构合并二叉堆只需要O（logN）
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
	int Npl;//null path length,到一个没有两个孩子的节点的最短距离
};

