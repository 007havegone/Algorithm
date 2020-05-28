/*
 *Solution使用常规的归并方法，里面的B数组还可以考虑用全局变量，则不用一直
 *重新创建，节省部分时间。
 *Solution2利用了反转字符串的特性来实现O(1)归并,不需要开额外数组，最终空间内复杂度为
 *栈的深度O(logn)，时间复杂度为O(nlogn)
 */
#include <iostream>
using namespace std;

const int N = 107;
int arr[N];
class Solution
{
public:
	static void Merge(int *A, int low, int mid, int high)
	{
		int *B = new int[high - low + 1];
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
		for (int i = low, k = 0; i <= high; i++)
			A[i] = B[k++];
		delete[]B;
	}
	static void MergeSort(int *A, int low, int high)
	{
		if (low < high)//长度大于1
		{
			int mid = (high + low) / 2;
			MergeSort(A, low, mid);
			MergeSort(A, mid + 1, high);
			Merge(A, low, mid, high);
		}
	}
};
class Solution2
{
public:
	static void	MergeSort(int *A,int low,int high)
	{
		if(low<high)
		{
			int mid = (high + low) >> 1;
			MergeSort(A, low, mid);
			MergeSort(A, mid+1, high);
			Merge(A, low, mid, high);
		}
	}
	static void Merge(int *A,int low,int mid,int high)
	{
		int i = low, p = mid + 1, j = mid + 1;//p指向待转移串起点，j指向转移串结束点下一个位置
		while(j<=high&&i<j)//j为扫描完，同时i!=j，未确定整体有序
		{
			while (i < j&&A[i] <= A[j])++i;//找切入点，此处A[i]<=A[j]，否则不稳定
			if (i >= j)break;//整体已有序，结束
			while (j <= high && A[j] < A[i])//此处A[j]<A[i]，否则不稳定
				++j;//找到待插入串的结束位置
			Reverse(A, i, p - 1);
			Reverse(A, p, j - 1);
			Reverse(A, i, j - 1);//反转后A[p,j-1]的内容转移到最终位置
			i += (j - p);//跳过被转移的数
			p = j;//从新记录转移串起点
		}
	}
	static void Reverse(int *A,int l,int r)
	{
		while(l<r)
			swap(A[l++], A[r--]);
	}
};
int main()
{
	cout << "输入个数:";
	int n;
	cin >> n;
	cout << "输入数字:";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	Solution2::MergeSort(arr, 0, n-1);
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}