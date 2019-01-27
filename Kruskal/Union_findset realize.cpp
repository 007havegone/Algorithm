#include <iostream>
#include <algorithm>
using namespace std;

const int N = 107;
struct Edge
{
	int u, v;
	int dis;
	bool operator<(const Edge&e)const {
		return dis < e.dis;
	}
}e[N*N];
int father[N];
int n, m;//n���㣬m����
void Init(int n)
{
	for (int i = 1; i <= n; i++)
		father[i] = i;
}
//������ͬʱ�鲢����
int Find(int i)
{
	if (father[i] != i)
		father[i] = Find(father[i]);//��������Ϊ�Լ��ĸ��ף��鲢
	return father[i];
}
int merge(int a, int b)
{
	int p = Find(a);
	int q = Find(b);
	if (p == q)
		return 0;
	if (p < q)//ͳһС����Ϊ��һ�����ȵĸ���
		father[q] = p;
	else
		father[p] = q;
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
				return ans;
		}
	}
	return 0;
}
int main()
{
	cin >> n >> m;
	Init(n);
	for (int i = 0; i < m; i++)
		cin >> e[i].u >> e[i].v >> e[i].dis;
	sort(e, e + m);
	int ans=Kruskal(n);
	cout << "ans = " << ans << endl;
}