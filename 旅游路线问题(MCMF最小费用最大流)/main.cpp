#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <cstring>
using namespace std;

const int INF = 1000000000;
const int M = 150;
const int N = 10000;

int top;
int dist[N], pre[N];//源点到i的最短距离,pre[i]记录前驱
bool vis[N];//标记数组
int c[N];//入队次数
int maxflow, mincost;//最大流，最小费用
string str[M];
map<string, int>maze;
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v, next, cap, flow, cost;
}E[M];
/*
	v 邻接点 next 指向下一个邻接点的边
	cap 容量 flow 流量 cost 费用，费用为负，经过点越多费用月地，转化为最小费用最大流
*/
void init() {
	memset(V, -1, sizeof(V));
	top = 0;
}
void addEdge(int u, int v, int c, int cost) {
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].cost = cost;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void add(int u, int v, int c, int cost) {
	addEdge(u, v, c, cost);
	addEdge(v, u, 0, -cost);
}
/*
	Short Path Fastest Algorithm
*/
bool SPFA(int s, int t, int n)
{
	int i, u, v;
	queue<int> Q;
	memset(vis, 0, sizeof(vis));//初始化访问数组
	memset(c, 0, sizeof(c));//初始化访问次数
	memset(pre, -1, sizeof(pre));//初始化前驱数组
	for (int i = 1; i <= n; i++)//初始化距离
		dist[i] = INF;
	vis[s] = true;
	c[s]++;
	dist[s] = 0;//起点距离为0
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		vis[u] = false;//出队消除标记
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&dist[v] > dist[u] + E[i].cost)//松弛操作
			{
				dist[v] = dist[u] + E[i].cost;
				pre[v] = i;//记录前驱
				if (!vis[v]) {//不在队内
					c[v]++;
					Q.push(v);//入队
					vis[v] = true;//标记
					if (c[v] > n)//超过入队上限，说明有负环
						return false;
				}
			}
		}
	}
	cout << "最短路数组" << endl;
	cout << "dist []= ";
	for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << endl;
	if (dist[t] == INF)
		return false;//距离为INF，在无法到达
	return true;
}
int MCMF(int s, int t, int n)
{
	int d;//可增流量
	maxflow = mincost = 0;
	while (SPFA(s, t, n))//找到了s-t的最短路
	{
		d = INF;
		cout << "增广路径:" << t;
		for (int i = pre[t]; i != -1; i = pre[E[i ^ 1].v]) {
			d = min(d, E[i].cap - E[i].flow);//获取最小可增流了
			cout << "--" << E[i ^ 1].v;
		}
		cout << "增流: " << d << endl;
		for (int i = pre[t]; i != -1; i = pre[E[i ^ 1].v]) {//修改混合网络，增加增广路上正向边，减少反向边
			E[i].flow += d;
			E[i ^ 1].flow -= d;
		}
		maxflow += d;//更新最大流
		mincost += dist[t] * d;//更新最小费用
	}
	return maxflow;
}
void print(int s, int t) {
	int v;
	vis[s] = 1;
	for (int i = V[s].first; ~i; i = E[i].next)
	{
		v = E[i].v;
		if (!vis[v] && (E[i].flow > 0 && E[i].cost <= 0 || E[i].flow < 0 && E[i].cost >= 0))
		{
			if (v <= t)//也可以后打印，路线为一个环
				cout << str[v] << endl;
			print(v, t);

		}
	}
}
int main() {
	int n, m, i;
	string str1, str2;
	cout << "输入景点的个数n和直达的路线m:" << endl;
	cin >> n >> m;
	init();
	maze.clear();//清空映射
	for (i = 1; i <= n; i++) {
		cin >> str[i];
		maze[str[i]] = i;//创建映射
		if (i == 1 || i == n)
			add(i, i + n, 2, 0);//起点或源点容量为2
		else
			add(i, i + n, 1, 0);
	}
	cout << "输入两个可以直达的两个景点名 str1,str2:" << endl;
	for (i = 1; i <= m; i++)
	{
		cin >> str1 >> str2;
		int a = maze[str1], b = maze[str2];
		if (a < b)
		{
			if (a == 1 && b == n)
				add(a + n, b, 2, -1);
			else
				add(a + n, b, 1, -1);
		}
		else {
			if (b == 1 && a == n)
				add(b + n, a, 2, -1);
			else
				add(b + n, a, 1, -1);
		}
	}
	if (MCMF(1, 2 * n, 2 * n) == 2) {//找到到终点的路线2条
		cout << "最多经过的景点个数:" << -mincost << endl;
		cout << "依次经过的景点:" << endl;
		cout << str[1] << endl;
		memset(vis, 0, sizeof(vis));
		print(1, n);
		cout << str[1] << endl;
	}
	else
		cout << "No solution!\n";
	return 0;

}
