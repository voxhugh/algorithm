#include <iostream>
using namespace std;
#define MAX 100
#define ERROR -1
typedef char VexType;

typedef struct graph
{
	VexType vexs[MAX];//���㼯��
	int matrix[MAX][MAX];//�ڽӾ���
	int vexNum;//�������
	int arcNum;//����
}Graph, * DGraph;
//��ȡ����λ��
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
//����
bool crtGraph(DGraph& G)
{
	G = new Graph;
	//���붥����
	int vNum = 0;
	cout << "��������" << endl;
	cin >> vNum;
	if (vNum<0 || vNum>MAX)
	{
		return false;
	}
	G->vexNum = vNum;
	//�������
	cout << "������" << endl;
	int aNum = 0;
	cin >> aNum;
	if (aNum<0 || aNum>MAX * MAX)
	{
		return false;
	}
	G->arcNum = aNum;
	//��ʼ���ڽӾ���
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			G->matrix[i][j] = 0;
		}
	}
	//���붥��
	for (int i = 0; i < G->vexNum; i++)
	{
		cout << "V" << i + 1 << "��" << endl;
		cin >> G->vexs[i];
	}
	//�����
	cout << "Arcs��" << endl;
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
//��ӡ����ͼ
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