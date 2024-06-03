#include <iostream>
using namespace std;

int seqSearch(int a[], int len, int k)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] == k)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	int a[] = { 3,44,38,5,47,15,36,26,4,19,50,48 };
	int len = sizeof(a) / sizeof(a[0]);
	seqSearch(a, len, 26);
	system("pause");
	return 0;
}