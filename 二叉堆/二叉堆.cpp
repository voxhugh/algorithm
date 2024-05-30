#include <iostream>
using namespace std;
#define ERROR -1

typedef struct heapnode
{
	int capacity;//����
	int size;//��С
	int* values;//����
}HeapNode, * BinHeap;
//����
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
//���µ�����
void adjust_down(BinHeap& heap, int root, int length)
{
	int F = root;//��ǰ���
	int N = 2 * F;//���ӽ��
	while (N < length)
	{
		if (N + 1 < length && heap->values[N] < heap->values[N + 1])
		{
			N++;
		}
		if (heap->values[F] < heap->values[N])
		{
			swap(&heap->values[F], &heap->values[N]);
			F = N;
			N = 2 * F;
		}
		else
		{
			break;
		}
	}
}
//��������ʼ��
void crtHeap(BinHeap& heap, int MaxSize)
{
	int nums[] = { 48,62,35,77,55,14,35,98 };
	heap = new HeapNode;
	heap->capacity = MaxSize;
	heap->size = sizeof(nums) / sizeof(nums[0]);
	heap->values = new int[MaxSize];
	for (int i = 0; i < heap->size; i++)
	{
		heap->values[i] = nums[i];
	}
	for (int i = heap->size / 2 - 1; i >= 0; i--)
	{
		adjust_down(heap, i, heap->size);
	}
}
//������
void heapSort(BinHeap& heap)
{
	int end = heap->size;
	while (end > 1)
	{
		swap(&heap->values[0], &heap->values[end - 1]);//����β����
		adjust_down(heap, 0, --end);//Ȼ��ȥβ �Ը����µ���
	}
}
//����
bool insertHeap(BinHeap& heap, int k)
{
	if (heap->size == heap->capacity)
	{
		return false;
	}
	int i;
	for (i = ++heap->size; heap->values[i / 2] < k; i /= 2)
	{
		heap->values[i] = heap->values[i / 2];
	}
	heap->values[i] = k;
	return true;
}
//ɾ�����Ԫ
int delMax(BinHeap& heap)
{
	if (heap->size == 0)
	{
		return ERROR;
	}
	int temp = heap->values[0];
	heap->values[0] = heap->values[heap->size - 1];
	adjust_down(heap, 0, --heap->size);
	return temp;
}
int main()
{
	BinHeap heap;
	crtHeap(heap, 30);
	heapSort(heap);
	system("pause");
	return 0;
}