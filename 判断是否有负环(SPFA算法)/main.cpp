#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
/*
	http://poj.org/problem?id=3259

	问题描述：FJ有F个农场，每个农庄里有N块地，有M条双向边：(S,E,T)表示S和E之间有一条双向边，需要T时间才能走完。

	还有W个虫洞:(S,E,T)表示从S到E有一条单向边，从S到E会使得时间倒退T时间。问在每个农场里FJ能不能回到比开始还早的时间，如果可以输出YES，否则输出NO。

	解题思路：实际上是求是否存在负环。

*/
const int INF = 0x3f3f3f3f;
const int N = 505;

struct Edge {//边 
	int v, cost;//起点到终点v的花费为cost 
	Edge(int v, int cost) :v(v), cost(cost) {}
};

int dist[N];//距离
bool vis[N];//标记结点是否进队列
int cnt[N];//标记结点进队列的次数 
vector<Edge>g[N];//图的邻接表表示
//或用 vector<pair<int,int>> g[N];
bool SPFA(int n, int s)//n是结点的个数，s是源点 
{
	queue<int>q;
	for (int i = 0; i <= n; i++) {
		vis[i] = false;
		cnt[i] = 0;
		dist[i] = INF;
	}
	vis[s] = true;
	dist[s] = 0;
	cnt[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;//出队列标记为false 
		size_t num = g[u].size();//以u为起点的终点个数
		for (int i = 0; i < num; i++) {
			int v = g[u][i].v;//终点编号 
			if (dist[u] + g[u][i].cost < dist[v]) {
				dist[v] = dist[u] + g[u][i].cost;
				if (!vis[v]) {
					q.push(v);
					vis[v] = true;
					cnt[v]++;
					if (cnt[v] >= n)
						return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	int T, n, m, w, a, b, t;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 0; i <= n; i++)
			g[i].clear();
		while (m--) {
			scanf("%d%d%d", &a, &b, &t);
			g[a].push_back(Edge(b, t));
			g[b].push_back(Edge(a, t));
		}
		while (w--) {
			scanf("%d%d%d", &a, &b, &t);
			g[a].push_back(Edge(b, -t));
		}
		int flag = SPFA(n, 1);
		if (flag)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
