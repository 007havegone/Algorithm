#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
��Ա����
	vector<int> info �ɸõ���������б߹��ɵ�����ı�
	vector<int> next ��������һ����to�����λ��
	vector<int> to to[i]��ʾ���Ϊi�ı�ָ��Ľ��
��Ա����
	Graph(int n,int m) ��ʼ��Ϊn�����㣬m����
	add(int u,int v) ���һ����u��v�ı�

*/
struct Graph {
	typedef vector<int> VI;
	//using VI = vector<int>;	//c++11֧��
	VI info, next, to;
	
	Graph(int n = 0, int m = 0) :to(0), next(0) {
		info.resize(n);
		next.resize(m);
		next.resize(m);
	}

	int edge_size()	//���رߵ�����
	{
		return to.size();
	}

	int vertex_size()	//����ֵΪ����ı��+1����Ŵ�0��ʼ
	{
		return info.size();
	}
	void expand(int i) 
	{
		if (info.size() < i + 1)
			info.resize(i + 1);
	}
	void add(int i, int j)	//���һ��i��j�ı�
	{
		expand(i), expand(j);//�Ƿ���Ҫ��չ�ڴ�
		to.push_back(j);//ѹ���յ�����
		next.push_back(info[i]);
		info[i] = to.size() - 1;//����iΪ����һ���ڱ�
	}
	void del_back()	//ɾ�����һ����ӵı�
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
	void clear()	//���ͼ��
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