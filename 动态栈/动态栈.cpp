#include <iostream>
#include <cmath>
using namespace std;
typedef char ElemType;
#define ERROR '-1'//����ElemTypeΪchar�����Ӧ�ַ�'-1'

typedef struct Node
{
	ElemType data;
	struct Node* next;
}StackNode,*LinkStack;
//��ʼ��
void initLinkStack(LinkStack& S)
{
	S = new StackNode;//ջ��ǰ����ͷ���
	S->data = 0;//��¼ջ��Ԫ�ظ���
	S->next = NULL;
}
//��ջ
void Push(LinkStack& S, ElemType elem)
{
	//�Ƿ��ѳ�ʼ��
	if (!S)
	{
		return;
	}
	//ջ����ȳ�������ջ��ͷ��
	StackNode* p = new StackNode;
	p->data = elem;
	p->next = S->next;
	S->next = p;
	S->data++;//����ջ�޷��������������ʱ���Ԫ�ظ���ֻ�ܲ���ʱ��¼
}
//��ջ
ElemType Pop(LinkStack& S)
{
	//�п�
	if (!S || !S->data)
	{
		return ERROR;
	}
	StackNode* temp;
	ElemType tempdata;
	temp = S->next;//�ݴ�ջ��Ԫ��
	tempdata = temp->data;//����ջ��Ԫ��ֵ
	S->next = temp->next;
	S->data--;
	delete temp;
	temp = NULL;
	return tempdata;
}
//��ȡջ��
ElemType stackTop(const LinkStack& S)
{
	//�п�
	if (!S || !S->data)
	{
		return ERROR;
	}
	return S->next->data;
}
//����
void destroyStack(LinkStack& S)
{
	//ջ��Ϊ��
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
//�Ƿ�Ϊ��������� �����ж����ȼ�������	�񷵻�0
int isOperator_Priority(ElemType elem)
{
	/*	����Ϊ��������������ȼ�������Խ�����ȼ�Խ�ߣ�
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
//����
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
//���ʽ��ֵ	���������ֻ�ṩ�������������ʽ����'#'�������Ҳ�������Ϊ��Ȼ����
int expr(string str)
{
	//׼��������̬ջ
	LinkStack NUM;//��Ų�����
	LinkStack OPT;//��������
	initLinkStack(NUM);
	initLinkStack(OPT);
	int ret1;//�ݴ��ַ����ȼ�
	int ret2;//�ݴ�OPTջ�����ȼ�
	//�����ַ���
	for (int i = 0; i < str.size(); i++)
	{
		//������ ֱ����ջ
		if (!(ret1=isOperator_Priority(str[i])))
		{
			Push(NUM, str[i]);
			continue;
		}
		//����� ջΪ�գ�ֱ����ջ
		if ((ret2 = stackTop(OPT))=='-1')
		{
			Push(OPT, str[i]);
			continue;
		}
		ret2 = isOperator_Priority(ret2);
		//����ջ�����ȼ� �� ���ʽ����ʱ ��ʼ��ջ����
		if (ret1<=ret2||str[i]=='#')
		{
			ElemType op =Pop(OPT);//�������ջ
			int num2 = Pop(NUM)-'0';//������2��ջ	char to int
			int num1 = Pop(NUM)-'0';//������1��ջ	char to int
			int expNum = execute(num1, op, num2);//������ʽ��ֵ
			Push(NUM, expNum+'0');//�����ջ	int to char
			continue;
		}//����ջ�����������ջ
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