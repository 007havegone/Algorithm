#include <iostream>
#include <queue>
#include <cstring>
using namespace	std;
const int INF = 0x3f3f3f3f;
const int N = 100;//������
const int M = 10000;//�߸���
int h[N], g[N], pre[N];
/*
	h[i]Ϊ��i�����ĸ߶�
	g[i]Ϊ�߶�Ϊi�Ľ������
	pre[i]Ϊ��i������ǰ����
*/
int top;
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v;//�յ�
	int cap;//����
	int flow;//����
	int next;//ָ����һ���ڽӵ�
}E[M];

void init() {
	memset(V, -1, sizeof(V));
	top = 0;
}
void addEdge(int u, int v, int c) {
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void add(int u, int v, int c) {
	addEdge(u, v, c);
	addEdge(v, u, 0);
}
/*��ʼ�����߶�*/
void set_h(int t,int n) {
	queue<int> Q;
	memset(h, -1, sizeof(h));
	memset(g, 0, sizeof(g));
	int u, v;
	h[t] = 0;
	Q.push(t);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		++g[h[u]];
		for (int j = V[u].first; ~j; j = E[j].next)
		{
			v = E[j].v;
			if (h[v] == -1) {
				h[v] = h[u] + 1;
				Q.push(v);
			}
		}
	}
	cout << "h[]=";
	for (int i = 0; i <= n; i++)
		cout << h[i] << " ";
	cout << endl;
}
//sΪ��㣬tΪ�յ㣬nΪ�����
int ISAP(int s, int t, int n) {
	int u, v, d;
	int i, j, maxflow=0;
	set_h(t, n-1);//��ʼ���߶�
	u = s;//��ǰ�������
	while (h[s]<n)
	{
		if (u == s)
			d = INF;
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&h[u] == h[v] + 1) {
				pre[v] = i;//��¼ǰ����
				d = min(d, E[i].cap - E[i].flow);//���Ż�
				u = v;
				if (u == t) {//�ҵ����
					cout << "������·Ϊ:" << u;
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						cout << "--" << u;
					}
					cout << "  ����:" << d << endl;
					maxflow += d;
					d = INF;
				}
				break;
			}
		}
		if (i == -1)//������ǰ��
		{
			if (--g[h[u]] == 0)//��ǰ���߶ȸı䣬����-1
				break;
			//��ʼ�߶�Ϊ�����-1
			int minh = n - 1;
			for (j = V[u].first; ~j; j = E[j].next) {
				v = E[j].v;
				if (E[j].cap > E[j].flow)
					minh = min(minh, h[v]);
			}
			h[u] = minh+1;
			cout << "������ǩ��ĸ߶�" << endl;
			for (int k = 0; k <= n-1; k++)
				cout << h[k] << " ";
			cout << endl;
			++g[h[u]];
			if (u != s)
				u = E[pre[u] ^ 1].v;
		}
	}
	return maxflow;
}
/*��ӡʵ������*/
void printflow(int m) {
	cout << "ʵ����������:" << endl;
	for (int i = 1; i <= m; i++) {
		for (int j = V[i].first; ~j; j = E[j].next)
			if(E[j].flow>0)
				cout << i << "--" << E[j].v << endl;
	}
}
/*��ӡ�ڽӱ�*/
void printG(int n) {
	cout << "�ڽӱ�����:" << endl;
	for (int i = 0; i <= n; i++)
	{
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next)
		{
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].next;
		}
		cout << "]\n";
	}
}
int main() {
	int m, n, total;
	int u, v;
	cout << "����ŮְԱ����m����ְԱ����n:\n";
	cin >> m >> n;
	total = m + n;
	init();
	for (int i = 1; i <= m; i++)
		add(0, i, 1);
	for (int j = m + 1; j <= total; j++)
		add(j, total + 1, 1);
	cout << "���������ƥ���Ů�Ա��u�����Ա��v(������Ϊ-1����)\n";
	while (cin >> u >> v && u + v != -2) {
		add(u, v, 1);
	}
	printG(total + 1);
	cout << "����ͼ�����ƥ����Ϊ:" << ISAP(0, total + 1, total + 2) << endl;
	printflow(m);

	return 0;
}