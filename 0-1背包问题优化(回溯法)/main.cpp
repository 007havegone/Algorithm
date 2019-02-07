/*
	�����㷨������ʱ��ȡ�����������������ɵĽ�������޽纯�����Դ��������ɽ��ĸ������Ӷ�����

	ԭ�����������Һ��ӽ�������Ϊ2^n-1��
	Լ������ʱ�临�Ӷ�ΪO��1�����޽纯��ʱ�临�Ӷ�ΪO��n����
	�ܵ�ʱ�临�Ӷ�ΪO��n*2^n+1*2^n)=O��n*2^n��

	�����������е��κ�ʱ�̣��������ӿ�ʼ��㵽��ǰ��չ����·�������ĳ���Ϊn��ͬʱʹ��bestc[]�����������Կռ临�Ӷ�ΪO��n����

	����ͨ������ԭ�ȵ��Ͻ纯���Ĺ�ֵ����С�Ͻ磬�Ӷ��ӿ���ٶȣ��������Ч�ʡ�
	��Ϊʣ���������ܻ�õ�����ֵ

	����Ʒ����λ�����ǵ�������Ȼ��������˳�򿼲������Ʒ
 */
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1005;//�����Ʒ��Ŀ
int i, j, n, W;//��Ʒ�����ͱ�������
double w[N], v[N];//��Ʒ�������ͼ۸�
bool x[N];//��¼��Ʒ�Ƿ����
bool bestX[N];//����ѡ��
double cw, cv;//��ǰ�������ͼ۸�
double bestV;//���ż�ֵ

//���޽纯�����Ͻ��С�����Լ���
double bound(int i) {
	double wleft = W - cw;//ʣ������
	double brv = 0.0;
	while (i <= n && w[i] < wleft)
	{
		wleft -= w[i];
		brv += v[i];
		i++;
	}
	if (i <= n) {//�����и�ķ�ʽװ�����������Ͻ硣
		brv += v[i] / w[i] * wleft;
	}
	return brv + cv;
}
void Backtrack(int t) {
	if (t > n) {//����Ҷ��
		bestV = cv;
		for ( i = 1; i <= n; i++) {
			bestX[i] = x[i];
		}
		return;
	}
	if (cw + x[t] <= W) {//����Լ����������������
		cw += w[t];
		cv += v[t];
		x[t] = 1;
		Backtrack(t + 1);
		cw -= w[t];
		cv -= v[t];
	}
	if (bound(t + 1) > bestV) {//�����޽���������������
		x[t] = 0;
		Backtrack(t + 1);
	}
}
struct Object
{
	int id;//��Ʒ���
	double d;//��λ�����۸�
	bool operator<(const Object& obj)const {//����λ�۸���
		return d > obj.d;
	}
};
void Knapsack(int W, int n) {
	cw = 0.0;
	cv = 0.0;
	bestV = 0.0;
	double sumw = 0.0;
	double sumv = 0.0;
	Object *Q = new Object[n];//��0��ʼ
	for (i = 1; i <= n; i++) {
		sumv += v[i];
		sumw += w[i];
		Q[i - 1].id = i;
		Q[i - 1].d = 1.0*v[i] / w[i];
	}
	if (sumw <= W) {
		bestV = sumv;
		cout << "���뱳������Ʒ����ֵΪ:" << bestV << endl;
		cout << "������Ʒ���뱳��" << endl;
		return;
	}
	sort(Q, Q + n);//����
	for (int i = 1; i <= n; i++) {//������ú�������ļ۸񴫵ݸ�ԭ����
		v[i] = v[Q[i - 1].id];
		w[i] = v[Q[i - 1].id];
	}
	Backtrack(1);
	cout << "���뱳������Ʒ����ֵΪ:" << bestV << endl;
	cout << "���뱳������Ʒ���Ϊ:";
	for (int i = 1; i <= n; i++)
		if (bestX[i]) {
			cout << Q[i - 1].id << " ";
		}
	cout << endl;
}
	
int main() {
	cout << "������Ʒ������:";
	cin >> n;
	cout << "���뱳��������:";
	cin >> W;
	cout << "������Ʒ�������ͼ۸񣨿ո������:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	Knapsack(W, n);

	return 0;
}
