#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
成员变量
	vector<int> info 由该点出发的所有边构成的链表的表
	vector<int> next 链表中下一条在to数组的位置
	vector<int> to to[i]表示编号为i的边指向的结点
成员函数
	Graph(int n,int m) 初始化为n个顶点，m条边
	add(int u,int v) 添加一条从u到v的边

*/
struct Graph {
	typedef vector<int> VI;
	//using VI = vector<int>;	//c++11支持
	VI info, next, to;
	
	Graph(int n = 0, int m = 0) :to(0), next(0) {
		info.resize(n);
		next.resize(m);
		next.resize(m);
	}

	int edge_size()	//返回边的数量
	{
		return to.size();
	}

	int vertex_size()	//返回值为最大点的编号+1，编号从0开始
	{
		return info.size();
	}
	void expand(int i) 
	{
		if (info.size() < i + 1)
			info.resize(i + 1);
	}
	void add(int i, int j)	//添加一条i到j的边
	{
		expand(i), expand(j);//是否需要拓展内存
		to.push_back(j);//压入终点数组
		next.push_back(info[i]);
		info[i] = to.size() - 1;//更新i为起点第一条邻边
	}
	void del_back()	//删除最后一次添加的边
	{
		int i;
		for(i=0;i<info.size();i++)
			if (info[i] == to.size() - 1) {
				info[i] = next.back();
				break;
			}
		to.pop_back();
		next.pop_back();
	}
	void clear()	//清空图类
	{
		info.clear();
		to.resize(0);
		next.resize(0);
	}

};

int main()
{
	Graph g;
}