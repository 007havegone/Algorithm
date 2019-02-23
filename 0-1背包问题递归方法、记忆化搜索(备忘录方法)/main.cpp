#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20;//最大物品数
const int maxn = 100;//最大背包容量
int w[N], v[N];
//1、纯递归，效率较低，有重复子问题
int solveKs(int w[],int v[],int index,int capacity) {
	if (index < 0 || capacity <= 0) {
		return 0;
	}
	//假设不放入
	int ret = solveKs(w, v, index - 1, capacity);
	if (capacity >= w[index]) {//假设容量充足
		ret = max(ret, v[index] + solveKs(w, v, index - 1, capacity - w[index]));
	}
	return ret;
}
int knapsack(int w[], int v[], int len, int C) {
	return solveKs(w, v, len - 1, C);
}
/*
	2、记忆化搜索(备忘录方法),动态规范的一种变形，自顶向下，而动态规划自底向上
	比较：
		若有大量的子问题无需求解时，用备忘录方法较省时。但当无需计算的子问题只有少部分或全部都要计算时，
		用递推方法（动态规划，打表）比备忘录方法要好(如矩阵连乘，最优二分搜索树)。
	*/

int remem[N][maxn+1];//remem[i][j]前i+1个商品容量为j的最大价值,商品编号从0开始
int solveKs2(int w[], int v[], int index, int capacity) {
	if (index < 0 || capacity <= 0)
		return 0;
	//该子问题已求解，直接放回表内的值
	if (remem[index][capacity]) {
		return remem[index][capacity];
	}
	int ret = solveKs2(w, v, index - 1, capacity);
	if (capacity >= w[index])
		ret = max(ret, solveKs2(w, v, index - 1, capacity - w[index]) + v[index]);
	return ret;
}
int knapsack2(int w[], int v[], int len, int C) {
	memset(remem, 0, sizeof(remem));
	return solveKs2(w, v, len - 1, C);
}
int main()
{
	int w[] = { 2,5,4,2,3 };
	int v[] = { 6,3,5,4,6 };
	size_t sz = sizeof(w) / sizeof(int);
	//cout << "最大价值为:" << knapsack(w, v, sz, 10);
	cout << "最大价值为:" << knapsack2(w, v, sz, 10);
	return 0;
}