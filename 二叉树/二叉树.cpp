#include <iostream>
using namespace std;
#define ElemType char
#define EMPTY '.'//��ʾ�޽��

typedef struct BiTNode
{
	ElemType val;//ֵ��
	struct BiTNode* LeftChild;//����
	struct BiTNode* RightChild;//�Һ���
}BiTreeNode,*BiTree;
//����	����
void createBiTree(BiTree& root)
{
	char ch;
	cin >> ch;
	//�����ַ���'.'��ʾ�޽��
	if (ch == EMPTY)
	{
		root = NULL;
		return;
	}
	root = new BiTreeNode;
	root->val = ch;
	//����������
	createBiTree(root->LeftChild);
	//����������
	createBiTree(root->RightChild);

}
//�������
void preOrderTraverseBiTree(const BiTree& root)
{
	if (root)
	{
		//���ʽ��
		cout << root->val << " ";
		//����������
		preOrderTraverseBiTree(root->LeftChild);
		//����������
		preOrderTraverseBiTree(root->RightChild);
	}
}
//�������
void inOrderTraverseBiTree(const BiTree& root)
{
	if (root)
	{
		inOrderTraverseBiTree(root->LeftChild);
		cout << root->val << " ";
		inOrderTraverseBiTree(root->RightChild);
	}
}
//�������
void postOrderTraverseBiTree(const BiTree& root)
{
	if (root)
	{
		postOrderTraverseBiTree(root->LeftChild);
		postOrderTraverseBiTree(root->RightChild);
		cout << root->val << " ";
	}
}
//��ȡ���
int getDepthBiTree(const BiTree& root)
{
	//NULL ���Ϊ0
	if (!root)
	{
		return 0;
	}
	int l, r,max;
	//��ȡ���������
	l = getDepthBiTree(root->LeftChild);
	//��ȡ���������
	r = getDepthBiTree(root->RightChild);
	//������ȣ�Max(l,r)+1
	max = l > r ? l + 1 : r + 1;
	return max;
}
//��ȡҶ�ӽ����
int countLeaves(const BiTree& root)
{
	//NULL ����0
	if (!root)
	{
		return 0;
	}
	//Ҷ�ӽ��
	if (root->LeftChild == NULL && root->RightChild == NULL)
	{
		return 1;
	}
	int lCount, rCount;
	//ͳ��������Ҷ�ӽ��
	lCount = countLeaves(root->LeftChild);
	//ͳ��������Ҷ�ӽ��
	rCount = countLeaves(root->RightChild);
	return lCount + rCount;
}
int main()
{		/*����	������ABD.G...CE..F..
				������.DGB.A.E.C.F.
				������.GD.B..E..FCA	*/
	BiTree BT;
	createBiTree(BT);
	preOrderTraverseBiTree(BT);
	inOrderTraverseBiTree(BT);
	postOrderTraverseBiTree(BT);
	system("pause");
	return 0;
}