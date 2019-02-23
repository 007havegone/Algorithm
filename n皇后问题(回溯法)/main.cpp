/*
	n皇后问题的解空间为m叉树(m==n),树的深度为n，
	除了最后一层，一共共有1+n+n^2+...+n^（n-1）=（n^n-1)/(n-1）=n^(n-1)个结点
	每个结点拓展出n个分支
	每个分支都需要约束函数判断，约束函数时间复杂度为O(n)
	故时间复杂度为O(n^(n+1))
	空间复杂度为O(n)
*/
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1007;
int x[N];//记录x[i]为第i个棋子放在(i,x[i])
int cnt = 0;//记录方案数
int n;//棋子数

bool check(int t) {
	for (int i = 1; i < t; i++) {
		if(x[i]==x[t]||(abs(i-t)==abs(x[i]-x[t])))//同列或同一斜线
			return false;
	}
	return true;
}
void Backtrack(int t) {
	if (t > n) {
		cnt++;
		//叶子处输出O(n)
		cout << "方案:" << cnt;
		for (int i = 1; i <= n; i++) {
			cout << "(" << i <<  "," << x[i] << ")" << " ";
		}
		cout << "\n------------------------------------------\n";
	}
	for (int i = 1; i <= n; i++) {
		x[t] = i;
		if (check(t))
			Backtrack(t + 1);
	}
}
int main() {
	cout << "输入棋子的个数:";
	cin >> n;
	memset(x, 0, sizeof(x));
	Backtrack(1);
	if (!cnt)
		cout << "没有符合的方案" << endl;
	else
		cout << "共有" << cnt << "种方案" << endl;
}