#include <iostream>
#include <cmath>
using namespace std;
typedef char ElemType;
#define ERROR '-1'//由于ElemType为char，则对应字符'-1'

typedef struct Node
{
	ElemType data;
	struct Node* next;
}StackNode,*LinkStack;
//初始化
void initLinkStack(LinkStack& S)
{
	S = new StackNode;//栈顶前包含头结点
	S->data = 0;//记录栈中元素个数
	S->next = NULL;
}
//入栈
void Push(LinkStack& S, ElemType elem)
{
	//是否已初始化
	if (!S)
	{
		return;
	}
	//栈后进先出，故入栈即头插
	StackNode* p = new StackNode;
	p->data = elem;
	p->next = S->next;
	S->next = p;
	S->data++;//由于栈无法遍历操作，非质变求元素个数只能插入时记录
}
//出栈
ElemType Pop(LinkStack& S)
{
	//判空
	if (!S || !S->data)
	{
		return ERROR;
	}
	StackNode* temp;
	ElemType tempdata;
	temp = S->next;//暂存栈顶元素
	tempdata = temp->data;//返回栈顶元素值
	S->next = temp->next;
	S->data--;
	delete temp;
	temp = NULL;
	return tempdata;
}
//获取栈顶
ElemType stackTop(const LinkStack& S)
{
	//判空
	if (!S || !S->data)
	{
		return ERROR;
	}
	return S->next->data;
}
//销毁
void destroyStack(LinkStack& S)
{
	//栈不为空
	if (S && S->data)
	{
		StackNode* current = S;
		StackNode* prior = S;
		for (int i = 0; i < S->data; i++)
		{
			current = current->next;
			delete prior;
			prior = current;		
		}
		delete current;
		current = NULL;
	}
}
//是否为算数运算符 是则判断优先级并返回	否返回0
int isOperator_Priority(ElemType elem)
{
	/*	以下为算数运算符的优先级，数字越大优先级越高：
	*	+	1
	*	-	1
	*	*	2
	*	/	2
	*	^	3
	*/
	switch (elem)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return 0;
	}
}
//运算
int execute(int num1, char op, int num2)
{
	switch (op)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	default:
		return pow(num1,num2);
	}
}
//表达式求值	（简单起见，只提供无括号算术表达式，以'#'结束，且操作数均为自然数）
int expr(string str)
{
	//准备两个动态栈
	LinkStack NUM;//存放操作数
	LinkStack OPT;//存放运算符
	initLinkStack(NUM);
	initLinkStack(OPT);
	int ret1;//暂存字符优先级
	int ret2;//暂存OPT栈顶优先级
	//遍历字符串
	for (int i = 0; i < str.size(); i++)
	{
		//操作数 直接入栈
		if (!(ret1=isOperator_Priority(str[i])))
		{
			Push(NUM, str[i]);
			continue;
		}
		//运算符 栈为空，直接入栈
		if ((ret2 = stackTop(OPT))=='-1')
		{
			Push(OPT, str[i]);
			continue;
		}
		ret2 = isOperator_Priority(ret2);
		//低于栈顶优先级 或 表达式结束时 开始弹栈运算
		if (ret1<=ret2||str[i]=='#')
		{
			ElemType op =Pop(OPT);//运算符出栈
			int num2 = Pop(NUM)-'0';//操作数2出栈	char to int
			int num1 = Pop(NUM)-'0';//操作数1出栈	char to int
			int expNum = execute(num1, op, num2);//计算表达式的值
			Push(NUM, expNum+'0');//结果入栈	int to char
			continue;
		}//高于栈顶，运算符入栈
		else
		{
			Push(OPT, str[i]);
		}
	}
	return Pop(NUM);
}
int main()
{
	string str1 = "8/2^3+5*6#";
	cout << expr(str1) << endl;
	system("pause");
	return 0;
}