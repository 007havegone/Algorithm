#include <iostream>
#include <vector>
#include <functional>
using namespace std;
//c++ oj优化
class Solution {
private:
	int fact(int n) {
		int ans = 1;
		for (int i = 1; i <= n; ++i) ans *= i;
		return ans;
	}
public:
	vector<vector<int>> permute(vector<int>& nums) {
		const int n = nums.size();
		vector<vector<int>> ans;
		ans.reserve(fact(n));

		std::function<void(vector<int>&, int)> permutation =
			[&ans, n, &permutation](vector<int>& nums, int k) {
			if (k == n - 1) ans.push_back(nums);
			for (int i = k; i < n; ++i) {
				std::swap(nums[k], nums[i]);
				permutation(nums, k + 1);
				std::swap(nums[k], nums[i]);
			}
		};
		permutation(nums, 0);
		return ans;
	}
};
const int N = 10;
int n;
int cnt = 0;
int x[N];
void Backtrack(int t) {
	if (t > n) {
		cnt++;
		for (int i = 1; i <= n; i++)
			cout << x[i] << " ";
		cout << endl;
		return;
	}
	for (int i = t; i <= n; i++) {
		swap(x[i], x[t]);
		Backtrack(t + 1);
		swap(x[i], x[t]);
	}

}
int main() {
	cout << "输入数字的个数:";
	cin >> n;
	cout << "依次输入数字:";
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	Backtrack(1);
	cout << "全排列个数为:" << cnt << endl;
}