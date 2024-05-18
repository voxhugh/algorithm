#include <iostream>
using namespace std;
#define MAXVEX 20
#define ERROR -1
typedef char VexType;

typedef struct arcnode
{
	int toVex;//弧头顶点索引
	int weight;//权重
	struct arcnode* next;//指向下一个顶点
}ArcNode;//边表

typedef struct vexnode
{
	VexType vex;//顶点
	ArcNode* firstVex;//指向第一个结点
}VexNode;//顶点表

typedef struct adjlist
{
	int vexNum;//顶点数
	int arcNum;//弧数
	VexNode* Vexs;//维护顶点表
}AdjList, * DN;//邻接表

//获取顶点位置
int vexLocate(const DN& N, VexType v)
{
	for (int i = 0; i < N->vexNum; i++)
	{
		if (N->Vexs[i].vex == v)
		{
			return i;
		}
	}
	return ERROR;
}
//生成一个边结点
ArcNode*& newArc(int vId, int w)
{
	ArcNode* theArc = new ArcNode;
	theArc->toVex = vId;
	theArc->weight = w;
	theArc->next = NULL;
	return theArc;
}
//创建
void crtDN(DN& N)
{
	//初始化顶点、弧个数
	N = new AdjList;
	string vexSeed = "ABCDEF";
	N->vexNum = vexSeed.size();
	N->arcNum = 10;
	//初始化顶点表
	N->Vexs = new VexNode[MAXVEX];
	for (int i = 0; i < N->vexNum; i++)
	{
		N->Vexs[i].vex = vexSeed[i];
		N->Vexs[i].firstVex = NULL;
	}
	//初始化边表

	//A
	N->Vexs[0].firstVex = newArc(2, 5);
	N->Vexs[0].firstVex->next = newArc(4, 7);
	//B
	N->Vexs[1].firstVex = newArc(3, 4);
	//C
	N->Vexs[2].firstVex = newArc(1, 8);
	N->Vexs[2].firstVex->next = newArc(6, 9);
	//D
	N->Vexs[3].firstVex = newArc(3, 5);
	N->Vexs[3].firstVex->next = newArc(6, 6);
	//E
	N->Vexs[4].firstVex = newArc(4, 5);
	//F
	N->Vexs[5].firstVex = newArc(1, 2);
	N->Vexs[5].firstVex->next = newArc(5, 1);
}
//销毁
void dropDN(DN& N)
{
	//删除边表
	for (int i = 0; i < N->vexNum; i++)
	{
		ArcNode* P = N->Vexs[i].firstVex;
		while (P)
		{
			ArcNode* temp = P;
			P = P->next;
			delete temp;
		}
	}
	//删除顶点表
	delete[]N->Vexs;
	N->Vexs = NULL;
	//删除有向网
	delete N;
	N = NULL;
}
//获取顶点出度
int getOD(const DN& N, VexType v)
{
	int vId = vexLocate(N, v);
	if (vId == ERROR)
	{
		return ERROR;
	}
	ArcNode* P = N->Vexs[vId].firstVex;
	int num = 0;
	while (P)
	{
		num++;
		P = P->next;
	}
	return num;
}
//删除弧
bool delArc(DN& N, VexType v1, VexType v2)
{
	int v1Id = vexLocate(N, v1);
	int v2Id = vexLocate(N, v2);
	if (v1Id == ERROR || v2Id == ERROR)
	{
		return false;
	}
	ArcNode* P = N->Vexs[v1Id].firstVex;
	ArcNode* FP = P;
	while (P)
	{
		if (P->toVex == v2Id)
		{
			break;
		}
		FP = P;
		P = P->next;
	}
	//未找到
	if (P == NULL || P->toVex != v2Id)
	{
		return false;
	}
	//第一个即是
	else if (FP == P)
	{
		N->Vexs[v1Id].firstVex = NULL;
	}
	//找到
	else
	{
		FP->next = P->next;
	}
	delete P;
	N->arcNum--;
	return true;
}
//打印
void printDN(const DN& N)
{
	for (int i = 0; i < N->vexNum; i++)
	{
		cout << N->Vexs[i].vex;
		ArcNode* P = N->Vexs[i].firstVex;
		while (P)
		{
			cout << " —> " << N->Vexs[P->toVex - 1].vex << "[" << P->weight << "]";
			P = P->next;
		}
		cout << endl;
	}
}
int main()
{
	DN N;
	crtDN(N);
	printDN(N);
	system("pause");
	return 0;
}