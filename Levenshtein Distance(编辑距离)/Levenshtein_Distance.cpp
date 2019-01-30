/*
	�༭���룬�ֳ�Levenshtein���룬��ָ�����ִ�֮�䣬��һ��ת����һ����������ٱ༭����������
	��ɵı༭����������һ���ַ��滻����һ���ַ�������һ���ַ���ɾ��һ���ַ���

	diff = ( s1[i-1]==s2[j-1] )
	d[i][j] = min(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+diff(i,j))
*/

#include <iostream>
#include <cstring>
using namespace std;
const int N = 100;
char s1[N], s2[N];
int d[N][N];//d[i][j]��ʾs1ǰi���ַ���s2ǰj���ַ��ı༭����
int len1;
int len2;
int min(int a, int b)
{
	return a < b ? a : b;
}

int Levenshtein_Dis(char *str1, char*str2)
{
	len1 = strlen(str1);//���㳤��
	len2 = strlen(str2);
	for (int i = 0; i <= len1; i++)//��2�����ĳ���Ϊ0����ʼ�༭����Ϊi
		d[i][0] = i;
	for (int j = 0; j <= len2; j++)//��һ�����ĳ���Ϊ0����ʼ�༭����Ϊj
		d[0][j] = j;
	for(int i=1;i<=len1;i++)
		for (int j = 1; j <= len2; j++)
		{
			int diff;
			if (str1[i - 1] == str2[j - 1])
				diff = 0;
			else
				diff = 1;
			d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + diff);
		}
	return d[len1][len2];
}
void howToEdit(int i,int j)
{
	if (!i || !j)
		return;
	int diff;
	if (s1[i - 1] == s2[j - 1])
		diff = 0;
	else
		diff = 1;
	if (d[i - 1][j - 1] + diff == d[i][j]){//�����滻
		howToEdit(i - 1, j - 1);
		if(diff)
			cout << "replace " << s1[i - 1] << " to " << s2[j - 1] << endl;
	}
	else if (d[i][j - 1] + 1 == d[i][j]) {//���Ϊ����
		howToEdit(i, j - 1);
		cout << "insert " << s2[j - 1] << "before "<< s1[i] << endl;
	}
	else {//�����ʾɾ��
		howToEdit(i - 1, j);
		cout << "delete " << s1[i - 1] << endl;
	}
}
int main()
{
	cout << "�����ַ���s1: " << endl;
	cin >> s1;
	cout << "�����ַ���s2: " << endl;
	cin >> s2;
	cout << s1 << "��" << s2 << "�ı༭������:" << Levenshtein_Dis(s1, s2) << endl;
	howToEdit(len1, len2);
	return 0;

}