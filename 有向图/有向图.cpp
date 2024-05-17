#include <iostream>
using namespace std;
#define MAX 100
#define ERROR -1
typedef char VexType;

typedef struct graph
{
	VexType vexs[MAX];//顶点集合
	int matrix[MAX][MAX];//邻接矩阵
	int vexNum;//顶点个数
	int arcNum;//边数
}Graph, * DGraph;
//获取顶点位置
int vexLocate(const DGraph& G, VexType vex)
{
	for (int i = 0; i < G->vexNum; i++)
	{
		if (G->vexs[i] == vex)
		{
			return i;
		}
	}
	return ERROR;
}
//创建
bool crtGraph(DGraph& G)
{
	G = new Graph;
	//输入顶点数
	int vNum = 0;
	cout << "顶点数：" << endl;
	cin >> vNum;
	if (vNum<0 || vNum>MAX)
	{
		return false;
	}
	G->vexNum = vNum;
	//输入边数
	cout << "边数：" << endl;
	int aNum = 0;
	cin >> aNum;
	if (aNum<0 || aNum>MAX * MAX)
	{
		return false;
	}
	G->arcNum = aNum;
	//初始化邻接矩阵
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			G->matrix[i][j] = 0;
		}
	}
	//读入顶点
	for (int i = 0; i < G->vexNum; i++)
	{
		cout << "V" << i + 1 << "：" << endl;
		cin >> G->vexs[i];
	}
	//读入边
	cout << "Arcs：" << endl;
	for (int i = 0; i < G->arcNum; i++)
	{
		string nowArc;
		cin >> nowArc;
		int p1 = vexLocate(G, nowArc[0]);
		int p2 = vexLocate(G, nowArc[1]);
		G->matrix[p1][p2] = 1;
	}
	return true;
}
//打印有向图
void printDGraph(const DGraph& G)
{
	if (!G->vexNum || !G->arcNum)
	{
		return;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		cout << G->vexs[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			cout << G->matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
int main()
{
	DGraph G;
	crtGraph(G);
	printDGraph(G);
	system("pause");
	return 0;
}