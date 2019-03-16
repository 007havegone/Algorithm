#include <iostream>
#include <queue>
#include <cstring>
#include <utility>
using namespace std;

/*
	Bellman-Ford算法非常简单，核心代码只有4行，并且可以完美的解决带有负权边的图
*/
const int N = 10000;
const int INF = 0x3f3f3f3f;
int n, m;
int u[N];//边起点
int v[N];//边终点
int w[N];//边权值
int dis[N];//dis[i]表示源点到i的距离

/*
	有一些边松弛后，得到最优解后不再变化，但是Bellman算法重复判断。
	SPFA算法每次仅对最短路径估计值发生变化了的顶点的所有出边执行松弛操作，从而进行优化

*/
void Bellman_Ford(int s)
{
	for (int i = 1; i <= n; i++)//初始化
		dis[i] = INF;
	dis[s] = 0;//起点距离为0
	for (int k = 1; k <= n - 1; k++)//最多|N-1|次,每一次至少有一个结点成为最优解
	{
		int flag = 0;
		for (int i = 1; i <= m; i++)//松弛操作
		{
			if (dis[u[i]] + w[i] < dis[v[i]]) {
				dis[v[i]] = dis[u[i]] + w[i];
				flag = 1;
			}
		}
		if (!flag)//没有更新，提前跳出
			break;
	}
	bool flag = 0;
	for (int i = 1; i <= m; i++)
		if (dis[u[i]] + w[i] < dis[v[i]]) {
			flag = 1;
			break;
		}
	if (flag)cout << "存在负权回路\n";
}
void print(int n) {
	for (int i = 1; i <= n; i++)
		if (dis[i] == INF)
			cout << "INF" << " ";
		else
			cout << dis[i] << " ";
	cout << endl;
}

void init(int n) {
	for (int i = 1; i <= n; i++) {
		u[i] = 0;
		v[i] = 0;
		w[i] = INF;
	}
}
int main()
{
	int src;
	cout << "输入结点个数n和边的个数m:\n";
	cin >> n >> m;
	init(m);
	cout << "依次输入u、v及其距离dis(u,v):\n";
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i];
	}
	cout << "输入起点:";
	cin >> src;
	Bellman_Ford(src);
	print(n);
	return 0;
}