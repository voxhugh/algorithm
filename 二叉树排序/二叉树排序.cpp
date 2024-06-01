#include <iostream>
using namespace std;

typedef struct node
{
	int val;
	struct node* l, * r;
}Node;
Node* newNode(int k)
{
	Node* N = new Node;
	N->val = k;
	N->r = N->l = NULL;
	return N;
}
Node* crtBt(Node* root, int k)
{
	if (k < root->val && root->l == NULL)
	{
		root->l = newNode(k);
		return root;
	}
	if (k > root->val && root->r == NULL)
	{
		root->r = newNode(k);
		return root;
	}
	if (k == root->val)
	{
		return root;
	}
	if (k < root->val)
	{
		crtBt(root->l, k);
	}
	if (k > root->val)
	{
		crtBt(root->r, k);
	}
}
void btSort(int a[], int len, Node*& root)
{
	root = newNode(a[0]);
	for (int i = 1; i < len; i++)
	{
		crtBt(root, a[i]);
	}
}
void printSeq(const Node* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->l)
	{
		printSeq(root->l);
	}
	cout << root->val << " ";
	if (root->r)
	{
		printSeq(root->r);
	}
}
int main()
{
	Node* tree;
	int a[] = { 5,7,1,4,2,8,3,0,9,6 };
	int len = sizeof(a) / sizeof(a[0]);
	btSort(a, len, tree);
	printSeq(tree);
	cout << endl;
	system("pause");
	return 0;
}