#include <iostream>
using namespace std;
#define N 20	//最大N个叶子结点
#define M 2*N-1	//最大2N-1个总结点
typedef struct
{
	int weight;//权值
	int parent, lchild, rchild;//三个指针
}HTNode,*HuffmanTree;//哈夫曼树结点
//筛选
void select(const HuffmanTree &ht, int end, int* s1, int* s2)//传入哈夫曼树，扫描[1,end],取两个最小值的索引存入s1，s2
{
	int w1 = M;
	int w2 = w1;
	*s1 = 0;
	for (int i = 1; i <= end; i++)
	{
		if (ht[i].weight < w1 && ht[i].parent == 0)//最小
		{
			//保存次小
			*s2 = *s1;
			w2 = w1;
			//更新最小
			w1 = ht[i].weight;
			*s1 = i;
		}
		else if (ht[i].weight < w2 && ht[i].parent == 0)//次小
		{
			w2 = ht[i].weight;
			*s2 = i;
		}
	}
}
//创建
void crtHuffmanTree(HuffmanTree& ht, int weight[], int weight_len)//传入哈夫曼树，树林，树林中权值个数
{
	//初始化哈夫曼树
	ht = new HTNode[M + 1];
	for (int i = 0; i < weight_len; i++)
	{
		ht[i + 1].weight = weight[i];//按原顺序将叶子结点存入树中
		ht[i+1].lchild = ht[i+1].rchild = ht[i + 1].parent = 0;//三个指针均初始化为0
	}
	//开始取两个最小值存入weight_len+1~2*weight_len-1
	for (int i = weight_len + 1; i <= 2 * weight_len - 1; i++)
	{
		//筛选
		int s1, s2;
		select(ht, i - 1, &s1, &s2);
		//保存结点权值
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		//更新指针
		ht[i].parent = 0;
		ht[i].lchild = s1;
		ht[i].rchild = s2;
		ht[s1].parent = i;
		ht[s2].parent = i;
	}
}
int main()
{
	int weight[] = { 4,7,2,3 };
	HuffmanTree ht;
	crtHuffmanTree(ht, weight, 4);
	system("pause");
	return 0;
}