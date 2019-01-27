/*
	采用邻接表和优先队列实现
	复杂度为 O(nlogn)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
//数组从1开始存储 
const int INF = 0x3fffffff;
const int N = 107;
typedef struct Node {
	int lowcost;//最短距离
	int close;//最近临点
	int u;//点的下标 
	bool operator<(const Node&n)const
	{
		return lowcost > n.lowcost;
	}
}NodeType;
struct Link {
	Link(int mv, int mdis) :v(mv), dis(mdis) {}
	int v;
	int dis;
};
bool flag[N];
NodeType Nodes[N];//创建结点组 
vector<Link> G[N];//存放边的关系 

void Prim(int u0, int n)
{
	memset(flag, false, sizeof(flag));//设置未访问 
	/*优先队列 ,考虑为什么不能用指针。有重复，值更改后底层不会调整堆
		从而导致，新元素插入后，堆的顺序有误*/
	priority_queue<NodeType> que;
	//初始化结点 
	for (int i = 1; i <= n; i++)
	{
		Nodes[i].u = i;
		Nodes[i].close = u0;
		Nodes[i].lowcost = INF;
	}
	for (auto i = G[u0].begin(); i != G[u0].end(); i++)
		Nodes[i->v].lowcost = i->dis;
	Nodes[u0].lowcost = 0;
	que.push(Nodes[u0]);
	while (!que.empty())
	{
		NodeType pn = que.top(); que.pop();
		int t = pn.u;
		if (flag[t])
			continue;
		flag[t] = true;//标记已访问 
		cout << "访问:" << t << " ";
		//遍历所有邻接点 
		for (auto i = G[t].begin(); i != G[t].end(); i++)
		{
			int e = i->v;
			//更新所有未访问邻接点e 
			if (!flag[e])
			{
				if (i->dis < Nodes[e].lowcost)//更新最近 
				{
					Nodes[e].lowcost = i->dis;
					Nodes[e].close = t;
				}
				que.push(Nodes[e]);
				cout << " " << e;
			}
		}
		cout << " lowcost 7 = " << Nodes[7].lowcost;
		cout << " lowcost 3 = " << Nodes[3].lowcost;
		cout << endl;
	}

}
int main() {
	int n, m;
	int a, b, v, sta;
	int sum = 0;
	cout << "输入结点数和边数" << endl;
	cin >> n >> m;
	//清空地图 
	for (int i = 1; i <= n; i++)
		while (!G[i].empty())
			G[i].pop_back();
	cout << "输入边的信息" << endl;
	// 初始地图 
	while (m--)
	{
		cin >> a >> b >> v;
		G[a].push_back(Link(b, v));
		G[b].push_back((Link(a, v)));
	}
	cout << "输入起点" << endl;
	cin >> sta;
	Prim(sta, n);
	for (int i = 1; i <= n; i++) {
		cout << Nodes[i].lowcost << " ";
		sum += Nodes[i].lowcost;
	}
	cout << "\n最小生成树的权值为: " << sum << endl;

}