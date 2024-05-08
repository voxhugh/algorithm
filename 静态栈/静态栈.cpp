#include <iostream>
using namespace std;
typedef char ElemType;
#define MaxSize 50
#define ERROR -1

typedef struct Stack
{
	ElemType arr[MaxSize];
	int top;
}Stack,*Stack_;
//初始化
void initStack(Stack_ &S)
{
	S = new Stack;//开辟到堆区
	S->top = -1;//空栈
}
//判空
bool isEmpty(const Stack_ &S)
{
	if (!S || S->top == -1)
	{
		return true;
	}
	return false;
}
//判满
bool isFull(const Stack_ &S)
{
	if (S->top == MaxSize - 1)
	{
		return true;
	}
	return false;
}
//入栈
void Push(Stack_ &S,ElemType elem)
{
	//判断栈是否已满 或 尚未初始化
	if (isFull(S)||!S)
	{
		return;
	}
	S->top++;//栈顶指针更新
	S->arr[S->top] = elem;
}
//出栈
ElemType Pop(Stack_ &S)
{
	//判断栈是否为空
	if (isEmpty(S))
	{
		return;
	}
	S->top--;
	return S->arr[S->top + 1];
}
//获取栈顶
ElemType stackTop(const Stack_ &S)
{
	if (isEmpty(S))
	{
		return ERROR;
	}
	return S->arr[S->top];
}
//清空
void cleanStack(Stack_ &S)
{
	S->top = -1;
}
//销毁
void destroyStack(Stack_ &S)
{
	delete S;
	S = NULL;
}
//是否为括号
int isBracket(ElemType elem)
{
	switch (elem)
	{
	case '(':
	case '[':
	case '{':
		return 1;//左括号
	case ')':
	case ']':
	case '}':
		return 2;//右括号
	default:
		return 0;//非括号
	}
}
//括号匹配
void bracketMatch(string str)
{
	//准备工作
	Stack_ S;
	initStack(S);
	ElemType elem;
	//扫描字符串
	for (int i = 0; i < str.size(); i++)
	{
		if (elem = isBracket(str[i]))//如果为括号
		{
			switch (elem)
			{
			case 1://左括号，则入栈
				Push(S, str[i]);
				break;
			case 2://右括号
				{
					//字符串不合规范
					if (isEmpty(S))
					{
						cout << "右括号多余！" << endl;
						return;
					}
					//匹配，则出栈
					if (stackTop(S) == '(' && str[i] == ')')//匹配'('
					{
						Pop(S);
						break;
					}
					else if (stackTop(S) == '[' && str[i] == ']')//匹配'['
					{
						Pop(S);
						break;
					}
					else if (stackTop(S) == '{' && str[i] == '}')//匹配'{'
					{
						Pop(S);
						break;
					}
				}
			}
		}
	}
	//检定栈是否为空
	if (isEmpty(S))
	{
		cout << "括号匹配！" << endl;	
	}
	else
	{
		cout << "左括号多余！" << endl;
	}
}
int main()
{
	string str1 = "(())abc{[(])}";	//左右括号次序不对
	string str2 = "(()))abc{[]}";	//右括号冗余
	string str3 = "(()()abc{[]}";	//左括号冗余
	string str4 = "(())abc{[]()}";	//完全匹配
	bracketMatch(str1);
	bracketMatch(str2);
	bracketMatch(str3);
	bracketMatch(str4);
	system("pause");
	return 0;
}