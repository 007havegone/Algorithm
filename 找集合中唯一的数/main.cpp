#include <iostream>
using namespace std;

/*
	一组数有一个数只出现一次(或奇数次)，其他数出现偶数次，找出只出现一次的数
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