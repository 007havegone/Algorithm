#include <iostream>
using namespace std;
const int N = 1007;
bool x[N];//��¼x[i]�Ƿ������
bool bestX[N];//��¼���Ž�
int bestn;//��¼����ֵ
int cn;//��ǰ�ŵĸ���
int n, m;//nΪ�������mΪ����
int a[N][N];//�ڽӾ����ʾͼ

/*
	���ҽ�����2^n������ʱ�临�Ӷ�ΪO(n*2^n+1*2^1)=O(n*2^n)
	�ռ临�Ӷ�ΪbestX��������ͻ��ݹ��̵�·������ΪO(n)
*/
bool Place(int t) {//Լ������O(n)
	bool ok = true;
	for (int i = 1; i < t; i++) {
		if (x[i] && a[i][t] == 0) {//��֮ǰ�����ŵĽ��û�ߣ���0����ǰ����
			ok = false;
			break;
		}
	}
	return ok;
}
void Backtrack(int t) {
	if (t > n) {//����Ҷ��
		for (int i = 1; i <= n; i++) {
			bestX[i] = x[i];
		}
		bestn = cn;
		return;
	}
	if (Place(t)) {//����Լ����������������
		cn++;
		x[t] = 1;
		Backtrack(t + 1);
		cn--;
	}
	if (n - t + cn > bestn) {//�����޽����������������� O(1��
		x[t] = 0;
		Backtrack(t + 1);
	}
}
int main() {
	int u, v;
	cout << "���������n:";
	cin >> n;
	cout << "����ͼ�ı߸���m:";
	cin >> m;
	memset(a, 0, sizeof(a));
	cout << "����ߵĹ�ϵ:";
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		a[v][u] = a[u][v] = 1;
	}
	bestn = 0;//��ʼ��
	cn = 0;
	Backtrack(1);
	cout << "����ŵĸ���Ϊ:" << bestn << endl;
	cout << "ѡ�еĽ��Ϊ:";
	for (int i = 1; i <= n; i++) {
		if (bestX[i])
			cout << i << " ";
	}
	cout << endl;
	return 0;
}
