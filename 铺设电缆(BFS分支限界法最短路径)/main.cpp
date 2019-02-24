/*
	��֧�޽編������4����(��������4������)�������ռ����ʱ�临�Ӷ�Ϊ4^n
	���ǿռ����������δ֪�ġ�
	ʵ���ϣ�ÿ��������������һ�Σ������ظ����룬��˶���m*n�ķ�����˵��
	��ദ��O(m*n)����㣬����ÿ�����ʱ��ΪO(1)��ʱ�临�Ӷ�Ϊ(m*n)
	��������·����ҪO(L)������LΪ·���ĳ���

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
}Position;//λ��
int grid[N][N];//��ͼ

//���s���յ�e��·��path������PathLen
bool BFS(Position s,Position e,Position *&path,int &PathLen) {
	if (s.x == s.x&&s.y == e.y)//����յ�һ��
	{
		PathLen = 0;
		return true;
	}
	Position DIR[4] = { {0,1},{0,-1},{-1,0},{1,0} };//�������ҷ���
	Position here, next;
	here = s;
	grid[s.x][s.y] = 0;//�����Ϊ0
	queue<Position> Q;
	Q.push(here);
	for (;;) 
	{
		for (int i = 0; i < 4; i++) {
			next.x = here.x + DIR[i].x;
			next.y = here.y + DIR[i].y;
			if (grid[next.x][next.y] == -1) {//��δ����
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
	PathLen = grid[e.x][e.y];//��ȡ����
	path = new Position[PathLen];
	here = e;//��ʼ����Ϊԭ���յ�
	//��������·��
	for (int i = PathLen - 1; i >= 0; i--) {
		path[i] = here;
		for (int j = 0; j < 4; j++) {
			next.x = here.x + DIR[j].x;
			next.y = here.y + DIR[j].y;
			if (grid[next.x][next.y] == i)break;//�ҵ���һ��λ��
		}
		here = next;//����
	}
	return true;
}
void init(int m, int n) {//��ʼ����ͼ,��Ǵ���0��ʾ�Ѳ��ߣ�δ����-1��ǽ��-2
	for (int i = 1; i <= m; i++)//�������г�ʼ��Ϊ-1
		for (int j = 1; j <= n; j++)
			grid[i][j] = -1;;
	for (int i = 0; i <= n + 1; i++)//������������Χǽ
		grid[0][i] = grid[m + 1][i] = -2;
	for (int i = 0; i < m + 1; i++)//������������Χǽ
		grid[i][0] = grid[i][n + 1] = -2;

}
int main() {
	Position a, b, *way;//a��㣬b�յ�
	int Len, m, n;//����·�����ȣ�m*n�ķ�������
	cout << "���뷽��Ĵ�СM��N" << endl;
	cin >> m >> n;
	init(m, n);
	while (!(m == 0 && n == 0)) {
		cout << "�����ϰ��������x,y(����0 0����)" << endl;
		cin >> m >> n;
		grid[m][n] = -2;
	}
	cout << "�����������:" << endl;
	cin >> a.x >> a.y;
	cout << "�����յ�����:" << endl;
	cin >> b.x >> b.y;
	if (BFS(a, b, way, Len)) {
		cout << "���·������Ϊ:" << Len << endl;
		cout << "����·��������Ϊ:" << endl;
		for (int i = 0; i < Len; i++) {
			cout << "("<< way[i].x << "," << way[i].y << ")" << endl;
		}
	}
	else
		cout << "�޷�����" << endl;
	return 0;
}
