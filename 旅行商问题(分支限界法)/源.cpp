#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 100;//������
const int INF = 0x3f3f3f3f;//�����
int n, m;//��������·�߸���
int g[N][N];
int bestx[N];//���Ž�����
int bestl;//����ֵ
struct Node
{
	Node(){}
	Node(int _cl,int _id) {
		id = _id;
		cl = _cl;
	}
	int id;//������
	int cl;//��ǰ·��
	int x[N];//������
};
//������·�̷ǵݼ�����
bool operator<(const Node&a, const Node& b) {
	return a.cl > b.cl;
}
void priorbfs() {
	int t;
	priority_queue<Node> q;
	Node livenode, newnode;//livenodeΪ����㣬newnodeΪ�������
	newnode = Node(0, 2);
	for (int i = 1; i <= n; i++)
		newnode.x[i] = i;
	q.push(newnode);
	while (!q.empty()) {
		livenode = q.top();
		q.pop();
		t = livenode.id;
		if (t == n) {//��������һ��
			//�ж��Ƿ���ǰһ����·��ͬʱ�͵�һ�������·��
			if (g[livenode.x[t - 1]][livenode.x[t]] != INF && g[livenode.x[1]][livenode.x[t]] != INF)
				if (livenode.cl + g[livenode.x[t - 1]][livenode.x[t]] + g[livenode.x[1]][livenode.x[t]] < bestl) {
					//�������Ž�
					bestl = livenode.cl + g[livenode.x[t - 1]][livenode.x[t]] + g[livenode.x[1]][livenode.x[t]];
					for (int i = 1; i <= n; i++) {
						bestx[i] = livenode.x[i];
						//cout << bestx[i];//�м����
					}
					//cout << endl;
				}
			continue;
		}
		//�ж��Ƿ������޽�����������ֱ�ӽ���
		if (livenode.cl >= bestl)
			continue;
		for (int i = t; i <= n; i++) {//�����Ӽ���
			
			if (g[livenode.x[t-1]][livenode.x[i]] != INF ) {//x[t-1]��x[t]����·��
				double cl = livenode.cl + g[livenode.x[t - 1]][livenode.x[i]];
				newnode = Node(cl, t + 1);
				for (int j = 1; j <= n; j++)//�������ڵ�Ľ�����
					newnode.x[j] = livenode.x[j];
				swap(newnode.x[i], newnode.x[t]);
				q.push(newnode);
			}
		}
	}
}
void init() {//��ʼ��
	memset(bestx, 0, sizeof(bestx));
	memset(g, INF, sizeof(g));
	bestl = INF;
}
void print() {
	cout << "\n���ܶٻ�·����Ϊ:" << bestl << endl;
	cout << "���ŵ�·��Ϊ:";
	for (int i = 1; i <= n; i++) {
		cout << bestx[i] << "-->";
	}
	cout << "1" << endl;;
}
int main() {
	int u, v, value;
	cout << "���������:";
	cin >> n;
	init();
	cout << "����·�߸���:";
	cin >> m;
	cout << "������u��v�;���value:" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> value;
		g[v][u] = g[u][v] = min(value, g[u][v]);//ȡ��Сֵ
	}
	priorbfs();
	print();
}
