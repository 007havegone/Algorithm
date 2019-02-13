/*
https://vjudge.net/problem/POJ-3468
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define lchild k<<1
#define rchild lchild|1
typedef long long LL;
using namespace std;
const int N = 100000 << 2 | 1;
int n, m;
LL num[N];
struct Node
{
	int l, r;
	LL lz, w;
}tree[N];
void build(int k, int L, int R) {
	tree[k].lz = 0;
	tree[k].l = L;
	tree[k].r = R;
	if (L == R) {
		tree[k].w = num[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(lchild, L, mid);
	build(rchild, mid+1, R);
	tree[k].w = tree[lchild].w + tree[rchild].w;
}
void down(int k) {
	tree[lchild].lz += tree[k].lz;
	tree[rchild].lz += tree[k].lz;
	tree[lchild].w += (tree[lchild].r - tree[lchild].l + 1)*tree[k].lz;
	tree[rchild].w += (tree[rchild].r - tree[rchild].l + 1)*tree[k].lz;
	tree[k].lz = 0;
}
void update(int k, int L, int R, LL val) {
	if (L <= tree[k].l&&tree[k].r <= R) {
		tree[k].lz += val;
		tree[k].w += val * (tree[k].r - tree[k].l + 1);
		return;
	}
	if (tree[k].lz)down(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (L <= mid)update(lchild, L, R, val);
	if (R > mid)update(rchild, L, R, val);
	tree[k].w = tree[lchild].w + tree[rchild].w;
}
LL Query(int k, int L, int R) {
	if (L <= tree[k].l&&tree[k].r <= R) {
		return tree[k].w;
	}
	if (tree[k].lz)down(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	LL ans = 0;
	if (L <= mid)ans += Query(lchild, L, R);
	if (R > mid)ans += Query(rchild, L, R);
	return ans;
}
int main()
{
	string temp;
	LL x, y, z;
	while (cin >> n >> m) {
		for (int j = 1; j <= n; j++) {
			scanf("%lld", &num[j]);
		}
		build(1, 1, n);
		while (m--) {
			cin >> temp;
			switch (temp[0]) {
			case 'C':
				scanf("%lld%lld%lld", &x, &y, &z);
				update(1, x, y, z);
				break;
			case 'Q':
				scanf("%lld%lld", &x, &y);
				printf("%lld\n", Query(1, x, y));
				break;
			}
		}
	}
}
