#include <iostream>
using namespace std;
#define MAXVEX 20
#define ERROR -1
#include <queue>
typedef char VexType;
bool visited[MAXVEX] = { false };

typedef struct adjmatrix
{
	VexType vexs[MAXVEX];
	int matrix[MAXVEX][MAXVEX];
	int vexNum;
	int edgeNum;
}AdjMatrix, * UG;
//创建
void crtUG(UG& G)
{
	//初始化边数
	G = new AdjMatrix;
	G->edgeNum = 10;
	//初始化顶点、顶点数
	string vexSeed = "ABCDEFGHI";
	G->vexNum = vexSeed.size();
	for (int i = 0; i < G->vexNum; i++)
	{
		G->vexs[i] = vexSeed[i];
	}
	//初始化边
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{

			G->matrix[i][j] = 0;
		}
	}
	//示例UG：AB,AD,AE,BC,BD,CF,DG,EG,GH,HI
	for (int i = 0; i < G->vexNum; i++)
	{
		if (i == 0)
		{
			G->matrix[i][1] = 1;
			G->matrix[i][3] = 1;
			G->matrix[i][4] = 1;
			G->matrix[1][i] = 1;
			G->matrix[3][i] = 1;
			G->matrix[4][i] = 1;
		}
		else if (i == 1)
		{
			G->matrix[i][2] = 1;
			G->matrix[i][3] = 1;
			G->matrix[2][i] = 1;
			G->matrix[3][i] = 1;
		}
		else if (i == 2)
		{
			G->matrix[i][5] = 1;
			G->matrix[5][i] = 1;
		}
		else if (i == 3)
		{
			G->matrix[i][6] = 1;
			G->matrix[6][i] = 1;
		}
		else if (i == 4)
		{
			G->matrix[i][6] = 1;
			G->matrix[6][i] = 1;
		}
		else if (i == 6)
		{
			G->matrix[i][7] = 1;
			G->matrix[7][i] = 1;
		}
		else if (i == 7)
		{
			G->matrix[i][8] = 1;
			G->matrix[8][i] = 1;
		}
	}
}
//获取顶点位置
int vexLocate(const UG& G, VexType k)
{
	if (!G)
	{
		return ERROR;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		if (G->vexs[i] == k)
		{
			return i;
		}
	}
	return ERROR;
}
//广度优先遍历
bool BFS(const UG& G, VexType v)
{
	if (!G)
	{
		return false;
	}
	int v0 = vexLocate(G, v);
	if (v0 == ERROR)
	{
		return false;
	}
	//访问起始节点，入队
	cout << G->vexs[v0] << " ";
	visited[v0] = true;
	queue<int> q;
	q.push(v0);
	while (!q.empty())
	{
		//弹出
		q.pop();
		//访问v0周边顶点，依次入队
		for (int i = 0; i < G->vexNum; i++)
		{
			if (G->matrix[v0][i] && !visited[i])
			{
				cout << G->vexs[i] << " ";
				visited[i] = true;
				q.push(i);
			}
		}
		//v0指向队头
		if (!q.empty())
		{
			v0 = q.front();
		}
	}
	return true;
}
int main()
{
	UG G;
	crtUG(G);
	BFS(G, 'A');
	system("pause");
	return 0;
}