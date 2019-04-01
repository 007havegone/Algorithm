#include <iostream>
using namespace std;

/*

	�޷��żӷ� x+y =  x+y, x+y<2^w
					  x+y-2^w, 2^w <= x+y < 2^(w+1)
*/
int uadd_ok(unsigned x, unsigned y)
{
	unsigned sum = x + y;
	return sum >= x;
}
/*					x+y-2^w, 2^(w-1) <= x+y	�����
	�з��żӷ� x+y=	x+y,	-2^(w-1)) <= x+y < 2^(w-1) ����
					x+y+2^w, x+y < -2^(w-1)	�����
*/					
int tadd_ok(int x, int y)
{
	int sum = x + y;
	int neg_over = x < 0 && y < 0 && sum >= 0;
	int pos_over = x >= 0 && y >= 0 && sum < 0;
	return !neg_over && !pos_over;
}
int tsub_ok(int x, int y)
{
	tadd_ok(x, -y);
	/*
		�� y= TMINʱ,-y=TMIN,����x�õ��Ĵ𰸶��Ǵ��.
		����-yӦΪӦ��|TMAX+1|
		��x<0ʱ,sum=x+y����,���ǵõ����ȴ�Ǹ����
		��x>=0ʱ,sum+x+yӦ��Ϊ�����,���ĵõ����ȷʵ����
	*/
}

int tsub_ovf(int x, int y) {
	int sub = x - y;
	if (x >= 0 && y < 0 && sub < 0)
		return 1;
	if (x < 0 && y >= 0 && sub >= 0)
		return 1;
	return 0;
}

int tmult_ok(int x, int y)
{
	int p = x * y;
	/*x Ϊ0 ����,���� p/x == y*/
	return !x || p / x == y;
}

// ���ó���,��64λ�����32λ�˷��Ƿ����
int tmult_ok2(int x, int y)
{
	long long pll = (long long)x*y;
	return pll == (int)pll;
}

int main()
{


}