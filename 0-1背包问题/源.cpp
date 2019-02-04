#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1005;
const int M = 105;
int c[M][maxn];//c[i][j]��ʾǰi����Ʒ��������Ϊj�ı��������ֵ
int w[M], v[M];//w[i]��ʾ��i����Ʒ������v[i]��ʾ1��i����Ʒ�ļ�ֵ
int x[M];//x[i]��ʾ��i����Ʒ�Ƿ����

void Init(int n,int W)
{
	//��0����Ϊ0
	for (int i = 0; i <= n; i++)
		c[i][0] = 0;
	//��0����Ϊ0
	for (int i = 0; i <= W; i++)
		c[0][i] = 0;
}
void DP(int n, int W)
{
	for (int i = 1; i <= n; i++)//����ÿ����Ʒ
	{
		for (int j = 1; j <= W; j++) {//����ÿ�ּ�ֵ
			if (j < w[i])
				c[i][j] = c[i - 1][j];
			else
				c[i][j] = max(c[i - 1][j], c[i - 1][j - w[i]] + v[i]);
		}
	}
}
void print(int n, int W)
{
	for (int i = n; i >= 1; i--) {
		if (c[i][W] > c[i - 1][W]) {
			x[i] = 1;
			W -= w[i];
		}
		else
			x[i] = 0;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (x[i]) {
			cout << i << " ";
			sum += v[i];
		}
	}
	cout << "\nSum = " << sum << endl;;
}
int main() {
	int i, j, n, W;//WΪ����������nΪ��Ʒ����
	cout << "������Ʒ�ĸ���n: ";
	cin >> n;

	cout << "���뱳������W:";
	cin >> W;
	cout << "��������ÿ����Ʒ������w�ͼ�ֵv���ո����:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	Init(n, W);
	DP(n, W);
	print(n, W);
}