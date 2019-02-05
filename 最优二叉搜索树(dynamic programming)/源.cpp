/*
	���ڸ�������������S={s1,s2,s3...sn}���ؼ��ֽ���Ϊʵ��㡣����ÿ���ؼ��ֲ��Ҹ���Ϊpi������ʧ�ܽ��
	��Ϊ���㣬��Ӧ{e0,e1,e2.....en}��ÿ������Ĳ��Ҹ���Ϊqi��e0��ʾС��s1��ֵ��en��ʾ����sn��ֵ��
	���н����Ҹ���֮��Ϊ1.����Сƽ���Ƚϴ����Ķ��������������Ŷ�����������

	�������������㣺����<��<�ҽ�㣬���ÿ��ѡ�����ܱ�֤���ʴ�Ľ�㡣���Թ�����˼���޷��������Ŷ�����������

	���ñ����������������һ���� O��4n^2/ n^1.5)�ò�ͬ�Ķ�����������ָ�����𣩡�

	�������������Ž�Ľṹ������

	����skΪ����������T(1,n)�ĸ�����ôԭ�����Ϊ���������⣬������T(1,k-1)��������T(k+1,n)
*/

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 107;//ʵ���������Ŀ
double p[N];//p[i]Ϊ��i��ʵ���ĸ��ʣ���1��ʼ
double q[N];//q[j]Ϊ��j������ĸ��ʣ���0��ʼ
double c[N][N];//c[i][j]��ʾ����A={ai,ai+1,....,aj}��ʵ����B={ei-1,ei,....,ej}���������С����
double w[N][N];//w[i][j]��ʾ q[i-1]��p[i]��q[i]��....p[j]��q[j]�ĸ��ʺ�
int s[N][N];//s[i][j]��ʾ ����A={ai,ai+1,....,aj}��ʵ����B={ei-1,ei,....,ej}����������Ž⣬�����ڵ�
int n;
/*
	������ķ����Ͷ����֪
				0													i-1=j ֻ��һ��������
	c[i][j]=	min{ c[i][k-1]+c[k+1][j] }+w[i][j] ���� i<=k<=j		j>=i

			 q[i-1]															i-1=j ֻ��һ��������
	w[i][j]= q[i-1] + p[i] + q[i] + p[i+1] +q[i+1] + ....+ p[j] + q[j]		j>=i

*/
void optimal_BST(int n) {
	int i, j, d, k;
	double temp;
	//��ʼ��c[][]��w[][]
	for ( i = 1; i <= n + 1; i++)
		c[i][i - 1] = 0.0;
	for ( i = 1; i <= n + 1; i++)
		w[i][i - 1] = q[i - 1];

	for ( d = 1; d <= n; d++) {//��ģ��1��n
		for ( i = 1; i <= n - d + 1; i++) {
			j = i + d - 1;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			c[i][j] = c[i][i - 1] + c[i + 1][j];
			s[i][j] = i;
			for (k = i + 1; k <= j; k++) {
				temp = c[i][k - 1] + c[k + 1][j];
				if (temp < c[i][j]) {
					c[i][j] = temp;
					s[i][j] = k;
				}
			}
			c[i][j] += w[i][j];
		}
	}
}
//��ȱ���
void Construct_Optimal_BST(int i, int j, bool flag) {
	if (flag == 0)
	{
		cout << "S" << s[i][j] << " is root" << endl;
	}
	int k = s[i][j];
	//������ΪҶ��
	if (k - 1 < i) {
		cout << "e" << k - 1 << " is the left child of " << "S" << k << endl;
	}//����Ҷ��
	else {
		cout << "S" << s[i][k - 1] << " is the left child of " << "S" << k << endl;
		Construct_Optimal_BST(i, k - 1, true);
	}
	//������ΪҶ��
	if (k >= j) {
		cout << "e" << k << " is the right child of " << "S" << k << endl;
	}//����Ҷ��
	else {
		cout << "S" << s[k + 1][j] << " is the right child of " << "S" << k << endl;
		Construct_Optimal_BST(k + 1, j, true);
	}
}
//��ȱ���(�������)
void Construct_Optimal_BST(int i, int j) {
	queue<pair<int, int>> que;
	int flag = 0;
	que.push(make_pair(i, j));
	while (!que.empty()) {
		auto t = que.front();
		que.pop();
		int k = s[t.first][t.second];
		if (k - 1 < t.first)
			cout << "e" << k - 1 << " is the left child of " << "S" << k << endl;
		else {
			cout << "S" << s[t.first][k - 1] << " is the left child of " << "S" << k << endl;
			que.push(make_pair(t.first, k - 1));
		}
		if (k >= t.second)
			cout << "e" << k << " is the right child of " << "S" << k << endl;
		else {
			cout << "S" << s[k + 1][t.second] << " is the right child of " << "S" << k << endl;
			que.push(make_pair(k + 1, t.second));
		}
	}
}
int main() {
	cout << "����ʵ���ĸ���:";
	cin >> n;
	cout << "����n��ʵ���ĸ���:";
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	cout << "����n+1������ĸ���:";
	for (int i = 0; i <= n; i++)
		cin >> q[i];
	optimal_BST(n);
	cout << c[1][n] << endl;

	Construct_Optimal_BST(1, n, false);
	//Construct_Optimal_BST(1, n);
	return 0;
}