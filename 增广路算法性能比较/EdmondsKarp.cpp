#include <iostream>
#include <iomanip>
#include <cstring>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;
const int N = 20000;//��󶥵���
const int INF = 0x3f3f3f3f;//�����
int g[N][N];//�������磨��ʼʱ��������Ϊ0��
bool vis[N];//��������
int pre[N];//ǰ������
int n, m;//�������ͱ߸���
class EdmondsKarp
{
public:
	static int EK(int s, int t) {
		int u, v, d, maxflow;
		maxflow = 0;
		while (bfs(s, t)) {
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
	static bool bfs(int s, int t) {//�������Ѱ�ҿ�����·
		memset(vis, 0, sizeof(vis));
		memset(pre, -1, sizeof(pre));
		queue<int> q;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			for (int i = 1; i <= n; i++) {
				if (!vis[i] && g[now][i] > 0) {
					vis[i] = true;
					pre[i] = now;
					if (i == t)	return true;//�ҵ�������·
					q.push(i);
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
	cout << EdmondsKarp::EK(1, n) << endl;

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//���� nanosecondΪ��λ
	duration<double, nano> time_span = duration_cast<duration<double, nano>>(t2 - t1);
	cout << "Edmonds-Karp Algorithm takes " << time_span.count() << " nanoseconds.\n\n";
	return 0;
}