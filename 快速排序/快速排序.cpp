#include <iostream>
using namespace std;

void quickSort(int a[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int axis = a[left];
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end && a[end] >= axis)
		{
			end--;
		}
		if (begin < end)
		{
			a[begin] = a[end];
		}
		while (begin < end && a[begin] < axis)
		{
			begin++;
		}
		if (begin < end)
		{
			a[end] = a[begin];

		}
	}
	a[begin] = axis;
	quickSort(a, left, begin - 1);
	quickSort(a, begin + 1, right);
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
	int a[] = { 8,7,1,4,2,5,3,0,9,6 };
	int len = sizeof(a) / sizeof(a[0]);
	quickSort(a, 0, len - 1);
	printSeq(a, len);
	system("pause");
	return 0;
}