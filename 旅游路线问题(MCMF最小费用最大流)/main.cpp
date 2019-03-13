#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <cstring>
using namespace std;

const int INF = 1000000000;
const int M = 150;
const int N = 10000;

int top;
int dist[N], pre[N];//Դ�㵽i����̾���,pre[i]��¼ǰ��
bool vis[N];//�������
int c[N];//��Ӵ���
int maxflow, mincost;//���������С����
string str[M];
map<string, int>maze;
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v, next, cap, flow, cost;
}E[M];
/*
	v �ڽӵ� next ָ����һ���ڽӵ�ı�
	cap ���� flow ���� cost ���ã�����Ϊ����������Խ������µأ�ת��Ϊ��С���������
*/
void init() {
	memset(V, -1, sizeof(V));
	top = 0;
}
void addEdge(int u, int v, int c, int cost) {
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].cost = cost;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void add(int u, int v, int c, int cost) {
	addEdge(u, v, c, cost);
	addEdge(v, u, 0, -cost);
}
/*
	Short Path Fastest Algorithm
*/
bool SPFA(int s, int t, int n)
{
	int i, u, v;
	queue<int> Q;
	memset(vis, 0, sizeof(vis));//��ʼ����������
	memset(c, 0, sizeof(c));//��ʼ�����ʴ���
	memset(pre, -1, sizeof(pre));//��ʼ��ǰ������
	for (int i = 1; i <= n; i++)//��ʼ������
		dist[i] = INF;
	vis[s] = true;
	c[s]++;
	dist[s] = 0;//������Ϊ0
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		vis[u] = false;//�����������
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&dist[v] > dist[u] + E[i].cost)//�ɳڲ���
			{
				dist[v] = dist[u] + E[i].cost;
				pre[v] = i;//��¼ǰ��
				if (!vis[v]) {//���ڶ���
					c[v]++;
					Q.push(v);//���
					vis[v] = true;//���
					if (c[v] > n)//����������ޣ�˵���и���
						return false;
				}
			}
		}
	}
	cout << "���·����" << endl;
	cout << "dist []= ";
	for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << endl;
	if (dist[t] == INF)
		return false;//����ΪINF�����޷�����
	return true;
}
int MCMF(int s, int t, int n)
{
	int d;//��������
	maxflow = mincost = 0;
	while (SPFA(s, t, n))//�ҵ���s-t�����·
	{
		d = INF;
		cout << "����·��:" << t;
		for (int i = pre[t]; i != -1; i = pre[E[i ^ 1].v]) {
			d = min(d, E[i].cap - E[i].flow);//��ȡ��С��������
			cout << "--" << E[i ^ 1].v;
		}
		cout << "����: " << d << endl;
		for (int i = pre[t]; i != -1; i = pre[E[i ^ 1].v]) {//�޸Ļ�����磬��������·������ߣ����ٷ����
			E[i].flow += d;
			E[i ^ 1].flow -= d;
		}
		maxflow += d;//���������
		mincost += dist[t] * d;//������С����
	}
	return maxflow;
}
void print(int s, int t) {
	int v;
	vis[s] = 1;
	for (int i = V[s].first; ~i; i = E[i].next)
	{
		v = E[i].v;
		if (!vis[v] && (E[i].flow > 0 && E[i].cost <= 0 || E[i].flow < 0 && E[i].cost >= 0))
		{
			if (v <= t)//Ҳ���Ժ��ӡ��·��Ϊһ����
				cout << str[v] << endl;
			print(v, t);

		}
	}
}
int main() {
	int n, m, i;
	string str1, str2;
	cout << "���뾰��ĸ���n��ֱ���·��m:" << endl;
	cin >> n >> m;
	init();
	maze.clear();//���ӳ��
	for (i = 1; i <= n; i++) {
		cin >> str[i];
		maze[str[i]] = i;//����ӳ��
		if (i == 1 || i == n)
			add(i, i + n, 2, 0);//����Դ������Ϊ2
		else
			add(i, i + n, 1, 0);
	}
	cout << "������������ֱ������������� str1,str2:" << endl;
	for (i = 1; i <= m; i++)
	{
		cin >> str1 >> str2;
		int a = maze[str1], b = maze[str2];
		if (a < b)
		{
			if (a == 1 && b == n)
				add(a + n, b, 2, -1);
			else
				add(a + n, b, 1, -1);
		}
		else {
			if (b == 1 && a == n)
				add(b + n, a, 2, -1);
			else
				add(b + n, a, 1, -1);
		}
	}
	if (MCMF(1, 2 * n, 2 * n) == 2) {//�ҵ����յ��·��2��
		cout << "��ྭ���ľ������:" << -mincost << endl;
		cout << "���ξ����ľ���:" << endl;
		cout << str[1] << endl;
		memset(vis, 0, sizeof(vis));
		print(1, n);
		cout << str[1] << endl;
	}
	else
		cout << "No solution!\n";
	return 0;

}
