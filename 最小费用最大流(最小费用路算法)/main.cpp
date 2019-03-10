#include <iostream>
#include <algorithm>
#include <cstring>
#include <tuple>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;//�����
const int N = 100;//�������
const int M = 10000;//������
int top;
int pre[N],c[N];//preǰ�������飬cÿ�������ʴ���
int dist[N];//��Դ�㵽n����̾���(��С��λ���úͣ�
bool vis[N];//��������
struct Vertex//�ڽӱ�ͷ
{
	int first;
}V[N];
struct Edge
{
	int v;//���յ�
	int cap;//����
	int flow;//����
	int cost;//����
	int next;//��һ���ڽӵ�
}E[M];
/*
	SPFA֧�ָ�Ȩ��,������·��ʱ����O(E)
*/
bool SPFA(int s, int t, int n) {	//Shortest Path Faster Algorithm
	int i, u, v;
	queue<int> Q;
	memset(pre, -1, sizeof(pre));//ǰ��������Ϊ-1
	memset(dist, 0x3f, sizeof(dist));//ÿ����㵽Դ������ʼ��Ϊ����
	memset(vis, false, sizeof(vis));//��ʼ��ÿ�����δ����
	memset(c, 0, sizeof(c));//ÿ�������ʴ���Ϊ0
	
	vis[s] = true;
	c[s]++;
	dist[s] = 0;
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		vis[u] = false;
		//ȡ�����ʱ��
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&dist[v] > dist[u] + E[i].cost) {//�ɳڲ���
				dist[v] = dist[u] + E[i].cost;//������̾���
				pre[v] = i;//����ǰ��
				if (!vis[v])
				{
					c[v]++;
					Q.push(v);		//���
					vis[v] = true;	//���
					if (c[v] > n)//����������ޣ�˵���и���
						return false;
				}
			}
		}
	}
	cout << "���·����" << endl;
	cout << "dist[] =";
	for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << endl;
	if (dist[t] == INF)
		return false;
	return true;
}
/*
	SPFAʱ�临�Ӷ�ΪO(E)
	�ػ��ߵĸ���ΪO(VE)
	����ܵ�ʱ�临�Ӷ�ΪO(VE^2)
	�ռ临�Ӷ�ΪO(V)
*/
tuple<int,int> MCMF(int s, int t, int n) {//MinCost MaxFlow
	int d;
	int i, mincost,maxflow;
	mincost = 0;
	maxflow = 0;
	while (SPFA(s, t, n)) {
		d = INF;
		cout << "����·Ϊ: v" << t;
		for (int i = pre[t]; ~i; i = pre[E[i ^ 1].v]) {
			cout << "--v" << E[i ^ 1].v;
			d = min(d, E[i].cap - E[i].flow);//Ѱ����С��������
		}
		cout << "����:" << d << endl;
		maxflow += d;
		for (int i = pre[t]; ~i; i = pre[E[i ^ 1].v]) {//����·�����+d�����������-d
			E[i].flow += d;
			E[i ^ 1].flow -= d;
		}
		mincost += dist[t] * d;//dist[t]Ϊ��·���ϵ�λ��������֮��
	}
	return make_tuple(maxflow, mincost);
}
void init(int n) {
	memset(V, -1, sizeof(V));//��ʼ���ڽӱ�ͷΪ-1�����ձ�
	top = 0;
}
void addEdge(int u, int v, int w, int c) {
	E[top].v = v;
	E[top].flow = 0;
	E[top].cap = w;
	E[top].cost = c;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void add(int u, int v, int w, int c) {
	addEdge(u, v, w, c);
	addEdge(v, u, 0, -c);
}

void printG(int n) {
	cout << "�ڽӱ�����:\n";
	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].cost << " " << E[j].next;
		}
		cout << "]\n";
	}

}
void printflow(int n) {
	cout << "����ʵ��������:" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow > 0)
			{
				cout << "v" << i << "--v" << E[j].v << "  " << E[j].flow << "  " << E[j].cost << endl;
			}
		}
	}
}
int main() {
	int n, m;//������ͱ���
	int u, v, w, c;
	tuple<int, int> ans;//��һ��ֵΪmaxflow���ڶ���ֵΪmincost
	cout << "���������n�ͱ���m:\n";
	cin >> n >> m;
	init(n);//��ʼ���ڽӱ��top
	cout << "�������������u,v,��(u--v)������w����λ��������c:\n";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w >> c;
		add(u, v, w, c);
	}
	printG(n);
	ans = MCMF(1, n, n);
	cout << "�������С����Ϊ:" << get<1>(ans) << endl;
	cout << "������������Ϊ:" << get<0>(ans) << endl;
	printflow(n);
	
	return 0;
}