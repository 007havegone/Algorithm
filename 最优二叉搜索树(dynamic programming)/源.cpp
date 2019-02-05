/*
	对于给定的有序序列S={s1,s2,s3...sn}，关键字结点成为实结点。对于每个关键字查找概率为pi，查找失败结点
	称为虚结点，对应{e0,e1,e2.....en}，每个虚结点的查找概率为qi。e0表示小于s1的值，en表示大于sn的值。
	所有结点查找概率之和为1.求最小平均比较次数的二叉搜索树（最优二叉搜索树）

	二叉搜索树满足：左结点<根<右结点，因此每次选出不能保证概率大的结点。所以哈夫曼思想无法构建最优二叉搜索树。

	采用暴力穷所所有情况，一共有 O（4n^2/ n^1.5)棵不同的二叉搜索树（指数级别）。

	该问题满足最优解的结构特征。

	假设sk为二叉搜索树T(1,n)的根，那么原问题变为两个子问题，左子树T(1,k-1)和右子树T(k+1,n)
*/

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 107;//实结点的最大数目
double p[N];//p[i]为第i个实结点的概率，从1开始
double q[N];//q[j]为第j个虚结点的概率，从0开始
double c[N][N];//c[i][j]表示集合A={ai,ai+1,....,aj}的实结点和B={ei-1,ei,....,ej}的虚结点的最小次数
double w[N][N];//w[i][j]表示 q[i-1]、p[i]、q[i]、....p[j]、q[j]的概率和
int s[N][N];//s[i][j]表示 集合A={ai,ai+1,....,aj}的实结点和B={ei-1,ei,....,ej}的虚结点的最优解，即根节点
int n;
/*
	由上面的分析和定义可知
				0													i-1=j 只有一个左虚结点
	c[i][j]=	min{ c[i][k-1]+c[k+1][j] }+w[i][j] 其中 i<=k<=j		j>=i

			 q[i-1]															i-1=j 只有一个左虚结点
	w[i][j]= q[i-1] + p[i] + q[i] + p[i+1] +q[i+1] + ....+ p[j] + q[j]		j>=i

*/
void optimal_BST(int n) {
	int i, j, d, k;
	double temp;
	//初始化c[][]和w[][]
	for ( i = 1; i <= n + 1; i++)
		c[i][i - 1] = 0.0;
	for ( i = 1; i <= n + 1; i++)
		w[i][i - 1] = q[i - 1];

	for ( d = 1; d <= n; d++) {//规模从1到n
		for ( i = 1; i <= n - d + 1; i++) {
			j = i + d - 1;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			c[i][j] = c[i][i - 1] + c[i + 1][j];
			s[i][j] = i;
			for (k = i + 1; k <= j; k++) {
				temp = c[i][k - 1] + c[k + 1][j];
				if (temp < c[i][j]) {
					c[i][j] = temp;
					s[i][j] = k;
				}
			}
			c[i][j] += w[i][j];
		}
	}
}
//深度遍历
void Construct_Optimal_BST(int i, int j, bool flag) {
	if (flag == 0)
	{
		cout << "S" << s[i][j] << " is root" << endl;
	}
	int k = s[i][j];
	//左子树为叶子
	if (k - 1 < i) {
		cout << "e" << k - 1 << " is the left child of " << "S" << k << endl;
	}//不是叶子
	else {
		cout << "S" << s[i][k - 1] << " is the left child of " << "S" << k << endl;
		Construct_Optimal_BST(i, k - 1, true);
	}
	//右子树为叶子
	if (k >= j) {
		cout << "e" << k << " is the right child of " << "S" << k << endl;
	}//不是叶子
	else {
		cout << "S" << s[k + 1][j] << " is the right child of " << "S" << k << endl;
		Construct_Optimal_BST(k + 1, j, true);
	}
}
//广度遍历(层序遍历)
void Construct_Optimal_BST(int i, int j) {
	queue<pair<int, int>> que;
	int flag = 0;
	que.push(make_pair(i, j));
	while (!que.empty()) {
		auto t = que.front();
		que.pop();
		int k = s[t.first][t.second];
		if (k - 1 < t.first)
			cout << "e" << k - 1 << " is the left child of " << "S" << k << endl;
		else {
			cout << "S" << s[t.first][k - 1] << " is the left child of " << "S" << k << endl;
			que.push(make_pair(t.first, k - 1));
		}
		if (k >= t.second)
			cout << "e" << k << " is the right child of " << "S" << k << endl;
		else {
			cout << "S" << s[k + 1][t.second] << " is the right child of " << "S" << k << endl;
			que.push(make_pair(k + 1, t.second));
		}
	}
}
int main() {
	cout << "输入实结点的个数:";
	cin >> n;
	cout << "输入n个实结点的概率:";
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	cout << "输入n+1个虚结点的概率:";
	for (int i = 0; i <= n; i++)
		cin >> q[i];
	optimal_BST(n);
	cout << c[1][n] << endl;

	Construct_Optimal_BST(1, n, false);
	//Construct_Optimal_BST(1, n);
	return 0;
}