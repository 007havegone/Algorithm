#include <iostream>
using namespace std;

const int N = 107;
int arr[N];
void Merge(int *A,int low,int mid,int high)
{
	int *B = new int[high-low+1];
	int k = 0;
	int i = low, j = mid + 1;
	while (i <= mid && j <= high)
	{
		if (A[i] <= A[j])
			B[k++] = A[i++];
		else
			B[k++] = A[j++];
	}
	while (i <= mid)B[k++] = A[i++];
	while (j <= high)B[k++] = A[j++];
	for (int i=low, k = 0; i <= high; i++)
		A[i] = B[k++];
	delete[]B;
}
void MergeSort(int *A, int low, int high)
{
	if (low < high)//长度大于1
	{
		int mid = (high + low) / 2;
		MergeSort(A, low, mid);
		MergeSort(A, mid + 1, high);
		Merge(A, low, mid, high);
	}
}
int main()
{
	cout << "输入个数:";
	int n;
	cin >> n;
	cout << "输入数字:";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	MergeSort(arr, 0, n-1);
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}