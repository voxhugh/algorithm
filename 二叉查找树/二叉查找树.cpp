#include <iostream>
using namespace std;
typedef int ElemType;
#define ERROR -1

typedef struct bstnode
{
	ElemType val;
	struct bstnode* LeftChild, * RightChild;
}BSTNode,*BST;
//创建	先序
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
	root->val = ch-'0';//转为int
	createBST(root->LeftChild);
	createBST(root->RightChild);
}
//插入
void insertBST(BST& root,ElemType k)
{
	//若为空
	if (!root)
	{
		root = new BSTNode;
		root->val = k;
		root->LeftChild = NULL;
		root->RightChild = NULL;
	}//若小于根结点
	else if (k < root->val)
	{
		insertBST(root->LeftChild,k);
	}//若大于根节点
	else if (k > root->val)
	{
		insertBST(root->RightChild,k);
	}
}
//查找
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
//删除
ElemType delBST(BST& root, ElemType k)
{
	//若为空树
	if (!root)
	{
		return ERROR;
	}
	BSTNode* fp = NULL;
	BSTNode* p = root;
	int flag = 0;
	//查找结点
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
	//若未找到
	if (!flag)
	{
		return ERROR;
	}
	//p在fp的哪一分支
	if (fp->RightChild == p)
	{
		flag = 0;//复用flag
	}
	//接下来讨论结点p情况：

	//若为叶子结点
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
	//若只有左子树
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
	//若只有右子树
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
	//若既有左子树，又有右子树
	else
	{
		//找到中序序列中p的直接前驱
		BSTNode* temp = p->LeftChild;
		while (temp)
		{
			//必定是p左子树的右下方结点
			if (temp->RightChild)
			{
				temp = temp->RightChild;
			}
			else
			{
				break;
			}
		}
		//下面分配p的左右子树
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
		/* 例：521..43...6.87..9..*/
	BST bst;
	createBST(bst);
	insertBST(bst, 10);
	searchBST(bst, 10);
	delBST(bst, 8);
	system("pause");
	return 0;
}