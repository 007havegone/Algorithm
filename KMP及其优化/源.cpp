/*
	������ʵ�ֵ�KMP�㷨�Դ��Ĵ洢λ�ô�0��ʼ
	�ٽ�㼴ģʽ��jǰ��û���κη�����ͬ�Ӵ�ʱ����next[j]=-1
	����������ص�λ���1��ʼ
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1000;
int Next[N];
int NextVal[N];
//��� O��n+m�� nΪ�������ȣ�mΪģʽ������
//� O��n*m��
int index_BF(const string& s,const string& t, int pos) {//pos��ʼ���ҵ㣬λ���1��ʼ
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
	if (j == lent)return i - lent + 1;//���ص�λ���1��ʼ
	return 0;
}
//ʱ�临�Ӷ� O��m+n��
/*
	��ģʽ��Ϊt�������j��������ƥ���next[j]=k
*/
void getNext(string str) {
	int i = 0;
	int j = -1;//�����j��λ�õ�nextֵ
	Next[0] = -1;//�����ٽ��next[0]=-1
	int len = str.length();
	while (i < len) {
		if (j == -1 || str[i] == str[j]) {//ֱ���ٽ�����t[k]=t[j]��next[j+1]=next[j]+1
			i++;
			j++;
			Next[i] = j;
		}
		else
			j = Next[j];//�����൱��������Ϊģʽ�����������鿴t[next[k]]��t[j]�Ĺ�ϵ
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
			/*�������j��λ�÷�����ƥ�䣬����t[j]=t[k],��Ϊ�����t[j]������s[i]��ƥ�䣬����Ҫ����t[k]��t[next[j]]��Ƚϣ�����
			  ��t[next[k]]��Ƚϣ��� next[j]= k'= next[k]
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
	BF�㷨֮��������ʹ�ã���Ȼʱ�临�Ӷ�ΪO��m*n��,��ʵ��ʹ���нӽ�O��m+n��
	KMP�㷨ֻ����������ģʽ��֮����ںܶಿ��ƥ�������£�������i��ָ����Ҫ���ݣ����Ż�
	�Եñ�BF�㷨��öࡣ����KMP�㷨�����ص���ָʾ������ָ��������ݣ���������ֻ���������
	ͷ��βɨ��һ�飬�Դ������������Ӵ���ļ�����Ч�����Ա߶���ƥ��
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