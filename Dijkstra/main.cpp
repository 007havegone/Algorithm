#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
//�±��1��ʼ 
const int INF = 10e7;//�����
int n, m, mp[107][107];//���У���·����ͼ 
bool flag[107];//�Ƿ����
int Dis[107];
struct Node {
	int u;//����
	int step;//����
	Node(int m_u, int m_step) :u(m_u), step(m_step) {
	}
	//ע��Ҫconst����Ϊ�ǳ�Ա���� 
	bool operator<(const Node& n)const//��Сֵ���� 
	{
		return step > n.step;
	}
};

void disjktra(int sta)
{
	priority_queue<Node> que;
	que.push(Node(sta, 0));
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= n; i++)
		Dis[i] = INF;
	Dis[sta] = 0;
	while (!que.empty()) {
		Node top = que.top();
		que.pop();
		int t = top.u;
		if (flag[t])
			continue;
		flag[t] = 1;
		for (int i = 1; i <= n; i++)
		{
			if (!flag[i] && mp[t][i] < INF)
			{
				if (Dis[i] > Dis[t] + mp[t][i])
					Dis[i] = Dis[t] + mp[t][i];
				que.push(Node(i, Dis[i]));
			}
		}
	}
}
int main()
{
	cout << "�����������·����" << endl;
	int sta;
	int ci, cj, dis;
	while (cin >> n >> m)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mp[i][j] = INF;//��ʼ��mp

		cout << "����·��" << endl;
		while (m--)
		{
			cin >> ci >> cj >> dis;
			mp[ci][cj] = min(mp[ci][cj], dis);
		}
		cout << "���������" << endl;
		cin >> sta;
		disjktra(sta);
		cout << "��ǰλ��Ϊ " << sta << endl;
		for (int i = 1; i <= n; i++)
			cout << "��λ�� " << i << "�ľ���Ϊ " << Dis[i] << endl;
	}
}