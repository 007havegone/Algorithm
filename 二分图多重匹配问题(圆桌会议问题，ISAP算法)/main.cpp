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
	pre[i]为第i个结点的前驱边
	h[i]为第i个结点的高度
	g[i]为高度为i的结点数量
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
					//cout << "增广路径:" << t;
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						//cout << "--" << u;
					}
					//cout << "增流: " << d << endl;
					maxflow += d;
					//d = INF;可省略，因为u回退到u下一次循环开始会将d置为INF
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
			/*cout << "重贴标签后的高度:" << endl;
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
	cout << "网络邻接表如下:" << endl;
	for (int i = 0; i <= n; i++)
	{
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next)
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].next;
		cout << "]\n";
	}
}
void print(int m, int n) {
	cout << "每个代表团的安排情况:" << endl;
	for (int i = 1; i <= m; i++) {
		cout << "第" << i << "个代表团安排的会议桌号:";
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
	cout << "输入代表团数m和会议桌数n:" << endl;
	cin >> m >> n;
	init();
	total = m + n;
	cout << "依次输入每个代表团的人数:\n";
	for (int i = 1; i <= m; i++)
	{
		cin >> c;
		cnt += c;
		add(0, i, c);
	}
	cout << "依次输入每个会议桌可安排人数:\n";
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
		cout << "会议桌安排成功!\n";
		print(m, n);
		printG(total + 1);
	}
	else
		cout << "无法安排所有代表团" << endl;
	return 0;
}