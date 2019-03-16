#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

/*
	http://poj.org/problem?id=3259

	问题描述：FJ有F个农场，每个农庄里有N块地，有M条双向边：(S,E,T)表示S和E之间有一条双向边，需要T时间才能走完。

	还有W个虫洞:(S,E,T)表示从S到E有一条单向边，从S到E会使得时间倒退T时间。问在每个农场里FJ能不能回到比开始还早的时间，如果可以输出YES，否则输出NO。

	解题思路：实际上是求是否存在负环。

*/

int dist[505];
const int INF = 10000000;
struct Edge {
	int start, end, w;//从u到v有一条花费为w的路 
}edge[6000];

//n个结点 m条边 
bool Bellman_ford(int n, int m)
{
	memset(dist, INF, sizeof(dist));
	dist[1] = 0;
	//进行n-1次松弛操作
	for (int i = 1; i < n; i++)
		for (int j = 0; j < m; j++)
			if (dist[edge[j].end] > dist[edge[j].start] + edge[j].w)
				dist[edge[j].end] = dist[edge[j].start] + edge[j].w;
	//判断是否存在负环
	for (int j = 0; j < m; j++)
		if (dist[edge[j].end] > dist[edge[j].start] + edge[j].w)
			return true;
	return false;
}

int main()
{
	int F, N, M, W, a, b, t;
	scanf("%d", &F);
	while (F--) {
		scanf("%d%d%d", &N, &M, &W);
		int k = 0;
		while (M--) {
			//双向边 
			scanf("%d%d%d", &a, &b, &t);
			edge[k].start = a, edge[k].end = b, edge[k].w = t;
			k++;
			edge[k].start = b, edge[k].end = a, edge[k].w = t;
			k++;
		}
		while (W--) {
			//单向边
			scanf("%d%d%d", &a, &b, &t);
			edge[k].start = a, edge[k].end = b, edge[k].w = -t;
			k++;
		}
		bool flag = Bellman_ford(N, k);
		printf("%s\n", flag ? "YES" : "NO");
	}
	return 0;
}
