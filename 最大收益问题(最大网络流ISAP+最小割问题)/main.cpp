#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 100;
const int M = 10000;
const int INF = 0x3fffffff;
int pre[N], h[N], g[N];
int top;
bool flag[N];//DFS��ʱ��������
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v, cap, flow, next;
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
void seth(int t, int n) {
	memset(h, -1, sizeof(h));
	memset(g, 0, sizeof(g));
	int u, v;
	queue<int> Q;
	Q.push(t);
	h[t] = 0;
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		++g[h[u]];
		for (int j = V[u].first; ~j; j = E[j].next) {
			v = E[j].v;
			if (h[v] == -1) {
				h[v] = h[u] + 1;
				Q.push(v);
			}
		}
	}
	cout << "h[] =";
	for (int i = 0; i <= n; i++)
		cout << h[i] << " ";
	cout << endl;
}
int ISAP(int s, int t, int n) {
	seth(t, n - 1);
	int maxflow = 0;
	int d, u, v, i, j;
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
					cout << "����·:" << u;
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						cout << " " << u;
					}
					maxflow += d;
					cout << "��������Ϊ:" << d << endl;
					d = INF;
				}
				break;
			}
		}
		if (i == -1) {
			if (--g[h[u]] == 0)
				break;
			int minh = n - 1;
			for (j = V[u].first; ~j; j = E[j].next) {
				v = E[j].v;
				if (E[j].cap > E[j].flow) 
					minh = min(minh, h[v]);
			}
			h[u] = minh + 1;
			++g[h[u]];
			if (u != s)
				u = E[pre[u] ^ 1].v;
		}
	}
	return maxflow;
}
void DFS(int s) {
	flag[s] = 1;
	for (int i = V[s].first; ~i; i = E[i].next) {
		if (E[i].cap > E[i].flow && !flag[E[i].v])
		{
			DFS(E[i].v);
		}
	}
}
void print(int m,int n) {
	DFS(0);
	cout << "������淽������:" << endl;
	cout << "ѡ�е�ʵ����:";
	for (int i = 1; i <= m; i++)
		if (flag[i])
			cout << i << " ";
	cout << endl;
	cout << "ѡ�е��������:";
	for (int i = m + 1; i <= m + n; i++)
		if (flag[i])
			cout << i-m << " ";
	cout << endl;
}
void printG(int n) {
	cout << "�����ڽӱ�����:" << endl;
	for (int i = 0; i <= n; i++) {
		cout << "v" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) 
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].next;
		cout << "]\n";
	}
}
int main() {
	int m, n, sum = 0;
	int cost,total;
	cout << "����ʵ����m��������n:";
	cin >> m >> n;
	init();
	total = m + n;
	cout << "��������ʵ�������Ч��͸�ʵ����Ҫ������(Ϊ0����)\n";
	for (int i = 1; i <= m; i++) {
		cin >> cost;
		sum += cost;
		add(0, i, cost);
		while (cin >> cost && cost)//���ʵ�������ĵĹ�ϵΪ�������ζ�ſ���֧����������������
			add(i, cost + m, INF);
	}
	cout << "�����������������ķ���:\n";
	for (int i = m + 1; i <= total; i++) {
		cin >> cost;
		add(i, total + 1, cost);
	}
	cout << "���ľ�����Ϊ:" <<  sum - ISAP(0, total + 1, total + 2) << endl;
	printG(total + 1);
	print(m, n);
}
