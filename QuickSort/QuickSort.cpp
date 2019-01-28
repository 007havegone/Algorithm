/*
	快速排序的2中思路，小改进
*/

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 107;
int nums[N];
int n;
/*
基准元素选择有以下几张方法：
取第一个元素,
取最后一个元素,
取中间元素,
取第一个，最后一个，中间一个的中位数
取第一个，最后一个中间的随机数

据统计，越随机，效率越接近O(nlogn)
*/

/*交换次数过多，一些没必要*/
int partition(int A[], int low, int high)
{
	int pivot = A[low];
	int i = low;
	int j = high;
	while (i < j)
	{
		while (i < j&&A[j] >= pivot)j--;
		if (i < j)
			swap(A[i++], A[j]);
		while (i < j&&A[i] <= pivot)i++;
		if (i < j)
			swap(A[i], A[j--]);
	}
	return i;
}
/*将基准元素保存，不用一直交换，最后一次赋值基准元素就行*/
int partition2(int A[], int low, int high)
{
	int pivot = A[low];
	int i = low;
	int j = high;
	while (i<j)
	{
		while (i < j&&A[j] >= pivot)j--;
		if (i < j)
			A[i++] = A[j];
		while (i < j&&A[i] <= pivot)i++;
		if (i < j)
			A[j--] = A[i];
	}
	A[i] = pivot;
	return i;
}
/*
找到小于pivot和大于pivot的值，直接进行交换，最后在放置pivot，也可以适当减少次数
*/
int partiton3(int A[], int low, int high)
{
	int pivot = A[low];
	int i = low;
	int j = high;
	while (i < j)
	{
		while (i < j&&A[i] <= pivot)i++;
		while (i < j&&A[j] >= pivot)j--;
		if (i < j)
			swap(A[i++], A[j--]);
	}
	if (pivot < A[i])
	{
		swap(A[i - 1], A[low]);
		return i - 1;
	}
	swap(A[i], A[low]);
	return i;
}
void quickSort(int A[], int low, int high)
{
	int mid;
	if (low < high)//数组长度大于1时
	{
		//mid = partition(A, low, high);
		//mid = partition2(A, low, high);
		mid = partiton3(A, low, high);
		quickSort(A, low, mid - 1);
		quickSort(A, mid + 1, high);
	}
}
void quickSort(int A[], int len)
{
	quickSort(A, 0, len - 1);
	
}
int main()
{
	cout << "输入数字个数" << endl;
	cin >> n;
	cout << "输入数字" << endl;
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	quickSort(nums,n);
	cout << "After quickSort : ";
	for (int i = 0; i < n; i++)
		cout << nums[i] << " ";
}