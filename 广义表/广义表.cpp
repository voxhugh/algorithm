#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct GLNode
{
	ElemType tag;//��־��
	union
	{
		char atom;//��һ���֣�ԭ�ӽ��������
		struct//�ڶ����֣��ӱ���ṹ��
		{
			struct GLNode* hp, * tp;//ͷָ�룺ָ���ӱ�	βָ�룺ָ��ͬ����һ�����
		}ptr;
	};
}GLNode, * Glist;
//��������ʼ��
Glist& createGlist(Glist& C)
{
	/*���������C(a, (b, c, d))*/

	//���ٵ�����
	C = new GLNode;
	C->tag = 1;
	//��ͷ��a
	C->ptr.hp = new GLNode;
	C->ptr.hp->tag = 0;
	C->ptr.hp->atom = 'a';
	//��β���ӱ�(b,c,d)
	C->ptr.tp = new GLNode;
	C->ptr.tp->tag = 1;
	C->ptr.tp->ptr.tp = NULL;
	//�ӱ��һ��Ԫ�أ�b
	C->ptr.tp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->tag = 1;
	C->ptr.tp->ptr.hp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.hp->tag = 0;
	C->ptr.tp->ptr.hp->ptr.hp->atom = 'b';
	//�ӱ�ڶ���Ԫ�أ�c
	C->ptr.tp->ptr.hp->ptr.tp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->tag = 1;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->tag = 0;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->atom = 'c';
	//�ӱ������Ԫ�أ�d
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->tag = 1;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->tag = 0;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->atom = 'd';
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.tp = NULL;

	return C;
}
//����
void copyGlist(const Glist& C, Glist& T)
{
	//CΪ�ձ�
	if (!C)
	{
		T = NULL;
		return;
	}
	//�ǿ�
	T = new GLNode;
	T->tag = C->tag;
	//ԭ�ӽ��
	if (C->tag == 0)
	{
		T->atom = C->atom;
		return;
	}
	//����
	copyGlist(C->ptr.hp, T->ptr.hp);//���Ʊ�ͷ
	copyGlist(C->ptr.tp, T->ptr.tp);//���Ʊ�β
}
//��ӡ
void printGlist(const Glist& C)
{
	if (!C)
	{
		return;
	}
	else if (C->tag == 0)
	{
		cout << C->atom << " ";
		return;
	}
	printGlist(C->ptr.hp);
	printGlist(C->ptr.tp);
}
int main()
{
	Glist C;
	createGlist(C);
	Glist T;
	copyGlist(C, T);
	printGlist(T);
	cout << endl;
	system("pause");
	return 0;
}