#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
/*
	��dfs������ĵط�����������ȥ��
	 ��ȶ��У�����������������������ƣ�
	 �ڻ�����һȦ���ص��ѱ������Ľ�㼴�и����������������µ�ʱ�临�Ӷ�ΪO(m)����
	 ����poj��3259�����£�ò��û�бȼ��������
	 http://poj.org/problem?id=3259
*/
const int INF = 0x3f3f3f3f;
const int N = 505;
bool flag;
int dist[N];
bool inStack[N];
struct Edge
{
	int v, cost;
	Edge(int av, int acost) :v(av), cost(acost) {}
};
vector<Edge> g[N];

void SPFA(int s)
{
	size_t t = g[s].size();
	for (int j = 0; j < t && !flag; j++)
	{
		int v = g[s][j].v;
		//cout << s << "-->" << v << " ";
		if (dist[v] > dist[s] + g[s][j].cost)
		{
			//cout << v << " ";
			if (inStack[v])
			{
				flag = 1;
				return;
			}
			//cout << "��ջ" << endl;
			dist[v] = dist[s] + g[s][j].cost;
			inStack[s] = 1;
			SPFA(v);
			//cout << "��ջ" << endl;
			inStack[s] = 0;
		}
	}
}
void init(int n)
{
	for (int i = 0; i <= n; i++)
		inStack[i] = 0;
	for (int i = 0; i <= n; i++)
		dist[i] = INF;
	dist[1] = 0;
	flag = 0;
}
int main()
{
	int T, n, m, w, a, b, t;
	scanf("%d", &T);
	while (T--)
	{
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
		init(n);
		SPFA(1);
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
}
