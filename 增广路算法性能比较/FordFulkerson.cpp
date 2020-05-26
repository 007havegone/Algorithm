#include <iostream>
#include <iomanip>
#include <cstring>
#include <stack>
#include<chrono>
using namespace std;
using namespace std::chrono;
const int N = 20000;//最大顶点数
const int INF = 0x3f3f3f3f;//无穷大
int g[N][N];//残余网络（初始时各边容量为0）
bool vis[N];//访问数组
int pre[N];//前驱数组
int n, m;//结点个数和边个数
class FordFulkerson
{
public:
	static int FF(int s, int t) {
		int u, v, d, maxflow;
		maxflow = 0;
		while (dfs(s, t)) {
			v = t;
			d = INF;
			while (v != s) {
				u = pre[v];
				if (d > g[u][v])
					d = g[u][v];
				v = u;
			}
			maxflow += d;
			v = t;
			while (v != s) {
				u = pre[v];
				g[u][v] -= d;
				g[v][u] += d;
				v = u;
			}
		}
		return maxflow;

	}
private:
	static bool dfs(int s, int t) {//广度优先寻找可增广路
		memset(vis, 0, sizeof(vis));
		memset(pre, -1, sizeof(pre));
		stack<int> sta;
		vis[s] = true;
		sta.push(s);
		while (!sta.empty()) {
			int now = sta.top();
			sta.pop();
			for (int i = 1; i <= n; i++) {
				if (!vis[i] && g[now][i] > 0) {
					vis[i] = true;
					pre[i] = now;
					if (i == t)	return true;//找到可增光路
					sta.push(i);
				}
			}
		}
		return false;
	}
};

int main() {
	int u, v, w;
	memset(g, 0, sizeof(g));
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		g[u][v] += w;
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cout << FordFulkerson::FF(1, n) << endl;
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//采用 nanosecond为单位
	duration<double, nano> time_span = duration_cast<duration<double, nano>>(t2 - t1);
	cout << "Ford-Fulkerson Algorithm takes " << time_span.count() << " nanoseconds.\n\n";
	return 0;
}