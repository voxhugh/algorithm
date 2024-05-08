#include <iostream>
using namespace std;
typedef int ElemType;
#define ERROR -1
#define OK 1

typedef struct Node//���н��
{
	ElemType data;
	struct Node* next;
}QueueNode,*QueueNode_;
typedef struct Queue//����ָ��
{
	QueueNode_ front;//��ͷָ��
	QueueNode_ rear;//��βָ��
}Queue,*LinkQueue;
//��ʼ��
void initLinkQueue(LinkQueue& Q)
{
	Q = new Queue;//����ָ���ʼ��
	Q->front = new QueueNode;//����ͷ����ʼ��
	Q->front->data = 0;
	Q->front->next = NULL;
	Q->rear = Q->front;//��ʼ��ָ��ͷ���
}
//���
ElemType enQueue(LinkQueue& Q, ElemType q)
{
	//��δ��ʼ��
	if (!Q || !Q->front)
	{
		return ERROR;
	}
	QueueNode_ p = new QueueNode;
	p->data = q;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}
//����
ElemType deQueue(LinkQueue& Q)
{
	//�п� �� δ��ʼ��
	if (!Q || !Q->front||!Q->front->next)
	{
		return ERROR;
	}
	QueueNode_ temp;
	ElemType tempData;
	temp = Q->front->next;
	tempData = temp->data;
	Q->front->next = temp->next;
	delete temp;
	temp = NULL;
	return tempData;
}
//��ȡ��ͷ
ElemType queueFront(const LinkQueue& Q)
{
	if (!Q || !Q->front || !Q->front->next)
	{
		return ERROR;
	}
	return Q->front->next->data;
}
int main()
{
	LinkQueue Q;
	initLinkQueue(Q);
	enQueue(Q, 1);
	enQueue(Q, 2);
	enQueue(Q, 3);
	deQueue(Q);
	cout << "��ͷ��" << queueFront(Q) << endl;
	system("pause");
	return 0;
}