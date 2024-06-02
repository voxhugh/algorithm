#include <iostream>
using namespace std;
typedef char VexType;

typedef struct arc
{
	int fromV;
	struct arc* next;
}Arc;
typedef struct vex
{
	VexType v;
	Arc* In;
}Vex;
typedef struct
{
	int vNum;
	Vex* vs;
}iAdjList, * DAG;

Arc* newArc(int v)
{
	Arc* A = new Arc;
	A->fromV = v;
	A->next = NULL;
	return A;
}
int vexLocate(const DAG& G, VexType v)
{
	for (int i = 0; i < G->vNum; i++)
	{
		if (G->vs[i].v == v)
		{
			return i;
		}
	}
	return -1;
}
void crtDAG(DAG& G)
{
	G = new iAdjList;
	string vexSeed = "ABCDE";
	G->vNum = vexSeed.size();
	G->vs = new Vex[G->vNum];
	for (int i = 0; i < G->vNum; i++)
	{
		G->vs[i].v = vexSeed[i];
	}
	//AB AD BC BD CE DC DE
	G->vs[0].In = NULL;
	G->vs[1].In = newArc(0);
	G->vs[2].In = newArc(1);
	G->vs[2].In->next = newArc(3);
	G->vs[3].In = newArc(0);
	G->vs[3].In->next = newArc(1);
	G->vs[4].In = newArc(2);
	G->vs[4].In->next = newArc(3);
}
void deleteV(DAG& G, int i)
{
	G->vs[i].v = '.';
	for (int j = 0; j < G->vNum; j++)
	{
		if (G->vs[j].v == '.' || G->vs[j].In == NULL)
		{
			continue;
		}
		Arc* p = G->vs[j].In;
		Arc* f = NULL;
		while (p)
		{
			f = p;
			if (p->fromV == i)
			{
				break;
			}
			p = p->next;
		}
		if (f == p)
		{
			G->vs[j].In = NULL;
			delete p;
			p = NULL;
		}
		else if (p)
		{
			f->next = p->next;
			delete p;
			p = NULL;
		}
	}
}
void topoSort(DAG& G)
{
	for (int i = 0; i < G->vNum; i++)
	{
		if (G->vs[i].v != '.' && G->vs[i].In == NULL)
		{
			cout << G->vs[i].v << " ";
			deleteV(G, i);
			i = 0;
		}
	}
	cout << endl;
}
int main()
{
	DAG G;
	crtDAG(G);
	topoSort(G);
	system("pause");
	return 0;
}