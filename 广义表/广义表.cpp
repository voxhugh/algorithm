#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct GLNode
{
	ElemType tag;//标志域
	union
	{
		char atom;//第一部分：原子结点数据域
		struct//第二部分：子表结点结构体
		{
			struct GLNode* hp, * tp;//头指针：指向子表	尾指针：指向同层下一个结点
		}ptr;
	};
}GLNode, * Glist;
//创建并初始化
Glist& createGlist(Glist& C)
{
	/*例：广义表C(a, (b, c, d))*/

	//开辟到堆区
	C = new GLNode;
	C->tag = 1;
	//表头：a
	C->ptr.hp = new GLNode;
	C->ptr.hp->tag = 0;
	C->ptr.hp->atom = 'a';
	//表尾：子表(b,c,d)
	C->ptr.tp = new GLNode;
	C->ptr.tp->tag = 1;
	C->ptr.tp->ptr.tp = NULL;
	//子表第一个元素：b
	C->ptr.tp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->tag = 1;
	C->ptr.tp->ptr.hp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.hp->tag = 0;
	C->ptr.tp->ptr.hp->ptr.hp->atom = 'b';
	//子表第二个元素：c
	C->ptr.tp->ptr.hp->ptr.tp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->tag = 1;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->tag = 0;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->atom = 'c';
	//子表第三个元素：d
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->tag = 1;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp = new GLNode;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->tag = 0;
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->atom = 'd';
	C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.tp = NULL;

	return C;
}
//复制
void copyGlist(const Glist& C, Glist& T)
{
	//C为空表
	if (!C)
	{
		T = NULL;
		return;
	}
	//非空
	T = new GLNode;
	T->tag = C->tag;
	//原子结点
	if (C->tag == 0)
	{
		T->atom = C->atom;
		return;
	}
	//表结点
	copyGlist(C->ptr.hp, T->ptr.hp);//复制表头
	copyGlist(C->ptr.tp, T->ptr.tp);//复制表尾
}
//打印
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