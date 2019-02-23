/*
https://vjudge.net/problem/HDU-1698
*/
#include <iostream>
#include <cstdio>
#define lchild k<<1
#define rchild lchild|1
using namespace std;
const int N = 100000 << 2 | 1;
struct Node
{
	int l, r, w, lz;
}tree[N];

void build(int k, int l, int r) {
	tree[k].l = l;
	tree[k].r = r;
	tree[k].lz = 0;
	if (l == r) {
		tree[k].w = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tree[k].w = tree[lchild].w + tree[rchild].w;
}
void down(int k) {
	tree[lchild].lz = tree[rchild].lz = tree[k].lz;
	tree[lchild].w = tree[k].lz*(tree[lchild].r - tree[lchild].l + 1);
	tree[rchild].w = tree[k].lz*(tree[rchild].r - tree[rchild].l + 1);
	tree[k].lz = 0;
}
void update(int k, int L, int R, int val) {
	if (L <= tree[k].l&&tree[k].r <= R) {
		tree[k].w = val * (tree[k].r - tree[k].l + 1);
		tree[k].lz = val;
		return;
	}
	if (tree[k].lz)down(k);
	int mid = (tree[k].r + tree[k].l) >> 1;
	if (L <= mid)update(lchild, L, R, val);
	if (R > mid)update(rchild, L, R, val);
	tree[k].w = tree[lchild].w + tree[rchild].w;
}
int main() {
	int cases;
	int L, R, val;
	int n, t;
	int i = 1;
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d%d", &n, &t);
		build(1, 1, n);
		while (t--) {
			scanf("%d%d%d", &L, &R, &val);
			update(1, L, R, val);
		}
		printf("Case %d: The total value of the hook is %d.\n", i++, tree[1].w);
	}
}