#include <iostream>
using namespace std;
#define ElemType char
typedef struct avlnode
{
	ElemType val;//值
	struct avlnode* LeftChild, * RightChild;//左右孩子
	int bf;//平衡因子
}AVLTreeNode,*AVLTree;
//创建	先序
void createAVL(AVLTree& root)
{
	ElemType ch;
	cin >> ch;
	if (ch == '.')
	{
		root = NULL;
		return;
	}
	root = new AVLTreeNode;
	root->val = ch;
	root->bf = 0;
	createAVL(root->LeftChild);
	createAVL(root->RightChild);
}
//插入	重构为平衡二叉树
void insertAVLTree(AVLTree& root, ElemType k)
{
	//首先为插入结点S开辟空间
	AVLTreeNode* S = new AVLTreeNode;
	S->val = k;
	S->bf = 0;
	S->RightChild = S->LeftChild = NULL;
	//树为空
	if (!root)
	{
		root = S;
		return;
	}
	//树非空，准备指针
	AVLTreeNode* A = root;//A：距离插入位置最近的bf非零的结点
	AVLTreeNode* FA = NULL;
	AVLTreeNode* p = root;
	AVLTreeNode* fp = NULL;
	//寻找插入位置，寻找A
	while (p)
	{
		if (p->bf)
		{
			A = p;
			FA = fp;
		}
		fp = p;
		if (k < p->val)
		{
			p = p->LeftChild;
		}
		else
		{
			p = p->RightChild;
		}
	}
	//插入S
	if (k < fp->val)
	{
		fp->LeftChild = S;
	}
	else
	{
		fp->RightChild = S;
	}
	//确定B，更新A的bf
	AVLTreeNode* B = NULL;//B：S所在子树的根结点
	if (k < A->val)
	{
		B = A->LeftChild;
		A->bf++;
	}
	else
	{
		B = A->RightChild;
		A->bf--;
	}
	//更新B~S路径上所有结点的bf
	p = B;
	while (p)
	{
		if (k < p->val)
		{
			p->bf = 1;
			p = p->LeftChild;
		}
		else
		{
			p->bf = -1;
			p = p->RightChild;
		}
	}
	//判断失衡类型并调整

	if (A->bf == 2 && B->bf == 1)//LL型
	{
		A->LeftChild = B->RightChild;
		B->RightChild = A;
		//更新bf（A：2->0	B：1->0）
		A->bf = 0;
		B->bf = 0;
		if (!FA)//A为根节点
		{
			root = B;
		}
		else if (FA->LeftChild == A)//A为FA的左孩子
		{
			FA->LeftChild = B;
		}
		else//A为FA的右孩子
		{
			FA->RightChild = B;
		}
	}
	else if (A->bf == -2 && B->bf == -1)//RR型
	{
		A->RightChild = B->LeftChild;
		B->LeftChild = A;
		A->bf = 0;
		B->bf = 0;
		if (!FA)
		{
			root = B;
		}
		else if (FA->LeftChild == A)
		{
			FA->LeftChild = B;
		}
		else
		{
			FA->RightChild = B;
		}
	}
	else if (A->bf == 2 && B->bf == -1)//LR型
	{
		AVLTreeNode* C = B->RightChild;
		B->RightChild = C->LeftChild;
		A->LeftChild = C->RightChild;
		C->LeftChild = B;
		C->RightChild = A;
		//判断S所在C的分支
		if (k < C->val)
		{
			A->bf = -1;
			B->bf = 0;
			C->bf = 0;
		}
		else if (k > C->val)
		{
			A->bf = 0;
			B->bf = 1;
			C->bf = 0;
		}
		else
		{
			A->bf = 0;
			B->bf = 0;
		}
		if (!FA)
		{
			root = C;
		}
		else if (FA->LeftChild == A)
		{
			FA->LeftChild = C;
		}
		else
		{
			FA->RightChild = C;
		}
	}
}
int main()
{
	AVLTree avlt;
	createAVL(avlt);
	/*	LL：421..3..5..[0]
		RR：21..43..5..[6]
		LR：721..53..6..8..[4]	*/
	insertAVLTree(avlt,4);
	system("pause");
	return 0;
}