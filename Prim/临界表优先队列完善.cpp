/*
	�����ڽӱ�����ȶ���ʵ��
	���Ӷ�Ϊ O(nlogn)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
//�����1��ʼ�洢 
const int INF = 0x3fffffff;
const int N = 107;
typedef struct Node {
	int lowcost;//��̾���
	int close;//����ٵ�
	int u;//����±� 
	bool operator<(const Node&n)const
	{
		return lowcost > n.lowcost;
	}
}NodeType;
struct Link {
	Link(int mv, int mdis) :v(mv), dis(mdis) {}
	int v;
	int dis;
};
bool flag[N];
NodeType Nodes[N];//��������� 
vector<Link> G[N];//��űߵĹ�ϵ 

void Prim(int u0, int n)
{
	memset(flag, false, sizeof(flag));//����δ���� 
	/*���ȶ��� ,����Ϊʲô������ָ�롣���ظ���ֵ���ĺ�ײ㲻�������
		�Ӷ����£���Ԫ�ز���󣬶ѵ�˳������*/
	priority_queue<NodeType> que;
	//��ʼ����� 
	for (int i = 1; i <= n; i++)
	{
		Nodes[i].u = i;
		Nodes[i].close = u0;
		Nodes[i].lowcost = INF;
	}
	for (auto i = G[u0].begin(); i != G[u0].end(); i++)
		Nodes[i->v].lowcost = i->dis;
	Nodes[u0].lowcost = 0;
	que.push(Nodes[u0]);
	while (!que.empty())
	{
		NodeType pn = que.top(); que.pop();
		int t = pn.u;
		if (flag[t])
			continue;
		flag[t] = true;//����ѷ��� 
		cout << "����:" << t << " ";
		//���������ڽӵ� 
		for (auto i = G[t].begin(); i != G[t].end(); i++)
		{
			int e = i->v;
			//��������δ�����ڽӵ�e 
			if (!flag[e])
			{
				if (i->dis < Nodes[e].lowcost)//������� 
				{
					Nodes[e].lowcost = i->dis;
					Nodes[e].close = t;
				}
				que.push(Nodes[e]);
				cout << " " << e;
			}
		}
		cout << " lowcost 7 = " << Nodes[7].lowcost;
		cout << " lowcost 3 = " << Nodes[3].lowcost;
		cout << endl;
	}

}
int main() {
	int n, m;
	int a, b, v, sta;
	int sum = 0;
	cout << "���������ͱ���" << endl;
	cin >> n >> m;
	//��յ�ͼ 
	for (int i = 1; i <= n; i++)
		while (!G[i].empty())
			G[i].pop_back();
	cout << "����ߵ���Ϣ" << endl;
	// ��ʼ��ͼ 
	while (m--)
	{
		cin >> a >> b >> v;
		G[a].push_back(Link(b, v));
		G[b].push_back((Link(a, v)));
	}
	cout << "�������" << endl;
	cin >> sta;
	Prim(sta, n);
	for (int i = 1; i <= n; i++) {
		cout << Nodes[i].lowcost << " ";
		sum += Nodes[i].lowcost;
	}
	cout << "\n��С��������ȨֵΪ: " << sum << endl;

}