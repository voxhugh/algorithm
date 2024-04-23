#include <iostream>
using namespace std;
#define ElemType char
#define ERROR -1
#define OK 1

typedef struct Node
{
	ElemType data;//������
	struct Node* next;//ָ����
}Node,*LinkList;
//��ʼ��
void initList(LinkList &L)
{
	L = new Node;//����ͷ���
	L->data = 0;//���������
	L->next = NULL;//��ʼ��Ϊ������
}
//ͷ�巨����
void createListFront(LinkList &L)
{
	Node* p;//p:�½��
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
//β�巨����
void createListBack(LinkList& L)
{
	Node* p;
	Node* t = L;//t:βָ��
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
//��ȡ
Node* getData(const LinkList& L, int pos)
{
	//λ�÷Ƿ�
	if (pos<1 || pos>L->data)
	{
		return NULL;
	}
	Node* current = L;//current:��ʼָ��ͷ���
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	return current;
}
//����
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
//���
int listLength(const LinkList& L)
{
	return L->data;
}
//�п�
bool isEmpty(const LinkList& L)
{
	if (!L||!L->data)//δ��ʼ����ձ�
	{
		return true;
	}
	return false;
}
//����	��ָ��λ�ú�
int listInsert(LinkList& L, int pos,char ch)
{
	//λ�÷Ƿ�
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	Node* current = L;
	Node* p = new Node;
	p->data = ch;
	//����λ��
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	//��λ��֮�����
	p->next = current->next;
	current->next = p;
	return OK;
}
//ɾ��
int listDelete(LinkList& L, int pos)
{
	//λ�÷Ƿ�
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	Node* current = L;
	//����λ��
	for (int i = 0; i < pos-1; i++)
	{
		current = current->next;
	}
	Node* temp = current->next;//ָ���ɾ�����
	//ɾ�����
	current->next = temp->next;
	delete temp;
	temp = NULL;
	return OK;
}
//���
void listClear(const LinkList& L)
{
	//������δ��ʼ��
	if (!L)
	{
		return;
	}
	//�����ѳ�ʼ��
	L->next = NULL;
	L->data = 0;
}
//����
void dropList(LinkList& L)
{
	delete L;
	L = NULL;
}
//��ӡ
void printList(const LinkList& L)
{
	//������δ��ʼ��������Ϊ��
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