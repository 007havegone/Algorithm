#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10000;
/*
	ʱ�临�Ӷ�O(nlogn)
*/
struct Node
{
	int id;
	int x, y;
	//��Ա��������<
	/*bool operator<(const Node&b)const {
		return min(b.x, y) >= min(b.y, x);
	}*/

}T[N];
//�ǳ�Ա��������<
//bool operator<(const Node&a, const Node& b) {
//	return min(b.x, a.y) >= min(b.y, a.x);
//}  
//�Ƚ���
bool cmp(const Node&a, const Node&b) {
	return min(b.x, a.y) >= min(b.y, a.x);//���ñ�������������
}
int main() {
	int n;
	int f1 = 0, f2 = 0;
	cout << "�����������ĸ���n:";
	cin >> n;
	cout << "��������ÿ������ڵ�һ̨�����͵ڶ�̨�����ӹ���ʱ��:" << endl;
	for (int i = 0; i < n; i++) {
		cin >> T[i].x >> T[i].y;
		T[i].id = i + 1;
	}
	sort(T, T + n,cmp);//��������O(nlogn)
	for (int i = 0; i < n; i++) {
		f1 += T[i].x;
		f2 = max(f1, f2) + T[i].y;
	}
	cout << "���ӹ�˳��Ϊ:";
	for (int i = 0; i < n; i++)
		cout << T[i].id << " ";
	cout << endl;
	cout << "���ʱ��Ϊ:" << f2;
}