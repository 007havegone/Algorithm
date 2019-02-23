/*
	���������2��˼·��С�Ľ�
*/

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 107;
int nums[N];
int n;
/*
��׼Ԫ��ѡ�������¼��ŷ�����
ȡ��һ��Ԫ��,
ȡ���һ��Ԫ��,
ȡ�м�Ԫ��,
ȡ��һ�������һ�����м�һ������λ��
ȡ��һ�������һ���м�������

��ͳ�ƣ�Խ�����Ч��Խ�ӽ�O(nlogn)
*/

/*�����������࣬һЩû��Ҫ*/
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
/*����׼Ԫ�ر��棬����һֱ���������һ�θ�ֵ��׼Ԫ�ؾ���*/
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
�ҵ�С��pivot�ʹ���pivot��ֵ��ֱ�ӽ��н���������ڷ���pivot��Ҳ�����ʵ����ٴ���
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
	if (low < high)//���鳤�ȴ���1ʱ
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
	cout << "�������ָ���" << endl;
	cin >> n;
	cout << "��������" << endl;
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	quickSort(nums,n);
	cout << "After quickSort : ";
	for (int i = 0; i < n; i++)
		cout << nums[i] << " ";
}