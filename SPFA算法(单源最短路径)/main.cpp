#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 100;
int n, m, src;//����������������
/*	�ڽӱ�
	g[i][j].first��ʾi���ĵ�j���ߵĽ����
	g[i][j].second��ʾ�ߵĳ���
*/
vector<pair<int, int>> g[N + 10];
int dist[N+10];//dist[i]Դ�㵽i����̾���
bool inQue[N + 10];
int c[N + 10];
queue<int> que;//������Ż��Ľ��

/*
	����һ���Ƚ��ȳ��Ķ�������������Ż��Ľ�㣬�Ż�ʱȡ������u������u�㵱ǰ�����·������ֵ��
	u��ָ����ڵ�v�����ɳڲ��������v������·������ֵ������������v���ڵ�ǰ�Ķ����У���v������β��
	����ȡ���������ɳڣ�ֱ������Ϊ�ա�
	ֻҪ���·�����ڣ�����SPFA�㷨�ض��������Сֵ����Ϊÿ�ν�������β�����Ǿ����ɳڲ����õ��ġ�
	������֮��ÿ�ε��Ż�������ĳ�������С·������ֵd[v]��С�������㷨��ִ�л�ʹdԽ��ԽС�����費���ڸ�Ȩ��·��
	ÿ����㶼����Сֵ�������㷨��������ִ����ȥ������d�𽥱�С��ֱ���ﵽ���·��ֵʱ���㷨������

	���Ӷ�:���� O(|V|*|E|)
*/
/*
	û�и���(֧�ָ�Ȩͼ)
	ÿ������������ȷ��һ���㱻���³������������·ֵ
	�����֤��ֻ��Ҫ����㿴���Ǹ����ϣ���ÿ��ȷ���õĵ������㼯�ϼ��ɣ���
	�����ܹ���Ҫ |V|-1 �Σ���㲻�ø��£���
	
	����и���
	��ôÿ�����Ǳ㲻��˵�������Ѿ�ȷ����һ���㣬�������������·��
	������Ϊ����ȫ����ͨ���ڸ��������ϼ�Ȧ�����ﵽ���̵�Ŀ�ģ����Ʒ����Ǹ�֤����

	����һ����ȫͼ�����n-1�����ܸ��µ�n�������Ե����Ӵ���n-1�ξ�˵���и���
	����Ϊʲô�ǣ�n����Ϊ����һ���ڵ�ʱ�� �������>n��1��ô����һ�����ڵ��ͼ�ᱻ�ж�Ϊ���ڸ��� �ۺϿ���ȡ>n
*/
bool SPFA() {
	memset(dist, 63, sizeof(dist));//63�� 0x3f
	memset(c, 0, sizeof(c));
	dist[src] = 0;//��ʼ��������Ϊ0
	while (!que.empty())que.pop();
	que.push(src);
	inQue[src] = true;
	c[src]++;//��Ӵ���
	while (!que.empty())//�Ż��ĵ�δ��
	{
		int u = que.front(); que.pop();
		for (int i = 0; i < g[u].size(); i++)//�����ڽӵ㣬�ɳڲ���
		{
			if (dist[u] + g[u][i].second < dist[g[u][i].first]) {
				dist[g[u][i].first] = dist[u] + g[u][i].second;
				if (!inQue[g[u][i].first]) {//���ڶ����������Ӳ���
					inQue[g[u][i].first] = true;
					que.push(g[u][i].first);
					c[g[u][i].first]++;
					if (c[g[u][i].first] > n)//��Ӵ�������n-1
						return false;
				}

			}
		}
		//���
		inQue[u] = false;
	}
	return true;
}

void print() {
	for (int i = 1; i <= n; i++)
		if (dist[i] == INF)
			cout << "INF" << " ";
		else
			cout << dist[i] << " ";
	cout << endl;
}
int main() {
	int u, v, w;
	cout << "����������ͱ߸���:" << endl;
	cin >> n >> m;
	cout << "��������u,v�������w:\n";
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g[u].push_back(make_pair(v, w));
	}
	cout << "�������:";
	cin >> src;
	if (SPFA())
		print();
	else
		cout << "���ڸ���" << endl;
}
