#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
/*
	HDU 2066 一个人的旅行
	https://blog.csdn.net/qq_37785469/article/details/75829311
*/
const int INF = 0x3f3f3f3f;
const int N = 100;
int n;
int g[N][N];//邻接矩阵
int dist[N];//最短距离
bool vis[N];//访问数组

void Dijkstra()
{
	memset(vis, 0, sizeof(vis));//置为为访问
	for (int i = 1; i <= n; i++)//初始化为0到个节点距离
		dist[i] = g[0][i];
	vis[0] = 1;
	dist[0] = 0;
	for (int k = 1; k <= n; k++)//n+1个节点，除了0点还需要找n次
	{
		int mdist = INF;
		int t = -1;
		for (int i = 1; i <= n; i++)
			if (!vis[i] && dist[i] < mdist)
			{
				mdist = dist[i];
				t = i;
			}
		vis[t] = 1;
		if (t == -1)
			break;
		for (int i = 1; i <= n; i++)
		{
			if (!vis[i] && dist[i] > dist[t] + g[t][i])
				dist[i] = dist[t] + g[t][i];
		}
	}

}
void print()
{
	for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << endl;
}
/*
	Dijstra处理多源最短路径问题，可以假设为起点0，
	0到多个原点的距离置为0，从而求0到各个终点的距离	
*/
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
		Dijkstra();
		int mindist = INF;
		while (d--) {//获取终点
			scanf("%d", &u);
			mindist = min(mindist, dist[u]);
		}
		printf("%d\n", mindist);
	}
	return 0;
}