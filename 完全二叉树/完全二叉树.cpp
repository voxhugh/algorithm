#include <iostream>
using namespace std;
#define ElemType char

typedef struct cbtnode
{
	ElemType val;
	struct cbtnode* LeftChild, * RightChild;
}CBTNode,*CBT;
//��ʼ��
void initCBT(CBT& root)
{
	cout << "��������ڵ㣺" << endl;
	char ch;
	cin >> ch;
	root = new CBTNode;
	root->val = ch;
	root->LeftChild = NULL;
	root->RightChild = NULL;
}
//���
void addCBTNode(CBT& root)
{
	//��Ϊ��
	if (!root)
	{
		return;
	}
	int flag = 0;
	do
	{
		//��ӡ��ǰ���
		string str = flag ? "��" : "��";
		cout << "��ǰ�ڵ㣺" << root->val << endl;
		//��ʾ�����ҽ������������ڱ����ʾ
		cout << "�Ƿ����"<<str<<"������1 / 0" << endl;
		cin >> flag;
		//���������
		if (flag && str == "��")
		{
			root->LeftChild = new CBTNode;
			cout << "������ֵ��" << endl;
			ElemType k;
			cin >> k;
			root->LeftChild->val = k;
			addCBTNode(root->LeftChild);
		}
		//���������������������
		else if (flag && str == "��")
		{
			root->RightChild = new CBTNode;
			cout << "������ֵ��" << endl;
			ElemType k;
			cin >> k;
			root->RightChild->val = k;
			addCBTNode(root->RightChild);
			flag--;//�����ϣ��˳�ѭ��
		}
		//����������
		else if(str=="��")
		{
			root->LeftChild = NULL;
			root->RightChild = NULL;
		}
		//��������
		else
		{
			root->RightChild = NULL;
		}
	} while (flag);
	
}
//��ѯ
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