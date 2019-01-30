/*
	编辑距离，又称Levenshtein距离，是指两个字串之间，由一个转成另一个所需的最少编辑操作次数。
	许可的编辑操作包括将一个字符替换成另一个字符，插入一个字符，删除一个字符。

	diff = ( s1[i-1]==s2[j-1] )
	d[i][j] = min(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+diff(i,j))
*/

#include <iostream>
#include <cstring>
using namespace std;
const int N = 100;
char s1[N], s2[N];
int d[N][N];//d[i][j]表示s1前i个字符和s2前j个字符的编辑距离
int len1;
int len2;
int min(int a, int b)
{
	return a < b ? a : b;
}

int Levenshtein_Dis(char *str1, char*str2)
{
	len1 = strlen(str1);//计算长度
	len2 = strlen(str2);
	for (int i = 0; i <= len1; i++)//第2个串的长度为0，初始编辑距离为i
		d[i][0] = i;
	for (int j = 0; j <= len2; j++)//第一个串的长度为0，初始编辑距离为j
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
	if (d[i - 1][j - 1] + diff == d[i][j]){//优先替换
		howToEdit(i - 1, j - 1);
		if(diff)
			cout << "replace " << s1[i - 1] << " to " << s2[j - 1] << endl;
	}
	else if (d[i][j - 1] + 1 == d[i][j]) {//左侧为插入
		howToEdit(i, j - 1);
		cout << "insert " << s2[j - 1] << "before "<< s1[i] << endl;
	}
	else {//上面表示删除
		howToEdit(i - 1, j);
		cout << "delete " << s1[i - 1] << endl;
	}
}
int main()
{
	cout << "输入字符串s1: " << endl;
	cin >> s1;
	cout << "输入字符串s2: " << endl;
	cin >> s2;
	cout << s1 << "和" << s2 << "的编辑距离是:" << Levenshtein_Dis(s1, s2) << endl;
	howToEdit(len1, len2);
	return 0;

}