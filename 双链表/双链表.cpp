#include <iostream>
using namespace std;
typedef char ElemType;
#define ERROR -1
#define OK 1

typedef struct DNode
{
	ElemType data;//数据域
	struct DNode* prior, * next;//前后指针域
}DNode,*DoubleList;
//初始化
void initDoubleList(DoubleList& L)
{
	L = new DNode;
	L->data = 0;
	L->prior = NULL;
	L->next = NULL;
}
//建表	尾插
void createDoubleList(DoubleList& L)
{
	DNode* p;
	DNode* t = L;//t:尾指针
	ElemType ch = 0;
	while (true)
	{
		cin >> ch;
		if (ch == '$')
		{
			t->next = NULL;
			break;
		}
		p = new DNode;
		p->data = ch;
		p->prior = t;
		t->next = p;
		t = p;
		L->data++;
	}
}
//插入	在指定位置后
int dListInsert(DoubleList& L, int pos, char ch)
{
	//位置非法
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	DNode* current = L;
	DNode* p = new DNode;
	p->data = ch;
	//查找位置
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	//在位置之后插入
	p->next = current->next;
	current->next->prior = p;
	current->next = p;
	p->prior = current;
	L->data++;
	return OK;
}
//删除
int dListDelete(DoubleList& L, int pos)
{
	//位置非法
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	DNode* current = L;
	//查找位置
	for (int i = 0; i < pos - 1; i++)
	{
		current = current->next;
	}
	DNode* temp = current->next;//指向待删除结点
	//删除结点
	current->next = temp->next;
	temp->next->prior = current;
	delete temp;
	temp = NULL;
	L->data--;
	return OK;
}
//查找指定元素的直接前驱
DNode* getPriorByData(const DoubleList& L, char ch)
{
	//未初始化或空表
	if (!L || !L->next)
	{
		return NULL;
	}
	DNode* current = L;
	for (int i = 0; i < L->data; i++)
	{
		current = current->next;
		if (current->data == ch)
		{
			return current->prior;
		}
	}
	return NULL;
}
int main()
{
	DoubleList L;
	initDoubleList(L);
	createDoubleList(L);
	DNode* node= getPriorByData(L, 'k');
	cout << node->data << endl;
	system("pause");
	return 0;
}