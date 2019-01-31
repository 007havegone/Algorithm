class Solution {
public:
	int uniquePaths(int m, int n) {
		int mp[103][103];
		for (int i = 1; i <= n; i++)
			mp[1][i] = 1;
		for (int i = 1; i <= m; i++)
			mp[i][1] = 1;
		for(int i=2;i<=m;i++)
			for (int j = 2; j <= n; j++) {
				mp[i][j] = mp[i - 1][j] + mp[i][j - 1];
			}

		return mp[m][n];
	}
};