#include <iostream>
using namespace std;
#define MAXVEX 20
#define ERROR -1
typedef char VexType;

typedef struct arcnode
{
	int vTail, vHead;//��β����ͷ
	struct arcnode* nextH, * nextT;//��ͷ�ֵܣ���β�ֵ�
}ArcNode;//�����

typedef struct vexnode
{
	VexType vex;//����
	ArcNode* firstIn, * firstOut;//�׸���ȣ��׸�����
}VexNode;//������

typedef struct ortholist
{
	int vexNum;
	int arcNum;
	VexNode* vexs;//ά�������
}OrthoList, * DCG;//ʮ������

//���ɻ����
ArcNode*& newAN(int t, int h, ArcNode* nH = NULL, ArcNode* nT = NULL)
{
	ArcNode* theAN = new ArcNode;
	theAN->vTail = t;
	theAN->vHead = h;
	theAN->nextH = nH;
	theAN->nextT = nT;
	return theAN;
}
//����
void crtDCG(DCG& G)
{
	int rank;
	cout << "������ȫͼ��������" << endl;
	cin >> rank;
	if (rank<1 || rank>MAXVEX)
	{
		cout << "���Ϸ���" << endl;
		return;
	}
	//��������
	string vexSeed = "ABCDEFGHIJKLMNOPQRST";
	//��ʼ��������������
	G = new OrthoList;
	G->vexNum = rank;
	G->arcNum = rank * (rank - 1);
	//��ʼ�������
	G->vexs = new VexNode[MAXVEX];
	for (int i = 0; i < G->vexNum; i++)
	{
		G->vexs[i].vex = vexSeed[i];
		G->vexs[i].firstIn = NULL;
		G->vexs[i].firstOut = NULL;
	}
	//��ʼ����
	for (int i = 0; i < G->vexNum; i++)
	{
		//��ʼ����ͷ����β����β�ֵ�
		G->vexs[i].firstOut = newAN(i, (i + 1) % G->vexNum);
		ArcNode* now = G->vexs[i].firstOut;
		for (int j = 1; j < G->vexNum - 1; j++)
		{
			now->nextT = newAN(i, (i + j + 1) % G->vexNum);
			now = now->nextT;
		}
	}
	//��ʼ��firstIn
	for (int i = 0; i < G->vexNum; i++)
	{
		ArcNode* P = NULL;
		//���Ҷ����firstIn
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
		//��ֵ
		G->vexs[i].firstIn = P;
	}
	//��ʼ��nextH	ͬ��ʼ��firstIn�����ﲻ��ʵ��
}
//��ȡ����λ��
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
//��ȡ�����
int vexDegree(DCG& G, VexType v)
{
	int vId = vexLocate(G, v);
	if (vId == ERROR)
	{
		return ERROR;
	}
	//��ȡ����
	int OD = 0;
	ArcNode* P = G->vexs[vId].firstOut;
	while (P)
	{
		OD++;
		P = P->nextT;
	}
	//��ȡ���
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
//��ӡ
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