#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1005;
const int M = 105;
int c[M][maxn];//c[i][j]表示前i个物品放入容量为j的背包的最大值
int w[M], v[M];//w[i]表示第i个物品重量，v[i]表示1第i个物品的价值
int x[M];//x[i]表示第i个物品是否放入

void Init(int n,int W)
{
	//第0列置为0
	for (int i = 0; i <= n; i++)
		c[i][0] = 0;
	//第0行置为0
	for (int i = 0; i <= W; i++)
		c[0][i] = 0;
}
void DP(int n, int W)
{
	for (int i = 1; i <= n; i++)//遍历每件商品
	{
		for (int j = 1; j <= W; j++) {//遍历每种价值
			if (j < w[i])
				c[i][j] = c[i - 1][j];
			else
				c[i][j] = max(c[i - 1][j], c[i - 1][j - w[i]] + v[i]);
		}
	}
}
void print(int n, int W)
{
	for (int i = n; i >= 1; i--) {
		if (c[i][W] > c[i - 1][W]) {
			x[i] = 1;
			W -= w[i];
		}
		else
			x[i] = 0;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (x[i]) {
			cout << i << " ";
			sum += v[i];
		}
	}
	cout << "\nSum = " << sum << endl;;
}
int main() {
	int i, j, n, W;//W为背包容量，n为物品个数
	cout << "输入物品的个数n: ";
	cin >> n;

	cout << "输入背包容量W:";
	cin >> W;
	cout << "依次输入每个商品的重量w和价值v，空格隔开:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	Init(n, W);
	DP(n, W);
	print(n, W);
}