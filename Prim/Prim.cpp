/*
	时间复杂度为O(n^2)

*/
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100;
const int INF = 0x3fffffff;
int lowcost[N];//最短距离 
int close[N];//邻近的边 
bool flag[N];//是否访问
int G[N][N];
void Prim(int u0, int n)//u0为其实点，n为顶点个数 
{
	//重置lowcost和flag和close
	flag[u0] = true;
	for (int i = 1; i <= n; i++)
	{
		if (i != u0)
		{
			flag[i] = false;
			close[i] = u0;
			lowcost[i] = G[u0][i];
		}
		else
			lowcost[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		int t = u0;
		int dis = INF;
		//寻找最短距离的点t
		for (int j = 1; j <= n; j++) {
			if (!flag[j] && lowcost[j] < dis)
			{
				dis = lowcost[j];
				t = j;
			}
		}
		if (t == u0)
			break;//未找到
		//找到加入 
		flag[t] = true;
		for (int j = 1; j <= n; j++)
		{
			if (!flag[j] && G[t][j] < lowcost[j]) {
				lowcost[j] = G[t][j];
				close[j] = t;
			}
		}
	}
}
int main()
{
	int n, m;
	int a, b, v;
	int sta;
	int sum = 0;
	cout << "输入点的个数和边的个数" << endl;
	cin >> n >> m;
	//初始化图 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			G[i][j] = INF;
	cout << "输入边和长度" << endl;
	while (m--)
	{
		cin >> a >> b >> v;
		G[a][b] = G[b][a] = min(G[a][b], v);
	}
	cout << "输入起点" << endl;
	cin >> sta;
	Prim(sta, n);
	for (int i = 1; i <= n; i++) {
		sum += lowcost[i];
		cout << lowcost[i] << " ";
	}
	cout << "\n最小生成树权值为:" << sum << endl;
}
