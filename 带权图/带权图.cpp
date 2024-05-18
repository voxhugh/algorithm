#include <iostream>
using namespace std;
#define MAXVEX 20
#define ERROR -1
typedef char VexType;

typedef struct arcnode
{
	int toVex;//��ͷ��������
	int weight;//Ȩ��
	struct arcnode* next;//ָ����һ������
}ArcNode;//�߱�

typedef struct vexnode
{
	VexType vex;//����
	ArcNode* firstVex;//ָ���һ�����
}VexNode;//�����

typedef struct adjlist
{
	int vexNum;//������
	int arcNum;//����
	VexNode* Vexs;//ά�������
}AdjList, * DN;//�ڽӱ�

//��ȡ����λ��
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
//����һ���߽��
ArcNode*& newArc(int vId, int w)
{
	ArcNode* theArc = new ArcNode;
	theArc->toVex = vId;
	theArc->weight = w;
	theArc->next = NULL;
	return theArc;
}
//����
void crtDN(DN& N)
{
	//��ʼ�����㡢������
	N = new AdjList;
	string vexSeed = "ABCDEF";
	N->vexNum = vexSeed.size();
	N->arcNum = 10;
	//��ʼ�������
	N->Vexs = new VexNode[MAXVEX];
	for (int i = 0; i < N->vexNum; i++)
	{
		N->Vexs[i].vex = vexSeed[i];
		N->Vexs[i].firstVex = NULL;
	}
	//��ʼ���߱�

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
//����
void dropDN(DN& N)
{
	//ɾ���߱�
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
	//ɾ�������
	delete[]N->Vexs;
	N->Vexs = NULL;
	//ɾ��������
	delete N;
	N = NULL;
}
//��ȡ�������
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
//ɾ����
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
	//δ�ҵ�
	if (P == NULL || P->toVex != v2Id)
	{
		return false;
	}
	//��һ������
	else if (FP == P)
	{
		N->Vexs[v1Id].firstVex = NULL;
	}
	//�ҵ�
	else
	{
		FP->next = P->next;
	}
	delete P;
	N->arcNum--;
	return true;
}
//��ӡ
void printDN(const DN& N)
{
	for (int i = 0; i < N->vexNum; i++)
	{
		cout << N->Vexs[i].vex;
		ArcNode* P = N->Vexs[i].firstVex;
		while (P)
		{
			cout << " ��> " << N->Vexs[P->toVex - 1].vex << "[" << P->weight << "]";
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