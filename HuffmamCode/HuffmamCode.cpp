/*
 realize the huffmam code and improve by priority_queue
 run on O(nlogn)
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXLEAF = 30;
const int MAXNODE = MAXLEAF * 2 - 1;
const int MAXBIT = 100;
#define MAXVALUE 10000;

typedef struct HfNode {
	double weight;
	char value;
	int parents;
	int left;
	int right;
	int i;
}HuffNodeType;
struct Comp {
	//按weight从小到大排序 
	bool operator()(const HuffNodeType* h1, const HuffNodeType* h2)
	{
		return h1->weight > h2->weight;
	}
};

typedef struct HfCode {
	int bits[MAXBIT];
	int sta;//开始存放位置 
}HuffCodeType;

HuffCodeType HuffCode[MAXLEAF];
HuffNodeType HuffNode[MAXNODE];

void HuffTreeImprove(HuffNodeType *HuffNode, int n)
{
	double m1, m2;
	int x1, x2;
	for (int i = 0; i < MAXNODE; i++)
	{
		HuffNode[i].left = -1;
		HuffNode[i].right = -1;
		HuffNode[i].parents = -1;
		HuffNode[i].weight = 0;
		HuffNode[i].i = i;
	}
	for (int i = 0; i < n; i++)
		cin >> HuffNode[i].value >> HuffNode[i].weight;
	priority_queue<HuffNodeType*, vector<HuffNodeType*>, Comp> que;
	for (int i = 0; i < n; i++)
		que.push(&HuffNode[i]);

	for (int i = 0; i < n - 1; i++)
	{
		HuffNodeType* p1 = que.top(); que.pop(); x1 = p1->i; m1 = p1->weight;
		HuffNodeType* p2 = que.top(); que.pop(); x2 = p2->i; m2 = p2->weight;
		HuffNode[x1].parents = i + n;
		HuffNode[x2].parents = i + n;
		HuffNode[i + n].left = x1;
		HuffNode[i + n].right = x2;
		HuffNode[i + n].weight = m1 + m2;

		que.push(HuffNode + i + n);
		cout << m1 << " " << m2 << endl;
	}
}
void HuffTreeInit(HuffNodeType *HuffNode, int n) {
	double m1, m2;//存放质量 
	int x1, x2;//存放位置
	//初始化 
	for (int i = 0; i < MAXNODE; i++)
	{
		HuffNode[i].left = -1;
		HuffNode[i].right = -1;
		HuffNode[i].parents = -1;
		HuffNode[i].weight = 0;
	}
	//读取 
	for (int i = 0; i < n; i++)
		cin >> HuffNode[i].value >> HuffNode[i].weight;

	for (int i = 0; i < n - 1; i++)//进行n-1次构建 
	{
		m1 = m2 = MAXVALUE;
		x1 = x2 = 0;
		for (int j = 0; j < n + i; j++)
		{
			if (m1 > HuffNode[j].weight&&HuffNode[j].parents == -1)
			{
				m2 = m1;
				x2 = x1;
				m1 = HuffNode[j].weight;
				x1 = j;
			}
			else if (m2 > HuffNode[j].weight&&HuffNode[j].parents == -1)
			{
				m2 = HuffNode[j].weight;
				x2 = j;
			}
		}
		HuffNode[n + i].weight = m1 + m2;
		HuffNode[n + i].left = x1;
		HuffNode[n + i].right = x2;
		HuffNode[x1].parents = HuffNode[x2].parents = n + i;
		cout << m1 << " " << m2 << endl;
	}
}
void GetHuffCode(HuffCodeType *HuffCode, int n)
{
	HuffCodeType cd;       /* 定义一个临时变量来存放求解编码时的信息 */
	int i, j, c, p;
	for (i = 0; i < n; i++)
	{
		cd.sta = n - 1;
		c = i;
		p = HuffNode[c].parents;
		while (p != -1)
		{
			if (HuffNode[p].left == c)
				cd.bits[cd.sta] = 0;
			else
				cd.bits[cd.sta] = 1;
			cd.sta--;        /*前移一位 */
			c = p;
			p = HuffNode[c].parents;    /* 设置下一循环条件 */
		}
		/* 把叶子结点的编码信息从临时编码cd中复制出来，放入编码结构体数组 */
		for (j = cd.sta + 1; j < n; j++)
			HuffCode[i].bits[j] = cd.bits[j];
		HuffCode[i].sta = cd.sta + 1;
	}
}
int main() {
	int n;
	cout << "输入结点个数\n";
	cin >> n;
	//	HuffTreeInit(HuffNode,n);
	HuffTreeImprove(HuffNode, n);//优先队列优化 
	GetHuffCode(HuffCode, n);
	for (int i = 0; i < n; i++)
	{
		cout << HuffNode[i].value << "  Huffman code is :";
		for (int j = HuffCode[i].sta; j < n; j++)
			cout << HuffCode[i].bits[j];
		cout << endl;
	}
	return 0;
}