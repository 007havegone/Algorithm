#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <queue>
using namespace std;
const int N = 105;//��󶥵���
const int INF = 0x3f3f3f3f;//�����
int g[N][N];//�������磨��ʼʱ��������Ϊ0��
int f[N][N];//ʵ�����磨��ʼʱ����Ϊ0����
bool vis[N];//��������
int pre[N];//ǰ������
int n, m;//�������ͱ߸���

void print() {//��ӡʵ������
	cout << "----------------ʵ����������:----------------" << endl;
	cout << "  ";
	for (int i = 1; i <= n; i++)
		cout << setw(7) << "v" << i;
	cout << endl;
	for (int i = 1; i <= n; i++) {
		cout << "v" << i;
		for (int j = 1; j <= n; j++)
			cout << setw(7) << f[i][j] << " ";
		cout << endl;
	}
}
bool bfs(int s,int t) {//�������Ѱ�ҿ�����·
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	queue<int> q;
	vis[s] = true;
	q.push(s);
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (int i = 1; i <= n; i++) {//Ѱ�ҿ�����·
			if (!vis[i] && g[now][i] > 0) {//�Ƿ�δ������������
				vis[i] = true;
				pre[i] = now;
				if (i == t)	return true;//�ҵ�������·
				q.push(i);
			}
		}
	}
	return false;//�Ҳ���������·
}
/*
	VΪ���,EΪ��
	��֤������·��O(VE),����bfs��ȡ������·��ΪO(E)
	��ʱ�临�Ӷ�Ϊ(V*E^2)
*/
//�������·�㷨 (Edmonds-Karp�㷨��Shortest Argumemt Path��SAP�㷨��
int EK(int s, int t) {
	int u, v, d, maxflow;
	maxflow = 0;
	while (bfs(s, t)) {//��������
		v = t;
		d = INF;
		while (v != s) {//��ȡ��С������d
			u = pre[v];
			if (d > g[u][v])
				d = g[u][v];
			v = u;
		}
		maxflow += d;
		v = t;
		while (v != s) {
			u = pre[v];
			g[u][v] -= d;//��������������߼���
			g[v][u] += d;//���������з��������
			if (f[v][u] > 0)//ʵ���������з���ߣ��������������������
				f[v][u] -= d;//һ�����Ա�֤f[v][u]>=d,k��f[v][u]�ķ����,d����k>=d
			else
				f[u][v] += d;
			v = u;
		}
	}
	return maxflow;

}

int main() {
	int u, v, w;
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	cout << "���������n�ͱ���m:\n";
	cin >> n >> m;
	cout << "���������������u��v��(u->v)������w:\n";
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		g[u][v] += w;
	}
	cout << "�����������ֵ" << EK(1, n) << endl;
	print();//���ʵ������
	return 0;
}