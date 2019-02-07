#include <iostream>
using namespace std;
const int N = 1007;
bool x[N];//记录x[i]是否加入团
bool bestX[N];//记录最优解
int bestn;//记录最优值
int cn;//当前团的个数
int n, m;//n为结点数，m为边数
int a[N][N];//邻接矩阵表示图

/*
	左右结点各有2^n个，故时间复杂度为O(n*2^n+1*2^1)=O(n*2^n)
	空间复杂度为bestX辅助数组和回溯过程的路径，故为O(n)
*/
bool Place(int t) {//约束函数O(n)
	bool ok = true;
	for (int i = 1; i < t; i++) {
		if (x[i] && a[i][t] == 0) {//与之前加入团的结点没边，置0并提前结束
			ok = false;
			break;
		}
	}
	return ok;
}
void Backtrack(int t) {
	if (t > n) {//到达叶子
		for (int i = 1; i <= n; i++) {
			bestX[i] = x[i];
		}
		bestn = cn;
		return;
	}
	if (Place(t)) {//满足约束条件进入左子树
		cn++;
		x[t] = 1;
		Backtrack(t + 1);
		cn--;
	}
	if (n - t + cn > bestn) {//满足限界条件，进入右子树 O(1）
		x[t] = 0;
		Backtrack(t + 1);
	}
}
int main() {
	int u, v;
	cout << "输入结点个数n:";
	cin >> n;
	cout << "输入图的边个数m:";
	cin >> m;
	memset(a, 0, sizeof(a));
	cout << "输入边的关系:";
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		a[v][u] = a[u][v] = 1;
	}
	bestn = 0;//初始化
	cn = 0;
	Backtrack(1);
	cout << "最大团的个数为:" << bestn << endl;
	cout << "选中的结点为:";
	for (int i = 1; i <= n; i++) {
		if (bestX[i])
			cout << i << " ";
	}
	cout << endl;
	return 0;
}
