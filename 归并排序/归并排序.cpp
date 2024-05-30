#include <iostream>
using namespace std;
int b[50] = { 0 };

void merge(int a[], int low, int mid, int high)
{
	int begin1 = low;
	int begin2 = mid + 1;
	int index = 0;
	while (begin1 <= mid && begin2 <= high)
	{
		if (a[begin1] <= a[begin2])
		{
			b[index++] = a[begin1++];
		}
		else
		{
			b[index++] = a[begin2++];
		}
	}
	while (begin1 <= mid)
	{
		b[index++] = a[begin1++];
	}
	while (begin2 <= mid)
	{
		b[index++] = a[begin2++];
	}
	for (int i = 0; i < index; i++)
	{
		a[i + low] = b[i];
	}
}
void mergeSort(int a[], int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int mid = (low + high) / 2;
	mergeSort(a, low, mid);
	mergeSort(a, mid + 1, high);
	merge(a, low, mid, high);
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
	int a[] = { 3,6,1,9,4,2,0,5,8,7 };
	int len = sizeof(a) / sizeof(a[0]);
	mergeSort(a, 0, len - 1);
	printSeq(a, len);
	system("pause");
	return 0;
}