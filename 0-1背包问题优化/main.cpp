#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 10005;
const int M = 105;
int dp[maxn];//dp[j]表示当前已放入容量为j的购物车获得的最大价值
int w[M], v[M];//w[i]表示第i个物品的质量，v[i]表示第i个物品的质量
int x[M];//x[i]表示第i个物品是否放入购物车
int i, j, n, W;//n表示n个物品，W表示购物车容量

void opt1(int n, int W) {
	for (i = 1; i <= W; i++)
		dp[i] = 0;
	for ( i = 1; i <= n; i++) {//遍历每个商品
		for ( j = W; j >0 ; j--) {
			if (j >= w[i])//背包容量大于商品质量，选择放入或不放入
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
		for (int j = 1; j <= W; j++) {
			cout << dp[j] << " ";
		}
		cout << endl;
	}
	
}
void opt2(int n, int W) {
	for (i = 1; i <= W; i++)
		dp[i] = 0;
	for ( i = 1; i <= n; i++){
		for (j = W; j >= w[i]; j--) {//减少一次判断，同时缩小了范围
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
		for (int j = 1; j <= W; j++) {
			cout << dp[j] << " ";
		}
		cout << endl;
	}
}
void opt3(int n, int W) {//当背包容量足够大时可以缩减
	for (i = 1; i <= W; i++)
		dp[i] = 0;
	int *sum = new int[n+1];//sum[i]表示从1~i的物品重量之和
	sum[0] = 0;
	for (i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + w[i];
	for (i = 1; i <= n; i++) {
		int bound = max(w[i], W - (sum[n] - sum[i - 1]));//sum[n]-sum[i-1]为i到n的质量，取剩余容量和w[i]的最大值
		for (j = W; j >= bound; j--)
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		for (int j = 1; j <= W; j++) {
			cout << dp[j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	cout << "输入物品的个数n: ";
	cin >> n;

	cout << "输入背包容量W:";
	cin >> W;
	cout << "依次输入每个商品的重量w和价值v，空格隔开:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	opt1(n, W);
	cout << endl;
	opt2(n, W);
	cout << endl;
	opt3(n, W);
	cout << endl;
	cout << dp[W] << endl;
}