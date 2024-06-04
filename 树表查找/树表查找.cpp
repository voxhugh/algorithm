#include <iostream>
using namespace std;

typedef struct node
{
	int val;
	struct node* l, * r;
}BiTNode, * BiTree;
bool insertBiT(BiTree& root, int k)
{
	if (!root)
	{
		root = new BiTNode;
		root->val = k;
		root->l = NULL;
		root->r = NULL;
		return true;
	}
	if (root->val == k)
	{
		return false;
	}
	else if (k < root->val)
	{
		return insertBiT(root->l, k);
	}
	else
	{
		return insertBiT(root->r, k);
	}
}
void crtBiTree(int a[], int len, BiTree& root)
{
	root = NULL;
	for (int i = 0; i < len; i++)
	{
		insertBiT(root, a[i]);
	}
}
BiTNode* BiTree_Search(const BiTree& root, int k)
{
	if (!root)
	{
		return NULL;
	}
	if (root->val == k)
	{
		return root;
	}
	else if (k < root->val)
	{
		return BiTree_Search(root->l, k);
	}
	else
	{
		return BiTree_Search(root->r, k);
	}
}
int main()
{
	int a[] = { 5,7,1,4,2,8,3,0,9,6 };
	int len = sizeof(a) / sizeof(a[0]);
	BiTree bit;
	crtBiTree(a, len, bit);
	BiTree_Search(bit, 9);
	system("pause");
	return 0;
}