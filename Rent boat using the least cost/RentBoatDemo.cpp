/*
	有n个站点，你需要从1号站点乘船到n号站点，
	你可以选择在任何站点停靠，不同站点间的停靠费用不同，满足rent[i][j] (i<j)
	即你只能在下游处停船，求1到n站点的最少花费

	第i到第j个站,(i,i+1,...,j)的最有解(最少租金)问题
	分析最优解的结构特征：
	假设我们已经知道第K歌站点停靠会得到最优解，那么原问题会变为两个子问题(i,i+1,...,k)、(k,k+1,...,j)

	假设第i个站点到第j个站点(i,i+1,...,j)的最优解是c,子问题(i,i+1,...,k)的最优解是a,子问题(k,k+1,...,j)的最优解是b,
	那么c=a+b,无论两个子问题的停靠策略如何都不影响他们的结果,因此只需要正c是最优解,则a和b一定是最优的.(即原问题的最优解包含子问题的最优解)
	反证法:如何a不是最优的,自问题一定存在一个最优解a',a'<a,那么a'+b<c,所以c不是最优的,这与c是最优假设矛盾,因此如果c是最优的,则a一定是最优的.
	同理可证b也是最优的.因此如果c是最优的,a和b一定是最优的

	m[i][j]表示i到j的最优解
	i=j m[i][j]=0
	j=i+1 m[i][j]=r[i][j]
	j>i+1 m[i][j]=min{m[i][k]+m[k][j],r[i][j]} (i<k<j)

	时间复杂度O(n^3)
	空间复杂度O(n^2),如果只求租金,可省略m[][]和s[][],空间复杂度将为O(1)
*/

#include <iostream>
using namespace std;
const int N = 1007;
/*r[i][j]为i直接到j的费用，m[i][j]为i到j的最少费用
  s[i][j]为i到j最少花费的通过的中介战
*/
int r[N][N], m[N][N], s[N][N];
int n;
void rent()
{
	int i, j, d, k;
	for (d = 3; d <= n; d++)//i为问题规模,初始化为2个站,故从3开始
	{
		for (i = 1; i <= n - d+1; i++)//开始结点i
		{
			j = i + d - 1;//访问i+1 i+2...j-1,j-1
			for (k = i + 1; k < j; k++)
			{
				int temp;;
				temp = m[i][k] + m[k][j];
				if (temp < m[i][j])//通过k点距离更短
				{
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
}
void print(int i, int j)
{
	if (s[i][j] == 0)
	{
		cout << "--" << j;
		return;
	}
	print(i, s[i][j]);
	print(s[i][j], j);
}
int main()
{
	int i, j;
	cout << "输入站点的个数:" << endl;
	cin >> n;
	cout << "依次输入各个站点的租金:" << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = i + 1; j <= n; j++)
		{
			cin >> r[i][j];
			m[i][j] = r[i][j];
		}
	}
	rent();
	cout << "花费最少的租金为" << m[1][n] << endl;
	cout << "最少租金经过的站点为:" << 1;
	print(1, n);
	return 0;
}