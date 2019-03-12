#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x3fffffff;
const int N = 100;
const int M = 10000;
int top;
int pre[N], h[N], g[N];
/*
	pre[i]Ϊ��i������ǰ����
	h[i]Ϊ��i�����ĸ߶�
	g[i]Ϊ�߶�Ϊi�Ľ������
*/
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v;
	int cap;
	int flow;
	int next;
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
void set_h(int t, int n) {
	memset(h, -1, sizeof(h));
	memset(g, 0, sizeof(g));
	int u, v;
	int i;
	queue<int> Q;
	Q.push(t);
	h[t] = 0;
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		++g[h[u]];
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (h[v] == -1) {
				h[v] = h[u] + 1;
				Q.push(v);
			}
		}
	}
	cout << "h[] =";
	for (int i = 0; i < n; i++)
		cout << h[i] << " ";
	cout << endl;
}
int ISAP(int s, int t, int n) {
	set_h(t, n);
	int maxflow = 0;
	int d;
	int u, v;
	int i, j;
	u = s;
	while (h[s] < n) {
		if (u == s)
			d = INF;
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (h[u] == h[v] + 1 && E[i].cap > E[i].flow)
			{
				pre[v] = i;
				d = min(d, E[i].cap - E[i].flow);
				u = v;
				if (u == t) {
					//cout << "����·��:" << t;
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						//cout << "--" << u;
					}
					//cout << "����: " << d << endl;
					maxflow += d;
					//d = INF;��ʡ�ԣ���Ϊu���˵�u��һ��ѭ����ʼ�Ὣd��ΪINF
				}
				break;
			}

		}
		if (i == -1) {
			if (--g[h[u]] == 0)
				break;
			int minh = n - 1;
			for (i = V[u].first; ~i; i = E[i].next) {
				v = E[i].v;
				if (E[i].cap > E[i].flow)
					minh = min(minh, h[v]);
			}
			h[u] = minh + 1;
			/*cout << "������ǩ��ĸ߶�:" << endl;
			for (int i = 1; i <= n; i++)
				cout << h[i] << " ";
			cout << endl;*/
			++g[h[u]];
			if (u != s) 
				u = E[pre[u] ^ 1].v;
		}
	}
	return maxflow;
}
void printG(int n) {
	cout << "�����ڽӱ�����:" << endl;
	for (int i = 0; i <= n; i++)
	{
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next)
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].next;
		cout << "]\n";
	}
}
void print(int m, int n) {
	cout << "ÿ�������ŵİ������:" << endl;
	for (int i = 1; i <= m; i++) {
		cout << "��" << i << "�������Ű��ŵĻ�������:";
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow == 1)
				cout << E[j].v - m << " ";
		}
		cout << endl;
	}
}
int main() {
	int m, n;
	int c, total;
	int cnt = 0;
	cout << "�����������m�ͻ�������n:" << endl;
	cin >> m >> n;
	init();
	total = m + n;
	cout << "��������ÿ�������ŵ�����:\n";
	for (int i = 1; i <= m; i++)
	{
		cin >> c;
		cnt += c;
		add(0, i, c);
	}
	cout << "��������ÿ���������ɰ�������:\n";
	for (int j = m + 1; j <= total; j++)
	{
		cin >> c;
		add(j, total + 1, c);
	}
	for (int i = 1; i <= m; i++)
		for (int j = m + 1; j <= total; j++)
			add(i, j, 1);

	printG(total + 1);
	if (cnt == ISAP(0, total + 1, total + 2)) {
		cout << "���������ųɹ�!\n";
		print(m, n);
		printG(total + 1);
	}
	else
		cout << "�޷��������д�����" << endl;
	return 0;
}