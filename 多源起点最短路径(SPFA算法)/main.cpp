#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#define NDEBUG //���ö���
#include <cassert>
using namespace std;
/*
	HDU 2066 һ���˵�����
	https://blog.csdn.net/qq_37785469/article/details/75829311
*/
const int N = 100;
const int INF = 0x3f3f3f3f;
int n;
int g[N][N];//�ڽӾ���
int dist[N];//dist[i]Դ�㵽i����̾���
int vis[N];//��������
void SPFA()
{
	memset(dist, INF, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[0] = 0;
	vis[0] = 1;
	int t;
	queue<int> que;
	while (!que.empty())que.pop();
	que.push(0);//0��Ϊ���
	while (!que.empty())//���ȶ��зǿ�
	{
		t = que.front(); que.pop();
		vis[t] = false;
		for (int i = 1; i <= n; i++)//�ɳڲ���
		{
			if (dist[i] > dist[t] + g[t][i]) {
				dist[i] = dist[t] + g[t][i];
				if (!vis[i]) {//�б仯Ϊ���Ż����У������
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
		SPFA();
		assert(0);
		int mindist = INF;
		while (d--) {//��ȡ�յ�
			scanf("%d", &u);
			mindist = min(mindist, dist[u]);
		}
		printf("%d\n", mindist);
	}
	return 0;
}