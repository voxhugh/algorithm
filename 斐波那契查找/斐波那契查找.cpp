#include <iostream>
using namespace std;
#define FibMax 100

void produceFib(int*& F, int len)
{
	F = new int[len];
	F[0] = 1;
	F[1] = 1;
	for (int i = 2; i < len; i++)
	{
		F[i] = F[i - 1] + F[i - 2];
	}
}
int Fibonacci_Search(int a[], int len, int val)
{
	int low, high, mid, k, * F;
	k = 0;
	low = 0;
	high = len - 1;
	F = NULL;

	//生成斐波那契
	produceFib(F, FibMax);
	//规格化有序表
	while (F[k] - 1 < high)
	{
		k++;
	}
	for (int i = high + 1; i <= F[k] - 1; i++)
	{
		a[i] = a[high];
	}
	//黄金比例查找
	while (low <= high)
	{
		mid = low + F[k - 1] - 1;
		if (a[mid] == val)
		{
			return mid;
		}
		else if (val < a[mid])
		{
			high = mid - 1;
			k -= 2;
		}
		else
		{
			low = mid + 1;
			k--;
		}
	}
	return -1;
}
int main()
{
	int a[11 + 5] = { 1,3,5,7,9,11,13,15,17,19,21 };
	Fibonacci_Search(a, 11, 19);
	system("pause");
	return 0;
}