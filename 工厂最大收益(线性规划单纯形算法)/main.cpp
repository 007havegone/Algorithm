#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
const int N = 100;
const double INF = 1e8;
float kernel[N][N];//存储非单纯性表
char FJL[N] = {};//非基本变量下标
char JL[N] = {};//基本变量下标
int n, m, i, j;
void print() {//打印单纯形表
	cout << endl;
	cout << "----------单纯表如下:----------" << endl;
	cout << "  ";
	cout << setw(7) << "b ";//setw设置下一次打印的宽度
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
	float max1;//max1存储最大的检验数
	float max2;//max2存储最大正检验数对应的基本变量的最大系数
	int e = -1;
	int k = -1;
	float min;//用于找离基行
	//循环直到问题的最优解或无解
	while (true) {
		max1 = 0;
		max2 = 0;
		min = INF;
		for (i = 1; i <= m; i++) {//找入基变量，即检验数中的最大值
			if (kernel[0][i] > max1) {
				max1 = kernel[0][i];
				e = i;
			}
		}
		if (max1 <= 0)//最大值<=0(包括无穷多解)，即所有检验数<=0,满足最优解条件
		{
			cout << endl;
			cout << "获得最优解:" << kernel[0][0] << endl;
			print();
			break;
		}
		for (j = 1; j <= m; j++) {//判断如果入基列(即最大的正检验数那列)都小于等于0，则无界解
			max2 = 0;
			if (kernel[0][j] > 0)
			{
				for (i = 1; i <= n; i++) 
					if (max2 < kernel[i][j])
						max2 = kernel[i][j];
				if (max2 == 0)//最大值为0，即满足正检验数对应列都小于等于0,无界解
				{
					cout << "解无界" << endl;
					return;//程序结束
				}
			}
		}
		for (i = 1; i <= n; i++) {//找离基行(即常数列/入基列正比值最小对应的行)
			float temp = kernel[i][0] / kernel[i][e];
			if (temp > 0 && temp < min)
			{
				min = temp;
				k = i;
			}
		}
		cout << "入基变量: " << "x" << FJL[e] << " ";
		cout << "离基变量: " << "x" << JL[k] << endl;
		//变基交换(转轴交换)
		swap(FJL[e], JL[k]);

		for (i = 0; i <= n; i++)
		{
			if (i != k)//非离基行
			{
				for (j = 0; j <= m; j++)
				{
					if (j != e)//非入基列
					{
						if (i == 0 && j == 0) //特殊位C0，即目标函数的值
							kernel[i][j] += kernel[i][e] * kernel[k][j] / kernel[k][e];
						else//一般位置
							kernel[i][j] -= kernel[i][e] * kernel[k][j] / kernel[k][e];
					}
				}
			}
		}
		for (i = 0; i <= n; i++)//计算特殊位，入基列
			if(i!=k)//非交叉位
				kernel[i][e] = -kernel[i][e] / kernel[k][e];
		for (i = 0; i <= m; i++)//计算特殊位，离基行
			if (i != e)//非交叉位
				kernel[k][i] = kernel[k][i] / kernel[k][e];
		kernel[k][e] = 1 / kernel[k][e];//计算特殊位，交叉位置
		print();//打印验证
	}
}

int main() {
	int i, j;
	cout << "输入非基本变量个数和非基本变量下标:" << endl;
	cin >> m;
	for (int i = 1; i <= m; i++)
		cin >> FJL[i];
	cout << "输入基本变量的个数和基本变量的下标:" << endl;
	cin >> n;
	for (i = 1; i <= n; i++)
		cin >> JL[i];
	cout << "输入约束标准型初始单纯形表参数:" << endl;
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= m; j++)
			cin >> kernel[i][j];
	}
	print();
	DCXA();
	return 0;
}