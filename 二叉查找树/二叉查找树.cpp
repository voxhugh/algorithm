#include <iostream>
using namespace std;
typedef int ElemType;
#define ERROR -1

typedef struct bstnode
{
	ElemType val;
	struct bstnode* LeftChild, * RightChild;
}BSTNode,*BST;
//����	����
void createBST(BST& root)
{
	char ch;
	cin >> ch;
	if (ch == '.')
	{
		root = NULL;
		return;
	}
	root = new BSTNode;
	root->val = ch-'0';//תΪint
	createBST(root->LeftChild);
	createBST(root->RightChild);
}
//����
void insertBST(BST& root,ElemType k)
{
	//��Ϊ��
	if (!root)
	{
		root = new BSTNode;
		root->val = k;
		root->LeftChild = NULL;
		root->RightChild = NULL;
	}//��С�ڸ����
	else if (k < root->val)
	{
		insertBST(root->LeftChild,k);
	}//�����ڸ��ڵ�
	else if (k > root->val)
	{
		insertBST(root->RightChild,k);
	}
}
//����
BSTNode* searchBST(const BST& root, ElemType k)
{
	if (!root)
	{
		return NULL;
	}
	else if (k == root->val)
	{
		return root;
	}
	else if (k < root->val)
	{
		searchBST(root->LeftChild,k);
	}
	else
	{
		searchBST(root->RightChild,k);
	}
}
//ɾ��
ElemType delBST(BST& root, ElemType k)
{
	//��Ϊ����
	if (!root)
	{
		return ERROR;
	}
	BSTNode* fp = NULL;
	BSTNode* p = root;
	int flag = 0;
	//���ҽ��
	while (root)
	{
		fp = p;
		if (p->val == k)
		{
			flag = 1;
			break;
		}
		else if (k < p->val)
		{
			p = p->LeftChild;
		}
		else
		{
			p = p->RightChild;
		}
	}
	//��δ�ҵ�
	if (!flag)
	{
		return ERROR;
	}
	//p��fp����һ��֧
	if (fp->RightChild == p)
	{
		flag = 0;//����flag
	}
	//���������۽��p�����

	//��ΪҶ�ӽ��
	if (p->LeftChild == NULL && p->RightChild == NULL)
	{
		if (flag)
		{
			fp->LeftChild = NULL;
		}
		else
		{
			fp->RightChild = NULL;
		}
	}
	//��ֻ��������
	else if (p->LeftChild && !p->RightChild)
	{
		if (flag)
		{
			fp->LeftChild = p->LeftChild;
		}
		else
		{
			fp->RightChild = p->LeftChild;
		}
	}
	//��ֻ��������
	else if (!p->LeftChild && p->RightChild)
	{
		if (flag)
		{
			fp->LeftChild = p->RightChild;
		}
		else
		{
			fp->RightChild = p->RightChild;
		}
	}
	//������������������������
	else
	{
		//�ҵ�����������p��ֱ��ǰ��
		BSTNode* temp = p->LeftChild;
		while (temp)
		{
			//�ض���p�����������·����
			if (temp->RightChild)
			{
				temp = temp->RightChild;
			}
			else
			{
				break;
			}
		}
		//�������p����������
		temp->RightChild = p->RightChild;
		if (flag)
		{
			fp->LeftChild = p->LeftChild;
		}
		else
		{
			fp->RightChild = p->LeftChild;
		}
	}
	delete p;
	p = NULL;
}
int main()
{
		/* ����521..43...6.87..9..*/
	BST bst;
	createBST(bst);
	insertBST(bst, 10);
	searchBST(bst, 10);
	delBST(bst, 8);
	system("pause");
	return 0;
}