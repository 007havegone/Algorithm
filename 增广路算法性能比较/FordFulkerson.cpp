#include <iostream>
#include <iomanip>
#include <cstring>
#include <stack>
#include<chrono>
using namespace std;
using namespace std::chrono;
const int N = 20000;//��󶥵���
const int INF = 0x3f3f3f3f;//�����
int g[N][N];//�������磨��ʼʱ��������Ϊ0��
bool vis[N];//��������
int pre[N];//ǰ������
int n, m;//�������ͱ߸���
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
	static bool dfs(int s, int t) {//�������Ѱ�ҿ�����·
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
					if (i == t)	return true;//�ҵ�������·
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
	//���� nanosecondΪ��λ
	duration<double, nano> time_span = duration_cast<duration<double, nano>>(t2 - t1);
	cout << "Ford-Fulkerson Algorithm takes " << time_span.count() << " nanoseconds.\n\n";
	return 0;
}