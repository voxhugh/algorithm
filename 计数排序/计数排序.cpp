#include <iostream>
using namespace std;

void countSort(int a[], int len)
{
	int Min = a[0];
	int Max = a[0];
	for (int i = 0; i < len; i++)
	{
		if (a[i] > Max)
		{
			Max = a[i];
		}
		if (a[i] < Min)
		{
			Min = a[i];
		}
	}
	int range = Max - Min + 1;
	int* b = new int[range];
	memset(b, 0, sizeof(int) * range);
	for (int i = 0; i < len; i++)
	{
		b[a[i] - Min]++;
	}
	int index = 0;
	for (int i = 0; i < range; i++)
	{
		while (b[i]--)
		{
			a[index++] = i + Min;
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
	int a[] = { 44,38,47,36,26,27,46,19,50,48 };
	int len = sizeof(a) / sizeof(a[0]);
	countSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}