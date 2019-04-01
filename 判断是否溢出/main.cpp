#include <iostream>
using namespace std;

/*

	无符号加法 x+y =  x+y, x+y<2^w
					  x+y-2^w, 2^w <= x+y < 2^(w+1)
*/
int uadd_ok(unsigned x, unsigned y)
{
	unsigned sum = x + y;
	return sum >= x;
}
/*					x+y-2^w, 2^(w-1) <= x+y	正溢出
	有符号加法 x+y=	x+y,	-2^(w-1)) <= x+y < 2^(w-1) 正常
					x+y+2^w, x+y < -2^(w-1)	负溢出
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
		当 y= TMIN时,-y=TMIN,任意x得到的答案都是错的.
		本来-y应为应该|TMAX+1|
		当x<0时,sum=x+y正常,但是得到结果却是负溢出
		当x>=0时,sum+x+y应该为正溢出,但的得到结果确实正常
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
	/*x 为0 错误,或者 p/x == y*/
	return !x || p / x == y;
}

// 不用除法,用64位数检测32位乘法是否溢出
int tmult_ok2(int x, int y)
{
	long long pll = (long long)x*y;
	return pll == (int)pll;
}

int main()
{


}