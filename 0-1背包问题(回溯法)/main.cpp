/*
	�����㷨��ƣ�
	1�����������ռ� ��1�������֯��ʽ��һ��ΪnԪ��	��2����Լ�����Խ������ȡֵ��Χ���޶������ƽ�ռ�Ĵ�С
	2��ȷ����ռ����֯��ʽ�������ڹ۲������ռ�Ĵ�С����ռ��Ϊ�Ӽ����������顢m������
	3��������ռ�	������Լ������֦����������Լ���������޽纯����ǰ��Ϊ�ܷ�õ����н⣬����Ϊ�ܷ�õ����Ž⡣

	��ռ�Ĵ�С�ͼ�֦�����ĺû�ֱ��Ӱ������Ч�ʣ��������������㷨�Ĺؼ�

*/

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1007;
bool x[N];//��¼��Ʒ��ѡ�����
double w[N],v[N];//��¼��Ʒ�������ͼ�ֵ
int n, W;//��Ʒ�����ͱ�������
int bestc[N];//��¼���Ž�
double bestV;//���ż�ֵ
double cw;//��ǰ����
double cv;//��ǰ��ֵ

int bound(int i) {
	double rv = 0;//ʣ���i��n��Ʒ�ļ�ֵ
	while (i <= n) {
		rv += v[i];
		i++;
	}
	return rv + cv;
}
void Backtrack(int t) {//�����ռ�����t��ʾ��ǰ��չ����ڵ�t��
	if (t > n) {//�����n+1�㼴Ҷ�ӣ���Ϊ���޽纯�����ܴﵽ�ײ���һ�������Ž�
		for (int i = 1; i <= n; i++)
			bestc[i] = x[i];
		bestV = cv;
		return;
	}
	if (cw + w[t] <= W) {//Լ��������ȷ�����н�
		x[t] = 1;
		cw += w[t];
		cv += v[t];
		Backtrack(t + 1);
		//x[t] = 0;//�ɼӿɲ��ӣ���������������
		cw -= w[t];
		cv -= v[t];
	}
	if (bound(t + 1) > bestV) {//�޽������������ҳ����Ž�
		x[t] = 0;
		Backtrack(t + 1);
	}
}

void Knapsack(int W,int n) {
	cw = 0;//��ʼ�������ͼ�ֵΪ0
	cv = 0;
	bestV = 0;//��ʼ�����Ž�Ϊ0
	double sumw = 0.0;
	double sumv = 0.0;
	for (int i = 1; i <= n; i++) {
		sumw += w[i];
		sumv += v[i];
	}
	if (sumw <= W) {//�ܷ���ȫ����ֱ�ӷ���
		bestV = sumv;
		cout << "���뱳������Ʒ����ֵΪ:" << bestV << endl;
		cout << "������Ʒ���뱳��" << endl;
		return;
	}
	/*for (int i = 1; i <= n; i++) {//���س�ʼ�������������кͳ�״̬�޹�
		bestc[i] = x[i] = 0;
	}*/
	Backtrack(1);
	cout << "���뱳������Ʒ����ֵΪ:" << bestV << endl;
	cout << "���뱳������Ʒ���Ϊ:";
	for (int i = 1; i <= n; i++) {
		if (bestc[i])
			cout << i << " ";
	}
}
int main() {
	cout << "������Ʒ������:";
	cin >> n;
	cout << "���뱳��������:";
	cin >> W;
	cout << "������Ʒ�������ͼ۸񣨿ո������:";
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];
	Knapsack(W,n);

	return 0;
}