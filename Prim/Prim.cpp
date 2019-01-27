/*
	ʱ�临�Ӷ�ΪO(n^2)

*/
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100;
const int INF = 0x3fffffff;
int lowcost[N];//��̾��� 
int close[N];//�ڽ��ı� 
bool flag[N];//�Ƿ����
int G[N][N];
void Prim(int u0, int n)//u0Ϊ��ʵ�㣬nΪ������� 
{
	//����lowcost��flag��close
	flag[u0] = true;
	for (int i = 1; i <= n; i++)
	{
		if (i != u0)
		{
			flag[i] = false;
			close[i] = u0;
			lowcost[i] = G[u0][i];
		}
		else
			lowcost[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		int t = u0;
		int dis = INF;
		//Ѱ����̾���ĵ�t
		for (int j = 1; j <= n; j++) {
			if (!flag[j] && lowcost[j] < dis)
			{
				dis = lowcost[j];
				t = j;
			}
		}
		if (t == u0)
			break;//δ�ҵ�
		//�ҵ����� 
		flag[t] = true;
		for (int j = 1; j <= n; j++)
		{
			if (!flag[j] && G[t][j] < lowcost[j]) {
				lowcost[j] = G[t][j];
				close[j] = t;
			}
		}
	}
}
int main()
{
	int n, m;
	int a, b, v;
	int sta;
	int sum = 0;
	cout << "�����ĸ����ͱߵĸ���" << endl;
	cin >> n >> m;
	//��ʼ��ͼ 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			G[i][j] = INF;
	cout << "����ߺͳ���" << endl;
	while (m--)
	{
		cin >> a >> b >> v;
		G[a][b] = G[b][a] = min(G[a][b], v);
	}
	cout << "�������" << endl;
	cin >> sta;
	Prim(sta, n);
	for (int i = 1; i <= n; i++) {
		sum += lowcost[i];
		cout << lowcost[i] << " ";
	}
	cout << "\n��С������ȨֵΪ:" << sum << endl;
}
