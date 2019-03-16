#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
/*
	http://poj.org/problem?id=3259

	����������FJ��F��ũ����ÿ��ũׯ����N��أ���M��˫��ߣ�(S,E,T)��ʾS��E֮����һ��˫��ߣ���ҪTʱ��������ꡣ

	����W���涴:(S,E,T)��ʾ��S��E��һ������ߣ���S��E��ʹ��ʱ�䵹��Tʱ�䡣����ÿ��ũ����FJ�ܲ��ܻص��ȿ�ʼ�����ʱ�䣬����������YES���������NO��

	����˼·��ʵ���������Ƿ���ڸ�����

*/
const int INF = 0x3f3f3f3f;
const int N = 505;

struct Edge {//�� 
	int v, cost;//��㵽�յ�v�Ļ���Ϊcost 
	Edge(int v, int cost) :v(v), cost(cost) {}
};

int dist[N];//����
bool vis[N];//��ǽ���Ƿ������
int cnt[N];//��ǽ������еĴ��� 
vector<Edge>g[N];//ͼ���ڽӱ��ʾ
//���� vector<pair<int,int>> g[N];
bool SPFA(int n, int s)//n�ǽ��ĸ�����s��Դ�� 
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
		vis[u] = false;//�����б��Ϊfalse 
		size_t num = g[u].size();//��uΪ�����յ����
		for (int i = 0; i < num; i++) {
			int v = g[u][i].v;//�յ��� 
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
