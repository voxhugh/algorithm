#include <iostream>
using namespace std;
#define ElemType char

typedef struct CNode
{
	ElemType data;//数据域
	struct CNode* next;//指针域
}CNode,*CLinkList;
//初始化
void initCLinkList(CLinkList& R)
{
	R = new CNode;//R:尾指针
	R->next = new CNode;//指向头结点
	R->next->data = 0;//头结点记录表长，初始为0
	R->next->next = NULL;//空表
}
//建表	尾插
void createCLinkList(CLinkList& R)
{
	CNode* temp = R->next;//暂存头结点的指针
	R = R->next;//让R从头结点开始插入数据
	CNode* p;
	ElemType ch;
	while (true)
	{
		cin >> ch;
		if (ch == '$')
		{
			R->next = temp;//表尾重新指向头结点
			break;
		}
		p = new CNode;
		p->data = ch;
		R->next = p;
		R = p;
		temp->data++;
	}
}
int main()
{
	CLinkList R;
	initCLinkList(R);
	createCLinkList(R);
	//printCLinkList(R);
	system("pause");
	return 0;
}