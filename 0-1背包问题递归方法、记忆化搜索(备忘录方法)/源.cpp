#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20;//�����Ʒ��
const int maxn = 100;//��󱳰�����
int w[N], v[N];
//1�����ݹ飬Ч�ʽϵͣ����ظ�������
int solveKs(int w[],int v[],int index,int capacity) {
	if (index < 0 || capacity <= 0) {
		return 0;
	}
	//���費����
	int ret = solveKs(w, v, index - 1, capacity);
	if (capacity >= w[index]) {//������������
		ret = max(ret, v[index] + solveKs(w, v, index - 1, capacity - w[index]));
	}
	return ret;
}
int knapsack(int w[], int v[], int len, int C) {
	return solveKs(w, v, len - 1, C);
}
/*
	2�����仯����(����¼����),��̬�淶��һ�ֱ��Σ��Զ����£�����̬�滮�Ե�����
	�Ƚϣ�
		���д������������������ʱ���ñ���¼������ʡʱ��������������������ֻ���ٲ��ֻ�ȫ����Ҫ����ʱ��
		�õ��Ʒ�������̬�滮������ȱ���¼����Ҫ��(��������ˣ����Ŷ���������)��
	*/

int remem[N][maxn+1];//remem[i][j]ǰi+1����Ʒ����Ϊj������ֵ,��Ʒ��Ŵ�0��ʼ
int solveKs2(int w[], int v[], int index, int capacity) {
	if (index < 0 || capacity <= 0)
		return 0;
	//������������⣬ֱ�ӷŻر��ڵ�ֵ
	if (remem[index][capacity]) {
		return remem[index][capacity];
	}
	int ret = solveKs2(w, v, index - 1, capacity);
	if (capacity >= w[index])
		ret = max(ret, solveKs2(w, v, index - 1, capacity - w[index]) + v[index]);
	return ret;
}
int knapsack2(int w[], int v[], int len, int C) {
	memset(remem, 0, sizeof(remem));
	return solveKs2(w, v, len - 1, C);
}
int main()
{
	int w[] = { 2,5,4,2,3 };
	int v[] = { 6,3,5,4,6 };
	size_t sz = sizeof(w) / sizeof(int);
	//cout << "����ֵΪ:" << knapsack(w, v, sz, 10);
	cout << "����ֵΪ:" << knapsack2(w, v, sz, 10);
	return 0;
}