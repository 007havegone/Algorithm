#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100;
const int INF = 0x3f3f3f3f;
int n, m;//�������ͱߵĸ���
int g[N][N];//�洢ͼ
int b[N][N];//b[i][0]��ʾ��i�������ڽӵ������b[i,1...n]��ʾ��i�������ڽӵ�
int q[N];//����,spfaʹ��
int dist[N];//dist[i]��ʾԴ�㵽��̾���
bool vis[N];//��������
void init()
{
	memset(g, INF, sizeof(g));
	for (int i = 1; i <= n; i++)
		b[i][0] = 0;
}
void SPFA(int s)
{
	int u, v;//��ǰ��������ڽӵ�
	memset(q, 0, sizeof(q));//��ʼ��Ϊ��
	memset(vis, 0, sizeof(vis));
	memset(dist, INF, sizeof(dist));//��ʼ��Ϊ����
	dist[s] = 0;
	int head = 0, last = 1;
	q[head] = s;
	vis[s] = 1;
	while (head < last)
	{
		u = q[head]; ++head;//����
		vis[u] = 0;//ȡ�����
		for (int i = 1; i <= b[u][0]; i++)//�ɳڲ���
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
	int s;//���
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
	cout << "�������s:";
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
