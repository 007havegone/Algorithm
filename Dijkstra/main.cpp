#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
//下标从1开始 
const int INF = 10e7;//无穷大
int n, m, mp[107][107];//城市，线路，地图 
bool flag[107];//是否访问
int Dis[107];
struct Node {
	int u;//城市
	int step;//距离
	Node(int m_u, int m_step) :u(m_u), step(m_step) {
	}
	//注意要const，因为是成员函数 
	bool operator<(const Node& n)const//最小值优先 
	{
		return step > n.step;
	}
};

void opt_dijkstra(int sta)
{
	priority_queue<Node> que;
	que.push(Node(sta, 0));
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= n; i++)
		Dis[i] = INF;
	Dis[sta] = 0;
	while (!que.empty()) {
		Node top = que.top();
		que.pop();
		int t = top.u;
		if (flag[t])
			continue;
		flag[t] = 1;
		for (int i = 1; i <= n; i++)
		{
			if (!flag[i] && mp[t][i] < INF)
			{
				if (Dis[i] > Dis[t] + mp[t][i])
					Dis[i] = Dis[t] + mp[t][i];
				que.push(Node(i, Dis[i]));
			}
		}
	}
}
void dijkstra(int sta)
{
	for (int i = 1; i <= n; i++)
		Dis[i] = INF;
	memset(flag, 0, sizeof(flag));//初始化未访问
	Dis[sta] = 0;
	for (int i = 1; i <= n; i++)//n次，每次一个点
	{
		int mindis = INF, mark = -1;
		for (int j = 1; j <= n; j++) {//找最近邻点
			if (!flag[j] && Dis[j] < mindis) {
				mindis = Dis[j];
				mark = j;
			}
		}
		if (mark == -1)break;
		flag[mark] = 1;
		for (int j = 1; j <= n; j++) {//松弛操作
			if (!flag[j] && Dis[j] > Dis[mark] + mp[mark][j]) {
				Dis[j] = Dis[mark] + mp[mark][j];
			}
		}
	}
}
int main()
{
	cout << "输入城市数和路线数" << endl;
	int sta;
	int ci, cj, dis;
	while (cin >> n >> m)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mp[i][j] = INF;//初始化mp

		cout << "输入路线" << endl;
		while (m--)
		{
			cin >> ci >> cj >> dis;
			mp[ci][cj] = min(mp[ci][cj], dis);
		}
		cout << "输入出发点" << endl;
		cin >> sta;
		dijkstra(sta);
		cout << "当前位置为 " << sta << endl;
		for (int i = 1; i <= n; i++)
			cout << "到位置 " << i << "的距离为 " << Dis[i] << endl;
	}
}