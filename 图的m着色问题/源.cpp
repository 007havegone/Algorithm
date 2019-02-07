/*
	除了最后一层有 1+m+m^2+m^3+....+m^(n-1)=(m^n-1)/(m-1)=m^(n-1)个结点需要扩展
	而这些结点每个都有m个分支，总的分支数为m^n,每个分支都需要判断约束函数，约束函数时间复杂度为O(n),
	故最坏时间复杂度为O(n*m^n)
	搜索中的最长路径为n，同时使用x[]辅助数组，空间复杂度O(n）。
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1007;

int x[N];//点的着色情况
int mp[N][N];//图的邻接矩阵
int sum = 0;//解的个数
int n, m, edge;//结点数和颜色数



bool CheckByMatrix(int t) {//检测1到t-1的颜色是否相同
	for (int i = 1; i < t; i++) {//可以采用邻接表来优化。
		if (mp[i][t] && x[i] == x[t])
			return false;
	}
	return true;
}
//采用邻接表结构优化
vector<int> vecs[N];//vecs[i]保存i结点的邻接点
bool CheckByAdjaList(int t) {
	for(int i=0;i<vecs[t].size();i++){
		int nebor = vecs[t][i];//邻接点
		if (nebor < t&&x[nebor] == x[t])//属于前t-1个邻接点同时颜色相同
			return false;
	}
	return true;
}
void Backtrack(int t) {
	if (t > n) {
		sum++;
		cout << "第" <<  sum << "种方案";
		for (int i = 1; i <= n; i++) {
			cout << x[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= m; i++) {
		x[t] = i;
		if (CheckByMatrix(t)) {
			Backtrack(t + 1);
		}
		/*if (CheckByAdjaList(t)) {
			Backtrack(t + 1);
		}*/
	}
}
void CreatAdjacencyMatrix(int edge) {
	int u, v;
	memset(mp, 0, sizeof(mp));
	for (int i = 0; i < edge; i++) {
		cin >> u >> v;
		mp[u][v] = mp[v][u] = 1;
	}
}
void CreatAdjacencyList(int edge) {
	int u, v;
	for (int i = 1; i <= n; i++) {//初始化
		vecs[i].clear();
	}
	for (int i = 0; i < edge; i++) {
		cin >> u >> v;
		vecs[u].push_back(v);
		vecs[v].push_back(u);
	}
}
int main() {
	cout << "输入结点个数:";
	cin >> n;
	cout << "输入颜色个数:";
	cin >> m;
	cout << "输入边数:";
	cin >> edge;
	cout << "输入图的边的结点u和v";
	memset(x, 0, sizeof(x));
	CreatAdjacencyMatrix(edge);
	//CreatAdjacencyList(edge);
	Backtrack(1);
}