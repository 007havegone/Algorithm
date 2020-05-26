/**
 * 算法导论思考题7-1
 */
#include<iostream>
using namespace std;
template<typename T, unsigned N>
void prinrArr(T(&arr)[N])
{
	cout << "[ ";
	for (auto i : arr)
		cout << i << " ";
	cout << "]\n";
}
class HoareQuickSort
{
public:
	static void sort(int A[], int p, int q)
	{
		if (p < q)
		{
			int t = HoarePartition(A, p, q);
			sort(A, p, t);//这里是[p,t]而不是[p,t-1]，t位置的数并不是在正确位置
			sort(A, t + 1, q);
		}
	}
	static int HoarePartition(int A[], int p, int q)
	{
		int x = A[p];
		int i = p - 1;
		int j = q + 1;
		/*
			结束时有 A[p]~A[j] <= A[j+1]~A[q]
			因此返回的值为两个区间的分界线。
			但是该位置的数并不是排好序的。
			下一次递归的时候需要包含在其中一个分区中
		 */
		while (true)
		{
			while (A[--j] > x);
			while (A[++i] < x);
			if (i < j)
				swap(A[i], A[j]);
			else
				return j;
		}
	}

};
int main()
{
	int A[] = { 13,19,9,5,12,8,7,4,11,2,6,21 };
	int B[] = { 13,19,50,20,2,15,20,4,11,53,6,21 };
	int szA = sizeof(A) / sizeof(A[0]);
	HoareQuickSort::sort(A, 0, szA - 1);
	HoareQuickSort::sort(B, 0, szA - 1);
	prinrArr(A);
	prinrArr(B);
}