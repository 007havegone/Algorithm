
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 107;
struct Edge {
	int u;
	int v;
	int dis;
	//sort from mixn to maxn
	bool operator<(const Edge&e)const {
		return dis < e.dis;
	}
}e[N*N];
int nodeset[N];
int n, m;//n���㣬m����

void Init(int n)
{
	for (int i = 1; i <= n; i++)
		nodeset[i] = i;
}
int merge(int a, int b)
{
	int p = nodeset[a];
	int q = nodeset[b];
	if (p == q)
		return 0;
	for (int i = 1; i <= n; i++)
	{
		if (nodeset[i] == p)
			nodeset[i] = q;
	}
	return 1;
}
int Kruskal(int n)
{
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		if (merge(e[i].u, e[i].v))
		{
			ans += e[i].dis;
			n--;
			if (n == 1)
				break;
		}
	}
	return ans;
	
}
int main()
{
	cout << "���������ͱߵĸ���" << endl;
	cin >> n >> m;
	Init(n);
	cout << "������u,v������dis" << endl;
	for (int i = 0; i < m; i++)
		cin >> e[i].u >> e[i].v >> e[i].dis;
	sort(e, e + m);
	int ans=Kruskal(n);
	cout << "the minimun cost is " << ans << endl;
}