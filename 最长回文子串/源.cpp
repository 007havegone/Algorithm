#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1007;
int c[N][N];
pair<int, int> ans;
class Solution {
public:
	string longestPalindrome(string s) {
		int j, i, d;
		int len = s.length();
		if (len <= 1 || len == 2 && s[0] == s[1])
			return s;
		Init(len, s);
		for (d = 3; d <= len; d++) {
			for (i = 0; i < len - d + 1; i++) {
				j = i + d - 1;
				c[i][j] = c[i + 1][j - 1] && s[i] == s[j];
				if (c[i][j] && (j - i > ans.second - ans.first)) {
					ans.first = i;
					ans.second = j;
				}
			}
		}
		string ret = s.substr(ans.first, ans.second - ans.first + 1);//从first开始second-first+1个字符
		return ret;
	}
	void Init(int n, const string&s) {
		bool flag = 1;
		for (int i = 0; i < n; i++)
			c[i][i] = 1;//一个字符
		for (int i = 0; i < n - 1; i++) {
			c[i][i + 1] = (s[i] == s[i + 1]);//两个字符
			if (flag&&c[i][i + 1])
			{
				flag = 0;
				ans.first = i;
				ans.second = i + 1;
			}
		}
	}
};
int main() {

	Solution s;
	cout << s.longestPalindrome("adam");

}