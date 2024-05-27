#include <iostream>
using namespace std;

void selectSort(int a[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int k = i;
		for (int j = i + 1; j < len; j++)
		{
			if (a[k] > a[j])
			{
				k = j;
			}
		}
		if (k != i)
		{
			int temp = a[i];
			a[i] = a[k];
			a[k] = temp;
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
	int a[] = { 9,3,2,8,4,5,1 };
	int len = sizeof(a) / sizeof(a[0]);
	selectSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}