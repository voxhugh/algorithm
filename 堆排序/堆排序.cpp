#include <iostream>
using namespace std;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void adjust_down(int a[], int root, int len)
{
	int parent = root;
	int left = parent ? 2 * parent : 1;
	int right = left + 1;
	while (left < len)
	{
		int max = left;
		if (right<len && a[right]>a[left])
		{
			max = right;
		}
		if (a[max] > a[parent])
		{
			swap(&a[max], &a[parent]);
			parent = max;
			left = 2 * parent;
			right = left + 1;
		}
		else
		{
			break;
		}
	}
}
void heapSort(int a[], int len)
{
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		adjust_down(a, i, len);
	}
	int end = len;
	while (end > 1)
	{
		swap(&a[0], &a[end - 1]);
		adjust_down(a, 0, --end);
	}
}
void printSeq(int a[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
int main()
{
	int a[] = { 3,7,1,4,2,8,5,0,9,6 };
	int len = sizeof(a) / sizeof(a[0]);
	heapSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}