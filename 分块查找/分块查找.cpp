#include <iostream>
using namespace std;
#define BlockSize 5

typedef struct block
{
	int MaxValue;
	int start;
}Block;
typedef struct blocktable
{
	Block B[3];
}BlockTable;
int blockSearch(int a[], int len, int k)
{
	BlockTable table;
	//分块
	for (int i = 0; i < len; i += BlockSize)
	{
		int begin = i;
		int Max = a[i];
		for (int j = i; j < i + BlockSize; j++)
		{
			if (a[j] > Max)
			{
				Max = a[j];
			}
		}
		table.B[i / BlockSize].start = begin;
		table.B[i / BlockSize].MaxValue = Max;
	}
	//查找块表
	int index = 0;
	while (k > table.B[index].MaxValue)
	{
		index++;
	}
	//块内顺序查找
	for (int i = table.B[index].start; i < table.B[index].start + BlockSize; i++)
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
	int a[] = { 18,14,12,25,8,28,32,45,36,58,60,88,71 };
	int len = sizeof(a) / sizeof(a[0]);
	blockSearch(a, len, 60);
	system("pause");
	return 0;
}