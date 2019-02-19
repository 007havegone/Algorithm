#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int M = 1 << 13;
#define INF 0x3f3f3f3f
int dp[M + 2][20];//dp[i][j] 表示第i个状态，到达第j个城市的最短路径
int g[15][15];			//从0开始存储
int path[M + 2][15];    //最优路径，path[i][j]即经过{a,b,c,d,...}到j的最优解点
int n, m;              //n个城市，m条路
int bestl;            //最短路径长度
int sx, S;
/*
	时间复杂度 O(2^n*n^2) 空间复杂度 O(2^n)
*/

void Init() {
	sx = 0;
	bestl = INF;
	memset(path, 0, sizeof(path));
	memset(g, INF, sizeof(g));
	memset(dp, INF, sizeof(dp));
}
void Traveling() {
	dp[1][0] = 0;//设置1出发到达1的距离为0，起点为1，其他保持INF
	S = 1 << n;
	for (int i = 0; i < S; i++) {//遍历所有状态
		for (int j = 0; j < n; j++) {//寻找中介点
			if (!i&(1 << j))continue;
			for (int k = 0; k < n; k++) {//寻找终点
				if (i&(1 << k))continue;
				if (dp[i|(1 << k)][k] > dp[i][j] + g[j][k]) {
					dp[i|(1 << k)][k] = dp[i][j] + g[j][k];
					path[i|(1 << k)][k] = j;//设置最优解为j
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (bestl > dp[S - 1][i] + g[i][0]) {
			bestl = dp[S - 1][i] + g[i][0];
			sx = i;//记录S的终点
		}
	}
}
void print(int S, int val) {
	if (!S)return;//没有距离了
	for (int i = 0; i < n; i++) {
		if (dp[S][i] == val) {
			print(S ^ (1 << i), val - g[i][path[S][i]]);//递归调用，取出S-i的最优解
			cout << i+1 << "--->";
			break;
		}
	}
}
int main()
{
	int u, v, w;//u,v代表城市，w代表u和v城市之间路的长度
	cout << "请输入景点数 n(结点数):";
	cin >> n;
	cout << "请输入景点之间的连线数(边数):";
	cin >> m;
	Init();
	cout << "请依次输入两个景点u和v之间的距离w,格式:景点u 景点v 距离w";
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		g[u - 1][v - 1] = g[v - 1][u - 1] = w;
	}
	Traveling();
	cout << "最短路径: ";
	print(S - 1, bestl - g[sx][0]);
	cout << 1 << endl;
	cout << "最短路径长度:";
	cout << bestl << endl;
	return 0;
}
