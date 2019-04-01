#include <iostream>
#include <algorithm>
using namespace std;

//利用	a^a = 0的性质
void inplace_swap(int *x, int *y)
{
	if (x == y)//同一个数，不用交换
		return;
	*y = *x^*y;	//y=x^y
	*x = *x^*y;	//x=y
	*y = *x^*y;	//y=x

	//*x = *x + *y;	//x=x+y
	//*y = *x - *y;	//y=x
	//*x = *x - *y;	//x=y
}

void reverse_array(int a[], int cnt)
{
	int first, last;
	for (int first = 0, last = cnt - 1;
		first <= last;
		first++, last--)
		inplace_swap(&a[first], &a[last]);
}
int main()
{
	int arr1[] = { 1,2,3,4,5 };
	int arr2[] = { 1,2,3,4 };
	reverse_array(arr1, sizeof arr1 / sizeof (int));
	for (auto i : arr1)
		cout << i << " ";
	cout << endl;
	reverse_array(arr2, sizeof arr2 / sizeof(int));
	for (auto i : arr2)
		cout << i << " ";
	cout << endl;
}