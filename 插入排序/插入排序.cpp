#include <iostream>
using namespace std;

void insSort(int a[], int len)
{
	for (int i = 1; i < len; i++)
	{
		int temp = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > temp)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
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
	insSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}