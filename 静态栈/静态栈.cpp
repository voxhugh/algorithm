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
//��ʼ��
void initStack(Stack_ &S)
{
	S = new Stack;//���ٵ�����
	S->top = -1;//��ջ
}
//�п�
bool isEmpty(const Stack_ &S)
{
	if (!S || S->top == -1)
	{
		return true;
	}
	return false;
}
//����
bool isFull(const Stack_ &S)
{
	if (S->top == MaxSize - 1)
	{
		return true;
	}
	return false;
}
//��ջ
void Push(Stack_ &S,ElemType elem)
{
	//�ж�ջ�Ƿ����� �� ��δ��ʼ��
	if (isFull(S)||!S)
	{
		return;
	}
	S->top++;//ջ��ָ�����
	S->arr[S->top] = elem;
}
//��ջ
ElemType Pop(Stack_ &S)
{
	//�ж�ջ�Ƿ�Ϊ��
	if (isEmpty(S))
	{
		return;
	}
	S->top--;
	return S->arr[S->top + 1];
}
//��ȡջ��
ElemType stackTop(const Stack_ &S)
{
	if (isEmpty(S))
	{
		return ERROR;
	}
	return S->arr[S->top];
}
//���
void cleanStack(Stack_ &S)
{
	S->top = -1;
}
//����
void destroyStack(Stack_ &S)
{
	delete S;
	S = NULL;
}
//�Ƿ�Ϊ����
int isBracket(ElemType elem)
{
	switch (elem)
	{
	case '(':
	case '[':
	case '{':
		return 1;//������
	case ')':
	case ']':
	case '}':
		return 2;//������
	default:
		return 0;//������
	}
}
//����ƥ��
void bracketMatch(string str)
{
	//׼������
	Stack_ S;
	initStack(S);
	ElemType elem;
	//ɨ���ַ���
	for (int i = 0; i < str.size(); i++)
	{
		if (elem = isBracket(str[i]))//���Ϊ����
		{
			switch (elem)
			{
			case 1://�����ţ�����ջ
				Push(S, str[i]);
				break;
			case 2://������
				{
					//�ַ������Ϲ淶
					if (isEmpty(S))
					{
						cout << "�����Ŷ��࣡" << endl;
						return;
					}
					//ƥ�䣬���ջ
					if (stackTop(S) == '(' && str[i] == ')')//ƥ��'('
					{
						Pop(S);
						break;
					}
					else if (stackTop(S) == '[' && str[i] == ']')//ƥ��'['
					{
						Pop(S);
						break;
					}
					else if (stackTop(S) == '{' && str[i] == '}')//ƥ��'{'
					{
						Pop(S);
						break;
					}
				}
			}
		}
	}
	//�춨ջ�Ƿ�Ϊ��
	if (isEmpty(S))
	{
		cout << "����ƥ�䣡" << endl;	
	}
	else
	{
		cout << "�����Ŷ��࣡" << endl;
	}
}
int main()
{
	string str1 = "(())abc{[(])}";	//�������Ŵ��򲻶�
	string str2 = "(()))abc{[]}";	//����������
	string str3 = "(()()abc{[]}";	//����������
	string str4 = "(())abc{[]()}";	//��ȫƥ��
	bracketMatch(str1);
	bracketMatch(str2);
	bracketMatch(str3);
	bracketMatch(str4);
	system("pause");
	return 0;
}