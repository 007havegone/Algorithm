#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 100;//顶点个数
const int M = 10000;//边个数
int n, m;
/*
	前向星，静态数组表示
*/
int head[N];//记录i为起点边的头结点位置
struct Edge
{
	int u, v, w;//起点u，终点v，权值w
}mp[M];

/*
	时间复杂度为排序算法O(nlogn)
	空间复杂度为O(m+n)

*/
void init()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> mp[i].u >> mp[i].v >> mp[i].w;
	sort(mp + 1, mp + m + 1, [](Edge e1, Edge e2)->bool {
		if (e1.u == e2.u) {
			if (e1.v == e2.v)return e1.w < e2.w;
			else return e1.v < e2.v;
		}
		else return e1.u < e2.u;
	});
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= m; i++)
	{
		if (mp[i].u != mp[i - 1].u)
			head[mp[i].u] = i;
	}
}

void travel()
{
	for(int i=1;i<=n;i++)
		for (int j = head[i];mp[j].u==i&&j<=m;j++)
			cout << mp[j].u << " " << mp[j].v << " " << mp[j].w << endl;
}

int main()
{

}