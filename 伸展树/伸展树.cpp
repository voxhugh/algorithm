#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct splayTreeNode
{
	ElemType val;
	splayTreeNode* LeftChild, * RightChild, * Parent;//����һ����ָ��
}SplayNode,*SplayTree;
//����
void createSplayTree(SplayTree& root, SplayNode* p)
{
	char ch;
	cin >> ch;
	if (ch == '.')
	{
		root = NULL;
		return;
	}
	root = new SplayNode;
	root->val = ch - '0';
	root->Parent = p;
	createSplayTree(root->LeftChild,root);
	createSplayTree(root->RightChild,root);
}
//����
SplayNode*& zag(SplayNode*& T)
{
	if (T->Parent)
	{
		T->LeftChild->Parent = T->Parent;
		T->Parent->RightChild = T->LeftChild;
		T->LeftChild = T->Parent;
		T->Parent = T->LeftChild->Parent;
		T->LeftChild->Parent = T;
	}
	return T;
}
//����
SplayNode*& zig(SplayNode*& T)
{
	if (T->Parent)
	{
		T->RightChild->Parent = T->Parent;
		T->Parent->LeftChild = T->RightChild;
		T->RightChild = T->Parent;
		T->Parent = T->RightChild->Parent;
		T->RightChild->Parent = T;
	}
	return T;
}
int main()
{
	SplayTree spt;
	createSplayTree(spt,NULL);
	system("pause");
	return 0;
}