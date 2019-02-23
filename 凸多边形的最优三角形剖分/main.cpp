#include <iostream>
using namespace std;
const int N = 1007;
int g[N][N];//g[i][j]��ʾai-1 ��aj-1�ľ��룬�±��0��ʼ
int m[N][N];//m[i][j] Ϊ{ai-1,ai,ai+1....aj},��i=j����ʾһ���ң�Ϊ0,��1��ʼ�洢
int s[N][N];//�洢���Ų��ԣ���1��ʼ�洢

void Init(int n)
{
	//s[i][i]->{ai-1,ai}
	for (int i = 1; i <= n; i++)//�������ʼ��a0-a1 a1-a2Ϊ0
		s[i][i] = m[i][i] = 0;
}
void Convexpolygontriangulation(int n) {
	Init(n);
	int d, k, j, i;
	for (d = 2; d <= n;d++) {//�����ģΪ2,��������
		for (i = 1; i <= n - d + 1; i++) {
			j = i + d - 1;
			//i-1 i i+1 ... i+k.. j
			//������1��i-1...k		������2��k...j	���ϣ�i-1 ->k  k -> j	i-1 -> j
			m[i][j] = m[i + 1][j] + g[i - 1][i] + g[i - 1][j] + g[i][j];//��k=i
			s[i][j] = i;
			for (k = i + 1; k < j; k++) {
				int temp = m[i][k] + m[k + 1][j] + g[i - 1][k] + g[i - 1][j] + g[k][j];
				if (temp < m[i][j]) {
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
}
void print(int i, int j)
{
	if (i == j)//Ϊ1����ai-1 ai����
		return;
	int k = s[i][j];//����ֽ��
	if (k > i)//������3����
		cout << "{ V" << i - 1 << "  V" << k << " }" << endl;
	if (j > k + 1)//������3����
		cout << "{ V" << k << "  V" << j << " }" << endl;
	print(i, k);
	print(k + 1, j);

}
int main()
{
	int n;
	cout << "���붥�����:";
	cin >> n;
	n--;
	cout << "��������ߵĹ�ϵ�� a0-a1 a0-a2 ... an-2-an-1 : " << endl;
	for(int i=0;i<=n;i++)
		for (int j = 0; j <=n; j++)
		{
			cin >> g[i][j];
		}
	Convexpolygontriangulation(n);
	cout << m[1][n] << endl;
	//��֤
	/*for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << s[i][j] << " ";
		cout << endl;
	}*/
	print(1, n);//a0-an�ĵ�

	return 0;
}