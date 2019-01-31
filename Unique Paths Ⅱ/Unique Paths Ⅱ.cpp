#include <vector>
#include <iostream>
using namespace std;
/*
	Input:
	[
	  [0,0,0],
	  [0,1,0],
	  [0,0,0]
	]
	Output: 2
	Explanation:
	There is one obstacle in the middle of the 3x3 grid above.
	There are two ways to reach the bottom-right corner:
	1. Right -> Right -> Down -> Down
	2. Down -> Down -> Right -> Right
*/
class Solution {
public:
	//时间复杂度O(n^2),空间复杂度O(1),在原数组中操作
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		//起始点走不通，返回0
		if (obstacleGrid[0][0] == 1)
			return 0;
		bool flag = 0;
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		cout << m << " " << n << endl;
		for (int i = 0; i < m; i++)
		{
			if (obstacleGrid[i][0] || flag) {
				obstacleGrid[i][0] = 0;
				flag = 1;
			}
			else
				obstacleGrid[i][0] = 1;
		}
		
		flag = 0;
		//要从1开始，因为之前已经将第一列中的[0][0]置为了1，而且已经开始已经排除了[0][0]为1的情况
		for (int i = 1; i < n; i++) {
			if (obstacleGrid[0][i] || flag) {
				obstacleGrid[0][i] = 0;
				flag = 1;
			}
			else
				obstacleGrid[0][i] = 1;
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (obstacleGrid[i][j] == 1)
					obstacleGrid[i][j] = 0;
				else
					obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
			}
		}
		return obstacleGrid[m - 1][n - 1];
		
	}
};
int main()
{
	vector<vector<int>> vecs{ {0,0,0},{0,1,0},{0,0,0} };
	Solution s;
	s.uniquePathsWithObstacles(vecs);
}