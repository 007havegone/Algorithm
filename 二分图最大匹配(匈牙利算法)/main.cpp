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
void printG(int n) {	//网络邻接表
	cout << "邻接表如下:" << endl;
	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			cout << "]--[" << E[j].v << " " << E[j].next;
		}
		cout << "]\n";
	}
}

void print(int n) {
	cout << "配对方案如下:" << endl;
	for (int i = 1; i <= n; i++)
		if (match[i])
			cout << i << "--" << match[i] << endl;
}
/*
	匈牙利算法
	找一条增广路的复杂度最坏为O(E),最多找V条增广路，时间复杂度为O(VE)
*/
bool maxmatch(int u) {
	int v;
	for (int i = V[u].first; ~i; i = E[i].next) {
		v = E[i].v;//邻接点
		if (!vis[v]) {//该结点还未访问
			vis[v] = 1;
			if (!match[v] || maxmatch(match[v])) {
				//v结点未匹配或者v的匹配点找到了其他的匹配
				match[u] = v;
				match[v] = u;
				return true;
			}
		}
	}
	return false;//邻接边都检查完毕，没有找到匹配点
}
int main() {
	int n, m, total, num = 0;
	int u, v;
	cout << "输入女销售员人数m和男销售员人数n:";
	cin >> m >> n;
	init();
	total = m + n;
	cout << "请输入可以配对的男女销售员编号u,v(两个-1结束):" << endl;
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
	cout << "最大匹配数:" << num << endl;
	print(m);
}
