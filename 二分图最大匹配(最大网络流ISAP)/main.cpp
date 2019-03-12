#include <iostream>
#include <queue>
#include <cstring>
using namespace	std;
const int INF = 0x3f3f3f3f;
const int N = 100;//结点个数
const int M = 10000;//边个数
int h[N], g[N], pre[N];
/*
	h[i]为第i个结点的高度
	g[i]为高度为i的结点数量
	pre[i]为第i个结点的前驱边
*/
int top;
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v;//终点
	int cap;//容量
	int flow;//流量
	int next;//指向下一个邻接点
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
/*初始化结点高度*/
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
//s为起点，t为终点，n为结点数
int ISAP(int s, int t, int n) {
	int u, v, d;
	int i, j, maxflow=0;
	set_h(t, n-1);//初始化高度
	u = s;//当前工作结点
	while (h[s]<n)
	{
		if (u == s)
			d = INF;
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&h[u] == h[v] + 1) {
				pre[v] = i;//记录前驱边
				d = min(d, E[i].cap - E[i].flow);//可优化
				u = v;
				if (u == t) {//找到汇点
					cout << "可增广路为:" << u;
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						cout << "--" << u;
					}
					cout << "  增流:" << d << endl;
					maxflow += d;
					d = INF;
				}
				break;
			}
		}
		if (i == -1)//不可以前进
		{
			if (--g[h[u]] == 0)//当前结点高度改变，数量-1
				break;
			//初始高度为结点数-1
			int minh = n - 1;
			for (j = V[u].first; ~j; j = E[j].next) {
				v = E[j].v;
				if (E[j].cap > E[j].flow)
					minh = min(minh, h[v]);
			}
			h[u] = minh+1;
			cout << "重贴标签后的高度" << endl;
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
/*打印实流网络*/
void printflow(int m) {
	cout << "实流网络如下:" << endl;
	for (int i = 1; i <= m; i++) {
		for (int j = V[i].first; ~j; j = E[j].next)
			if(E[j].flow>0)
				cout << i << "--" << E[j].v << endl;
	}
}
/*打印邻接表*/
void printG(int n) {
	cout << "邻接表如下:" << endl;
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
	cout << "输入女职员人数m和男职员人数n:\n";
	cin >> m >> n;
	total = m + n;
	init();
	for (int i = 1; i <= m; i++)
		add(0, i, 1);
	for (int j = m + 1; j <= total; j++)
		add(j, total + 1, 1);
	cout << "请输入可以匹配的女性编号u和男性编号v(两个均为-1结束)\n";
	while (cin >> u >> v && u + v != -2) {
		add(u, v, 1);
	}
	printG(total + 1);
	cout << "二分图的最大匹配数为:" << ISAP(0, total + 1, total + 2) << endl;
	printflow(m);

	return 0;
}