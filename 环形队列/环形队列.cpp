#include <iostream>
using namespace std;
#define MAXSIZE 50
typedef int ElemType;
#define ERROR -1

typedef struct Queue
{
	ElemType q[MAXSIZE];
	int front;//头指针：指向队头
	int rear;//尾指针：指向队尾的下一个位置
}CQueue,*CQueue_;
//初始化
void initCQueue(CQueue_& Q)
{
	Q = new CQueue;
	Q->front = 0;
	Q->rear = 0;
}
//求队长
int CQueueLength(const CQueue_& Q)
{
	return Q->rear - Q->front;
}
//判空
bool isEmpty(const CQueue_& Q)
{
	if (Q->front == Q->rear)
	{
		return true;
	}
	return false;
}
//判满
bool isFull(const CQueue_& Q)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)//rear指向队列最后一个空间时，代表队满
	{
		return true;
	}
	return false;
}
//入队
void enCQueue(CQueue_& Q,ElemType elem)
{
	if (isFull(Q))
	{
		return;
	}
	Q->q[Q->rear] = elem;
	Q->rear++;
}
//出队
ElemType deCQueue(CQueue_& Q)
{
	if (isEmpty(Q))
	{
		return ERROR;
	}
	Q->front++;
	return Q->q[Q->front - 1];
}
int main()
{
	CQueue_ Q;
	initCQueue(Q);
	enCQueue(Q, 1);
	enCQueue(Q, 2);
	enCQueue(Q, 3);
	deCQueue(Q);
	system("pause");
	return 0;
}