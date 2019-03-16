#include<iostream>
/*
	http://poj.org/problem?id=3259

	����������FJ��F��ũ����ÿ��ũׯ����N��أ���M��˫��ߣ�(S,E,T)��ʾS��E֮����һ��˫��ߣ���ҪTʱ��������ꡣ

	����W���涴:(S,E,T)��ʾ��S��E��һ������ߣ���S��E��ʹ��ʱ�䵹��Tʱ�䡣����ÿ��ũ����FJ�ܲ��ܻص��ȿ�ʼ�����ʱ�䣬����������YES���������NO��

	����˼·��ʵ���������Ƿ���ڸ�����

*/
using namespace std;
const int N = 505;
const int INF = 10000000;
int dp[N][N];

//floyd�㷨�ж��Ƿ���ڸ��� 
bool floyd(int n)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				if (dp[i][j] > dp[i][k] + dp[k][j])
					dp[i][j] = dp[i][k] + dp[k][j];
			if (dp[i][i] < 0)//���ָ���
				return true;
		}
	return false;
}

int main()
{
	int F, N, M, W, a, b, t;
	scanf("%d", &F);
	while (F--) {
		scanf("%d%d%d", &N, &M, &W);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				dp[i][j] = (i == j) ? 0 : INF;
		while (M--) {
			//˫��� 
			scanf("%d%d%d", &a, &b, &t);
			if (t < dp[a][b])
				dp[a][b] = dp[b][a] = t;
		}
		while (W--) {
			//�����
			scanf("%d%d%d", &a, &b, &t);
			dp[a][b] = -t;//���ű�ʾʹʱ�䵹��-t 
		}
		if (floyd(N))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
