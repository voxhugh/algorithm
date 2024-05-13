#include <iostream>
using namespace std;
#define RED true	//红：true
#define BLACK false	//黑：false
#define NIL NULL	//Nil：叶结点
#define OK 1
#define ERROR -1
#define NEXT 2
#define FLAG25 25		//递归标志——删除操作X两子&R无子：第二种
#define FLAG43 43		//递归标志——删除操作X两子&R无子：第四种
#define FLAG69 69		//递归标志——删除操作X两子&R无子：第六种
#define FLAG87 87		//递归标志——删除操作X两子&R无子：第八种
#define FLAG5 5			//递归标志——删除操作X两子&R无子：第五种
#define FLAG9 9			//递归标志——删除操作X两子&R无子：第九种
typedef int ElemType;

typedef struct node
{
	ElemType val;
	struct node* left, * right, * parent;
	bool color;//色值域
}RbNode, * RbTree;
//创建
void createRb(RbTree& root, RbNode* f)
{
	//须用户指定查找树序列
	char value;
	cin >> value;
	if (value == '.')//表示Nil
	{
		root = NULL;
		return;
	}
	root = new RbNode;
	root->val = value - '0';
	root->parent = f;
	cout << "当前：" << root->val;
	cout << "\t颜色：红1、黑0\t";
	cin >> root->color;
	cout << "【" << root->val << "】" << "左子树：" << endl;
	createRb(root->left, root);
	cout << "【" << root->val << "】右子树：" << endl;
	createRb(root->right, root);
}
//查找
int findRb(const RbTree& root, ElemType k, RbNode*& s)
{
	//叶结点
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
//左旋
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
//右旋
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
//获取直接后继（中序）
int getNext(RbTree& root, RbNode*& N, RbNode*& R)
{
	if (!root)
	{
		return ERROR;
	}
	int ret;
	ret = getNext(root->left, N, R);//左
	switch (ret)
	{
	case NEXT:
		R = root;
	case OK:
		return OK;
	default:
		break;
	}
	if (root->val == N->val)//中
	{
		return NEXT;
	}
	ret = getNext(root->right, N, R);//右
	return ret == NEXT ? NEXT : ERROR;
}
//插入
RbNode*& insertRb(RbTree& root, ElemType k)
{
	//N：待插	P：父	G：祖父	U：叔叔
	RbNode* N = NULL;
	RbNode* G = NULL;
	RbNode* U = NULL;
	RbNode* P = NULL;
	findRb(root, k, P);

	//查找成功
	if (P->left || P->right)
	{
		P->val = k;
		//自平衡
		if (P->color == BLACK || P->parent->color == BLACK)
		{
			return P;
		}
		//处理递归在连红结点的情况
		N = P;
		P = N->parent;
	}
	//查找失败
	else
	{
		N = new RbNode;
		N->val = k;
		N->color = RED;
		N->left = N->right = NULL;
		N->parent = P;
		//P,N相连
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

	//插入正式开始

	//空树
	if (!root)//变黑后插入
	{
		N->color = BLACK;
		root = N;
	}
	//P黑
	if (P->color == BLACK)//直接插入
	{
		return N;
	}
	//P红&U红
	else if (U->color == RED)
	{
		P->color = BLACK;//P变黑
		U->color = BLACK;//U变黑

		if (G->parent == NULL)//若G为根，则变黑
		{
			G->color = BLACK;
		}
		else//不为根，则变红
		{
			G->color = RED;
			//若GP为红，向上递归
			RbNode* GP = G->parent;
			if (GP->color == RED)
			{
				insertRb(root, GP->val);
			}
		}
	}
	//P红&U黑&PNG
	else if (P->right == N && G->left == P)
	{
		RbNode* newN = zag(P);//P左旋
		newN = newN->left;
		insertRb(root, newN->val);//递归到NPG情况
	}
	//P红&U黑&NPG
	else if (P->left == N && G->left == P)
	{
		zig(G);//G右旋
		//P与G换色
		bool temp = P->color;
		P->color = G->color;
		G->color = temp;
	}
	return N;
}
//删除
int deleteRb(RbTree& root, ElemType k, int flag = 0, int tempK = 0)
{
	//flag：部分递归操作标志	tempK：查找树结构被破坏时的临时检索值
	//X：待删	R：后继	P：父	S：兄弟
	RbNode* X = NULL;
	RbNode* R = NULL;
	RbNode* P = NULL;
	RbNode* S = NULL;
	RbNode* SL = NULL;
	RbNode* SR = NULL;
	int ret = findRb(root, k, X);
	//查找失败，返回
	if (ret == ERROR)
	{
		return ERROR;
	}
	//查找成功，针对递归情况初始化
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

	//删除正式开始

	//X无子
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
		//直接删除
		delete X;
		X = NULL;
		return OK;
	}
	//X一子
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
		ElemType tempXN = XN->val;//X子替代X
		deleteRb(root, XN->val);//递归删除X子
		X->val = tempXN;
		return OK;
	}
	//X两子&RR
	else if (X->left != NIL && X->right != NIL && R->right != NIL)
	{
		ElemType tempR = R->val;//R替代X
		deleteRb(root, R->val);//递归删除R
		X->val = tempR;
		return OK;
	}
	//以下情景均为：X两子&R无子

	//【1】R红
	else if (R->color == RED)
	{
		//变为X色，逻辑删除
		if (P->left == R)
		{
			P->left = NIL;
		}
		else
		{
			P->right = NIL;
		}
	}
	//【2】R黑&S红&RP
	else if (S->color = RED && P->left == R)
	{
		S->color = BLACK;//S变黑
		P->color = RED;//P变红
		zag(P);//P左旋
		deleteRb(root, k, FLAG25, R->val);//递归到第五种处理
	}
	//【3】R黑&S黑&SR红&RP
	else if (S->color == BLACK && SR->color == RED && P->left == R)
	{
		S->color = P->color;//S变为P色
		P->color = BLACK;//P变黑
		SR->color = BLACK;//SR变黑
		zag(P);//P左旋
		//逻辑删除
		P->left = NIL;
	}
	//【4】R黑&S黑&SR黑&SL红&RP
	else if (S->color == BLACK && SR->color == BLACK && SL->color == RED && P->left == R)
	{
		S->color = RED;//S变红
		SL->color = BLACK;//SL变黑
		zig(S);//S右旋
		deleteRb(root, k, FLAG43, R->val);//递归到第三种处理
	}
	//【5】R黑&S黑&SR黑&SL黑&RP
	else if (S->color == BLACK && SR->color == BLACK && SL->color == BLACK && P->left == R)
	{
		S->color = RED;//S变红
		deleteRb(root, k, FLAG5, P->val);//P替代R递归处理
	}
	//【6】R黑&S红&PR
	else if (S->color == RED && P->right == R)
	{
		S->color = BLACK;//S变黑
		P->color = RED;//P变红
		zig(P);//P右旋
		deleteRb(root, k, FLAG69, S->val);//递归到第九种处理
	}
	//【7】R黑&S黑&SL红&PR
	else if (S->color == BLACK && SL->color == RED && P->right == R)
	{
		S->color = P->color;//S变为P色
		P->color = BLACK;//P变黑
		SL->color = BLACK;//SL变黑
		zig(P);//P右旋
		//逻辑删除
		P->right = NIL;
	}
	//【8】R黑&S黑&SR红&SL黑&PR
	else if (S->color == BLACK && SR->color == RED && SL->color == BLACK && P->right == R)
	{
		S->color = RED;//S变红
		SR->color = BLACK;//SR变黑
		zag(S);//S左旋
		deleteRb(root, k, FLAG87, P->val);//递归到第七种处理
	}
	//【9】R黑&S黑&SR黑&SL黑&PR
	else if (S->color == BLACK && SR->color == BLACK && SL->color == BLACK && P->right == R)
	{
		S->color = RED;//S变红
		deleteRb(root, k, FLAG9, P->val);//P替代R递归处理
	}
	//删除
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