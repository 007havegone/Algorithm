#include<iostream>
#include<algorithm>
using namespace std;

template<typename T, unsigned N>
void prinrArr(T(&arr)[N])
{
	cout << "[ ";
	for (auto i : arr)
		cout << i << " ";
	cout << "]\n";
}
class QuickSort
{
public:
	static void quicksort(int A[], int p, int q)
	{
		if (p < q)
		{
			int t = partition(A, p, q);
			quicksort(A, p, t - 1);
			quicksort(A, t + 1, q);
		}
	}
	//二向切分
	static int partition(int A[], int p, int q)
	{
		int x = A[q];
		int i = p - 1;
		for (int j = p; j < q; ++j)
		{
			if (A[j] <= x)
			{
				++i;
				swap(A[i], A[j]);
			}
		}
		swap(A[i + 1], A[q]);
		return i + 1;
	}
	//算法导论7.1-2 若全部元素相同时，采用一个flag，使得q=(p+q)/2
	static int partition2(int A[], int p, int q)
	{
		int x = A[q];
		int i = p - 1;
		bool flag = true;
		for (int j = p; j < q; ++j)
		{
			if (A[j] < x || A[j] == x && flag)
			{
				swap(A[++i], A[j]);
			}
			if (A[j] == x)
				flag = !flag;
		}
		swap(A[i + 1], A[q]);
		return i + 1;
	}
};
int main()
{
	int A[] = { 7,8,9,1,5,4,12,16 };
	int szA = sizeof(A) / sizeof(int);
	QuickSort::quicksort(A, 0, szA - 1);
	prinrArr(A);
	return 0;
}
