#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const int N = 100;
const int INF = 0x3f3f3f3f;
double g[N][N];//地图的邻接矩阵
double minout[N];//每个结点的最小出边
double minsum;//所有结点的最小出边之和
int bestx[N];//最优解向量
double bestl;//最优路径长度
int n, m;
struct Node
{
	double zl;//当前全程路程的长度下界
	double cl;//当前所有路程长度
	double rl;//剩余路程的长度下界
	int id;//空间树层数序号
	int x[N];
	Node(){}
	Node(double _cl, double _rl, double _zl, int _id) {
		cl = _cl;
		rl = _rl;
		zl = _zl;
		id = _id;
	}
	//全程路程的长度的下界非递减排序
	bool operator<(const Node& b)const {
		return zl > b.zl;
	}
};
bool Bound() {
	for (int i = 1; i <= n; i++) {//遍历整个图
		double mmin = INF;
		for (int j = 1; j <= n; j++) 
			if (g[i][j] != INF && g[i][j] < mmin) //找出每个结点的最短出边
				mmin = g[i][j];
		if (mmin == INF)//没有出边，不可能形成回路，直接结束
			return false;
		minout[i] = mmin;
		minsum += mmin;
	}
	cout << "所有结点的最少出边之和:""minsum= " << minsum << endl;
	return true;
}
void priorbfs() {
	int t;//临时保存结点id
	priority_queue<Node>q;
	Node newnode, livenode;
	newnode = Node(0, minsum, minsum, 2);//从第2层开始
	for (int i = 1; i <= n; i++)
		newnode.x[i] = i;
	q.push(newnode);
	while (!q.empty()) {
		livenode = q.top();
		q.pop();
		t = livenode.id;
		if (t == n) {//到达倒数第2层，即t=n时
			//当前节点与前一个结点和1是否有边
			if (g[livenode.x[n-1]][livenode.x[n]] != INF && g[livenode.x[n]][1] != INF) {
				double tsum = livenode.cl + g[livenode.x[n - 1]][livenode.x[n]] + g[livenode.x[n]][1];
				if (tsum < bestl)//更新最优解
				{
					bestl = tsum;
					//cout << "当前最优的解向量:";
					for (int i = 1; i <= n; i++) {//更新解向量
						bestx[i] = livenode.x[i];
						//cout << bestx[i];
					}
					//cout << endl;

				}
			}
			continue;
		}
		//判断是否满足限界条件
		if (livenode.zl >= bestl)
			continue;

		//还未到达叶子，拓展分支
		for (int i = t; i <= n;i++) {
			if (g[livenode.x[t - 1]][livenode.x[i]] != INF) {//是否与前一个结点有连线
				double cl = livenode.cl + g[livenode.x[t-1]][livenode.x[i]];
				double rl = livenode.rl - minout[livenode.x[i]];
				double zl = cl + rl;
				if (zl < bestl) {//是否满足限界条件
					newnode = Node(cl, rl, zl, t + 1);
					for (int k = 1; k <= n; k++)
						newnode.x[k] = livenode.x[k];
					swap(newnode.x[i], newnode.x[t]);
					q.push(newnode);
				}
			}
		}

	}
}
void init() {
	bestl = INF;
	minsum = 0;
	memset(bestx, 0, sizeof(bestx));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = INF;

}
void print() {
	cout << "最优哈密顿回路为:";
	for (int i = 1; i <= n; i++)
		cout << bestx[i] << "-->";
	cout << "1\n";
	cout << "最优解的路径长度:";
	cout << bestl << endl;
}
int main() {
	int u, v;
	double w;
	cout << "输入结点个数:";
	cin >> n;
	init();
	cout << "输入路线个数:";
	cin >> m;
	cout << "依次输入u和v和2结点间的距离:";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g[u][v] = g[v][u] = w;
	}
	if (!Bound()) {
		cout << "不存在哈密顿回路" << endl;
		return 0;
	}
	priorbfs();
	print();
	return 0;
}