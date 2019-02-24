/*
	分支限界法，按照4叉树(上下左右4个方向)分析，空间数最坏时间复杂度为4^n
	但是空间数的深度是未知的。
	实际上，每个结点最多进入队列一次，不会重复进入，因此对于m*n的方阵来说，
	最多处理O(m*n)个结点，生成每个结点时间为O(1)，时间复杂度为(m*n)
	构造最优路径需要O(L)，其中L为路径的长度

*/

#include <iostream>
#include <algorithm>	
#include <queue>
#include <iomanip>
using namespace std;
const int N = 100;
typedef struct 
{
	int x;
	int y;
}Position;//位置
int grid[N][N];//地图

//起点s，终点e，路径path，长度PathLen
bool BFS(Position s,Position e,Position *&path,int &PathLen) {
	if (s.x == s.x&&s.y == e.y)//起点终点一致
	{
		PathLen = 0;
		return true;
	}
	Position DIR[4] = { {0,1},{0,-1},{-1,0},{1,0} };//上下左右方向
	Position here, next;
	here = s;
	grid[s.x][s.y] = 0;//起点置为0
	queue<Position> Q;
	Q.push(here);
	for (;;) 
	{
		for (int i = 0; i < 4; i++) {
			next.x = here.x + DIR[i].x;
			next.y = here.y + DIR[i].y;
			if (grid[next.x][next.y] == -1) {//尚未访问
				grid[next.x][next.y] = grid[here.x][here.y] + 1;
				Q.push(next);
			}
			if (next.x == e.x&&next.y == e.y)break;
		}
		if (next.x == e.x&&next.y == e.y)break;
		if (Q.empty())return false;
		else
		{
			here = Q.front();
			Q.pop();
		}
	}
	PathLen = grid[e.x][e.y];//获取长度
	path = new Position[PathLen];
	here = e;//起始点置为原来终点
	//构造最优路径
	for (int i = PathLen - 1; i >= 0; i--) {
		path[i] = here;
		for (int j = 0; j < 4; j++) {
			next.x = here.x + DIR[j].x;
			next.y = here.y + DIR[j].y;
			if (grid[next.x][next.y] == i)break;//找到上一个位置
		}
		here = next;//更新
	}
	return true;
}
void init(int m, int n) {//初始化地图,标记大于0表示已布线，未布线-1，墙壁-2
	for (int i = 1; i <= m; i++)//方格阵列初始化为-1
		for (int j = 1; j <= n; j++)
			grid[i][j] = -1;;
	for (int i = 0; i <= n + 1; i++)//方格阵列上下围墙
		grid[0][i] = grid[m + 1][i] = -2;
	for (int i = 0; i < m + 1; i++)//方格阵列左右围墙
		grid[i][0] = grid[i][n + 1] = -2;

}
int main() {
	Position a, b, *way;//a起点，b终点
	int Len, m, n;//最优路径长度，m*n的方格阵列
	cout << "输入方针的大小M，N" << endl;
	cin >> m >> n;
	init(m, n);
	while (!(m == 0 && n == 0)) {
		cout << "输入障碍物的坐标x,y(输入0 0结束)" << endl;
		cin >> m >> n;
		grid[m][n] = -2;
	}
	cout << "输入起点坐标:" << endl;
	cin >> a.x >> a.y;
	cout << "输入终点坐标:" << endl;
	cin >> b.x >> b.y;
	if (BFS(a, b, way, Len)) {
		cout << "最短路径长度为:" << Len << endl;
		cout << "这条路径的坐标为:" << endl;
		for (int i = 0; i < Len; i++) {
			cout << "("<< way[i].x << "," << way[i].y << ")" << endl;
		}
	}
	else
		cout << "无法到达" << endl;
	return 0;
}
