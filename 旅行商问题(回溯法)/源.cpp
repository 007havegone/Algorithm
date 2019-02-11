#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF = 0x3fffffff;//无穷大距离
const int N = 100;//最大结点数
int mp[N][N];//图的邻接矩阵
int x[N];//记录当前选择
int bestX[N];//记录最优解
int cl;//当前所走路径长度
int bestl;//最佳长度
int n, m;//点数和边数
void Init(int n) {
	bestl = INF;
	cl = 0;
	memset(mp, 0x3f, sizeof(mp));
	for (int i = 1; i <= n; i++) {
		x[i] = i;
		bestX[i] = 0;
	}
}
void BackTrack(int t) {
	if (t > n) {
		if (mp[1][x[n]]!=INF&&cl+mp[1][x[n]]<bestl) {//结点1和最后一个结点是否有连线
			for (int i = 1; i <= n; i++)
				bestX[i] = x[i];
			bestl = cl+mp[1][x[n]];
		}
		return;
	}
	for (int i = t; i <= n; i++) {
		if (mp[x[t-1]][x[i]] != INF && cl + mp[x[t - 1]][x[i]] < bestl) {//约束条件
			swap(x[t], x[i]);
			cl += mp[x[t-1]][x[t]];
			BackTrack(t + 1);
			cl -= mp[x[t-1]][x[t]];
			swap(x[t], x[i]);
		}
	}
}
void print(int n) {
	cout << "最优路线为:";
	for (int i = 1; i <= n; i++) {
		cout << bestX[i] << "--";
	}
	cout << 1 << endl;
	cout << "最短路径为:" << bestl << endl;
}
int main() {
	int u, v, w;
	cout << "输入结点数n:";
	cin >> n;
	Init(n);
	cout << "输入连接点的边数m:";
	cin >> m;
	cout << "输入结点u和v及其距离" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		mp[u][v] = mp[v][u] = w;
	}
	BackTrack(2);
	print(n);
	return 0;
}