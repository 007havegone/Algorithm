#include<iostream>
/*
	http://poj.org/problem?id=3259

	问题描述：FJ有F个农场，每个农庄里有N块地，有M条双向边：(S,E,T)表示S和E之间有一条双向边，需要T时间才能走完。

	还有W个虫洞:(S,E,T)表示从S到E有一条单向边，从S到E会使得时间倒退T时间。问在每个农场里FJ能不能回到比开始还早的时间，如果可以输出YES，否则输出NO。

	解题思路：实际上是求是否存在负环。

*/
using namespace std;
const int N = 505;
const int INF = 10000000;
int dp[N][N];

//floyd算法判断是否存在负环 
bool floyd(int n)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				if (dp[i][j] > dp[i][k] + dp[k][j])
					dp[i][j] = dp[i][k] + dp[k][j];
			if (dp[i][i] < 0)//出现负环
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
			//双向边 
			scanf("%d%d%d", &a, &b, &t);
			if (t < dp[a][b])
				dp[a][b] = dp[b][a] = t;
		}
		while (W--) {
			//单向边
			scanf("%d%d%d", &a, &b, &t);
			dp[a][b] = -t;//负号表示使时间倒退-t 
		}
		if (floyd(N))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
