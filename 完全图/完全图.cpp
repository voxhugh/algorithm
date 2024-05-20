#include <iostream>
using namespace std;
#define MAXVEX 20
#define ERROR -1
typedef char VexType;

typedef struct arcnode
{
	int vTail, vHead;//弧尾，弧头
	struct arcnode* nextH, * nextT;//弧头兄弟，弧尾兄弟
}ArcNode;//弧结点

typedef struct vexnode
{
	VexType vex;//顶点
	ArcNode* firstIn, * firstOut;//首个入度，首个出度
}VexNode;//顶点结点

typedef struct ortholist
{
	int vexNum;
	int arcNum;
	VexNode* vexs;//维护顶点表
}OrthoList, * DCG;//十字链表

//生成弧结点
ArcNode*& newAN(int t, int h, ArcNode* nH = NULL, ArcNode* nT = NULL)
{
	ArcNode* theAN = new ArcNode;
	theAN->vTail = t;
	theAN->vHead = h;
	theAN->nextH = nH;
	theAN->nextT = nT;
	return theAN;
}
//创建
void crtDCG(DCG& G)
{
	int rank;
	cout << "有向完全图顶点数：" << endl;
	cin >> rank;
	if (rank<1 || rank>MAXVEX)
	{
		cout << "不合法！" << endl;
		return;
	}
	//顶点种子
	string vexSeed = "ABCDEFGHIJKLMNOPQRST";
	//初始化顶点数、弧数
	G = new OrthoList;
	G->vexNum = rank;
	G->arcNum = rank * (rank - 1);
	//初始化顶点表
	G->vexs = new VexNode[MAXVEX];
	for (int i = 0; i < G->vexNum; i++)
	{
		G->vexs[i].vex = vexSeed[i];
		G->vexs[i].firstIn = NULL;
		G->vexs[i].firstOut = NULL;
	}
	//初始化弧
	for (int i = 0; i < G->vexNum; i++)
	{
		//初始化弧头、弧尾、弧尾兄弟
		G->vexs[i].firstOut = newAN(i, (i + 1) % G->vexNum);
		ArcNode* now = G->vexs[i].firstOut;
		for (int j = 1; j < G->vexNum - 1; j++)
		{
			now->nextT = newAN(i, (i + j + 1) % G->vexNum);
			now = now->nextT;
		}
	}
	//初始化firstIn
	for (int i = 0; i < G->vexNum; i++)
	{
		ArcNode* P = NULL;
		//查找顶点的firstIn
		for (int j = 0; j < G->vexNum; j++)
		{
			if (G->vexs[j].firstOut == NULL || j == i)
			{
				continue;
			}
			P = G->vexs[j].firstOut;
			while (P)
			{
				if (P->vHead == i)
				{
					break;
				}
				P = P->nextT;
			}
		}
		//赋值
		G->vexs[i].firstIn = P;
	}
	//初始化nextH	同初始化firstIn，这里不再实现
}
//获取顶点位置
int vexLocate(const DCG& G, VexType v)
{
	if (!G || !G->vexs)
	{
		return ERROR;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		if (G->vexs[i].vex == v)
		{
			return i;
		}
	}
	return ERROR;
}
//获取顶点度
int vexDegree(DCG& G, VexType v)
{
	int vId = vexLocate(G, v);
	if (vId == ERROR)
	{
		return ERROR;
	}
	//获取出度
	int OD = 0;
	ArcNode* P = G->vexs[vId].firstOut;
	while (P)
	{
		OD++;
		P = P->nextT;
	}
	//获取入度
	int ID = 0;
	for (int i = 0; i < G->vexNum; i++)
	{
		if (i == vId)
		{
			continue;
		}
		P = G->vexs[i].firstOut;
		while (P)
		{
			if (P->vHead == vId)
			{
				ID++;
			}
		}
	}
	return OD + ID;
}
//打印
void printDCG(const DCG& G)
{
	if (!G || !G->vexs)
	{
		cout << "ERROR!" << endl;
		return;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		cout << G->vexs[i].vex << ":\t";
		ArcNode* P = G->vexs[i].firstOut;
		while (P)
		{
			cout << G->vexs[P->vHead].vex << " ";
			P = P->nextT;
		}
		cout << endl;
	}
}
int main()
{
	DCG G;
	crtDCG(G);
	printDCG(G);
	system("pause");
	return 0;
}