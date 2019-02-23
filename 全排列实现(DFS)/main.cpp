#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> flag;
vector<int>ans;
int n;
void DFS(vector<int>&vec) {
	if (ans.size() == n) {
		for (auto i : ans) 
			cout << i << " ";
		cout << endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (flag[i] == 0) {
			flag[i] = 1;
			ans.push_back(vec[i]);
			DFS(vec);
			flag[i] = 0;
			ans.pop_back();
		}
	}
}
int main() {
	vector<int> nums = { 1,2,3 };
	n = nums.size();
	flag = vector<int>(n, 0);
	DFS(nums);
}