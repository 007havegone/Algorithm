#include <iostream>
using namespace std;

/*
	һ������һ����ֻ����һ��(��������)������������ż���Σ��ҳ�ֻ����һ�ε���
*/

int main()
{
	int arr[] = { 13,2,4,5,6,6,5,5,5,4,2 };
	int arr1[] = { 1,2,3,2,1,3,3,1,2,15,15,15 };
	int ans = 0;
	for (auto &i : arr)
		ans = ans ^ i;
	cout << ans << endl;
	ans = 0;
	for (auto &i : arr1)
		ans = ans ^ i;
	cout << ans << endl;
}