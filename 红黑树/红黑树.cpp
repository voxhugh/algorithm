#include <iostream>
using namespace std;
#define RED true	//�죺true
#define BLACK false	//�ڣ�false
#define NIL NULL	//Nil��Ҷ���
#define OK 1
#define ERROR -1
#define NEXT 2
#define FLAG25 25		//�ݹ��־����ɾ������X����&R���ӣ��ڶ���
#define FLAG43 43		//�ݹ��־����ɾ������X����&R���ӣ�������
#define FLAG69 69		//�ݹ��־����ɾ������X����&R���ӣ�������
#define FLAG87 87		//�ݹ��־����ɾ������X����&R���ӣ��ڰ���
#define FLAG5 5			//�ݹ��־����ɾ������X����&R���ӣ�������
#define FLAG9 9			//�ݹ��־����ɾ������X����&R���ӣ��ھ���
typedef int ElemType;

typedef struct node
{
	ElemType val;
	struct node* left, * right, * parent;
	bool color;//ɫֵ��
}RbNode, * RbTree;
//����
void createRb(RbTree& root, RbNode* f)
{
	//���û�ָ������������
	char value;
	cin >> value;
	if (value == '.')//��ʾNil
	{
		root = NULL;
		return;
	}
	root = new RbNode;
	root->val = value - '0';
	root->parent = f;
	cout << "��ǰ��" << root->val;
	cout << "\t��ɫ����1����0\t";
	cin >> root->color;
	cout << "��" << root->val << "��" << "��������" << endl;
	createRb(root->left, root);
	cout << "��" << root->val << "����������" << endl;
	createRb(root->right, root);
}
//����
int findRb(const RbTree& root, ElemType k, RbNode*& s)
{
	//Ҷ���
	if (root == NIL)
	{
		return NEXT;
	}
	int ret = 0;
	if (k == root->val)
	{
		s = root;
		return OK;
	}
	else if (k < root->val)
	{
		ret = findRb(root->left, k, s);
	}
	else
	{
		ret = findRb(root->right, k, s);
	}
	switch (ret)
	{
	case 1:
		return OK;
	case 2:
		s = root;
	default:
		return ERROR;
	}
}
//����
RbNode*& zag(RbNode*& N)
{
	RbNode* P = N->parent;
	RbNode* R = N->right;
	R->left->parent = N;
	N->right = R->left;
	N->parent = R;
	R->left = N;
	R->parent = P;
	return R;
}
//����
RbNode*& zig(RbNode*& N)
{
	RbNode* P = N->parent;
	RbNode* L = N->left;
	L->right->parent = N;
	N->left = L->right;
	N->parent = L;
	L->right = N;
	L->parent = P;
	return L;
}
//��ȡֱ�Ӻ�̣�����
int getNext(RbTree& root, RbNode*& N, RbNode*& R)
{
	if (!root)
	{
		return ERROR;
	}
	int ret;
	ret = getNext(root->left, N, R);//��
	switch (ret)
	{
	case NEXT:
		R = root;
	case OK:
		return OK;
	default:
		break;
	}
	if (root->val == N->val)//��
	{
		return NEXT;
	}
	ret = getNext(root->right, N, R);//��
	return ret == NEXT ? NEXT : ERROR;
}
//����
RbNode*& insertRb(RbTree& root, ElemType k)
{
	//N������	P����	G���游	U������
	RbNode* N = NULL;
	RbNode* G = NULL;
	RbNode* U = NULL;
	RbNode* P = NULL;
	findRb(root, k, P);

	//���ҳɹ�
	if (P->left || P->right)
	{
		P->val = k;
		//��ƽ��
		if (P->color == BLACK || P->parent->color == BLACK)
		{
			return P;
		}
		//����ݹ�������������
		N = P;
		P = N->parent;
	}
	//����ʧ��
	else
	{
		N = new RbNode;
		N->val = k;
		N->color = RED;
		N->left = N->right = NULL;
		N->parent = P;
		//P,N����
		if (N->val < P->val)
		{
			P->left = N;
		}
		else
		{
			P->right = N;
		}
	}
	G = P->parent;
	U = G->right;

	//������ʽ��ʼ

	//����
	if (!root)//��ں����
	{
		N->color = BLACK;
		root = N;
	}
	//P��
	if (P->color == BLACK)//ֱ�Ӳ���
	{
		return N;
	}
	//P��&U��
	else if (U->color == RED)
	{
		P->color = BLACK;//P���
		U->color = BLACK;//U���

		if (G->parent == NULL)//��GΪ��������
		{
			G->color = BLACK;
		}
		else//��Ϊ��������
		{
			G->color = RED;
			//��GPΪ�죬���ϵݹ�
			RbNode* GP = G->parent;
			if (GP->color == RED)
			{
				insertRb(root, GP->val);
			}
		}
	}
	//P��&U��&PNG
	else if (P->right == N && G->left == P)
	{
		RbNode* newN = zag(P);//P����
		newN = newN->left;
		insertRb(root, newN->val);//�ݹ鵽NPG���
	}
	//P��&U��&NPG
	else if (P->left == N && G->left == P)
	{
		zig(G);//G����
		//P��G��ɫ
		bool temp = P->color;
		P->color = G->color;
		G->color = temp;
	}
	return N;
}
//ɾ��
int deleteRb(RbTree& root, ElemType k, int flag = 0, int tempK = 0)
{
	//flag�����ֵݹ������־	tempK���������ṹ���ƻ�ʱ����ʱ����ֵ
	//X����ɾ	R�����	P����	S���ֵ�
	RbNode* X = NULL;
	RbNode* R = NULL;
	RbNode* P = NULL;
	RbNode* S = NULL;
	RbNode* SL = NULL;
	RbNode* SR = NULL;
	int ret = findRb(root, k, X);
	//����ʧ�ܣ�����
	if (ret == ERROR)
	{
		return ERROR;
	}
	//���ҳɹ�����Եݹ������ʼ��
	if (flag == FLAG25)
	{
		findRb(root, tempK, R);
		P = R->parent;
		S = P->parent;
		SL = P->right;
		SR = S->right;
	}
	else if (flag == FLAG43)
	{
		findRb(root, tempK, R);
		P = R->parent;
		SL = P->right;
		S = SL->right;
		SR = S->right;
	}
	else if (flag == FLAG69)
	{
		findRb(root, tempK, S);
		SL = S->left;
		P = S->right;
		SR = P->left;
		R = P->right;
	}
	else if (flag == FLAG87)
	{
		findRb(root, tempK, P);
		R = P->right;
		SR = P->left;
		S = SR->left;
		SL = S->left;
	}
	else if (flag == FLAG5)
	{
		findRb(root, tempK, R);
		P = R->parent;
		S = P->right;
		SL = S->left;
		SR = S->right;
	}
	else if (flag == FLAG9)
	{
		findRb(root, tempK, R);
		P = R->parent;
		S = P->right;
		SL = S->left;
		SR = S->right;
	}
	else
	{
		getNext(root, X, R);
		P = R->parent;
		S = P->right;
		SL = S->left;
		SR = S->right;
	}

	//ɾ����ʽ��ʼ

	//X����
	if (X->left == NIL && X->right == NIL)
	{
		RbNode* tempP = X->parent;
		if (tempP->left == X)
		{
			tempP->left = NIL;
		}
		else
		{
			tempP->right = NIL;
		}
		//ֱ��ɾ��
		delete X;
		X = NULL;
		return OK;
	}
	//Xһ��
	else if (X->left && !X->right || !X->left && X->right)
	{
		RbNode* XN = NULL;
		if (X->left == NIL)
		{
			XN = X->right;
		}
		else
		{
			XN = X->left;
		}
		ElemType tempXN = XN->val;//X�����X
		deleteRb(root, XN->val);//�ݹ�ɾ��X��
		X->val = tempXN;
		return OK;
	}
	//X����&RR
	else if (X->left != NIL && X->right != NIL && R->right != NIL)
	{
		ElemType tempR = R->val;//R���X
		deleteRb(root, R->val);//�ݹ�ɾ��R
		X->val = tempR;
		return OK;
	}
	//�����龰��Ϊ��X����&R����

	//��1��R��
	else if (R->color == RED)
	{
		//��ΪXɫ���߼�ɾ��
		if (P->left == R)
		{
			P->left = NIL;
		}
		else
		{
			P->right = NIL;
		}
	}
	//��2��R��&S��&RP
	else if (S->color = RED && P->left == R)
	{
		S->color = BLACK;//S���
		P->color = RED;//P���
		zag(P);//P����
		deleteRb(root, k, FLAG25, R->val);//�ݹ鵽�����ִ���
	}
	//��3��R��&S��&SR��&RP
	else if (S->color == BLACK && SR->color == RED && P->left == R)
	{
		S->color = P->color;//S��ΪPɫ
		P->color = BLACK;//P���
		SR->color = BLACK;//SR���
		zag(P);//P����
		//�߼�ɾ��
		P->left = NIL;
	}
	//��4��R��&S��&SR��&SL��&RP
	else if (S->color == BLACK && SR->color == BLACK && SL->color == RED && P->left == R)
	{
		S->color = RED;//S���
		SL->color = BLACK;//SL���
		zig(S);//S����
		deleteRb(root, k, FLAG43, R->val);//�ݹ鵽�����ִ���
	}
	//��5��R��&S��&SR��&SL��&RP
	else if (S->color == BLACK && SR->color == BLACK && SL->color == BLACK && P->left == R)
	{
		S->color = RED;//S���
		deleteRb(root, k, FLAG5, P->val);//P���R�ݹ鴦��
	}
	//��6��R��&S��&PR
	else if (S->color == RED && P->right == R)
	{
		S->color = BLACK;//S���
		P->color = RED;//P���
		zig(P);//P����
		deleteRb(root, k, FLAG69, S->val);//�ݹ鵽�ھ��ִ���
	}
	//��7��R��&S��&SL��&PR
	else if (S->color == BLACK && SL->color == RED && P->right == R)
	{
		S->color = P->color;//S��ΪPɫ
		P->color = BLACK;//P���
		SL->color = BLACK;//SL���
		zig(P);//P����
		//�߼�ɾ��
		P->right = NIL;
	}
	//��8��R��&S��&SR��&SL��&PR
	else if (S->color == BLACK && SR->color == RED && SL->color == BLACK && P->right == R)
	{
		S->color = RED;//S���
		SR->color = BLACK;//SR���
		zag(S);//S����
		deleteRb(root, k, FLAG87, P->val);//�ݹ鵽�����ִ���
	}
	//��9��R��&S��&SR��&SL��&PR
	else if (S->color == BLACK && SR->color == BLACK && SL->color == BLACK && P->right == R)
	{
		S->color = RED;//S���
		deleteRb(root, k, FLAG9, P->val);//P���R�ݹ鴦��
	}
	//ɾ��
	X->val = R->val;
	delete R;
	R = NULL;
	return OK;
}
int main()
{
	RbTree rbt;
	createRb(rbt, NULL);
	insertRb(rbt, 9);
	deleteRb(rbt, 13);
	system("pause");
	return 0;
}