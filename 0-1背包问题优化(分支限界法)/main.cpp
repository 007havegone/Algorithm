#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
const int N = 10;//�����Ʒ��
int n, W;//��Ʒ��ͱ�������
int sumw, sumv;//��Ʒ���������ܼ�ֵ
int bestv;//���ż�ֵ
bool bestx[N];
int v[N];//��Ű��Լ۱�����ļ�ֵ������
int w[N];
struct Node
{
	Node() {}
	Node(int _cv, double _up, int _rw, int _id) :cv(_cv),up(_up),
									rw(_rw), id(_id) {
		memset(x, 0, sizeof(x));
	}
	int cv;//��ǰ��ֵ
	double up;//����
	int rw;//ʣ������
	int id;
	bool x[N];//��¼���Ž�
	bool operator<(const Node& b)const {//up�ķǵ�������
		return up < b.up;
	}
};
struct Goods
{
	int weight;
	int value;
}goods[N];
struct Object
{
	int id;
	double cp;//�Լ۱�
	bool operator<(const Object& b)const {//�Լ۱ȷǵ�������
		return cp > b.cp;

	}
}obj[N];
double bound(const Node& node) {
	int left = node.rw;//��ǰʣ��ռ�
	double maxvalue = node.cv;//��ǰ��ֵ
	int i = node.id;
	while (i <= n && left >= w[i]) {
		left -= w[i];
		maxvalue += v[i];
		i++;
	}
	if (left && i<=n) {
		maxvalue += 1.0 * left * v[i] / w[i];
	}
	return maxvalue;
}
void priorbfs() {
	int t, tcv, trw;//��Ϊ��ʱ����
	double tup;
	priority_queue<Node> q;
	q.push(Node(0, sumv, W, 1));//ѹ����ڵ�
	while (!q.empty()) {
		Node livenode, lnode, rnode;//�����������
		livenode = q.top();
		q.pop();
		cout << "��ǰ����idֵ:" << livenode.id << "��ǰ����upֵ:" << livenode.up << endl;
		cout << "��ǰ���Ľ�����:";
		for (int i = 1; i <= n; i++)
		{
			cout << livenode.x[i];
		}
		cout << endl;
		t = livenode.id;
		if (t > n || livenode.rw == 0) {//�������һ����߿ռ䲻��
			if (livenode.cv >= bestv) {//�������Ž�
				cout << "�������Ž�����:";
				for (int i = 1; i <= n; i++) {
					bestx[i] = livenode.x[i];
					cout << bestx[i];
				}
				cout << endl;
				bestv = livenode.cv;
			}
			continue;
		}
		if (livenode.up < bestv)//�޽�����
			continue;
		//��չ����
		trw = livenode.rw;
		tcv = livenode.cv;
		if (trw >= w[t]) {//Լ������
			lnode.cv = tcv + v[t];
			lnode.rw = trw - w[t];
			lnode.id = t + 1;
			tup = bound(lnode);
			lnode = Node(lnode.cv, tup, lnode.rw, lnode.id);
			for (int i = 1; i < t; i++) {
				lnode.x[i] = livenode.x[i];//���Ƹ��ڵ�����Ž�
			}
			lnode.x[t] = true;
			if (lnode.cv > bestv)
				bestv = lnode.cv;
			q.push(lnode);
		}
		rnode.cv = tcv;
		rnode.rw = trw;
		rnode.id = t + 1;
		tup = bound(rnode);
		if (tup >= bestv) {
			rnode = Node
			(rnode.cv, tup, rnode.rw, rnode.id);
			for (int i = 1; i < t; i++)
				rnode.x[i] = livenode.x[i];
			rnode.x[t] = false;
			q.push(rnode);
		}
	}
}
int main() {
	bestv = 0;
	sumv = 0;
	sumw = 0;
	cout << "������Ʒ����:";
	cin >> n;
	cout << "���뱳������:";
	cin >> W;
	cout << "��������ÿ����Ʒ�������ͼ�ֵ:";
	for (int i = 1; i <= n; i++) {
		cin >> goods[i].weight >> goods[i].value;
		sumv += goods[i].value;
		sumw += goods[i].weight;
		obj[i - 1].id = i;
		obj[i - 1].cp = 1.0* goods[i].value / goods[i].weight;
	}
	if (sumw <= W) {
		bestv = sumv;
		cout << "������Ʒ��ֵΪ:" << bestv << endl;
		cout << "����������Ʒ" << endl;
		return 0;
	}
	sort(obj, obj + n);//����
	cout << "�����:" << endl;
	for (int i = 1; i <= n; i++) {
		v[i] = goods[obj[i - 1].id].value;
		w[i] = goods[obj[i - 1].id].weight;
		cout << v[i] << " " << w[i] << endl;
	}
	priorbfs();
	cout << "���ż�ֵΪ:" << bestv << endl;
	cout << "�������Ʒ���Ϊ:";
	for (int i = 1; i <= n; i++)
	{
		if (bestx[i])
			cout << obj[i - 1].id << " ";
	}

	return 0;
}