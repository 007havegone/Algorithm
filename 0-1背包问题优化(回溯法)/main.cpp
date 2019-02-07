/*
	回溯算法的运行时间取决于搜索过程中生成的结点数。限界函数可以大大减少生成结点的个数，从而加速

	原先最坏情况下左右孩子结点个数均为2^n-1。
	约束函数时间复杂度为O（1），限界函数时间复杂度为O（n）。
	总的时间复杂度为O（n*2^n+1*2^n)=O（n*2^n）

	在搜索过程中的任何时刻，仅保留从开始结点到当前拓展结点的路径，最大的长度为n，同时使用bestc[]辅助数据所以空间复杂度为O（n）。

	可以通过减少原先的上界函数的估值。缩小上界，从而加快剪速度，提高搜索效率。
	改为剩余容量，能获得的最大价值

	将物品按单位质量非递增排序，然后按排序后的顺序考察各个物品
 */
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1005;//最大物品数目
int i, j, n, W;//物品个数和背包容量
double w[N], v[N];//物品的质量和价格
bool x[N];//记录物品是否放入
bool bestX[N];//最优选择
double cw, cv;//当前的质量和价格
double bestV;//最优价值

//该限界函数的上界更小，可以加速
double bound(int i) {
	double wleft = W - cw;//剩余容量
	double brv = 0.0;
	while (i <= n && w[i] < wleft)
	{
		wleft -= w[i];
		brv += v[i];
		i++;
	}
	if (i <= n) {//采用切割的方式装满背包，求上界。
		brv += v[i] / w[i] * wleft;
	}
	return brv + cv;
}
void Backtrack(int t) {
	if (t > n) {//到达叶子
		bestV = cv;
		for ( i = 1; i <= n; i++) {
			bestX[i] = x[i];
		}
		return;
	}
	if (cw + x[t] <= W) {//满足约束条件遍历左子树
		cw += w[t];
		cv += v[t];
		x[t] = 1;
		Backtrack(t + 1);
		cw -= w[t];
		cv -= v[t];
	}
	if (bound(t + 1) > bestV) {//满足限界条件遍历右子树
		x[t] = 0;
		Backtrack(t + 1);
	}
}
struct Object
{
	int id;//物品序号
	double d;//单位质量价格
	bool operator<(const Object& obj)const {//按单位价格降序
		return d > obj.d;
	}
};
void Knapsack(int W, int n) {
	cw = 0.0;
	cv = 0.0;
	bestV = 0.0;
	double sumw = 0.0;
	double sumv = 0.0;
	Object *Q = new Object[n];//从0开始
	for (i = 1; i <= n; i++) {
		sumv += v[i];
		sumw += w[i];
		Q[i - 1].id = i;
		Q[i - 1].d = 1.0*v[i] / w[i];
	}
	if (sumw <= W) {
		bestV = sumv;
		cout << "放入背包的物品最大价值为:" << bestV << endl;
		cout << "所有物品放入背包" << endl;
		return;
	}
	sort(Q, Q + n);//排序
	for (int i = 1; i <= n; i++) {//将排序好后的质量的价格传递给原数组
		v[i] = v[Q[i - 1].id];
		w[i] = v[Q[i - 1].id];
	}
	Backtrack(1);
	cout << "放入背包的物品最大价值为:" << bestV << endl;
	cout << "放入背包的物品序号为:";
	for (int i = 1; i <= n; i++)
		if (bestX[i]) {
			cout << Q[i - 1].id << " ";
		}
	cout << endl;
}
	
int main() {
	cout << "输入商品的数量:";
	cin >> n;
	cout << "输入背包的容量:";
	cin >> W;
	cout << "输入商品的质量和价格（空格隔开）:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	Knapsack(W, n);

	return 0;
}
