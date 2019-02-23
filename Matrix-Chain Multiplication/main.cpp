#include <iostream>
#include <cstring>
using namespace std;
const int N = 107;
int n;
int p[N];//矩阵的行列数
int m[N][N], s[N][N];
void maxtrixchain()
{
	int i, j, k, d;
	//初始化
	for (i = 0; i <= n; i++)
		m[i][i] = s[i][i] = 0;
	for (d = 2; d <= n; d++) {//d为问题规模
		for (i = 1; i <= n - d + 1; i++) {//
			j = i + d - 1;
			m[i][j] =m[i + 1][j] + p[i - 1] * p[i] * p[j];//初始决策为k=i
			s[i][j] = i;
			for (k = i + 1; k < j; k++) {
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[j] * p[k];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}

		}
	}
}
void print(int i, int j)
{
	if (i == j) {
		cout << "A[" << i << "]";
		return;
	}
	cout << "(";
	print(i, s[i][j]);
	print(s[i][j]+1, j);
	cout << ")";
		
}
int main()
{
	cout << "输入矩阵个数" << endl;
	cin >> n;
	int i, j;
	cout << "依次输入每个矩阵的行数和最后一个矩阵的列数:";
	for (int i = 0; i <= n; i++)
	{
		cin >> p[i];
	}
	maxtrixchain();
	print(1, n);
	cout << endl;
	cout << "最小计算量为:" << m[1][n] << endl;

}