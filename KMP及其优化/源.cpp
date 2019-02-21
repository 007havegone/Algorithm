/*
	本程序实现的KMP算法对串的存储位置从0开始
	临界点即模式串j前面没有任何符合相同子串时，设next[j]=-1
	输入输出返回的位序从1开始
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1000;
int Next[N];
int NextVal[N];
//最好 O（n+m） n为主串长度，m为模式串长度
//最坏 O（n*m）
int index_BF(const string& s,const string& t, int pos) {//pos开始查找点，位序从1开始
	int i = pos - 1, j = 0;
	int lens = s.length();
	int lent = t.length();
	while (i < lens&&j < lent) {
		if (s[i] == t[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == lent)return i - lent + 1;//返回的位序从1开始
	return 0;
}
//时间复杂度 O（m+n）
/*
	设模式串为t，假设第j个发生不匹配的next[j]=k
*/
void getNext(string str) {
	int i = 0;
	int j = -1;//保存第j个位置的next值
	Next[0] = -1;//设置临界点next[0]=-1
	int len = str.length();
	while (i < len) {
		if (j == -1 || str[i] == str[j]) {//直到临界点或者t[k]=t[j]则next[j+1]=next[j]+1
			i++;
			j++;
			Next[i] = j;
		}
		else
			j = Next[j];//否则相当于自身作为模式串和主串，查看t[next[k]]与t[j]的关系
	}
}
//optimal
void getNextVal(string str) {
	int i = 0;
	int j = -1;
	NextVal[0] = -1;
	int len = str.length();
	while (i < len) {
		if (j == -1 || str[i] == str[j]) {
			i++, j++;
			/*如果当第j个位置发生不匹配，且有t[j]=t[k],因为如果当t[j]与主串s[i]不匹配，不必要再与t[k]即t[next[j]]项比较，而是
			  与t[next[k]]相比较，即 next[j]= k'= next[k]
			*/
			if (str[i] != str[j]) {
				NextVal[i] = j;
			}else
				NextVal[i] = NextVal[j];
		}
		else
			j = NextVal[j];
	}
}
int index_KMP(const string& str, const string& t, int pos) {
	int i = pos - 1, j = 0;
	int lens = str.length();
	int lent = t.length();
	while (i < lens&& j < lent) {
		if (j == -1 || str[i] == t[j]) {
			i++;
			j++;
		}
		else
			j = NextVal[j];
	}
	if (j == lent)
		return i - lent + 1;
	return 0;
}
/*
	BF算法之所以仍在使用，虽然时间复杂度为O（m*n）,但实际使用中接近O（m+n）
	KMP算法只有在主串和模式串之间存在很多部分匹配的情况下（则主串i的指针需要回溯），才会
	显得比BF算法快得多。但是KMP算法最大的特点是指示主串的指针无须回溯，整个过程只需对主串从
	头到尾扫描一遍，对处理外设输入庞大的文件很有效，可以边读便匹配
*/
int main() {
	string s = "HelloHelloabaaccWorld";
	string t = "abaacc";
	getNext(t);
	getNextVal(t);
	cout << "next arr:";
	for (int i = 0; i < 6; i++)
		cout << Next[i]<<" ";
	cout << endl;
	cout << "nextVal arr:";
	for (int i = 0; i < 6; i++)
		cout << NextVal[i]<<" ";
	cout << endl;
	cout << index_BF(s, t, 1) << endl;
	cout << index_KMP(s, t, 1) << endl;
}