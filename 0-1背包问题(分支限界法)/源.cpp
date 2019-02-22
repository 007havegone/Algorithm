/*
	
	该分支限界法的解空间（子集树）的结点个数有 2^(n+1)-1
	左右结点数各有 2^(n+1)-1-1/2 = 2^n-1
	约束和限界函数的时间复杂度均为O(1）故时间复杂度为O(2^(n+1))

	空间复杂度最多有2^(n+1)-1个结点，每个结点为O（n)，空间复杂度为O(n*2^(n+1))
	可以用指针来存储父亲和左右节点，得到最优解后逆向查找,代替每个结点保存解向量
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 10;

struct Node
{
	int cv, rv;//当前价值，剩余价值
	int rw;//剩余容量
	int id;//结点层数序号
	bool x[N];//最优解向量
	Node() {
		memset(x, 0, sizeof(x));//解向量初始化为0
	}
	Node(int _cv, int _rv, int _rw, int _id) {
		cv = _cv;
		rv = _rv;
		rw = _rw;;
		id = _id;
	}
};
struct Goods
{
	int value;
	int weight;
}goods[N];
int bestp,bestx[N], W, n, sumw, sumv;
/*
	bestp为记录最优值
	bestx为最优解
	W记录容量
	sumw记录物品总质量
	sumv记录物品总价值
*/
void bfs() {
	int t, tcv, trv, trw;//作为临时值
	queue<Node> q;
	q.push(Node(0, sumv, W, 1));//将头结点压入
	while (!q.empty()) {
		Node livenode, lnode, rnode;//定义三个结点
		livenode = q.front();
		q.pop();
		t = livenode.id;
		//到达最后一个或者没有容量
		if (t > n || livenode.rw == 0) {
			if (livenode.cv >= bestp) {//更新最优解
				for (int i = 1; i <= n; i++) {
					bestx[i] = livenode.x[i];
				}
				bestp = livenode.cv;
			}
			continue;
		}
		//是否满足限界函数，否则结束搜索
		if (livenode.cv + livenode.rv < bestp)
			continue;
		//保存到临时值，方便后面使用
		tcv = livenode.cv;
		trv = livenode.rv-goods[t].value;//无论是否加入剩余价值都要减去
		trw = livenode.rw;
		//拓展左结点
		if (trw >= goods[t].weight) {
			lnode.rw = trw - goods[t].weight;
			lnode.cv = tcv + goods[t].value;
			lnode = Node(lnode.cv, trv, lnode.rw, t + 1);
			for (int i = 1; i < t; i++) {
				lnode.x[i] = livenode.x[i];//复制父节点的解向量
			}
			lnode.x[t] = true;//将第t个加入背包
			if (lnode.cv > bestp)
				bestp = lnode.cv;
			q.push(lnode);
		}
		//拓展右结点
		//是否满足限界函数，否则跳过
		if (tcv + trv < bestp)
			continue;
		rnode = Node(tcv, trv, trw, t + 1);
		for (int i = 1; i < t; i++) {
			rnode.x[i] = livenode.x[i];//复制父节点的解向量
		}
		rnode.x[t] = false;
		q.push(rnode);
	}
}
int main() {
	cout << "输入物品的个数:";
	cin >> n;
	cout << "输入背包的容量:";
	cin >> W;
	cout << "依次输入商品的质量和价值:";
	for (int i = 1; i <= n; i++) {
		cin >> goods[i].weight >> goods[i].value;
		sumw += goods[i].weight;//计算总质量
		sumv += goods[i].value;//计算总价值
	}
	if (sumw <= W) {
		bestp = sumv;
		cout << "放入背包的最大价值为:" << bestp << endl;
		cout << "将所有物品放入背包" << endl;
		return 0;
	}
	bfs();
	cout << "放入背包的最大价值为:" << bestp << endl;
	cout << "放入购物车的商品序号为:";
	for (int i = 1; i <= n; i++)
	{
		if (bestx[i])
			cout << i << " ";
	}

	return 0;
}