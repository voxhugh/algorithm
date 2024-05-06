#include <iostream>
using namespace std;
#define N 20	//���N��Ҷ�ӽ��
#define M 2*N-1	//���2N-1���ܽ��
typedef struct
{
	int weight;//Ȩֵ
	int parent, lchild, rchild;//����ָ��
}HTNode,*HuffmanTree;//�����������
//ɸѡ
void select(const HuffmanTree &ht, int end, int* s1, int* s2)//�������������ɨ��[1,end],ȡ������Сֵ����������s1��s2
{
	int w1 = M;
	int w2 = w1;
	*s1 = 0;
	for (int i = 1; i <= end; i++)
	{
		if (ht[i].weight < w1 && ht[i].parent == 0)//��С
		{
			//�����С
			*s2 = *s1;
			w2 = w1;
			//������С
			w1 = ht[i].weight;
			*s1 = i;
		}
		else if (ht[i].weight < w2 && ht[i].parent == 0)//��С
		{
			w2 = ht[i].weight;
			*s2 = i;
		}
	}
}
//����
void crtHuffmanTree(HuffmanTree& ht, int weight[], int weight_len)//����������������֣�������Ȩֵ����
{
	//��ʼ����������
	ht = new HTNode[M + 1];
	for (int i = 0; i < weight_len; i++)
	{
		ht[i + 1].weight = weight[i];//��ԭ˳��Ҷ�ӽ���������
		ht[i+1].lchild = ht[i+1].rchild = ht[i + 1].parent = 0;//����ָ�����ʼ��Ϊ0
	}
	//��ʼȡ������Сֵ����weight_len+1~2*weight_len-1
	for (int i = weight_len + 1; i <= 2 * weight_len - 1; i++)
	{
		//ɸѡ
		int s1, s2;
		select(ht, i - 1, &s1, &s2);
		//������Ȩֵ
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		//����ָ��
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