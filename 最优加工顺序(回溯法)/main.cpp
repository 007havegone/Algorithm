#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3fffffff;
const int MX = 10005;
int n, bestf, f1, f2;//f1为当前第一台机器加工的完成时间，f2为当前第二台机器加工完成的时间
int x[MX], bestX[MX];//x[i]表示第i次加工第x[i]个零件，bestX[i]记录最优解
struct Time
{
	int x;//第一台机器加工时间

	int y;//第二台机器加工时间
}T[MX];

/*
	时间复杂度约为O((n+1)!)
	空间复杂度约为O(n)
*/
void Backtrack(int t) {
	if (t > n) {
		for (int i = 1; i <= n; i++)
			bestX[i] = x[i];
		bestf = f2;
		return;
	}
	for (int i = t; i <= n; i++) {//按排列数遍历
		f1 += T[x[i]].x;
		int temp = f2;
		f2 = max(f1, f2) + T[x[i]].y;
		if (f2 < bestf) {
			swap(x[t], x[i]);
			Backtrack(t + 1);
			swap(x[t], x[i]);
		}
		f1 -= T[x[i]].x;
		f2 = temp;
	}
}

int main() {
	cout << "输入机器零件的个数n:";
	cin >> n;
	cout << "依次输入每个零件在第一台机器和第二台机器加工的时间:" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> T[i].x >> T[i].y;
		x[i] = i;
	}
	bestf = INF;
	f1 = f2 = 0;
	memset(bestX, 0, sizeof(bestX));
	Backtrack(1);
	cout << "最快加工顺序为:";
	for (int i = 1; i <= n; i++)
		cout << bestX[i] << " ";
	cout << endl;
	cout << "最短时间为:" << bestf;
}