#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int M = 1 << 13;
#define INF 0x3f3f3f3f
int dp[M + 2][20];//dp[i][j] ��ʾ��i��״̬�������j�����е����·��
int g[15][15];			//��0��ʼ�洢
int path[M + 2][15];    //����·����path[i][j]������{a,b,c,d,...}��j�����Ž��
int n, m;              //n�����У�m��·
int bestl;            //���·������
int sx, S;
/*
	ʱ�临�Ӷ� O(2^n*n^2) �ռ临�Ӷ� O(2^n)
*/

void Init() {
	sx = 0;
	bestl = INF;
	memset(path, 0, sizeof(path));
	memset(g, INF, sizeof(g));
	memset(dp, INF, sizeof(dp));
}
void Traveling() {
	dp[1][0] = 0;//����1��������1�ľ���Ϊ0�����Ϊ1����������INF
	S = 1 << n;
	for (int i = 0; i < S; i++) {//��������״̬
		for (int j = 0; j < n; j++) {//Ѱ���н��
			if (!i&(1 << j))continue;
			for (int k = 0; k < n; k++) {//Ѱ���յ�
				if (i&(1 << k))continue;
				if (dp[i|(1 << k)][k] > dp[i][j] + g[j][k]) {
					dp[i|(1 << k)][k] = dp[i][j] + g[j][k];
					path[i|(1 << k)][k] = j;//�������Ž�Ϊj
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (bestl > dp[S - 1][i] + g[i][0]) {
			bestl = dp[S - 1][i] + g[i][0];
			sx = i;//��¼S���յ�
		}
	}
}
void print(int S, int val) {
	if (!S)return;//û�о�����
	for (int i = 0; i < n; i++) {
		if (dp[S][i] == val) {
			print(S ^ (1 << i), val - g[i][path[S][i]]);//�ݹ���ã�ȡ��S-i�����Ž�
			cout << i+1 << "--->";
			break;
		}
	}
}
int main()
{
	int u, v, w;//u,v������У�w����u��v����֮��·�ĳ���
	cout << "�����뾰���� n(�����):";
	cin >> n;
	cout << "�����뾰��֮���������(����):";
	cin >> m;
	Init();
	cout << "������������������u��v֮��ľ���w,��ʽ:����u ����v ����w";
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		g[u - 1][v - 1] = g[v - 1][u - 1] = w;
	}
	Traveling();
	cout << "���·��: ";
	print(S - 1, bestl - g[sx][0]);
	cout << 1 << endl;
	cout << "���·������:";
	cout << bestl << endl;
	return 0;
}
