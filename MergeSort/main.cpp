/*
 *Solutionʹ�ó���Ĺ鲢�����������B���黹���Կ�����ȫ�ֱ���������һֱ
 *���´�������ʡ����ʱ�䡣
 *Solution2�����˷�ת�ַ�����������ʵ��O(1)�鲢,����Ҫ���������飬���տռ��ڸ��Ӷ�Ϊ
 *ջ�����O(logn)��ʱ�临�Ӷ�ΪO(nlogn)
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
		if (low < high)//���ȴ���1
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
		int i = low, p = mid + 1, j = mid + 1;//pָ���ת�ƴ���㣬jָ��ת�ƴ���������һ��λ��
		while(j<=high&&i<j)//jΪɨ���꣬ͬʱi!=j��δȷ����������
		{
			while (i < j&&A[i] <= A[j])++i;//������㣬�˴�A[i]<=A[j]�������ȶ�
			if (i >= j)break;//���������򣬽���
			while (j <= high && A[j] < A[i])//�˴�A[j]<A[i]�������ȶ�
				++j;//�ҵ������봮�Ľ���λ��
			Reverse(A, i, p - 1);
			Reverse(A, p, j - 1);
			Reverse(A, i, j - 1);//��ת��A[p,j-1]������ת�Ƶ�����λ��
			i += (j - p);//������ת�Ƶ���
			p = j;//���¼�¼ת�ƴ����
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
	cout << "�������:";
	int n;
	cin >> n;
	cout << "��������:";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	Solution2::MergeSort(arr, 0, n-1);
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}