#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 100;
int n, m, src;//结点数，边数，起点
/*	邻接表
	g[i][j].first表示i结点的第j条边的结点编号
	g[i][j].second表示边的长度
*/
vector<pair<int, int>> g[N + 10];
int dist[N+10];//dist[i]源点到i的最短距离
bool inQue[N + 10];
int c[N + 10];
queue<int> que;//保存待优化的结点

/*
	设立一个先进先出的队列用来保存贷优化的结点，优化时取出队首u，并用u点当前的最短路径估计值对
	u所指向的邻点v进行松弛操作，如果v点的最短路径估计值有所调整，且v不在当前的队列中，则将v点放入队尾。
	不断取出结点进行松弛，直到队列为空。
	只要最短路径存在，上述SPFA算法必定能求出最小值，因为每次将点放入队尾，都是经过松弛操作得到的。
	换而言之，每次的优化将会有某个点的最小路径估计值d[v]变小。所以算法的执行会使d越来越小。假设不存在负权回路，
	每个结点都有最小值。所以算法不会无限执行下去，随着d逐渐变小，直到达到最短路径值时，算法结束。

	复杂度:最坏情况 O(|V|*|E|)
*/
/*
	没有负环(支持负权图)
	每次我们至少能确定一个点被更新成了真正的最短路值
	（这个证明只需要将起点看作是个集合，将每次确定好的点加入起点集合即可），
	所以总共需要 |V|-1 次（起点不用更新）。
	
	如果有负环
	那么每次我们便不能说，我们已经确定了一个点，处于真正的最短路，
	这是因为，完全可以通过在负环上绕上几圈，来达到更短的目的，即推翻了那个证明。

	对于一个完全图最多有n-1个点能更新第n个点所以当进队大于n-1次就说明有负环
	至于为什么是＞n是因为对于一个节点时候 如果还是>n－1那么任意一个单节点的图会被判定为存在负环 综合考虑取>n
*/
bool SPFA() {
	memset(dist, 63, sizeof(dist));//63即 0x3f
	memset(c, 0, sizeof(c));
	dist[src] = 0;//初始化起点距离为0
	while (!que.empty())que.pop();
	que.push(src);
	inQue[src] = true;
	c[src]++;//入队次数
	while (!que.empty())//优化的点未空
	{
		int u = que.front(); que.pop();
		for (int i = 0; i < g[u].size(); i++)//遍历邻接点，松弛操作
		{
			if (dist[u] + g[u][i].second < dist[g[u][i].first]) {
				dist[g[u][i].first] = dist[u] + g[u][i].second;
				if (!inQue[g[u][i].first]) {//不在队内则进行入队操作
					inQue[g[u][i].first] = true;
					que.push(g[u][i].first);
					c[g[u][i].first]++;
					if (c[g[u][i].first] > n)//入队次数大于n-1
						return false;
				}

			}
		}
		//标记
		inQue[u] = false;
	}
	return true;
}

void print() {
	for (int i = 1; i <= n; i++)
		if (dist[i] == INF)
			cout << "INF" << " ";
		else
			cout << dist[i] << " ";
	cout << endl;
}
int main() {
	int u, v, w;
	cout << "输入结点个数和边个数:" << endl;
	cin >> n >> m;
	cout << "依次输入u,v及其距离w:\n";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g[u].push_back(make_pair(v, w));
	}
	cout << "输入起点:";
	cin >> src;
	if (SPFA())
		print();
	else
		cout << "存在负环" << endl;
}
