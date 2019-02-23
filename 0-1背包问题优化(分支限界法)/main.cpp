#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
const int N = 10;//最大物品数
int n, W;//物品书和背包容量
int sumw, sumv;//商品总质量和总价值
int bestv;//最优价值
bool bestx[N];
int v[N];//存放按性价比排序的价值和质量
int w[N];
struct Node
{
	Node() {}
	Node(int _cv, double _up, int _rw, int _id) :cv(_cv),up(_up),
									rw(_rw), id(_id) {
		memset(x, 0, sizeof(x));
	}
	int cv;//当前价值
	double up;//上限
	int rw;//剩余容量
	int id;
	bool x[N];//记录最优解
	bool operator<(const Node& b)const {//up的非递增序列
		return up < b.up;
	}
};
struct Goods
{
	int weight;
	int value;
}goods[N];
struct Object
{
	int id;
	double cp;//性价比
	bool operator<(const Object& b)const {//性价比非递增序列
		return cp > b.cp;

	}
}obj[N];
double bound(const Node& node) {
	int left = node.rw;//当前剩余空间
	double maxvalue = node.cv;//当前价值
	int i = node.id;
	while (i <= n && left >= w[i]) {
		left -= w[i];
		maxvalue += v[i];
		i++;
	}
	if (left && i<=n) {
		maxvalue += 1.0 * left * v[i] / w[i];
	}
	return maxvalue;
}
void priorbfs() {
	int t, tcv, trw;//作为临时变量
	double tup;
	priority_queue<Node> q;
	q.push(Node(0, sumv, W, 1));//压入根节点
	while (!q.empty()) {
		Node livenode, lnode, rnode;//创建三个结点
		livenode = q.top();
		q.pop();
		cout << "当前结点的id值:" << livenode.id << "当前结点的up值:" << livenode.up << endl;
		cout << "当前结点的解向量:";
		for (int i = 1; i <= n; i++)
		{
			cout << livenode.x[i];
		}
		cout << endl;
		t = livenode.id;
		if (t > n || livenode.rw == 0) {//到达最后一层或者空间不足
			if (livenode.cv >= bestv) {//更新最优解
				cout << "更新最优解向量:";
				for (int i = 1; i <= n; i++) {
					bestx[i] = livenode.x[i];
					cout << bestx[i];
				}
				cout << endl;
				bestv = livenode.cv;
			}
			continue;
		}
		if (livenode.up < bestv)//限界条件
			continue;
		//拓展左结点
		trw = livenode.rw;
		tcv = livenode.cv;
		if (trw >= w[t]) {//约束条件
			lnode.cv = tcv + v[t];
			lnode.rw = trw - w[t];
			lnode.id = t + 1;
			tup = bound(lnode);
			lnode = Node(lnode.cv, tup, lnode.rw, lnode.id);
			for (int i = 1; i < t; i++) {
				lnode.x[i] = livenode.x[i];//复制父节点的最优解
			}
			lnode.x[t] = true;
			if (lnode.cv > bestv)
				bestv = lnode.cv;
			q.push(lnode);
		}
		rnode.cv = tcv;
		rnode.rw = trw;
		rnode.id = t + 1;
		tup = bound(rnode);
		if (tup >= bestv) {
			rnode = Node
			(rnode.cv, tup, rnode.rw, rnode.id);
			for (int i = 1; i < t; i++)
				rnode.x[i] = livenode.x[i];
			rnode.x[t] = false;
			q.push(rnode);
		}
	}
}
int main() {
	bestv = 0;
	sumv = 0;
	sumw = 0;
	cout << "输入物品个数:";
	cin >> n;
	cout << "输入背包容量:";
	cin >> W;
	cout << "依次输入每个物品的质量和价值:";
	for (int i = 1; i <= n; i++) {
		cin >> goods[i].weight >> goods[i].value;
		sumv += goods[i].value;
		sumw += goods[i].weight;
		obj[i - 1].id = i;
		obj[i - 1].cp = 1.0* goods[i].value / goods[i].weight;
	}
	if (sumw <= W) {
		bestv = sumv;
		cout << "最优商品价值为:" << bestv << endl;
		cout << "购买所有物品" << endl;
		return 0;
	}
	sort(obj, obj + n);//排序
	cout << "排序后:" << endl;
	for (int i = 1; i <= n; i++) {
		v[i] = goods[obj[i - 1].id].value;
		w[i] = goods[obj[i - 1].id].weight;
		cout << v[i] << " " << w[i] << endl;
	}
	priorbfs();
	cout << "最优价值为:" << bestv << endl;
	cout << "购买的商品序号为:";
	for (int i = 1; i <= n; i++)
	{
		if (bestx[i])
			cout << obj[i - 1].id << " ";
	}

	return 0;
}