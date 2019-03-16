#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

/*
	http://poj.org/problem?id=3259

	����������FJ��F��ũ����ÿ��ũׯ����N��أ���M��˫��ߣ�(S,E,T)��ʾS��E֮����һ��˫��ߣ���ҪTʱ��������ꡣ

	����W���涴:(S,E,T)��ʾ��S��E��һ������ߣ���S��E��ʹ��ʱ�䵹��Tʱ�䡣����ÿ��ũ����FJ�ܲ��ܻص��ȿ�ʼ�����ʱ�䣬����������YES���������NO��

	����˼·��ʵ���������Ƿ���ڸ�����

*/

int dist[505];
const int INF = 10000000;
struct Edge {
	int start, end, w;//��u��v��һ������Ϊw��· 
}edge[6000];

//n����� m���� 
bool Bellman_ford(int n, int m)
{
	memset(dist, INF, sizeof(dist));
	dist[1] = 0;
	//����n-1���ɳڲ���
	for (int i = 1; i < n; i++)
		for (int j = 0; j < m; j++)
			if (dist[edge[j].end] > dist[edge[j].start] + edge[j].w)
				dist[edge[j].end] = dist[edge[j].start] + edge[j].w;
	//�ж��Ƿ���ڸ���
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
			//˫��� 
			scanf("%d%d%d", &a, &b, &t);
			edge[k].start = a, edge[k].end = b, edge[k].w = t;
			k++;
			edge[k].start = b, edge[k].end = a, edge[k].w = t;
			k++;
		}
		while (W--) {
			//�����
			scanf("%d%d%d", &a, &b, &t);
			edge[k].start = a, edge[k].end = b, edge[k].w = -t;
			k++;
		}
		bool flag = Bellman_ford(N, k);
		printf("%s\n", flag ? "YES" : "NO");
	}
	return 0;
}
