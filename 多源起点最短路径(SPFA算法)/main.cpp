#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#define NDEBUG //禁用断言
#include <cassert>
using namespace std;
/*
	HDU 2066 一个人的旅行
	https://blog.csdn.net/qq_37785469/article/details/75829311
*/
const int N = 100;
const int INF = 0x3f3f3f3f;
int n;
int g[N][N];//邻接矩阵
int dist[N];//dist[i]源点到i的最短距离
int vis[N];//访问数组
void SPFA()
{
	memset(dist, INF, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[0] = 0;
	vis[0] = 1;
	int t;
	queue<int> que;
	while (!que.empty())que.pop();
	que.push(0);//0作为起点
	while (!que.empty())//优先队列非空
	{
		t = que.front(); que.pop();
		vis[t] = false;
		for (int i = 1; i <= n; i++)//松弛操作
		{
			if (dist[i] > dist[t] + g[t][i]) {
				dist[i] = dist[t] + g[t][i];
				if (!vis[i]) {//有变化为佳优化队列，则入队
					vis[i] = 1;
					cout << "push " << i << endl;
					que.push(i);
				}
			}
		}
		for (int i = 0; i <= n; i++)
			cout << dist[i] << " ";
		cout << endl;
	}
}
int main()
{
	int t, s, d;//t为路径数，s为起点数，d为终点数
	int u, v, w;//起点，终点，权值
	while (scanf("%d%d%d", &t, &s, &d) != EOF)
	{
		n = 0;
		memset(g, INF, sizeof(g));
		while (t--)//获取边
		{
			scanf("%d%d%d", &u, &v, &w);
			if (w < g[u][v])
				g[u][v] = g[v][u] = w;
			n = max(n, max(u, v));//题目没有结点数，根据给出的结点求最大值
		}
		while (s--) {//获取起点
			scanf("%d", &u);
			g[0][u] = 0;//假定0为起点
		}
		SPFA();
		assert(0);
		int mindist = INF;
		while (d--) {//获取终点
			scanf("%d", &u);
			mindist = min(mindist, dist[u]);
		}
		printf("%d\n", mindist);
	}
	return 0;
}