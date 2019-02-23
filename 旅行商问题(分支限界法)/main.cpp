#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 100;//结点个数
const int INF = 0x3f3f3f3f;//无穷大
int n, m;//结点个数和路线个数
int g[N][N];
int bestx[N];//最优解向量
int bestl;//最优值
struct Node
{
	Node(){}
	Node(int _cl,int _id) {
		id = _id;
		cl = _cl;
	}
	int id;//结点序号
	int cl;//当前路程
	int x[N];//解向量
};
//按所走路程非递减排序
bool operator<(const Node&a, const Node& b) {
	return a.cl > b.cl;
}
void priorbfs() {
	int t;
	priority_queue<Node> q;
	Node livenode, newnode;//livenode为根结点，newnode为新增结点
	newnode = Node(0, 2);
	for (int i = 1; i <= n; i++)
		newnode.x[i] = i;
	q.push(newnode);
	while (!q.empty()) {
		livenode = q.top();
		q.pop();
		t = livenode.id;
		if (t == n) {//到达最有一层
			//判断是否与前一个有路径同时和第一个结点有路径
			if (g[livenode.x[t - 1]][livenode.x[t]] != INF && g[livenode.x[1]][livenode.x[t]] != INF)
				if (livenode.cl + g[livenode.x[t - 1]][livenode.x[t]] + g[livenode.x[1]][livenode.x[t]] < bestl) {
					//更新最优解
					bestl = livenode.cl + g[livenode.x[t - 1]][livenode.x[t]] + g[livenode.x[1]][livenode.x[t]];
					for (int i = 1; i <= n; i++) {
						bestx[i] = livenode.x[i];
						//cout << bestx[i];//中间测试
					}
					//cout << endl;
				}
			continue;
		}
		//判断是否满足限界条件，否则直接结束
		if (livenode.cl >= bestl)
			continue;
		for (int i = t; i <= n; i++) {//遍历子集数
			
			if (g[livenode.x[t-1]][livenode.x[i]] != INF ) {//x[t-1]与x[t]存在路径
				double cl = livenode.cl + g[livenode.x[t - 1]][livenode.x[i]];
				newnode = Node(cl, t + 1);
				for (int j = 1; j <= n; j++)//拷贝父节点的解向量
					newnode.x[j] = livenode.x[j];
				swap(newnode.x[i], newnode.x[t]);
				q.push(newnode);
			}
		}
	}
}
void init() {//初始化
	memset(bestx, 0, sizeof(bestx));
	memset(g, INF, sizeof(g));
	bestl = INF;
}
void print() {
	cout << "\n哈密顿回路长度为:" << bestl << endl;
	cout << "最优的路径为:";
	for (int i = 1; i <= n; i++) {
		cout << bestx[i] << "-->";
	}
	cout << "1" << endl;;
}
int main() {
	int u, v, value;
	cout << "输入结点个数:";
	cin >> n;
	init();
	cout << "输入路线个数:";
	cin >> m;
	cout << "输入结点u、v和距离value:" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> value;
		g[v][u] = g[u][v] = min(value, g[u][v]);//取最小值
	}
	priorbfs();
	print();
}
