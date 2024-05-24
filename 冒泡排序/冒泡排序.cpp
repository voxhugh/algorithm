#include <iostream>
using namespace std;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void BubbleSort(int a[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (a[i] > a[j])
			{
				swap(&a[i], &a[j]);
			}
		}
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
	int a[] = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
	int len = sizeof(a) / sizeof(a[0]);
	BubbleSort(a, 15);
	printSeq(a, 15);
	system("pause");
	return 0;
}