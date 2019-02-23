/*
	n�ʺ�����Ľ�ռ�Ϊm����(m==n),�������Ϊn��
	�������һ�㣬һ������1+n+n^2+...+n^��n-1��=��n^n-1)/(n-1��=n^(n-1)�����
	ÿ�������չ��n����֧
	ÿ����֧����ҪԼ�������жϣ�Լ������ʱ�临�Ӷ�ΪO(n)
	��ʱ�临�Ӷ�ΪO(n^(n+1))
	�ռ临�Ӷ�ΪO(n)
*/
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1007;
int x[N];//��¼x[i]Ϊ��i�����ӷ���(i,x[i])
int cnt = 0;//��¼������
int n;//������

bool check(int t) {
	for (int i = 1; i < t; i++) {
		if(x[i]==x[t]||(abs(i-t)==abs(x[i]-x[t])))//ͬ�л�ͬһб��
			return false;
	}
	return true;
}
void Backtrack(int t) {
	if (t > n) {
		cnt++;
		//Ҷ�Ӵ����O(n)
		cout << "����:" << cnt;
		for (int i = 1; i <= n; i++) {
			cout << "(" << i <<  "," << x[i] << ")" << " ";
		}
		cout << "\n------------------------------------------\n";
	}
	for (int i = 1; i <= n; i++) {
		x[t] = i;
		if (check(t))
			Backtrack(t + 1);
	}
}
int main() {
	cout << "�������ӵĸ���:";
	cin >> n;
	memset(x, 0, sizeof(x));
	Backtrack(1);
	if (!cnt)
		cout << "û�з��ϵķ���" << endl;
	else
		cout << "����" << cnt << "�ַ���" << endl;
}