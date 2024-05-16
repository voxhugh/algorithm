#include <iostream>
using namespace std;
#define MINSIZE 10
#define ERROR -1

typedef struct heapnode
{
	int capacity;//����
	int size;//��С
	int* values;//����
}HeapNode, * BinHeap;
//����
void crtHeap(BinHeap& heap, int nums[], int length, int MaxSize)
{
	if (MaxSize < MINSIZE)
	{
		cout << "������С��" << endl;
		return;
	}
	heap = new HeapNode;
	heap->capacity = MaxSize;
	heap->size = length;
	heap->values = new int[MaxSize + 1];
	heap->values[0] = -1;
	for (int i = 1; i <= heap->size; i++)
	{
		heap->values[i] = nums[i - 1];
	}
}
//�ؽ��ѣ�ע�⣺�Դ����Ϊ����
void sift(BinHeap& heap, int root, int length)
{
	//���ݸ�
	int temp = heap->values[root];
	heap->values[root] = heap->values[length];
	int i = root;//��ǰ���
	int j = 2 * i;//����
	while (j < length)
	{
		if (j + 1 < length)
		{
			heap->values[j] < heap->values[j + 1] ? j++ : j;
		}
		if (heap->values[i] < heap->values[j])
		{
			heap->values[i] = heap->values[j];
		}
		else
		{
			break;
		}
		i = j;
		j = 2 * i;
	}
	heap->values[i] = temp;
}
//��ʼ��
void initHeap(BinHeap& heap)
{
	for (int i = heap->size / 2; i > 0; i--)
	{
		sift(heap, i, heap->size);
	}
}
//������
void heapSort(BinHeap& heap)
{
	initHeap(heap);//��ʼ��
	for (int i = heap->size; i > 1; i--)
	{
		int temp = heap->values[1];
		heap->values[1] = heap->values[i];
		heap->values[i] = temp;
		sift(heap, 1, i);
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
	int temp = heap->values[1];
	heap->values[1] = heap->values[heap->size];
	sift(heap, 1, --heap->size);
	return temp;
}
int main()
{
	BinHeap heap;
	int nums[] = { 48,62,35,77,55,14,35,98 };
	crtHeap(heap, nums, sizeof(nums) / sizeof(nums[0]), 30);
	heapSort(heap);
	system("pause");
	return 0;
}