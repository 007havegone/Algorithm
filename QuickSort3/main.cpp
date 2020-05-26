/**
 *算法导论练习7.4-6
 * Medium Three的方法，取left、right和mid的中位数作为pivot。
 * 当数组较小时采用InsertSort
 */
#include<iostream>
#include<algorithm>
#include <random>		// std::default_random_engine
#include <chrono>       // std::chrono::system_clock
using namespace std;
/*
	一般情况下，CUTOFF取 5-15之间大多情况会取得不错的效果。
 */
const int CUTOFF = 3;
class QuickSortMedium3
{
public:
	static int Medium3(int A[], int left, int right)
	{
		int center = (left + right) / 2;
		if (A[left] > A[center])swap(A[left], A[center]);
		if (A[left] > A[right])swap(A[left], A[right]);
		if (A[center] > A[right])swap(A[center], A[right]);
		/* A[left] <= A[center] <= A[right]*/
		swap(A[center], A[right - 1]);
		return A[right - 1];
	}
	static void sort(int A[], int left, int right)
	{
		if (left + CUTOFF <= right)
		{
			int i = left, j = right - 1;
			int pivot = Medium3(A, left, right);
			while (true)
			{

				while (A[++i] < pivot);
				while (A[--j] > pivot);
				if (i < j)
					swap(A[i], A[j]);
				else
					break;
			}
			//	i结束时位于大于等于pivot的位置
			swap(A[i], A[right - 1]);
			sort(A, left, i - 1);
			sort(A, i + 1, right);
		}
		else
			InsertSort(A + left, right - left + 1);
	}
	/*
		插入排序处理三长度CUTOFF以下的数组
	 */
	static void InsertSort(int A[], int len)
	{
		if (len <= 1)
			return;
		for (int i = 1; i < len; ++i)
		{
			int j = i - 1;
			int t = A[i];
			while (j >= 0 && A[j] > t)
			{
				A[j + 1] = A[j];
				--j;
			}
			A[j + 1] = t;
		}
	}
};
/*
	比较两个数组是否相等。
 */
template<typename T, unsigned N, unsigned M>
bool equalArr(const T(&A)[N], const T(&B)[M])
{
	if (N != M)
		return false;
	for (int i = 0; i < N; ++i)
	{
		if (A[i] != B[i])
			return false;
	}
	return true;
}
/*
	打印数组
 */
template<typename T, unsigned N>
void printArr(const T(&arr)[N])
{
	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}
int main()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	int A[] = { 4,5,61,21,34,64,64,12,45,12,-110,15,-451,12,61,97,124,44,12,45,112,35,77 };
	int B[] = { 4,5,61,21,34,64,64,12,45,12,-110,15,-451,12,61,97,124,44,12,45,112,35,77 };
	//打乱顺序
	shuffle(begin(A), end(A), std::default_random_engine(seed));
	shuffle(begin(B), end(B), std::default_random_engine(seed));
	int sz = sizeof A / sizeof(int);
	//采用三中值的快速排序 数组A
	QuickSortMedium3::sort(A, 0, sz - 1);
	//标准库的快速排序 数组B
	sort(B, B + sz);

	printArr(A);
	cout << boolalpha << equalArr(A, B);
	return 0;
}