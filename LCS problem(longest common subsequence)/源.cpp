/* dynamic programming 
	find the longest commomn subsequence
	c[i][j]= 0	i=0 or j=0
			c[i]+c[j]  i、j>0 and x[i]=y[j]
			max{c[i][j-1],c[i-1][j]} i、j>0 and x[i] != y[j]
*/

#include <iostream>
#include <cstring>
using namespace std;

const int N = 1002;
int c[N][N], b[N][N];
char s1[N], s2[N];
int len1, len2;

void LCSL()
{
	int i, j;
	for(i=1;i<=len1;i++)
		for (j = 1; j <= len2; j++)
		{
			if (s1[i - 1] == s2[j - 1])
			{//当前字符相同，长度为该字符前的最长序列+1
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else {
				if (c[i][j - 1] >= c[i - 1][j])
				{
					c[i][j] = c[i][j - 1];
					b[i][j] = 2;
				}
				else
				{
					c[i][j] = c[i - 1][j];
					b[i][j] = 3;
				}
			}
		}
}
void Init()
{
	for (int i = 0; i <= len1; i++)
		c[i][0] = 0;
	for (int i = 0; i <= len2; i++)
		c[0][i] = 0;
}
void print(int i, int j)
{
	if (i==0||j==0)	return;
	if (b[i][j] == 1)
	{
		print(i - 1, j - 1);
		cout << s1[i - 1];
	}
	else if (b[i][j] == 2)
		print(i, j - 1);
	else
		print(i - 1, j);
}
int main()
{
	cout << "输入字符串 s1:" << endl;
	cin >> s1;
	cout << "输入字符串 s2:" << endl;
	cin >> s2;
	len1 = strlen(s1);
	len2 = strlen(s2);
	//cout << len1 << " " << len2 << endl;
	Init();
	LCSL();
	cout << "s1 和 s2 的最长公共子序列长度是:" << c[len1][len2] << endl;
	cout << "s1 和 s2 的最长公共子序列是:";
	print(len1, len2);
	return 0;
}

