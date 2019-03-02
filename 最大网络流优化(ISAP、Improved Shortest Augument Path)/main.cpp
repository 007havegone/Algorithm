#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N = 100;//结点数
const int M = 10000;//边数
const int INF = 0x3f3f3f3f;//无穷大
int top;//记录边的位序
int pre[N], h[N], g[N];
/*
	pre[]前驱边数组
	h[]高度数组
	g[]结点高度数量
*/
struct Vertex {
	int first;
}V[N];
struct Edge
{
	int v, next;//v为u的邻接点，next指向下一个邻接点边
	int cap, flow;//cap为边的容量，flow为实流量
}E[M];
void add_edge(int u, int v, int c) {//创建边
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].next = V[u].first;//链接到邻接表头
	V[u].first = top++;
}
void add(int u, int v, int c) {
	add_edge(u, v, c);
	add_edge(v, u, 0);
}
void set_h(int t, int n) {//标高函数
	queue<int>q;
	memset(h, -1, sizeof(h));//设置高度为-1作为未访问标记
	memset(g, 0, sizeof(g));
	h[t] = 0;
	q.push(t);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		g[h[v]]++;
		int i = V[v].first;
		for (; ~i; i = E[i].next) {
			int u = E[i].v;
			if (h[u] == -1)//还未访问
			{
				h[u] = h[v] + 1;
				q.push(u);//入队
			}
		}
	}
	cout << "初始化高度" << endl;
	cout << "h[]= ";
	for (int i = 1; i <= n; i++)
		cout << h[i] << " ";
	cout << endl;
}
/*
	V为结点,E为边
	可证每条边成为关键边次数最多为|V|/2,总共有E条边，故关键边有O(VE)
	即可增广路有O(VE)
	采用ISAP得到一条可增广路为O(V),故时间复杂度为O(V^2*E)
	空间复杂度为O(V)
*/
int ISAP(int s, int t, int n) {//Improved Shortest
	set_h(n, n);
	int ans = 0;
	int u = s;//记录当前处理结点
	int d;//记录最大可增量
	while (g[h[u]] < n) {//从0开始n个点最大高度为n-1
		int i = V[u].first;//获取头结点
		if (u == s)//起点，d置为无穷大
			d = INF;
		//遍历邻接点
		for (; ~i; i = E[i].next) {
			int v = E[i].v;
			if (E[i].cap > E[i].flow&&h[u] == h[v] + 1) {//边满足cap>flow同时高度满足
				pre[v] = i;//设置前驱边
				u = v;
				d = min(d, E[i].cap - E[i].flow);
				if (u == t) {//找到了可增广路
					cout << "增广路径:" << t;
					while (u != s) {
						int j = pre[u];
						E[j].flow += d;//正向边+d
						E[j ^ 1].flow -= d;//反向边-d
						u = E[j ^ 1].v;//更新u未前一个点
						cout << "--" << u;
					}
					cout << "增流:" << d << endl;
					ans += d;
					d = INF;
				}
				break;//找到了一个邻点结束
			}
		}
		if (i == -1) {//找不到可行邻边，无法前进
			if (g[h[u]] == 1)//该高度的结点只有一个结束
				break;
			int hmin = n - 1;
			for (int j = V[u].first; ~j; j = E[j].next)
				if (E[j].cap > E[j].flow)
					hmin = min(hmin, h[E[j].v]);
			h[u] = hmin + 1;//更新高度
			g[h[u]]++;
			if (u != s)//不是起始点，回退到上一个点
				u = E[pre[u] ^ 1].v;
			cout << "重新标高后高度:" << endl;
			cout << "h[]= ";
			for (int i = 1; i <= n; i++)
				cout << h[i] << " ";
			cout << endl;
		}
	}
	return ans;
}
void init(int n) {
	top = 0;
	memset(V, -1, sizeof(V));
}
void printg(int n) {
	cout << "---------网络邻接表如下:---------" << endl;
	for (int i = 1; i <= n; i++) {
		cout << "v" << i << "[" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			cout << "]--[" << E[j].v << " " << E[j].cap << " " <<
				E[j].flow << " " << E[j].next;
		}
		cout << "]\n";
	}
}
void printflow(int n) {
	cout << "---------实流边如下:---------" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow > 0)
				cout << i << "--" << E[j].v << " " << E[j].flow<< endl;
		}
	}
}
int main() {
	int n, m;
	int u, v, c;
	cout << "输入结点的个数n和边的个数m:" << endl;
	cin >> n >> m;
	init(n);
	cout << "依次输入两个结点u,v及边(u--v)的容量w:" << endl;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> c;
		add(u, v, c);//添加边
	}
	cout << endl;
	printg(n);
	cout << "网络的最大流值:" << ISAP(1, n, n) << endl;
	printg(n);
	printflow(n);
}