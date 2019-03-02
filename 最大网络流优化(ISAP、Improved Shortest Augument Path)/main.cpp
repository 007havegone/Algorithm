#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N = 100;//�����
const int M = 10000;//����
const int INF = 0x3f3f3f3f;//�����
int top;//��¼�ߵ�λ��
int pre[N], h[N], g[N];
/*
	pre[]ǰ��������
	h[]�߶�����
	g[]���߶�����
*/
struct Vertex {
	int first;
}V[N];
struct Edge
{
	int v, next;//vΪu���ڽӵ㣬nextָ����һ���ڽӵ��
	int cap, flow;//capΪ�ߵ�������flowΪʵ����
}E[M];
void add_edge(int u, int v, int c) {//������
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].next = V[u].first;//���ӵ��ڽӱ�ͷ
	V[u].first = top++;
}
void add(int u, int v, int c) {
	add_edge(u, v, c);
	add_edge(v, u, 0);
}
void set_h(int t, int n) {//��ߺ���
	queue<int>q;
	memset(h, -1, sizeof(h));//���ø߶�Ϊ-1��Ϊδ���ʱ��
	memset(g, 0, sizeof(g));
	h[t] = 0;
	q.push(t);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		g[h[v]]++;
		int i = V[v].first;
		for (; ~i; i = E[i].next) {
			int u = E[i].v;
			if (h[u] == -1)//��δ����
			{
				h[u] = h[v] + 1;
				q.push(u);//���
			}
		}
	}
	cout << "��ʼ���߶�" << endl;
	cout << "h[]= ";
	for (int i = 1; i <= n; i++)
		cout << h[i] << " ";
	cout << endl;
}
/*
	VΪ���,EΪ��
	��֤ÿ���߳�Ϊ�ؼ��ߴ������Ϊ|V|/2,�ܹ���E���ߣ��ʹؼ�����O(VE)
	��������·��O(VE)
	����ISAP�õ�һ��������·ΪO(V),��ʱ�临�Ӷ�ΪO(V^2*E)
	�ռ临�Ӷ�ΪO(V)
*/
int ISAP(int s, int t, int n) {//Improved Shortest
	set_h(n, n);
	int ans = 0;
	int u = s;//��¼��ǰ������
	int d;//��¼��������
	while (g[h[u]] < n) {//��0��ʼn�������߶�Ϊn-1
		int i = V[u].first;//��ȡͷ���
		if (u == s)//��㣬d��Ϊ�����
			d = INF;
		//�����ڽӵ�
		for (; ~i; i = E[i].next) {
			int v = E[i].v;
			if (E[i].cap > E[i].flow&&h[u] == h[v] + 1) {//������cap>flowͬʱ�߶�����
				pre[v] = i;//����ǰ����
				u = v;
				d = min(d, E[i].cap - E[i].flow);
				if (u == t) {//�ҵ��˿�����·
					cout << "����·��:" << t;
					while (u != s) {
						int j = pre[u];
						E[j].flow += d;//�����+d
						E[j ^ 1].flow -= d;//�����-d
						u = E[j ^ 1].v;//����uδǰһ����
						cout << "--" << u;
					}
					cout << "����:" << d << endl;
					ans += d;
					d = INF;
				}
				break;//�ҵ���һ���ڵ����
			}
		}
		if (i == -1) {//�Ҳ��������ڱߣ��޷�ǰ��
			if (g[h[u]] == 1)//�ø߶ȵĽ��ֻ��һ������
				break;
			int hmin = n - 1;
			for (int j = V[u].first; ~j; j = E[j].next)
				if (E[j].cap > E[j].flow)
					hmin = min(hmin, h[E[j].v]);
			h[u] = hmin + 1;//���¸߶�
			g[h[u]]++;
			if (u != s)//������ʼ�㣬���˵���һ����
				u = E[pre[u] ^ 1].v;
			cout << "���±�ߺ�߶�:" << endl;
			cout << "h[]= ";
			for (int i = 1; i <= n; i++)
				cout << h[i] << " ";
			cout << endl;
		}
	}
	return ans;
}
void init(int n) {
	top = 0;
	memset(V, -1, sizeof(V));
}
void printg(int n) {
	cout << "---------�����ڽӱ�����:---------" << endl;
	for (int i = 1; i <= n; i++) {
		cout << "v" << i << "[" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			cout << "]--[" << E[j].v << " " << E[j].cap << " " <<
				E[j].flow << " " << E[j].next;
		}
		cout << "]\n";
	}
}
void printflow(int n) {
	cout << "---------ʵ��������:---------" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow > 0)
				cout << i << "--" << E[j].v << " " << E[j].flow<< endl;
		}
	}
}
int main() {
	int n, m;
	int u, v, c;
	cout << "������ĸ���n�ͱߵĸ���m:" << endl;
	cin >> n >> m;
	init(n);
	cout << "���������������u,v����(u--v)������w:" << endl;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> c;
		add(u, v, c);//��ӱ�
	}
	cout << endl;
	printg(n);
	cout << "����������ֵ:" << ISAP(1, n, n) << endl;
	printg(n);
	printflow(n);
}