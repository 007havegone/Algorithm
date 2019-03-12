#include <iostream>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 100;
const int M = 10000;
int match[N];
bool vis[N];
int top;
struct Vertex
{
	int first;
}V[N];
struct Edge
{
	int v, next;
}E[M];
void init() {
	top = 0;
	memset(match, 0, sizeof(match));
	memset(V, -1, sizeof(V));
}
void add(int u, int v) {
	E[top].v = v;
	E[top].next = V[u].first;
	V[u].first = top++;
}
void printG(int n) {	//�����ڽӱ�
	cout << "�ڽӱ�����:" << endl;
	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			cout << "]--[" << E[j].v << " " << E[j].next;
		}
		cout << "]\n";
	}
}

void print(int n) {
	cout << "��Է�������:" << endl;
	for (int i = 1; i <= n; i++)
		if (match[i])
			cout << i << "--" << match[i] << endl;
}
/*
	�������㷨
	��һ������·�ĸ��Ӷ��ΪO(E),�����V������·��ʱ�临�Ӷ�ΪO(VE)
*/
bool maxmatch(int u) {
	int v;
	for (int i = V[u].first; ~i; i = E[i].next) {
		v = E[i].v;//�ڽӵ�
		if (!vis[v]) {//�ý�㻹δ����
			vis[v] = 1;
			if (!match[v] || maxmatch(match[v])) {
				//v���δƥ�����v��ƥ����ҵ���������ƥ��
				match[u] = v;
				match[v] = u;
				return true;
			}
		}
	}
	return false;//�ڽӱ߶������ϣ�û���ҵ�ƥ���
}
int main() {
	int n, m, total, num = 0;
	int u, v;
	cout << "����Ů����Ա����m��������Ա����n:";
	cin >> m >> n;
	init();
	total = m + n;
	cout << "�����������Ե���Ů����Ա���u,v(����-1����):" << endl;
	while (cin >> u >> v && u + v != -2) {
		add(u, v);
		add(v, u);
	}
	printG(total);

	for (int i = 1; i <= m; i++) {
		memset(vis, 0, sizeof(vis));
		if (maxmatch(i))
			num++;
	}
	cout << "���ƥ����:" << num << endl;
	print(m);
}
