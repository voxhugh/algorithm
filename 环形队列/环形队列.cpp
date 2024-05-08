#include <iostream>
using namespace std;
#define MAXSIZE 50
typedef int ElemType;
#define ERROR -1

typedef struct Queue
{
	ElemType q[MAXSIZE];
	int front;//ͷָ�룺ָ���ͷ
	int rear;//βָ�룺ָ���β����һ��λ��
}CQueue,*CQueue_;
//��ʼ��
void initCQueue(CQueue_& Q)
{
	Q = new CQueue;
	Q->front = 0;
	Q->rear = 0;
}
//��ӳ�
int CQueueLength(const CQueue_& Q)
{
	return Q->rear - Q->front;
}
//�п�
bool isEmpty(const CQueue_& Q)
{
	if (Q->front == Q->rear)
	{
		return true;
	}
	return false;
}
//����
bool isFull(const CQueue_& Q)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)//rearָ��������һ���ռ�ʱ���������
	{
		return true;
	}
	return false;
}
//���
void enCQueue(CQueue_& Q,ElemType elem)
{
	if (isFull(Q))
	{
		return;
	}
	Q->q[Q->rear] = elem;
	Q->rear++;
}
//����
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