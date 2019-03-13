#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 0x3fffffff;
const int N = 100;
const int M = 10000;
int top;
int h[N], g[N], pre[N];
bool flag[N*N];//标记染黑色的结点
bool dfsflag[N*N];//深度搜索到的结点

struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v, next, cap, flow;
}E[M];
void init() {
	memset(V, -1, sizeof(V));
	top = 0;
}
void addEdge(int u, int v, int c) {
	E[top].cap = c;
	E[top].flow = 0;
	E[top].v = v;
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
	h[t] = 0;
	queue<int> Q;
	Q.push(t);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		++g[h[u]];
		for (int i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
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
void printG(int n) {
	cout << "网络邻接表如下:" << endl;
	for (int i = 0; i < n; i++) {
		cout << "v" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next)
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].next;
		cout << "]\n";
	}
}
int ISAP(int s, int t, int n) {
	seth(t, n - 1);
	int u, v, i, j, d, maxflow = 0;
	u = s;
	while (h[s] < n) {
		if (u == s)
			d = INF;
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&h[u] == h[v] + 1)
			{
				d = min(d, E[i].cap - E[i].flow);
				pre[v] = i;
				u = v;
				if (u == t) {
					//cout << "增广路径" << u;
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						//cout << "--" << u;
					}
					//cout << "可增流为:" << d << endl;
					maxflow += d;
				}
				break;
			}
		}
		if (i == -1) {
			if (--g[h[u]] == 0)
				break;
			int minh = n - 1;
			for (j = V[u].first; ~j; j = E[j].next)
			{
				v = E[j].v;
				if (E[j].cap > E[j].flow)
					minh = min(minh, h[v]);
			}
			h[u] = minh + 1;
			/*cout << "重贴标签后:h[] =";
			for (int k = 0; k < n; k++)
				cout << h[k] << " ";
			cout << endl;*/
			++g[h[u]];
			if (u != s)
				u = E[pre[u] ^ 1].v;
		}
	}
	return maxflow;
}
void DFS(int s) {

	for (int i = V[s].first; ~i; i = E[i].next) {
		if (E[i].cap > E[i].flow) {
			int v = E[i].v;
			if (!dfsflag[v]) {
				dfsflag[v] = 1;
				DFS(v);
			}
		}
	}
}
void print(int m, int n) {
	cout << "最优选择方案如下:" << endl;
	cout << "选中物品的序号:";
	DFS(0);
	for (int i = 1; i <= m * n; i++)
		if (flag[i] && dfsflag[i] || !flag[i] && !dfsflag[i])
			cout << i << " ";
	cout << endl;
}
int main() {
	int n, m, total, sum = 0;
	int map[N][N];
	memset(flag, 0, sizeof(flag));
	memset(dfsflag, 0, sizeof(dfsflag));
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//上下左右四个方向
	cout << "输入货架的行数m和列数n:" << endl;
	cin >> m >> n;
	init();
	total = m * n;
	cout << "依次输入每行每个商品的价值:" << endl;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			sum += map[i][j];
		}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			if (((i + j) & 1) == 0)//==运算符优先级大于&
			{
				add(0, (i - 1)*n + j, map[i][j]);
				flag[(i - 1)*n + j] = 1;//1标记为黑色
				for (int k = 0; k < 4; k++) {
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if (x > 0 && x <= m && y > 0 && y <= n) {
						add((i - 1)*n + j, (x - 1)*n + y, INF);
					}
				}
			}
			else //初始化时为0，标记为白色
				add((i - 1)*n + j, total + 1, map[i][j]);
		}
	printG(total + 2);
	cout << sum - ISAP(0, total + 1, total + 2);
	print(m, n);
}