#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3fffffff;
const int MX = 10005;
int n, bestf, f1, f2;//f1Ϊ��ǰ��һ̨�����ӹ������ʱ�䣬f2Ϊ��ǰ�ڶ�̨�����ӹ���ɵ�ʱ��
int x[MX], bestX[MX];//x[i]��ʾ��i�μӹ���x[i]�������bestX[i]��¼���Ž�
struct Time
{
	int x;//��һ̨�����ӹ�ʱ��

	int y;//�ڶ�̨�����ӹ�ʱ��
}T[MX];

/*
	ʱ�临�Ӷ�ԼΪO((n+1)!)
	�ռ临�Ӷ�ԼΪO(n)
*/
void Backtrack(int t) {
	if (t > n) {
		for (int i = 1; i <= n; i++)
			bestX[i] = x[i];
		bestf = f2;
		return;
	}
	for (int i = t; i <= n; i++) {//������������
		f1 += T[x[i]].x;
		int temp = f2;
		f2 = max(f1, f2) + T[x[i]].y;
		if (f2 < bestf) {
			swap(x[t], x[i]);
			Backtrack(t + 1);
			swap(x[t], x[i]);
		}
		f1 -= T[x[i]].x;
		f2 = temp;
	}
}

int main() {
	cout << "�����������ĸ���n:";
	cin >> n;
	cout << "��������ÿ������ڵ�һ̨�����͵ڶ�̨�����ӹ���ʱ��:" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> T[i].x >> T[i].y;
		x[i] = i;
	}
	bestf = INF;
	f1 = f2 = 0;
	memset(bestX, 0, sizeof(bestX));
	Backtrack(1);
	cout << "���ӹ�˳��Ϊ:";
	for (int i = 1; i <= n; i++)
		cout << bestX[i] << " ";
	cout << endl;
	cout << "���ʱ��Ϊ:" << bestf;
}