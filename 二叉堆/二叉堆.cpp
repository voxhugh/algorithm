#include <iostream>
using namespace std;
#define ERROR -1

typedef struct heapnode
{
	int capacity;//容量
	int size;//大小
	int* values;//数组
}HeapNode, * BinHeap;
//交换
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
//向下调整堆
void adjust_down(BinHeap& heap, int root, int length)
{
	int F = root;//当前结点
	int N = 2 * F;//左子结点
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
//创建并初始化
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
//堆排序
void heapSort(BinHeap& heap)
{
	int end = heap->size;
	while (end > 1)
	{
		swap(&heap->values[0], &heap->values[end - 1]);//先首尾交换
		adjust_down(heap, 0, --end);//然后去尾 自根向下调整
	}
}
//插入
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
//删除最大元
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