#include <iostream>
using namespace std;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void destroy(int* N)
{
	delete N;
	N = NULL;
}
int getMaxDigit(int a[], int len)
{
	int max = 10;
	int digit = 1;
	for (int i = 0; i < len; i++)
	{
		if (a[i] >= max)
		{
			digit++;
			max *= 10;
		}
	}
	return digit;
}
void digitSort(int a[], int len)
{
	int* low = new int[len];
	int* other = new int[len];

	for (int i = 0; i < len; i++)
	{
		other[i] = a[i];
	}

	int digit = getMaxDigit(a, len);
	while (digit--)
	{
		for (int i = 0; i < len; i++)
		{
			low[i] = other[i] % 10;
			other[i] /= 10;
		}
		for (int i = 0; i < len; i++)
		{
			for (int j = i; j < len; j++)
			{
				if (low[j] < low[i])
				{
					swap(low[j], low[i]);
					swap(other[j], other[i]);
					swap(a[j], a[i]);
				}
			}
		}
	}
	destroy(low);
	destroy(other);
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
	digitSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}