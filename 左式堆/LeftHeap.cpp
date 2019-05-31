#include"LeftHeap.h"
#include<iostream>
using namespace std;

PriorityQueue Initialize()
{
	return NULL;
}

/*��ʽ�Ѻϲ��ľ���ʵ��*/
static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2);


int IsEmpty(PriorityQueue H)
{
	return H == NULL;
}

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL)//��һ����Ϊ�գ�����
		return H2;
	if (H2 == NULL)
		return H1;
	//����С�Ķѵ��������ʹ�ĶѺϲ������ﱣ֤H1<H2
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

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue	H2)
{
	if (H1->Left == NULL)
		H1->Left = H2;
	else
	{
		/*�������ǿգ����������ʹ�ĶѺϲ���
		Ȼ���γɵ����ӵ�H1����������*/
		H1->Right = Merge(H1->Right, H2);
		//����H1�ĺ��Ӻ�֤�������ĸ߶ȴ���������
		if (H1->Left->Npl < H1->Right->Npl)
			SwapChildren(H1);
		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}

PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
	PriorityQueue SingleNode;

	SingleNode = new TreeNode;
	if (SingleNode == NULL)
	{
		cerr << "Out of space!!!" << endl;
		exit(1);
	}
	else
	{
		SingleNode->Element = X;SingleNode->Npl = 0;
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


ElementType FindMin(PriorityQueue H)
{
	if (!IsEmpty(H))
		return H->Element;
	cerr << "Priority queue is empty" << endl;
	return 0;
}