/*
	�������������������ı��β���ʽ��ʱ�临�Ӷȿ����Ż���O(n^2)
				0							j=i-1
	c[i][j]= c[i][k-1]+c[k+1][j]+w[i][j],����s[i][j-1]<=k<=s[i+1][j]	j>=i
*/

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

const int N = 107;
int s[N][N];
double w[N][N], c[N][N];
double p[N], q[N];
int n;

void optimal_BST(int n) {
	int i, j, k, d;
	double temp;
	for ( i = 1; i<= n + 1; i++) {
		c[i][i - 1] = 0;
		w[i][i - 1] = q[i - 1];
	}
	for (d = 1; d <= n; d++) {
		for (i = 1; i <= n - d + 1; i++) {
			j = d + i - 1;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			int i1 = s[i][j - 1] > i ? s[i][j - 1] : i;
			int j1 = s[i + 1][j] < j ? s[i + 1][j] : j;
			c[i][j] = c[i][i1 - 1] + c[i1 + 1][j];//��ʼ��Ϊi1
			s[i][j] = i1;//��ʼ��
			//��i1+1��j1��Ѱ����ѵ�k
			for (k = i1 + 1; k <= j1; k++) {
				temp = c[i][k - 1] + c[k + 1][j];
				if (temp<c[i][j] && fabs(temp - c[i][j])>1E-6) {
					c[i][j] = temp;
					s[i][j] = k;
				}
			}
			c[i][j] += w[i][j];
		}
	}
}
//��ȱ���(�������)
void Construct_Optimal_BST(int i, int j) {
	queue<pair<int, int>> que;
	int flag = 1;
	que.push(make_pair(i, j));
	while (!que.empty()) {
		auto t = que.front();
		que.pop();
		int k = s[t.first][t.second];
		if (flag) {
			cout << "S" << k << " is the root" << endl;
			flag = 0;
		}
		if (k - 1 < t.first)//������ΪҶ��
			cout << "e" << k - 1 << " is the left child of " << "S" << k << endl;
		else {//��Ҷ��
			cout << "S" << s[t.first][k - 1] << " is the left child of " << "S" << k << endl;
			que.push(make_pair(t.first, k - 1));
		}
		if (k >= t.second)//������ΪҶ��
			cout << "e" << k << " is the right child of " << "S" << k << endl;
		else {//��Ҷ��
			cout << "S" << s[k + 1][t.second] << " is the right child of " << "S" << k << endl;
			que.push(make_pair(k + 1, t.second));
		}
	}
}
int main() {
	cout << "����ʵ���ĸ���:";
	cin >> n;
	cout << "��������ʵ���ĸ���:" << endl;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	cout << "������������ĸ���:" << endl;
	for (int i = 0; i <= n; i++)
		cin >> q[i];
	optimal_BST(n);
	Construct_Optimal_BST(1, n);//��ȱ���
}