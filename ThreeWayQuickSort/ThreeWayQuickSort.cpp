/**
 * 算法导论思考题7-2
 * 三向切分快速排序
 */
#include<iostream>
#include<functional>
#include<ctime>
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
class ThreeWayQuickSort
{
public:
	//三向切分的快速排序
	static void sort(int A[], int lo, int hi)
	{
		if (lo >= hi)return;
		int x = A[lo];
		// [lo,lt-1]为小于,[lt,i-1]为等于,[gt+1,hi]为大于,[i,gt]待判定
		int lt = lo, i = lo + 1, gt = hi;
		while (i <= gt)
		{
			if (A[i] < x)
				swap(A[lt++], A[i++]);
			else if (A[i] > x)
				swap(A[gt--], A[i]);
			else
				++i;
		}
		sort(A, lo, lt - 1);
		sort(A, gt + 1, hi);
	}
};

class RandomQuickSort
{
public:
	static void quickSort(int A[], int p, int q)
	{
		if (p < q)
		{
			srand(time(0));
			int i = p + rand() % (q - p + 1);
			swap(A[i], A[p]);
			pair<int, int> rang = partition(A, p, q);
			quickSort(A, p, rang.first);
			quickSort(A, rang.second, q);
		}
	}
	/*
		[lo,lt-1]小于x
		[lt,i-1]等于x
		[i,gt]待判定
		[gt+1,hi]大于x
	 */
	static pair<int, int> partition(int A[], int lo, int hi)
	{
		int lt = lo, i = lo + 1, gt = hi;
		int x = A[lo];
		while (i <= gt)
		{
			if (A[i] < x)
				swap(A[i++], A[lt++]);
			else if (A[i] > x)
				swap(A[i], A[gt--]);
			else
				i++;
		}
		return make_pair(lt - 1, gt + 1);
	}

};
int main()
{
	int A[] = { 7,8,9,1,5,4,12,16 };
	int B[] = { 15,14,12,12,8,16,0,88 };
	int szA = sizeof(A) / sizeof(int);
	// ThreeWayQuickSort::sort(A,0,szA-1);
	RandomQuickSort::quickSort(A, 0, szA - 1);
	prinrArr(A);
	return 0;
}