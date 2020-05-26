#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 10005;
const int M = 105;
int dp[maxn];//dp[j]��ʾ��ǰ�ѷ�������Ϊj�Ĺ��ﳵ��õ�����ֵ
int w[M], v[M];//w[i]��ʾ��i����Ʒ��������v[i]��ʾ��i����Ʒ������
int x[M];//x[i]��ʾ��i����Ʒ�Ƿ���빺�ﳵ
int i, j, n, W;//n��ʾn����Ʒ��W��ʾ���ﳵ����

void opt1(int n, int W) {
	for (i = 1; i <= W; i++)
		dp[i] = 0;
	for ( i = 1; i <= n; i++) {//����ÿ����Ʒ
		for ( j = W; j >0 ; j--) {
			if (j >= w[i])//��������������Ʒ������ѡ�����򲻷���
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
		for (int j = 1; j <= W; j++) {
			cout << dp[j] << " ";
		}
		cout << endl;
	}
	
}
void opt2(int n, int W) {
	for (i = 1; i <= W; i++)
		dp[i] = 0;
	for ( i = 1; i <= n; i++){
		for (j = W; j >= w[i]; j--) {//����һ���жϣ�ͬʱ��С�˷�Χ
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
		for (int j = 1; j <= W; j++) {
			cout << dp[j] << " ";
		}
		cout << endl;
	}
}
void opt3(int n, int W) {//�����������㹻��ʱ��������
	for (i = 1; i <= W; i++)
		dp[i] = 0;
	int *sum = new int[n+1];//sum[i]��ʾ��1~i����Ʒ����֮��
	sum[0] = 0;
	for (i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + w[i];
	for (i = 1; i <= n; i++) {
		int bound = max(w[i], W - (sum[n] - sum[i - 1]));//sum[n]-sum[i-1]Ϊi��n��������ȡʣ��������w[i]�����ֵ
		for (j = W; j >= bound; j--)
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		for (int j = 1; j <= W; j++) {
			cout << dp[j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	cout << "������Ʒ�ĸ���n: ";
	cin >> n;

	cout << "���뱳������W:";
	cin >> W;
	cout << "��������ÿ����Ʒ������w�ͼ�ֵv���ո����:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	opt1(n, W);
	cout << endl;
	opt2(n, W);
	cout << endl;
	opt3(n, W);
	cout << endl;
	cout << dp[W] << endl;
}