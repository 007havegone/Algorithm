#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1000;
int Next[N];
int NextVal[N];
int index_BF(const string& s,const string& t, int pos) {//pos开始查找点
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
	if (j == lent)return i - lent + 1;
	return 0;
}
void getNext(string str) {
	int i = 0;
	int j = -1;
	Next[0] = -1;
	int len = str.length();
	while (i < len) {
		if (j == -1 || str[i] == str[j]) {
			i++;
			j++;
			Next[i] = j;
		}
		else
			j = Next[j];
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