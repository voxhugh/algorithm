#include <iostream>
using namespace std;
#define ElemType char

typedef struct CNode
{
	ElemType data;//������
	struct CNode* next;//ָ����
}CNode,*CLinkList;
//��ʼ��
void initCLinkList(CLinkList& R)
{
	R = new CNode;//R:βָ��
	R->next = new CNode;//ָ��ͷ���
	R->next->data = 0;//ͷ����¼������ʼΪ0
	R->next->next = NULL;//�ձ�
}
//����	β��
void createCLinkList(CLinkList& R)
{
	CNode* temp = R->next;//�ݴ�ͷ����ָ��
	R = R->next;//��R��ͷ��㿪ʼ��������
	CNode* p;
	ElemType ch;
	while (true)
	{
		cin >> ch;
		if (ch == '$')
		{
			R->next = temp;//��β����ָ��ͷ���
			break;
		}
		p = new CNode;
		p->data = ch;
		R->next = p;
		R = p;
		temp->data++;
	}
}
int main()
{
	CLinkList R;
	initCLinkList(R);
	createCLinkList(R);
	//printCLinkList(R);
	system("pause");
	return 0;
}