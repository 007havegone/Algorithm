#include <iostream>
using namespace std;
const int N = 10;
int n;
int cnt = 0;
int x[N];
void Backtrack(int t) {
	if (t > n) {
		cnt++;
		for (int i = 1; i <= n; i++)
			cout << x[i] << " ";
		cout << endl;
		return;
	}
	for (int i = t; i <= n; i++) {
		swap(x[i], x[t]);
		Backtrack(t + 1);
		swap(x[i], x[t]);
	}

}
int main() {
	cout << "�������ֵĸ���:";
	cin >> n;
	cout << "������������:";
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	Backtrack(1);
	cout << "ȫ���и���Ϊ:" << cnt << endl;
}