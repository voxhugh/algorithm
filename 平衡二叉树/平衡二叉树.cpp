#include <iostream>
using namespace std;
#define ElemType char
typedef struct avlnode
{
	ElemType val;//ֵ
	struct avlnode* LeftChild, * RightChild;//���Һ���
	int bf;//ƽ������
}AVLTreeNode,*AVLTree;
//����	����
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
//����	�ع�Ϊƽ�������
void insertAVLTree(AVLTree& root, ElemType k)
{
	//����Ϊ������S���ٿռ�
	AVLTreeNode* S = new AVLTreeNode;
	S->val = k;
	S->bf = 0;
	S->RightChild = S->LeftChild = NULL;
	//��Ϊ��
	if (!root)
	{
		root = S;
		return;
	}
	//���ǿգ�׼��ָ��
	AVLTreeNode* A = root;//A���������λ�������bf����Ľ��
	AVLTreeNode* FA = NULL;
	AVLTreeNode* p = root;
	AVLTreeNode* fp = NULL;
	//Ѱ�Ҳ���λ�ã�Ѱ��A
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
	//����S
	if (k < fp->val)
	{
		fp->LeftChild = S;
	}
	else
	{
		fp->RightChild = S;
	}
	//ȷ��B������A��bf
	AVLTreeNode* B = NULL;//B��S���������ĸ����
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
	//����B~S·�������н���bf
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
	//�ж�ʧ�����Ͳ�����

	if (A->bf == 2 && B->bf == 1)//LL��
	{
		A->LeftChild = B->RightChild;
		B->RightChild = A;
		//����bf��A��2->0	B��1->0��
		A->bf = 0;
		B->bf = 0;
		if (!FA)//AΪ���ڵ�
		{
			root = B;
		}
		else if (FA->LeftChild == A)//AΪFA������
		{
			FA->LeftChild = B;
		}
		else//AΪFA���Һ���
		{
			FA->RightChild = B;
		}
	}
	else if (A->bf == -2 && B->bf == -1)//RR��
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
	else if (A->bf == 2 && B->bf == -1)//LR��
	{
		AVLTreeNode* C = B->RightChild;
		B->RightChild = C->LeftChild;
		A->LeftChild = C->RightChild;
		C->LeftChild = B;
		C->RightChild = A;
		//�ж�S����C�ķ�֧
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
	/*	LL��421..3..5..[0]
		RR��21..43..5..[6]
		LR��721..53..6..8..[4]	*/
	insertAVLTree(avlt,4);
	system("pause");
	return 0;
}