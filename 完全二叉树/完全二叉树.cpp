#include <iostream>
using namespace std;
#define ElemType char

typedef struct cbtnode
{
	ElemType val;
	struct cbtnode* LeftChild, * RightChild;
}CBTNode,*CBT;
//初始化
void initCBT(CBT& root)
{
	cout << "请输入根节点：" << endl;
	char ch;
	cin >> ch;
	root = new CBTNode;
	root->val = ch;
	root->LeftChild = NULL;
	root->RightChild = NULL;
}
//添加
void addCBTNode(CBT& root)
{
	//树为空
	if (!root)
	{
		return;
	}
	int flag = 0;
	do
	{
		//打印当前结点
		string str = flag ? "右" : "左";
		cout << "当前节点：" << root->val << endl;
		//提示，当且仅当左子树存在变更提示
		cout << "是否添加"<<str<<"子树？1 / 0" << endl;
		cin >> flag;
		//添加左子树
		if (flag && str == "左")
		{
			root->LeftChild = new CBTNode;
			cout << "输入结点值：" << endl;
			ElemType k;
			cin >> k;
			root->LeftChild->val = k;
			addCBTNode(root->LeftChild);
		}
		//已有左子树，添加右子树
		else if (flag && str == "右")
		{
			root->RightChild = new CBTNode;
			cout << "输入结点值：" << endl;
			ElemType k;
			cin >> k;
			root->RightChild->val = k;
			addCBTNode(root->RightChild);
			flag--;//添加完毕，退出循环
		}
		//无左右子树
		else if(str=="左")
		{
			root->LeftChild = NULL;
			root->RightChild = NULL;
		}
		//无右子树
		else
		{
			root->RightChild = NULL;
		}
	} while (flag);
	
}
//查询
CBTNode* findCBTNode(const CBT& root, ElemType value)
{
	if (!root)
	{
		return NULL;
	}
	if (value == root->val)
	{
		return root;
	}
	CBTNode * Left = findCBTNode(root->LeftChild, value);
	CBTNode * Right = findCBTNode(root->RightChild, value);
	return Left ? Left : Right;
}
int main()
{
	CBT cbt;
	initCBT(cbt);
	addCBTNode(cbt);
	findCBTNode(cbt, 'e');
	system("pause");
	return 0;
}