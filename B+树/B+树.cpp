#include <iostream>
using namespace std;
#define M 4 //阶数
#define UNAVAILABLE -1
typedef int ElemType;

typedef struct bpnode
{
	ElemType keys[M];	//M个key
	struct bpnode* kids[M];	//M颗子树
	int keyNum;		//key数
	struct bpnode* next;	//叶子结点的兄弟指针
}BPNode, * BPTree;
//生成结点并初始化
BPNode* newNode()
{
	BPNode* N = new BPNode;
	for (int i = 0; i < M; i++)
	{
		N->keys[i] = UNAVAILABLE;
		N->kids[i] = NULL;
	}
	N->keyNum = 0;
	N->next = NULL;
	return N;
}
//初始化
void initBPTree(BPTree& root)
{
	if (M < 3)
	{
		cout << "M最小三阶！" << endl;
		return;
	}
	root = newNode();
}
//寻最左叶结点
BPNode*& findMostLeft(BPTree& root)
{
	if (root->kids[0])
	{
		return findMostLeft(root->kids[0]);
	}
	return root;
}
//寻最右叶结点
BPNode*& findMostRight(BPTree& root)
{
	if (root->kids[M - 1])
	{
		return findMostRight(root->kids[M - 1]);
	}
	return root;
}
int main()
{
	BPTree bpt;
	initBPTree(bpt);
	system("pause");
	return 0;
}
