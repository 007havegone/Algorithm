#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
const int N = 100;
const double INF = 1e8;
float kernel[N][N];//�洢�ǵ����Ա�
char FJL[N] = {};//�ǻ��������±�
char JL[N] = {};//���������±�
int n, m, i, j;
void print() {//��ӡ�����α�
	cout << endl;
	cout << "----------����������:----------" << endl;
	cout << "  ";
	cout << setw(7) << "b ";//setw������һ�δ�ӡ�Ŀ��
	for (i = 1; i <= m; i++)
		cout << setw(7) << "x" << FJL[i];
	cout << endl;
	cout << "c ";
	for (i = 0; i <= n; i++)
	{
		if (i >= 1)
			cout << "x" << JL[i];
		for (j = 0; j <= m; j++)
			cout << setw(7) << kernel[i][j] << " ";
		cout << endl;
	}
}
void DCXA() {
	float max1;//max1�洢���ļ�����
	float max2;//max2�洢�������������Ӧ�Ļ������������ϵ��
	int e = -1;
	int k = -1;
	float min;//�����������
	//ѭ��ֱ����������Ž���޽�
	while (true) {
		max1 = 0;
		max2 = 0;
		min = INF;
		for (i = 1; i <= m; i++) {//��������������������е����ֵ
			if (kernel[0][i] > max1) {
				max1 = kernel[0][i];
				e = i;
			}
		}
		if (max1 <= 0)//���ֵ<=0(����������)�������м�����<=0,�������Ž�����
		{
			cout << endl;
			cout << "������Ž�:" << kernel[0][0] << endl;
			print();
			break;
		}
		for (j = 1; j <= m; j++) {//�ж���������(������������������)��С�ڵ���0�����޽��
			max2 = 0;
			if (kernel[0][j] > 0)
			{
				for (i = 1; i <= n; i++) 
					if (max2 < kernel[i][j])
						max2 = kernel[i][j];
				if (max2 == 0)//���ֵΪ0������������������Ӧ�ж�С�ڵ���0,�޽��
				{
					cout << "���޽�" << endl;
					return;//�������
				}
			}
		}
		for (i = 1; i <= n; i++) {//�������(��������/���������ֵ��С��Ӧ����)
			float temp = kernel[i][0] / kernel[i][e];
			if (temp > 0 && temp < min)
			{
				min = temp;
				k = i;
			}
		}
		cout << "�������: " << "x" << FJL[e] << " ";
		cout << "�������: " << "x" << JL[k] << endl;
		//�������(ת�ύ��)
		swap(FJL[e], JL[k]);

		for (i = 0; i <= n; i++)
		{
			if (i != k)//�������
			{
				for (j = 0; j <= m; j++)
				{
					if (j != e)//�������
					{
						if (i == 0 && j == 0) //����λC0����Ŀ�꺯����ֵ
							kernel[i][j] += kernel[i][e] * kernel[k][j] / kernel[k][e];
						else//һ��λ��
							kernel[i][j] -= kernel[i][e] * kernel[k][j] / kernel[k][e];
					}
				}
			}
		}
		for (i = 0; i <= n; i++)//��������λ�������
			if(i!=k)//�ǽ���λ
				kernel[i][e] = -kernel[i][e] / kernel[k][e];
		for (i = 0; i <= m; i++)//��������λ�������
			if (i != e)//�ǽ���λ
				kernel[k][i] = kernel[k][i] / kernel[k][e];
		kernel[k][e] = 1 / kernel[k][e];//��������λ������λ��
		print();//��ӡ��֤
	}
}

int main() {
	int i, j;
	cout << "����ǻ������������ͷǻ��������±�:" << endl;
	cin >> m;
	for (int i = 1; i <= m; i++)
		cin >> FJL[i];
	cout << "������������ĸ����ͻ����������±�:" << endl;
	cin >> n;
	for (i = 1; i <= n; i++)
		cin >> JL[i];
	cout << "����Լ����׼�ͳ�ʼ�����α����:" << endl;
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= m; j++)
			cin >> kernel[i][j];
	}
	print();
	DCXA();
	return 0;
}