#include <iostream>
using namespace std;

void shellSort(int a[], int len)
{
	int j;
	int dt = len;
	do
	{
		dt = dt / 3 + 1;
		for (int i = 0 + dt; i < len; i++)
		{
			if (a[i] < a[i - dt])
			{
				int temp = a[i];
				for (j = i - dt; j >= 0 && a[j] > temp; j -= dt)
				{
					a[j + dt] = a[j];
				}
				a[j + dt] = temp;
			}
		}
	} while (dt > 1);
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
	int a[] = { 5,4,3,1,7,6 };
	int len = sizeof(a) / sizeof(a[0]);
	shellSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}