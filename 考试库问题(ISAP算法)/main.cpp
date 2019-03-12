#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int INF = 0x3fffffff;
const int N = 100;
const int M = 10000;
int top;
int h[N], g[N], pre[N];
/*
	h[i]为第i个结点的高度
	g[i]为高度为i的结点的数量
	pre[i]为第i个结点的前驱边
*/
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
void printG(int m) {
	cout << "题库各题型的题目分布如下:" << endl;
	for (int i = 1; i <= m; i++) {
		cout << "题型" << i << ":";
		for (int j = V[i].first; ~j; j = E[j].next)
			if(E[j].v!=0)
				cout << E[j].v-m << " ";
		cout << endl;
	}
}
void print(int m) {
	cout << "试题抽取方案:" << endl;
	for (int i = 1; i <= m; i++) {
		cout << "第" << i << "个题型抽取的试题号:";
		for (int j = V[i].first; ~j; j = E[j].next)
			if (E[j].flow == 1)
				cout << E[j].v-m << " ";
		cout << endl;
	}
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
		for (int i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (h[v] == -1)
			{
				h[v] = h[u] + 1;
				Q.push(v);
			}
		}
	}
	/*cout << "h[] =";
	for (int i = 0; i <= n; i++)
		cout << h[i] << " ";
	cout << endl;*/
}
int ISAP(int s, int t, int n) {
	seth(t, n - 1);//初始化高度
	int maxflow, u, v, i, j, d;
	maxflow = 0;
	u = s;//当前工作节点
	while (h[s] < n) {//起始结点高度小于结点数
		if (u == s)
			d = INF;
		for (i = V[u].first; ~i; i = E[i].next) {//遍历所有邻接点
			v = E[i].v;//获取邻接点
			if (h[u] == h[v] + 1 && E[i].cap > E[i].flow) {//满足高度差为1，同时有可增广路
				d = min(d, E[i].cap - E[i].flow);
				pre[v] = i;
				u = v;
				if (u == t)//找到汇点
				{
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
					}
					maxflow += d;
					d = INF;
				}
				break;//找到邻接点结束
			}

		}
		if (i == -1) {//未找到邻接点
			if (--g[h[u]] == 0)//当前高度结点只有一个
				break;//没有可增广路结束查找
			int minh = n - 1;
			for (j = V[u].first; ~j; j = E[j].next) {//遍历所有邻接点找出最小高度
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
int main() {
	int m, n, total, cost, t, sum = 0;
	cout << "输入题型数m和试题数n:\n";
	cin >> m >> n;
	total = m + n;
	init();
	for (int i = m + 1; i <= total; i++)//每道题只选一次
		add(i, total + 1, 1);
	cout << "依次输入每种题型选择的数量:\n";
	for (int i = 1; i <= m; i++) {//每个题型选cost次，作为容量
		cin >> cost;
		sum += cost;
		add(0, i, cost);
	}
	cout << "依次输入每个试题所属的题型(0)结束:\n";
	for (int i = m + 1; i <= total; i++) {
		while (cin >> t && t != 0)
			add(t, i, 1);//添加题型和题目的连线
	}
	printG(m);
	if (sum == ISAP(0, total + 1, total + 2)) {
		cout << "抽取成功" << endl;
		print(m);
	}
	else
		cout << "抽取失败" << endl;
	return 0;
}