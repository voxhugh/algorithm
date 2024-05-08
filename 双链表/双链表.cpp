#include <iostream>
using namespace std;
typedef char ElemType;
#define ERROR -1
#define OK 1

typedef struct DNode
{
	ElemType data;//������
	struct DNode* prior, * next;//ǰ��ָ����
}DNode,*DoubleList;
//��ʼ��
void initDoubleList(DoubleList& L)
{
	L = new DNode;
	L->data = 0;
	L->prior = NULL;
	L->next = NULL;
}
//����	β��
void createDoubleList(DoubleList& L)
{
	DNode* p;
	DNode* t = L;//t:βָ��
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
//����	��ָ��λ�ú�
int dListInsert(DoubleList& L, int pos, char ch)
{
	//λ�÷Ƿ�
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	DNode* current = L;
	DNode* p = new DNode;
	p->data = ch;
	//����λ��
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	//��λ��֮�����
	p->next = current->next;
	current->next->prior = p;
	current->next = p;
	p->prior = current;
	L->data++;
	return OK;
}
//ɾ��
int dListDelete(DoubleList& L, int pos)
{
	//λ�÷Ƿ�
	if (pos<1 || pos>L->data)
	{
		return ERROR;
	}
	DNode* current = L;
	//����λ��
	for (int i = 0; i < pos - 1; i++)
	{
		current = current->next;
	}
	DNode* temp = current->next;//ָ���ɾ�����
	//ɾ�����
	current->next = temp->next;
	temp->next->prior = current;
	delete temp;
	temp = NULL;
	L->data--;
	return OK;
}
//����ָ��Ԫ�ص�ֱ��ǰ��
DNode* getPriorByData(const DoubleList& L, char ch)
{
	//δ��ʼ����ձ�
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