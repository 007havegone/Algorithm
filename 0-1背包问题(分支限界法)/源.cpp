/*
	
	�÷�֧�޽編�Ľ�ռ䣨�Ӽ������Ľ������� 2^(n+1)-1
	���ҽ�������� 2^(n+1)-1-1/2 = 2^n-1
	Լ�����޽纯����ʱ�临�ӶȾ�ΪO(1����ʱ�临�Ӷ�ΪO(2^(n+1))

	�ռ临�Ӷ������2^(n+1)-1����㣬ÿ�����ΪO��n)���ռ临�Ӷ�ΪO(n*2^(n+1))
	������ָ�����洢���׺����ҽڵ㣬�õ����Ž���������,����ÿ����㱣�������
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 10;

struct Node
{
	int cv, rv;//��ǰ��ֵ��ʣ���ֵ
	int rw;//ʣ������
	int id;//���������
	bool x[N];//���Ž�����
	Node() {
		memset(x, 0, sizeof(x));//��������ʼ��Ϊ0
	}
	Node(int _cv, int _rv, int _rw, int _id) {
		cv = _cv;
		rv = _rv;
		rw = _rw;;
		id = _id;
	}
};
struct Goods
{
	int value;
	int weight;
}goods[N];
int bestp,bestx[N], W, n, sumw, sumv;
/*
	bestpΪ��¼����ֵ
	bestxΪ���Ž�
	W��¼����
	sumw��¼��Ʒ������
	sumv��¼��Ʒ�ܼ�ֵ
*/
void bfs() {
	int t, tcv, trv, trw;//��Ϊ��ʱֵ
	queue<Node> q;
	q.push(Node(0, sumv, W, 1));//��ͷ���ѹ��
	while (!q.empty()) {
		Node livenode, lnode, rnode;//�����������
		livenode = q.front();
		q.pop();
		t = livenode.id;
		//�������һ������û������
		if (t > n || livenode.rw == 0) {
			if (livenode.cv >= bestp) {//�������Ž�
				for (int i = 1; i <= n; i++) {
					bestx[i] = livenode.x[i];
				}
				bestp = livenode.cv;
			}
			continue;
		}
		//�Ƿ������޽纯���������������
		if (livenode.cv + livenode.rv < bestp)
			continue;
		//���浽��ʱֵ���������ʹ��
		tcv = livenode.cv;
		trv = livenode.rv-goods[t].value;//�����Ƿ����ʣ���ֵ��Ҫ��ȥ
		trw = livenode.rw;
		//��չ����
		if (trw >= goods[t].weight) {
			lnode.rw = trw - goods[t].weight;
			lnode.cv = tcv + goods[t].value;
			lnode = Node(lnode.cv, trv, lnode.rw, t + 1);
			for (int i = 1; i < t; i++) {
				lnode.x[i] = livenode.x[i];//���Ƹ��ڵ�Ľ�����
			}
			lnode.x[t] = true;//����t�����뱳��
			if (lnode.cv > bestp)
				bestp = lnode.cv;
			q.push(lnode);
		}
		//��չ�ҽ��
		//�Ƿ������޽纯������������
		if (tcv + trv < bestp)
			continue;
		rnode = Node(tcv, trv, trw, t + 1);
		for (int i = 1; i < t; i++) {
			rnode.x[i] = livenode.x[i];//���Ƹ��ڵ�Ľ�����
		}
		rnode.x[t] = false;
		q.push(rnode);
	}
}
int main() {
	cout << "������Ʒ�ĸ���:";
	cin >> n;
	cout << "���뱳��������:";
	cin >> W;
	cout << "����������Ʒ�������ͼ�ֵ:";
	for (int i = 1; i <= n; i++) {
		cin >> goods[i].weight >> goods[i].value;
		sumw += goods[i].weight;//����������
		sumv += goods[i].value;//�����ܼ�ֵ
	}
	if (sumw <= W) {
		bestp = sumv;
		cout << "���뱳��������ֵΪ:" << bestp << endl;
		cout << "��������Ʒ���뱳��" << endl;
		return 0;
	}
	bfs();
	cout << "���뱳��������ֵΪ:" << bestp << endl;
	cout << "���빺�ﳵ����Ʒ���Ϊ:";
	for (int i = 1; i <= n; i++)
	{
		if (bestx[i])
			cout << i << " ";
	}

	return 0;
}