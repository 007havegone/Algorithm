/*
	Divide and Conquer
	X = A*10^n + B
	Y = C*10^m + D
	X*Y = A*C*10^(n+m) + A*D*10^n + B*C*10^m + B*D

	T(n)={ O(1),n=1
	     { 4T(n/2)+O(n),n>1
	T(n)=O(n*2)


*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int M = 100;
//save to large nums
char sa[1000];
char sb[1000];

typedef struct _Node {
	int s[M];//if the M is pertty large,you need to define as global values;
	int l;//the length of s
	int c;//exponent
}Node,*pNode;
void cp(pNode src, pNode des, int st, int l)
{
	//src is to be divide into des
	//st is the startindex to get num from arr, l is the len to get
	int i, j;
	for (i = st, j = 0; i < st + l;i++,j++)
	{
		des->s[j] = src->s[i];
	}
	des->l = l;
	des->c = st + src->c;//the exponent is the startindex to getnum plus the src's exponent
}
/*
	Divide and Conquer
	X = A*10^n + B
	Y = C*10^m + D
	X*Y = A*C*10^(n+m) + A*D*10^n + B*C*10^m + B*D
*/
void add(pNode pa, pNode pb, pNode ans)
{
	int k,i;
	int palen, pblen, len;
	int ca, cb;//ca cb is the current plus num in the pa and pb
	
	if (pa->c < pb->c)//keep the pa's exponent is greater than pb's
		swap(pa, pb);

	ans->c = pb->c;//set the ans is the smaller exponent
	int cc = 0;//init the carry num to 0
	palen = pa->l + pa->c;
	pblen = pb->l + pb->c;
	len = max(palen, pblen);//get the max
	len -= ans->c;//set the ans length is the max length of pa,pb then sub the minumum exponen
	k = pa->c - pb->c;// k is the left_zero fixed to a
	for (i = 0; i < len; i++)
	{
		if (i < k)
			ca = 0;
		else
			ca = pa->s[i - k];
		if (i < pb->l)
			cb = pb->s[i];
		else
			cb = 0;
		if (i >= pa->l + k)
			ca = 0;
		ans->s[i] = (ca + cb + cc) % 10;
		cc = (ca + cb + cc) / 10;
	}
	if (cc)
		ans->s[i++] = cc;
	ans->l = i;
}
void mul(pNode pa, pNode pb, pNode ans)
{
	int w,cc,i;//w is temp to save,cc is the carry num
	int ma = pa->l >> 1, mb = pb->l >> 1;//get the half len of pa and pb
	Node ah, al, bh, bl;
	Node t1, t2, t3, t4, z;

	if (!ma || !mb)// one of them length is 1,start to mul
	{
		if (!ma)//swap a,b to keep the pa's length > pb's length
			swap(pa, pb);

		ans->c = pa->c + pb->c;
		w = pb->s[0];//save the pb first num
		cc=0;//Init to 0
		for (i = 0; i < pa->l; i++)
		{
			ans->s[i] = (w*pa->s[i] + cc) % 10;
			cc = (w*pa->s[i] + cc) / 10;
		}
		if (cc)
			ans->s[i++] = cc;//if have any exponent last to add
		ans->l = i;
		return;//finish this work
	}
	//if len both larger than 1
	//divide them and add
	cp(pa, &ah, ma, pa->l - ma);//divide into 4 part
	cp(pa, &al, 0, ma);
	cp(pb, &bh, mb, pb->l - mb);
	cp(pb, &bl, 0, mb);

	//multiply them
	mul(&ah, &bh, &t1);
	mul(&ah, &bl, &t2);
	mul(&al, &bh, &t3);
	mul(&al, &bl, &t4);

	//add them
	add(&t3, &t4, ans);
	add(&t2, ans, &z);
	add(&t1, &z, ans);
}
int main()
{
	Node ans, a, b;
	cout << "Enter the large num a: " << endl;
	cin >> sa;
	cout << "Enter the large num b: " << endl;
	cin >> sb;

	//set the len
	a.l = strlen(sa);
	b.l = strlen(sb);
	cout << a.l << " " << b.l << endl;
	//Init the char[] to the int[]
	for (int i = a.l - 1, z = 0; i >= 0; i--)
		a.s[z++] = sa[i]-'0';
	a.c = 0;//set the exponent
	for (int i = b.l - 1, z = 0; i >= 0; i--)
		b.s[z++] = sb[i]-'0';
	b.c = 0;//set the exponent
	for (int i = 0; i < a.l; i++)
		cout << a.s[i];
	cout << endl;
	for (int i = 0; i < b.l; i++)
		cout << b.s[i];
	//start to mul
	mul(&a, &b, &ans);
	cout << "the ans is ";
	for (int i = ans.l - 1; i >= 0; i--)
		cout << ans.s[i];
	cout << endl;
	return 0;
}