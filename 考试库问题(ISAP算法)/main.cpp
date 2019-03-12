#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int INF = 0x3fffffff;
const int N = 100;
const int M = 10000;
int top;
int h[N], g[N], pre[N];
/*
	h[i]Ϊ��i�����ĸ߶�
	g[i]Ϊ�߶�Ϊi�Ľ�������
	pre[i]Ϊ��i������ǰ����
*/
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v, cap, flow, next;
}E[M];

void init() {
	memset(V, -1, sizeof(V));
	top = 0;
}
void addEdge(int u, int v, int c) {
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void add(int u, int v, int c) {
	addEdge(u, v, c);
	addEdge(v, u, 0);
}
void printG(int m) {
	cout << "�������͵���Ŀ�ֲ�����:" << endl;
	for (int i = 1; i <= m; i++) {
		cout << "����" << i << ":";
		for (int j = V[i].first; ~j; j = E[j].next)
			if(E[j].v!=0)
				cout << E[j].v-m << " ";
		cout << endl;
	}
}
void print(int m) {
	cout << "�����ȡ����:" << endl;
	for (int i = 1; i <= m; i++) {
		cout << "��" << i << "�����ͳ�ȡ�������:";
		for (int j = V[i].first; ~j; j = E[j].next)
			if (E[j].flow == 1)
				cout << E[j].v-m << " ";
		cout << endl;
	}
}
void seth(int t, int n) {
	memset(h, -1, sizeof(h));
	memset(g, 0, sizeof(g));
	int u, v;
	queue<int> Q;
	Q.push(t);
	h[t] = 0;
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		++g[h[u]];
		for (int i = V[u].first; ~i; i = E[i].next) {
			v = E[i].v;
			if (h[v] == -1)
			{
				h[v] = h[u] + 1;
				Q.push(v);
			}
		}
	}
	/*cout << "h[] =";
	for (int i = 0; i <= n; i++)
		cout << h[i] << " ";
	cout << endl;*/
}
int ISAP(int s, int t, int n) {
	seth(t, n - 1);//��ʼ���߶�
	int maxflow, u, v, i, j, d;
	maxflow = 0;
	u = s;//��ǰ�����ڵ�
	while (h[s] < n) {//��ʼ���߶�С�ڽ����
		if (u == s)
			d = INF;
		for (i = V[u].first; ~i; i = E[i].next) {//���������ڽӵ�
			v = E[i].v;//��ȡ�ڽӵ�
			if (h[u] == h[v] + 1 && E[i].cap > E[i].flow) {//����߶Ȳ�Ϊ1��ͬʱ�п�����·
				d = min(d, E[i].cap - E[i].flow);
				pre[v] = i;
				u = v;
				if (u == t)//�ҵ����
				{
					while (u != s) {
						j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
					}
					maxflow += d;
					d = INF;
				}
				break;//�ҵ��ڽӵ����
			}

		}
		if (i == -1) {//δ�ҵ��ڽӵ�
			if (--g[h[u]] == 0)//��ǰ�߶Ƚ��ֻ��һ��
				break;//û�п�����·��������
			int minh = n - 1;
			for (j = V[u].first; ~j; j = E[j].next) {//���������ڽӵ��ҳ���С�߶�
				v = E[j].v;
				if (E[j].cap > E[j].flow)
					minh = min(minh, h[v]);
			}
			h[u] = minh + 1;
			++g[h[u]];
			if (u != s)
				u = E[pre[u] ^ 1].v;
		}
	}
	return maxflow;
}
int main() {
	int m, n, total, cost, t, sum = 0;
	cout << "����������m��������n:\n";
	cin >> m >> n;
	total = m + n;
	init();
	for (int i = m + 1; i <= total; i++)//ÿ����ֻѡһ��
		add(i, total + 1, 1);
	cout << "��������ÿ������ѡ�������:\n";
	for (int i = 1; i <= m; i++) {//ÿ������ѡcost�Σ���Ϊ����
		cin >> cost;
		sum += cost;
		add(0, i, cost);
	}
	cout << "��������ÿ����������������(0)����:\n";
	for (int i = m + 1; i <= total; i++) {
		while (cin >> t && t != 0)
			add(t, i, 1);//������ͺ���Ŀ������
	}
	printG(m);
	if (sum == ISAP(0, total + 1, total + 2)) {
		cout << "��ȡ�ɹ�" << endl;
		print(m);
	}
	else
		cout << "��ȡʧ��" << endl;
	return 0;
}