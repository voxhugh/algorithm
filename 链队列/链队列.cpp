#include <iostream>
using namespace std;
typedef int ElemType;
#define ERROR -1
#define OK 1

typedef struct Node//队列结点
{
	ElemType data;
	struct Node* next;
}QueueNode,*QueueNode_;
typedef struct Queue//队列指针
{
	QueueNode_ front;//队头指针
	QueueNode_ rear;//队尾指针
}Queue,*LinkQueue;
//初始化
void initLinkQueue(LinkQueue& Q)
{
	Q = new Queue;//队列指针初始化
	Q->front = new QueueNode;//队列头结点初始化
	Q->front->data = 0;
	Q->front->next = NULL;
	Q->rear = Q->front;//初始均指向头结点
}
//入队
ElemType enQueue(LinkQueue& Q, ElemType q)
{
	//若未初始化
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
//出队
ElemType deQueue(LinkQueue& Q)
{
	//判空 或 未初始化
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
//获取队头
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
	cout << "队头：" << queueFront(Q) << endl;
	system("pause");
	return 0;
}