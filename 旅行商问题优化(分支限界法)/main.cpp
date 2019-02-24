#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const int N = 100;
const int INF = 0x3f3f3f3f;
double g[N][N];//��ͼ���ڽӾ���
double minout[N];//ÿ��������С����
double minsum;//���н�����С����֮��
int bestx[N];//���Ž�����
double bestl;//����·������
int n, m;
struct Node
{
	double zl;//��ǰȫ��·�̵ĳ����½�
	double cl;//��ǰ����·�̳���
	double rl;//ʣ��·�̵ĳ����½�
	int id;//�ռ����������
	int x[N];
	Node(){}
	Node(double _cl, double _rl, double _zl, int _id) {
		cl = _cl;
		rl = _rl;
		zl = _zl;
		id = _id;
	}
	//ȫ��·�̵ĳ��ȵ��½�ǵݼ�����
	bool operator<(const Node& b)const {
		return zl > b.zl;
	}
};
bool Bound() {
	for (int i = 1; i <= n; i++) {//��������ͼ
		double mmin = INF;
		for (int j = 1; j <= n; j++) 
			if (g[i][j] != INF && g[i][j] < mmin) //�ҳ�ÿ��������̳���
				mmin = g[i][j];
		if (mmin == INF)//û�г��ߣ��������γɻ�·��ֱ�ӽ���
			return false;
		minout[i] = mmin;
		minsum += mmin;
	}
	cout << "���н������ٳ���֮��:""minsum= " << minsum << endl;
	return true;
}
void priorbfs() {
	int t;//��ʱ������id
	priority_queue<Node>q;
	Node newnode, livenode;
	newnode = Node(0, minsum, minsum, 2);//�ӵ�2�㿪ʼ
	for (int i = 1; i <= n; i++)
		newnode.x[i] = i;
	q.push(newnode);
	while (!q.empty()) {
		livenode = q.top();
		q.pop();
		t = livenode.id;
		if (t == n) {//���ﵹ����2�㣬��t=nʱ
			//��ǰ�ڵ���ǰһ������1�Ƿ��б�
			if (g[livenode.x[n-1]][livenode.x[n]] != INF && g[livenode.x[n]][1] != INF) {
				double tsum = livenode.cl + g[livenode.x[n - 1]][livenode.x[n]] + g[livenode.x[n]][1];
				if (tsum < bestl)//�������Ž�
				{
					bestl = tsum;
					//cout << "��ǰ���ŵĽ�����:";
					for (int i = 1; i <= n; i++) {//���½�����
						bestx[i] = livenode.x[i];
						//cout << bestx[i];
					}
					//cout << endl;

				}
			}
			continue;
		}
		//�ж��Ƿ������޽�����
		if (livenode.zl >= bestl)
			continue;

		//��δ����Ҷ�ӣ���չ��֧
		for (int i = t; i <= n;i++) {
			if (g[livenode.x[t - 1]][livenode.x[i]] != INF) {//�Ƿ���ǰһ�����������
				double cl = livenode.cl + g[livenode.x[t-1]][livenode.x[i]];
				double rl = livenode.rl - minout[livenode.x[i]];
				double zl = cl + rl;
				if (zl < bestl) {//�Ƿ������޽�����
					newnode = Node(cl, rl, zl, t + 1);
					for (int k = 1; k <= n; k++)
						newnode.x[k] = livenode.x[k];
					swap(newnode.x[i], newnode.x[t]);
					q.push(newnode);
				}
			}
		}

	}
}
void init() {
	bestl = INF;
	minsum = 0;
	memset(bestx, 0, sizeof(bestx));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = INF;

}
void print() {
	cout << "���Ź��ܶٻ�·Ϊ:";
	for (int i = 1; i <= n; i++)
		cout << bestx[i] << "-->";
	cout << "1\n";
	cout << "���Ž��·������:";
	cout << bestl << endl;
}
int main() {
	int u, v;
	double w;
	cout << "���������:";
	cin >> n;
	init();
	cout << "����·�߸���:";
	cin >> m;
	cout << "��������u��v��2����ľ���:";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g[u][v] = g[v][u] = w;
	}
	if (!Bound()) {
		cout << "�����ڹ��ܶٻ�·" << endl;
		return 0;
	}
	priorbfs();
	print();
	return 0;
}