#include <iostream>
#include <algorithm>
#include <cstring>
#include <tuple>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;//无穷大
const int N = 100;//最大结点数
const int M = 10000;//最大边数
int top;
int pre[N],c[N];//pre前驱边数组，c每个结点访问次数
int dist[N];//从源点到n的最短距离(最小单位费用和）
bool vis[N];//访问数组
struct Vertex//邻接表头
{
	int first;
}V[N];
struct Edge
{
	int v;//边终点
	int cap;//容量
	int flow;//流量
	int cost;//费用
	int next;//下一个邻接点
}E[M];
/*
	SPFA支持负权边,找增广路的时间是O(E)
*/
bool SPFA(int s, int t, int n) {	//Shortest Path Faster Algorithm
	int i, u, v;
	queue<int> Q;
	memset(pre, -1, sizeof(pre));//前驱数组置为-1
	memset(dist, 0x3f, sizeof(dist));//每个结点到源点距离初始化为无穷
	memset(vis, false, sizeof(vis));//初始化每个结点未访问
	memset(c, 0, sizeof(c));//每个结点访问次数为0
	
	vis[s] = true;
	c[s]++;
	dist[s] = 0;
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		vis[u] = false;
		//取消访问标记
		for (i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow&&dist[v] > dist[u] + E[i].cost) {//松弛操作
				dist[v] = dist[u] + E[i].cost;//更新最短距离
				pre[v] = i;//更新前驱
				if (!vis[v])
				{
					c[v]++;
					Q.push(v);		//入队
					vis[v] = true;	//标记
					if (c[v] > n)//超过入队上限，说明有负环
						return false;
				}
			}
		}
	}
	cout << "最短路数组" << endl;
	cout << "dist[] =";
	for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << endl;
	if (dist[t] == INF)
		return false;
	return true;
}
/*
	SPFA时间复杂度为O(E)
	关机边的个数为O(VE)
	因此总的时间复杂度为O(VE^2)
	空间复杂度为O(V)
*/
tuple<int,int> MCMF(int s, int t, int n) {//MinCost MaxFlow
	int d;
	int i, mincost,maxflow;
	mincost = 0;
	maxflow = 0;
	while (SPFA(s, t, n)) {
		d = INF;
		cout << "增广路为: v" << t;
		for (int i = pre[t]; ~i; i = pre[E[i ^ 1].v]) {
			cout << "--v" << E[i ^ 1].v;
			d = min(d, E[i].cap - E[i].flow);//寻找最小可增广流
		}
		cout << "增流:" << d << endl;
		maxflow += d;
		for (int i = pre[t]; ~i; i = pre[E[i ^ 1].v]) {//增广路正向边+d，反向边流量-d
			E[i].flow += d;
			E[i ^ 1].flow -= d;
		}
		mincost += dist[t] * d;//dist[t]为该路径上单位流量费用之和
	}
	return make_tuple(maxflow, mincost);
}
void init(int n) {
	memset(V, -1, sizeof(V));//初始化邻接表头为-1，即空表
	top = 0;
}
void addEdge(int u, int v, int w, int c) {
	E[top].v = v;
	E[top].flow = 0;
	E[top].cap = w;
	E[top].cost = c;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void add(int u, int v, int w, int c) {
	addEdge(u, v, w, c);
	addEdge(v, u, 0, -c);
}

void printG(int n) {
	cout << "邻接表如下:\n";
	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			cout << "]--[" << E[j].v << " " << E[j].cap << " " << E[j].flow << " " << E[j].cost << " " << E[j].next;
		}
		cout << "]\n";
	}

}
void printflow(int n) {
	cout << "网络实流边如下:" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow > 0)
			{
				cout << "v" << i << "--v" << E[j].v << "  " << E[j].flow << "  " << E[j].cost << endl;
			}
		}
	}
}
int main() {
	int n, m;//结点数和边数
	int u, v, w, c;
	tuple<int, int> ans;//第一个值为maxflow，第二个值为mincost
	cout << "输入结点个数n和边数m:\n";
	cin >> n >> m;
	init(n);//初始化邻接表和top
	cout << "请输入两个结点u,v,边(u--v)的容量w，单位容量费用c:\n";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w >> c;
		add(u, v, w, c);
	}
	printG(n);
	ans = MCMF(1, n, n);
	cout << "网络的最小费用为:" << get<1>(ans) << endl;
	cout << "网络的最大流量为:" << get<0>(ans) << endl;
	printflow(n);
	
	return 0;
}