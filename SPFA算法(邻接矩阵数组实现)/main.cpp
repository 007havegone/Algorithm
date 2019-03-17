#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100;
const int INF = 0x3f3f3f3f;
int n, m;//结点个数和边的个数
int g[N][N];//存储图
int b[N][N];//b[i][0]表示第i个结点的邻接点个数，b[i,1...n]表示第i个结点的邻接点
int q[N];//队列,spfa使用
int dist[N];//dist[i]表示源点到最短距离
bool vis[N];//访问数组
void init()
{
	memset(g, INF, sizeof(g));
	for (int i = 1; i <= n; i++)
		b[i][0] = 0;
}
void SPFA(int s)
{
	int u, v;//当前处理结点和邻接点
	memset(q, 0, sizeof(q));//初始化为空
	memset(vis, 0, sizeof(vis));
	memset(dist, INF, sizeof(dist));//初始化为无穷
	dist[s] = 0;
	int head = 0, last = 1;
	q[head] = s;
	vis[s] = 1;
	while (head < last)
	{
		u = q[head]; ++head;//出队
		vis[u] = 0;//取消标记
		for (int i = 1; i <= b[u][0]; i++)//松弛操作
		{
			v = b[u][i];
			if (dist[v] > dist[u] + g[u][v])
			{
				dist[v] = dist[u] + g[u][v];
				if (!vis[v])
				{
					vis[v] = 1;
					q[last++] = v;
				}
			}
		}
	}
}
int main()
{
	int s;//起点
	int u, v, w;
	cin >> n >> m;
	init();
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		if (w < g[u][v]) {
			g[u][v] = w;
			b[u][0]++;
			b[u][b[u][0]] = v;
		}
	}
	cout << "输入起点s:";
	cin >> s;
	SPFA(s);
	cout << "dist []=";
	for (int i = 1; i <= n; i++)
		if (dist[i] != INF)
			cout << dist[i] << " ";
		else
			cout << "INF" << " ";
	cout << endl;

	return 0;
}
