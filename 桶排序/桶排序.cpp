#include <iostream>
using namespace std;
#include <vector>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void bucketSort(int a[], int len)
{
	int divisor = 10;
	for (int i = 0; i < len; i++)
	{
		if (a[i] > divisor)
		{
			divisor *= 10;
		}
	}
	divisor /= 10;

	const int bucketNum = 10;
	vector<int> buckets[bucketNum];
	for (int i = 0; i < len; i++)
	{
		//入桶
		int index = a[i] / divisor;
		buckets[index].push_back(a[i]);
		//桶内插入排序
		int j = buckets[index].size();
		while (--j > 0)
		{
			if (a[i] < buckets[index][j - 1])
			{
				swap(&buckets[index][j - 1], &buckets[index][j]);
			}
			else
			{
				break;
			}
		}
	}
	//出桶
	int k = 0;
	for (int i = 0; i < bucketNum; i++)
	{
		for (int j = 0; j < buckets[i].size(); j++)
		{
			a[k++] = buckets[i][j];
		}
		buckets[i].clear();
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
	bucketSort(a, len);
	printSeq(a, len);
	system("pause");
	return 0;
}