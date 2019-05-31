#include"SkewHeap.h"
#include<iostream>
using namespace std;
struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
};
PriorityQueue Initialize()
{
	return NULL;
}

int IsEmpty(PriorityQueue H)
{
	return H == NULL;
}

ElementType FindMin(PriorityQueue H)
{
	if (H != NULL)
		return H->Element;
	cerr << "Priority queue is empty" << endl;
	return 0;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2);

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL)
		return H2;
	if (H2 == NULL)
		return H1;
	if (H1->Element < H2->Element)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}

void SwapChildren(PriorityQueue H)
{
	PriorityQueue tmp;

	tmp = H->Left;
	H->Left = H->Right;
	H->Right = tmp;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL)
		H1->Left = H2;
	else {
		H1->Right = Merge(H1->Right, H2);
		SwapChildren(H1);//斜堆无条件交换
	}
	return H1;
}
PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
	PriorityQueue SingleNode;
	SingleNode = new TreeNode();
	if (SingleNode == NULL)
	{
		cerr << "Out of space!!!" << endl;
		exit(1);
	}
	else
	{
		SingleNode->Element = X;
		SingleNode->Left = SingleNode->Right = NULL;
		H = Merge(SingleNode, H);
	}
	return H;
}
PriorityQueue DeleteMin(PriorityQueue H)
{
	PriorityQueue LeftNode, RightNode;
	if (IsEmpty(H))
	{
		cerr << "Priority queue is empty" << endl;
		return H;
	}
	LeftNode = H->Left; RightNode = H->Right;
	delete H;
	return H = Merge(LeftNode, RightNode);

}