#include <iostream>
using namespace std;
#define ElemType char
#define EMPTY '.'//表示无结点

typedef struct BiTNode
{
	ElemType val;//值域
	struct BiTNode* LeftChild;//左孩子
	struct BiTNode* RightChild;//右孩子
}BiTreeNode,*BiTree;
//创建	先序
void createBiTree(BiTree& root)
{
	char ch;
	cin >> ch;
	//键入字符，'.'表示无结点
	if (ch == EMPTY)
	{
		root = NULL;
		return;
	}
	root = new BiTreeNode;
	root->val = ch;
	//创建左子树
	createBiTree(root->LeftChild);
	//创建右子树
	createBiTree(root->RightChild);

}
//先序遍历
void preOrderTraverseBiTree(const BiTree& root)
{
	if (root)
	{
		//访问结点
		cout << root->val << " ";
		//遍历左子树
		preOrderTraverseBiTree(root->LeftChild);
		//遍历右子树
		preOrderTraverseBiTree(root->RightChild);
	}
}
//中序遍历
void inOrderTraverseBiTree(const BiTree& root)
{
	if (root)
	{
		inOrderTraverseBiTree(root->LeftChild);
		cout << root->val << " ";
		inOrderTraverseBiTree(root->RightChild);
	}
}
//后序遍历
void postOrderTraverseBiTree(const BiTree& root)
{
	if (root)
	{
		postOrderTraverseBiTree(root->LeftChild);
		postOrderTraverseBiTree(root->RightChild);
		cout << root->val << " ";
	}
}
//获取深度
int getDepthBiTree(const BiTree& root)
{
	//NULL 深度为0
	if (!root)
	{
		return 0;
	}
	int l, r,max;
	//获取左子树深度
	l = getDepthBiTree(root->LeftChild);
	//获取右子树深度
	r = getDepthBiTree(root->RightChild);
	//树的深度：Max(l,r)+1
	max = l > r ? l + 1 : r + 1;
	return max;
}
//获取叶子结点数
int countLeaves(const BiTree& root)
{
	//NULL 返回0
	if (!root)
	{
		return 0;
	}
	//叶子结点
	if (root->LeftChild == NULL && root->RightChild == NULL)
	{
		return 1;
	}
	int lCount, rCount;
	//统计左子树叶子结点
	lCount = countLeaves(root->LeftChild);
	//统计右子树叶子结点
	rCount = countLeaves(root->RightChild);
	return lCount + rCount;
}
int main()
{		/*例：	【先序】ABD.G...CE..F..
				【中序】.DGB.A.E.C.F.
				【后序】.GD.B..E..FCA	*/
	BiTree BT;
	createBiTree(BT);
	preOrderTraverseBiTree(BT);
	inOrderTraverseBiTree(BT);
	postOrderTraverseBiTree(BT);
	system("pause");
	return 0;
}