#include <iostream>
#include <cstring>
using namespace std;

const int N=100;
const int M=10000;

struct Node
{
	int first;
}Vertex[N];
struct Edge
{
	int v, w, next;//�յ㣬Ȩֵ����һ���ڱ�λ��
}Edge[M];
int m, n, top;

void init()
{
	memset(Vertex, -1, sizeof(Vertex));
	top = 0;
}
void addEdge(int u, int v, int w)
{
	Edge[top].v = v;
	Edge[top].w = w;
	Edge[top].next = Vertex[u].first;
	Vertex[u].first = top++;
}
void add(int u, int v, int w)
{
	addEdge(u, v, w);
	addEdge(v, u, w);
}
void CreateMap()
{
	init();
	int u, v, w;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		add(u, v, w);
	}
}
void travel()
{
	for (int i = 1; i <= n; i++)
	{
		//-1Ϊÿ�������յ㣬-1ȡ����Ϊ0
		for (int j = Vertex[i].first; ~j; j = Edge[j].next)
			cout << Edge[j].v << " " << Edge[j].w << endl;
	}
}
int main()
{

}	