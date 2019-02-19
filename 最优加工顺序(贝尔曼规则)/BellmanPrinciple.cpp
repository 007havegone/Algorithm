#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10000;
/*
	时间复杂度O(nlogn)
*/
struct Node
{
	int id;
	int x, y;
	//成员函数重载<
	/*bool operator<(const Node&b)const {
		return min(b.x, y) >= min(b.y, x);
	}*/

}T[N];
//非成员函数重载<
//bool operator<(const Node&a, const Node& b) {
//	return min(b.x, a.y) >= min(b.y, a.x);
//}  
//比较器
bool cmp(const Node&a, const Node&b) {
	return min(b.x, a.y) >= min(b.y, a.x);//采用贝尔曼规则排序
}
int main() {
	int n;
	int f1 = 0, f2 = 0;
	cout << "输入机器零件的个数n:";
	cin >> n;
	cout << "依次输入每个零件在第一台机器和第二台机器加工的时间:" << endl;
	for (int i = 0; i < n; i++) {
		cin >> T[i].x >> T[i].y;
		T[i].id = i + 1;
	}
	sort(T, T + n,cmp);//快速排序O(nlogn)
	for (int i = 0; i < n; i++) {
		f1 += T[i].x;
		f2 = max(f1, f2) + T[i].y;
	}
	cout << "最快加工顺序为:";
	for (int i = 0; i < n; i++)
		cout << T[i].id << " ";
	cout << endl;
	cout << "最短时间为:" << f2;
}