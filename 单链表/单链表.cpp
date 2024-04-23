#include <iostream>
using namespace std;
#define ElemType char
#define ERROR -1
#define OK 1

typedef struct Node
{
	ElemType data;//数据域
	struct Node* next;//指针域
}Node,*LinkList;
//初始化
void initList(LinkList &L)
{
	L = new Node;//创建头结点
	L->data = 0;//存放链表长度
	L->next = NULL;//初始化为空链表
}
//头插法建表
void createListFront(LinkList &L)
{
	Node* p;//p:新结点
	ElemType ch = 0;
	while (true)
	{
		cin >> ch;
		if (ch == '$')
		{
			break;
		}
		p = new Node;
		p->data = ch;
		p->next = L->next;
		L->next = p;
		L->data++;
	}
}
//尾插法建表
void createListBack(LinkList& L)
{
	Node* p;
	Node* t = L;//t:尾指针
	ElemType ch = 0;
	while (true)
	{
		cin >> ch;
		if (ch == '$')
		{
			t->next = NULL;
			break;
		}
		p = new Node;
		p->data = ch;
		t->next = p;
		t = p;
		L->data++;
	}
}
//获取
Node* getData(const LinkList& L, int pos)
{
	//位置非法
	if (pos<1 || pos>L->data)
	{
		return NULL;
	}
	Node* current = L;//current:初始指向头结点
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	return current;
}
//查找
int dataLocate(const LinkList& L, char ch)
{
	Node* current = L->next;
	for (int i = 0; i < L->data; i++)
	{
		if (current->data == ch)
		{
			return i + 1;
		}
		current = current->next;
	}
	return ERROR;
}
//求表长
int listLength(const LinkList& L)
{
	return L->data;
}
//判空
bool isEmpty(const LinkList& L)
{
	if (!L||!L->data)//未初始化或空表
	{
		return true;
	}
	return false;
}
//插入	在指定位置后
int listInsert(LinkList& L, int pos,char ch)
{
	//位置非法
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	Node* current = L;
	Node* p = new Node;
	p->data = ch;
	//查找位置
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	//在位置之后插入
	p->next = current->next;
	current->next = p;
	return OK;
}
//删除
int listDelete(LinkList& L, int pos)
{
	//位置非法
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	Node* current = L;
	//查找位置
	for (int i = 0; i < pos-1; i++)
	{
		current = current->next;
	}
	Node* temp = current->next;//指向待删除结点
	//删除结点
	current->next = temp->next;
	delete temp;
	temp = NULL;
	return OK;
}
//清空
void listClear(const LinkList& L)
{
	//链表尚未初始化
	if (!L)
	{
		return;
	}
	//链表已初始化
	L->next = NULL;
	L->data = 0;
}
//销毁
void dropList(LinkList& L)
{
	delete L;
	L = NULL;
}
//打印
void printList(const LinkList& L)
{
	//链表尚未初始化或链表为空
	if (!L || !L->data)
	{
		return;
	}
	Node* current = L;
	for (int i = 0; i < L->data; i++)
	{
		current = current->next;
		cout << current->data << " ";
	}
	cout << endl;
}
int main()
{
	LinkList L;
	initList(L);
	createListBack(L);
	printList(L);
	dropList(L);
	system("pause");
	return 0;
}