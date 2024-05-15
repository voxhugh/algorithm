#include <iostream>
using namespace std;
#define M 4 //����
#define UNAVAILABLE -1
typedef int ElemType;

typedef struct bpnode
{
	ElemType keys[M];		//M��key
	struct bpnode* kids[M];	//M������
	int keyNum;				//key��
	struct bpnode* next;	//Ҷ�ӽ����ֵ�ָ��
}BPNode, * BPTree;
//���ɽ�㲢��ʼ��
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
//��ʼ��
void initBPTree(BPTree& root)
{
	if (M < 3)
	{
		cout << "M��С���ף�" << endl;
		return;
	}
	root = newNode();
}
//Ѱ����Ҷ���
BPNode*& findMostLeft(BPTree& root)
{
	if (root->kids[0])
	{
		return findMostLeft(root->kids[0]);
	}
	return root;
}
//Ѱ����Ҷ���
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