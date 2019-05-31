#include<iostream>
#include"SkewHeap.h"
using namespace std;

int main()
{
	PriorityQueue H1 = Initialize();
	int arr[] = { 4,5,1,2,3,11 };
	int arr2[] = { 42,11,21,33,55 };
	for (auto i : arr)
		Insert(i, H1);
	PriorityQueue H2 = Initialize();
	for (auto i : arr2)
		Insert(i, H2);

	PriorityQueue H3 = Merge(H1, H2);
	while (!IsEmpty(H3))
	{
		cout << FindMin(H3) << " ";
		H3 = DeleteMin(H3);
	}
	cout << endl;
	return 0;
}