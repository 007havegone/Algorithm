#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF = 0x3fffffff;//��������
const int N = 100;//�������
int mp[N][N];//ͼ���ڽӾ���
int x[N];//��¼��ǰѡ��
int bestX[N];//��¼���Ž�
int cl;//��ǰ����·������
int bestl;//��ѳ���
int n, m;//�����ͱ���
void Init(int n) {
	bestl = INF;
	cl = 0;
	memset(mp, 0x3f, sizeof(mp));
	for (int i = 1; i <= n; i++) {
		x[i] = i;
		bestX[i] = 0;
	}
}
void BackTrack(int t) {
	if (t > n) {
		if (mp[1][x[n]]!=INF&&cl+mp[1][x[n]]<bestl) {//���1�����һ������Ƿ�������
			for (int i = 1; i <= n; i++)
				bestX[i] = x[i];
			bestl = cl+mp[1][x[n]];
		}
		return;
	}
	for (int i = t; i <= n; i++) {
		if (mp[x[t-1]][x[i]] != INF && cl + mp[x[t - 1]][x[i]] < bestl) {//Լ������
			swap(x[t], x[i]);
			cl += mp[x[t-1]][x[t]];
			BackTrack(t + 1);
			cl -= mp[x[t-1]][x[t]];
			swap(x[t], x[i]);
		}
	}
}
void print(int n) {
	cout << "����·��Ϊ:";
	for (int i = 1; i <= n; i++) {
		cout << bestX[i] << "--";
	}
	cout << 1 << endl;
	cout << "���·��Ϊ:" << bestl << endl;
}
int main() {
	int u, v, w;
	cout << "��������n:";
	cin >> n;
	Init(n);
	cout << "�������ӵ�ı���m:";
	cin >> m;
	cout << "������u��v�������" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		mp[u][v] = mp[v][u] = w;
	}
	BackTrack(2);
	print(n);
	return 0;
}