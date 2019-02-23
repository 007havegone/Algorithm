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
	//ʱ�临�Ӷ�O(n^2),�ռ临�Ӷ�O(1),��ԭ�����в���
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		//��ʼ���߲�ͨ������0
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
		//Ҫ��1��ʼ����Ϊ֮ǰ�Ѿ�����һ���е�[0][0]��Ϊ��1�������Ѿ���ʼ�Ѿ��ų���[0][0]Ϊ1�����
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