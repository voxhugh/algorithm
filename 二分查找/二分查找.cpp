#include <iostream>
using namespace std;

int binSearch(int a[], int len, int k)
{
	int low = 0;
	int high = len - 1;
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == k)
		{
			return mid;
		}
		else if (k < a[mid])
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}
int main()
{
	int a[] = { 1,2,3,4,5,6,7,8,9 };
	int len = sizeof(a) / sizeof(a[0]);
	binSearch(a, len, 4);
	system("pause");
	return 0;
}