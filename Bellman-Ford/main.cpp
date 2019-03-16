#include <iostream>
#include <queue>
#include <cstring>
#include <utility>
using namespace std;

/*
	Bellman-Ford�㷨�ǳ��򵥣����Ĵ���ֻ��4�У����ҿ��������Ľ�����и�Ȩ�ߵ�ͼ
*/
const int N = 10000;
const int INF = 0x3f3f3f3f;
int n, m;
int u[N];//�����
int v[N];//���յ�
int w[N];//��Ȩֵ
int dis[N];//dis[i]��ʾԴ�㵽i�ľ���

/*
	��һЩ���ɳں󣬵õ����Ž���ٱ仯������Bellman�㷨�ظ��жϡ�
	SPFA�㷨ÿ�ν������·������ֵ�����仯�˵Ķ�������г���ִ���ɳڲ������Ӷ������Ż�

*/
void Bellman_Ford(int s)
{
	for (int i = 1; i <= n; i++)//��ʼ��
		dis[i] = INF;
	dis[s] = 0;//������Ϊ0
	for (int k = 1; k <= n - 1; k++)//���|N-1|��,ÿһ��������һ������Ϊ���Ž�
	{
		int flag = 0;
		for (int i = 1; i <= m; i++)//�ɳڲ���
		{
			if (dis[u[i]] + w[i] < dis[v[i]]) {
				dis[v[i]] = dis[u[i]] + w[i];
				flag = 1;
			}
		}
		if (!flag)//û�и��£���ǰ����
			break;
	}
	bool flag = 0;
	for (int i = 1; i <= m; i++)
		if (dis[u[i]] + w[i] < dis[v[i]]) {
			flag = 1;
			break;
		}
	if (flag)cout << "���ڸ�Ȩ��·\n";
}
void print(int n) {
	for (int i = 1; i <= n; i++)
		if (dis[i] == INF)
			cout << "INF" << " ";
		else
			cout << dis[i] << " ";
	cout << endl;
}

void init(int n) {
	for (int i = 1; i <= n; i++) {
		u[i] = 0;
		v[i] = 0;
		w[i] = INF;
	}
}
int main()
{
	int src;
	cout << "���������n�ͱߵĸ���m:\n";
	cin >> n >> m;
	init(m);
	cout << "��������u��v�������dis(u,v):\n";
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i];
	}
	cout << "�������:";
	cin >> src;
	Bellman_Ford(src);
	print(n);
	return 0;
}