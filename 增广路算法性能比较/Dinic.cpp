#include<iostream>
#include<cstring>
#include<queue>
#include<chrono>
const int INF = 0x3f3f3f3f;
const int MAXN = 20000, MAXM = 500000;//最大的点数和边数
using namespace std;
using namespace std::chrono;
struct Edge
{
	int v, f, nxt;//邻接点，流值，下一个点
};
int src, sink;
int g[MAXN + 10];//存放邻接表的第一个结点
int nume;
Edge e[MAXM * 2 + 10];
queue<int> que;
bool vis[MAXN + 10];
int dist[MAXN + 10];
int n, m;
void addEdge(int u, int v, int c)
{
	e[++nume].v = v;
	e[nume].f = c;
	e[nume].nxt = g[u];
	g[u] = nume;
	e[++nume].v = u;
	e[nume].f = 0;
	e[nume].nxt = g[v];
	g[v] = nume;
}
void init()
{
	memset(g, 0, sizeof(g));
	nume = 1;
	int u, v, c;
	cin >> n >> m;
	src = 1, sink = n;
	for(int i=0;i<m;++i)
	{
		cin >> u >> v >> c;
		addEdge(u, v, c);
	}
}
class Dinic
{
public:
	static int maxFlow()
	{
		int ret = 0;
		while (true)
		{
			memset(vis, 0, sizeof(vis));
			bfs();
			if (!vis[sink])return ret;
			ret += dfs(src, INF);
		}
	}
	static void bfs()
	{
		memset(dist, 0, sizeof(dist));
		while (!que.empty())que.pop();
		vis[src] = true;
		que.push(src);
		while (!que.empty())
		{
			int u = que.front(); que.pop();
			for (int i = g[u]; i; i = e[i].nxt)
			{
				if (e[i].f && !vis[e[i].v])
				{
					que.push(e[i].v);
					dist[e[i].v] = dist[u] + 1;
					vis[e[i].v] = true;
				}
			}

		}
	}
	
private:
	
	static int dfs(int u, int delta)
	{
		if (u == sink) {
			return delta;
		}
		int ret = 0;
		for (int i = g[u]; delta&&i; i = e[i].nxt)
		{
			if (e[i].f&&dist[e[i].v] == dist[u] + 1)
			{
				int dd = dfs(e[i].v, min(e[i].f, delta));
				e[i].f -= dd;
				e[i ^ 1].f += dd;
				delta -= dd;
				ret += dd;
			}
		}
		return ret;
	}
};
int main()
{
	init();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cout << Dinic::maxFlow() << endl;
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//采用 nanosecond为单位
	duration<double, nano> time_span = duration_cast<duration<double, nano>>(t2 - t1);
	cout << "Dinic Algorithm takes " << time_span.count() << " nanoseconds.\n\n";
}