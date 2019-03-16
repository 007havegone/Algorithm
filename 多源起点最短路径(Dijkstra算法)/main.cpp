#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
/*
	HDU 2066 һ���˵�����
	https://blog.csdn.net/qq_37785469/article/details/75829311
*/
const int INF = 0x3f3f3f3f;
const int N = 100;
int n;
int g[N][N];//�ڽӾ���
int dist[N];//��̾���
bool vis[N];//��������

void Dijkstra()
{
	memset(vis, 0, sizeof(vis));//��ΪΪ����
	for (int i = 1; i <= n; i++)//��ʼ��Ϊ0�����ڵ����
		dist[i] = g[0][i];
	vis[0] = 1;
	dist[0] = 0;
	for (int k = 1; k <= n; k++)//n+1���ڵ㣬����0�㻹��Ҫ��n��
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
	Dijstra�����Դ���·�����⣬���Լ���Ϊ���0��
	0�����ԭ��ľ�����Ϊ0���Ӷ���0�������յ�ľ���	
*/
int main()
{
	int t, s, d;//tΪ·������sΪ�������dΪ�յ���
	int u, v, w;//��㣬�յ㣬Ȩֵ
	while (scanf("%d%d%d", &t, &s, &d) != EOF)
	{
		n = 0;
		memset(g, INF, sizeof(g));
		while (t--)//��ȡ��
		{
			scanf("%d%d%d", &u, &v, &w);
			if (w < g[u][v])
				g[u][v] = g[v][u] = w;
			n = max(n, max(u, v));//��Ŀû�н���������ݸ����Ľ�������ֵ
		}
		while (s--) {//��ȡ���
			scanf("%d", &u);
			g[0][u] = 0;//�ٶ�0Ϊ���
		}
		Dijkstra();
		int mindist = INF;
		while (d--) {//��ȡ�յ�
			scanf("%d", &u);
			mindist = min(mindist, dist[u]);
		}
		printf("%d\n", mindist);
	}
	return 0;
}