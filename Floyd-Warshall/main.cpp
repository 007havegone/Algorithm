#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100;
const int INF = 1000000000;
int n, g[N][N];
void floyd() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

void print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << g[i][j] << " ";
		cout << endl;
	}
}
int main() {
	int m, u, v, w;
	cout << "输入结点个数:" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			g[i][j] = INF;
		}
	cout << "输入边的个数m:" << endl;
	cin >> m;
	cout << "依次输入u,v及其距离g[u][v]:\n";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g[v][u] = g[u][v] =	w;
	}
	floyd();
	print();

	return 0;
}