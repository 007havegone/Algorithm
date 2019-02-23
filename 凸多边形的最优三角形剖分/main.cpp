#include <iostream>
using namespace std;
const int N = 1007;
int g[N][N];//g[i][j]表示ai-1 到aj-1的距离，下标从0开始
int m[N][N];//m[i][j] 为{ai-1,ai,ai+1....aj},当i=j，表示一条弦，为0,从1开始存储
int s[N][N];//存储最优策略，从1开始存储

void Init(int n)
{
	//s[i][i]->{ai-1,ai}
	for (int i = 1; i <= n; i++)//两个点初始化a0-a1 a1-a2为0
		s[i][i] = m[i][i] = 0;
}
void Convexpolygontriangulation(int n) {
	Init(n);
	int d, k, j, i;
	for (d = 2; d <= n;d++) {//问题规模为2,即三个点
		for (i = 1; i <= n - d + 1; i++) {
			j = i + d - 1;
			//i-1 i i+1 ... i+k.. j
			//子问题1：i-1...k		子问题2：k...j	加上：i-1 ->k  k -> j	i-1 -> j
			m[i][j] = m[i + 1][j] + g[i - 1][i] + g[i - 1][j] + g[i][j];//当k=i
			s[i][j] = i;
			for (k = i + 1; k < j; k++) {
				int temp = m[i][k] + m[k + 1][j] + g[i - 1][k] + g[i - 1][j] + g[k][j];
				if (temp < m[i][j]) {
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
}
void print(int i, int j)
{
	if (i == j)//为1条线ai-1 ai结束
		return;
	int k = s[i][j];//保存分界点
	if (k > i)//即至少3个点
		cout << "{ V" << i - 1 << "  V" << k << " }" << endl;
	if (j > k + 1)//即至少3个点
		cout << "{ V" << k << "  V" << j << " }" << endl;
	print(i, k);
	print(k + 1, j);

}
int main()
{
	int n;
	cout << "输入顶点个数:";
	cin >> n;
	n--;
	cout << "依次输入边的关系按 a0-a1 a0-a2 ... an-2-an-1 : " << endl;
	for(int i=0;i<=n;i++)
		for (int j = 0; j <=n; j++)
		{
			cin >> g[i][j];
		}
	Convexpolygontriangulation(n);
	cout << m[1][n] << endl;
	//验证
	/*for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << s[i][j] << " ";
		cout << endl;
	}*/
	print(1, n);//a0-an的点

	return 0;
}