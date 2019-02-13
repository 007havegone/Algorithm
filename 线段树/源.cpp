#include <iostream>
#include <string>
#include <algorithm>
#define lchild k<<1
#define rchild lchild|1
using namespace std;
const int N = 100000 << 2 | 1;
struct Node
{
	int l, r, w, lz;
}tree[N];

void down(int k) {
	tree[lchild].lz += tree[k].lz;
	tree[rchild].lz += tree[k].lz;
	tree[lchild].w += (tree[lchild].r - tree[lchild].l + 1)*tree[k].lz;
	tree[rchild].w += (tree[rchild].r - tree[rchild].l + 1)*tree[k].lz;
	tree[k].lz = 0;
}
void build(int k, int L, int R) {
	tree[k].lz = 0;
	tree[k].l = L;
	tree[k].r = R;
	if (L == R) {
		cin >> tree[k].w;
		return;
	}
	int mid = (L + R) >> 1;
	build(lchild, L, mid);
	build(rchild, mid + 1, R);
	tree[k].w = tree[lchild].w + tree[rchild].w;
}
//将[L,R]的每个数加上val
void update(int k, int L, int R, int val) {
	if (L <= tree[k].l&&tree[k].r <= R) {
		tree[k].w += (tree[k].r - tree[k].l + 1)*val;
		tree[k].lz += val;
		return;
	}
	if (tree[k].lz)down(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (L <= mid)update(lchild, L, R, val);
	if (R > mid)update(rchild, L, R, val);
	tree[k].w = tree[lchild].w + tree[rchild].w;
}
int query(int k, int L, int R) {
	if (L <= tree[k].l&&tree[k].r <= R) {
		return tree[k].w;
	}
	if (tree[k].lz)down(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	int ans = 0;
	if (L <= mid)ans += query(lchild, L, R);
	if (R > mid)ans += query(rchild, L, R);
	return ans;
}
int main() {
	int n;
	int t;
	string c;
	int a, b, val;
	cin >> n;
	cin >> t;
	build(1, 1, n);
	while (t--) {
		cin >> c;
		if (c[0] == 'Q') {
			cin >> a >> b;
			cout << query(1, a, b) << endl;
		}
		else if (c[0] == 'A') {
			cin >> a >> b >> val;
			update(1, a, b, val);
		}
	}
}