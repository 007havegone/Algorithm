#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <queue>
using namespace std;
const int N = 105;//最大顶点数
const int INF = 0x3f3f3f3f;//无穷大
int g[N][N];//残余网络（初始时各边容量为0）
int f[N][N];//实流网络（初始时个边为0流）
bool vis[N];//访问数组
int pre[N];//前驱数组
int n, m;//结点个数和边个数

void print() {//打印实流网络
	cout << "----------------实流网络如下:----------------" << endl;
	cout << "  ";
	for (int i = 1; i <= n; i++)
		cout << setw(7) << "v" << i;
	cout << endl;
	for (int i = 1; i <= n; i++) {
		cout << "v" << i;
		for (int j = 1; j <= n; j++)
			cout << setw(7) << f[i][j] << " ";
		cout << endl;
	}
}
bool bfs(int s,int t) {//广度优先寻找可增广路
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	queue<int> q;
	vis[s] = true;
	q.push(s);
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (int i = 1; i <= n; i++) {//寻找可增广路
			if (!vis[i] && g[now][i] > 0) {//是否未访问且有相连
				vis[i] = true;
				pre[i] = now;
				if (i == t)	return true;//找到可增光路
				q.push(i);
			}
		}
	}
	return false;//找不到可增广路
}
/*
	V为结点,E为边
	可证可增广路共O(VE),采用bfs获取可增广路的为O(E)
	故时间复杂度为(V*E^2)
*/
//最短增广路算法 (Edmonds-Karp算法、Shortest Argumemt Path、SAP算法）
int EK(int s, int t) {
	int u, v, d, maxflow;
	maxflow = 0;
	while (bfs(s, t)) {//可以增广
		v = t;
		d = INF;
		while (v != s) {//获取最小可增量d
			u = pre[v];
			if (d > g[u][v])
				d = g[u][v];
			v = u;
		}
		maxflow += d;
		v = t;
		while (v != s) {
			u = pre[v];
			g[u][v] -= d;//残余网络中正向边减流
			g[v][u] += d;//残余网络中反向边增流
			if (f[v][u] > 0)//实际网络中有反向边，则减流，否则正向增流
				f[v][u] -= d;//一定可以保证f[v][u]>=d,k是f[v][u]的反向边,d满足k>=d
			else
				f[u][v] += d;
			v = u;
		}
	}
	return maxflow;

}

int main() {
	int u, v, w;
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	cout << "输入结点个数n和边数m:\n";
	cin >> n >> m;
	cout << "依次输入两个结点u、v即(u->v)的容量w:\n";
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		g[u][v] += w;
	}
	cout << "网络流的最大值" << EK(1, n) << endl;
	print();//输出实流网络
	return 0;
}