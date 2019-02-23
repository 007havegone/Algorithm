/*
	�������һ���� 1+m+m^2+m^3+....+m^(n-1)=(m^n-1)/(m-1)=m^(n-1)�������Ҫ��չ
	����Щ���ÿ������m����֧���ܵķ�֧��Ϊm^n,ÿ����֧����Ҫ�ж�Լ��������Լ������ʱ�临�Ӷ�ΪO(n),
	���ʱ�临�Ӷ�ΪO(n*m^n)
	�����е��·��Ϊn��ͬʱʹ��x[]�������飬�ռ临�Ӷ�O(n����
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1007;

int x[N];//�����ɫ���
int mp[N][N];//ͼ���ڽӾ���
int sum = 0;//��ĸ���
int n, m, edge;//���������ɫ��



bool CheckByMatrix(int t) {//���1��t-1����ɫ�Ƿ���ͬ
	for (int i = 1; i < t; i++) {//���Բ����ڽӱ����Ż���
		if (mp[i][t] && x[i] == x[t])
			return false;
	}
	return true;
}
//�����ڽӱ�ṹ�Ż�
vector<int> vecs[N];//vecs[i]����i�����ڽӵ�
bool CheckByAdjaList(int t) {
	for(int i=0;i<vecs[t].size();i++){
		int nebor = vecs[t][i];//�ڽӵ�
		if (nebor < t&&x[nebor] == x[t])//����ǰt-1���ڽӵ�ͬʱ��ɫ��ͬ
			return false;
	}
	return true;
}
void Backtrack(int t) {
	if (t > n) {
		sum++;
		cout << "��" <<  sum << "�ַ���";
		for (int i = 1; i <= n; i++) {
			cout << x[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= m; i++) {
		x[t] = i;
		if (CheckByMatrix(t)) {
			Backtrack(t + 1);
		}
		/*if (CheckByAdjaList(t)) {
			Backtrack(t + 1);
		}*/
	}
}
void CreatAdjacencyMatrix(int edge) {
	int u, v;
	memset(mp, 0, sizeof(mp));
	for (int i = 0; i < edge; i++) {
		cin >> u >> v;
		mp[u][v] = mp[v][u] = 1;
	}
}
void CreatAdjacencyList(int edge) {
	int u, v;
	for (int i = 1; i <= n; i++) {//��ʼ��
		vecs[i].clear();
	}
	for (int i = 0; i < edge; i++) {
		cin >> u >> v;
		vecs[u].push_back(v);
		vecs[v].push_back(u);
	}
}
int main() {
	cout << "���������:";
	cin >> n;
	cout << "������ɫ����:";
	cin >> m;
	cout << "�������:";
	cin >> edge;
	cout << "����ͼ�ıߵĽ��u��v";
	memset(x, 0, sizeof(x));
	CreatAdjacencyMatrix(edge);
	//CreatAdjacencyList(edge);
	Backtrack(1);
}