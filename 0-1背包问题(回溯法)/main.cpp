/*
	回溯算法设计：
	1、定义问题解空间 （1）解的组织形式，一般为n元组	（2）显约束，对解分量的取值范围的限定，控制解空间的大小
	2、确定解空间的组织形式，有利于观察搜索空间的大小，解空间分为子集树、排列书、m叉树。
	3、搜索解空间	根据隐约束（剪枝函数）包括约束函数和限界函数。前者为能否得到可行解，后者为能否得到最优解。

	解空间的大小和剪枝函数的好坏直接影响搜索效率，这两项是搜索算法的关键

*/

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1007;
bool x[N];//记录商品的选择情况
double w[N],v[N];//记录商品的质量和价值
int n, W;//商品数量和背包容量
int bestc[N];//记录最优解
double bestV;//最优价值
double cw;//当前质量
double cv;//当前价值

int bound(int i) {
	double rv = 0;//剩余第i到n物品的价值
	while (i <= n) {
		rv += v[i];
		i++;
	}
	return rv + cv;
}
void Backtrack(int t) {//搜索空间数，t表示当前拓展结点在第t层
	if (t > n) {//到达第n+1层即叶子，因为有限界函数，能达到底部的一定是最优解
		for (int i = 1; i <= n; i++)
			bestc[i] = x[i];
		bestV = cv;
		return;
	}
	if (cw + w[t] <= W) {//约束条件，确保可行解
		x[t] = 1;
		cw += w[t];
		cv += v[t];
		Backtrack(t + 1);
		//x[t] = 0;//可加可不加，结束后还有右子树
		cw -= w[t];
		cv -= v[t];
	}
	if (bound(t + 1) > bestV) {//限界条件，加速找出最优解
		x[t] = 0;
		Backtrack(t + 1);
	}
}

void Knapsack(int W,int n) {
	cw = 0;//初始化质量和价值为0
	cv = 0;
	bestV = 0;//初始化最优解为0
	double sumw = 0.0;
	double sumv = 0.0;
	for (int i = 1; i <= n; i++) {
		sumw += w[i];
		sumv += v[i];
	}
	if (sumw <= W) {//能放入全部，直接返回
		bestV = sumv;
		cout << "放入背包的物品最大价值为:" << bestV << endl;
		cout << "所有物品放入背包" << endl;
		return;
	}
	/*for (int i = 1; i <= n; i++) {//不必初始化，遍历过程中和初状态无关
		bestc[i] = x[i] = 0;
	}*/
	Backtrack(1);
	cout << "放入背包的物品最大价值为:" << bestV << endl;
	cout << "放入背包的物品序号为:";
	for (int i = 1; i <= n; i++) {
		if (bestc[i])
			cout << i << " ";
	}
}
int main() {
	cout << "输入商品的数量:";
	cin >> n;
	cout << "输入背包的容量:";
	cin >> W;
	cout << "输入商品的质量和价格（空格隔开）:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	Knapsack(W,n);

	return 0;
}