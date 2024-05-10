#include <iostream>
using namespace std;
#define N 4
#define OK 1
#define NEXTOK 2
#define ERROR -1
#include <queue>

class Node
{
public:
	//初始化
	Node()
	{
		this->ptrs = new Node * [N];
		for (int i = 0; i < N - 1; i++)
		{
			this->keys[i] = 0;
			this->ptrs[i] = NULL;
		}
		this->ptrs[N - 1] = NULL;
		this->father = NULL;
		this->keyNum = 0;
		this->ptrNum = 0;
	}

	int keys[N - 1];	//key数组
	Node** ptrs;	//维护4个分支
	Node* father;	//指向父节点
	int keyNum;		//记录key个数
	int ptrNum;		//记录分支个数
};
typedef Node* Tree234;
//创建
void create234(Tree234& root, Node* f)
{
	root = new Node;
	root->father = f;
	cout << "key数：" << endl;
	cin >> root->keyNum;
	if (root->keyNum < 1 || root->keyNum>3)
	{
		return;
	}
	cout << "key：";
	for (int i = 0; i < root->keyNum; i++)
	{
		cin >> root->keys[i];
	}
	cout << "分支数：" << endl;
	cin >> root->ptrNum;
	if (root->ptrNum < 1 || root->ptrNum>4)
	{
		return;
	}
	for (int i = 0; i < root->ptrNum; i++)
	{
		cout << "结点" << root->keys[0] << "...\t分支" << i + 1 << " ";
		create234(root->ptrs[i], root);
	}
}
//查找
Node* find234(const Tree234& root, int k)
{
	//成功返回结点，失败返回临近位置叶结点
	Node* ret = NULL;
	if (!root || !root->keyNum)
	{
		return NULL;
	}
	else if (root->keys[0] == k || root->keys[1] == k || root->keys[2] == k)//k = keyX
	{
		return root;
	}
	if (k < root->keys[0])//k < key1
	{
		ret = find234(root->ptrs[0], k);
		return ret ? ret : root;
	}
	else if (k > root->keys[root->keyNum - 1])//k > keyEnd
	{
		ret = find234(root->ptrs[root->ptrNum - 1], k);
		return ret ? ret : root;
	}
	else if (k > root->keys[0] && k < root->keys[1])//key1 < k < key2
	{
		ret = find234(root->ptrs[1], k);
		return ret ? ret : root;
	}
	else if (k > root->keys[1] && k < root->keys[2])//key2 < k < key3
	{
		ret = find234(root->ptrs[2], k);
		return ret ? ret : root;
	}
}
//分裂
Node*& split(Node*& theNode)
{
	//传入一个3key结点，分裂为三个1key结点，返回根节点
	theNode->keyNum = 1;
	theNode->ptrs[0] = new Node;
	theNode->ptrs[0]->keys[0] = theNode->keys[0];
	theNode->ptrs[0]->father = theNode;
	theNode->ptrs[0]->keyNum = 1;
	theNode->ptrs[1] = new Node;
	theNode->ptrs[1]->keys[0] = theNode->keys[2];
	theNode->ptrs[1]->father = theNode;
	theNode->ptrs[1]->keyNum = 1;
	theNode->keys[0] = theNode->keys[1];
	theNode->keys[1] = theNode->keys[2] = 0;
	return theNode;
}
//获取直接后继（中序）
int getNextInorder(const Tree234& root, Node*& theNode, Node*& latter)
{
	if (root == theNode)
	{
		return NEXTOK;
	}
	int i;
	for (i = 0; i < root->ptrNum; i++)
	{
		int ret = getNextInorder(root->ptrs[i], theNode, latter);
		if (ret == NEXTOK)
		{
			break;
		}
	}
	if (i < root->ptrNum - 1)
	{
		latter = root;
		return OK;
	}
	else if (i < root->ptrNum)
	{
		return NEXTOK;
	}
	return ERROR;
}
//插入
bool insert234(Tree234& root, int k)
{
	Node* pos = find234(root, k);
	//查找成功，无法插入
	if (pos->keys[0] == k || pos->keys[1] == k || pos->keys[2] == k)
	{
		return false;
	}
	//查找失败，开始插入

	int index = 0;//记录3key结点的分裂次数
	queue<Node*> insQ;//记录3key结点分裂后的待插入队列
	bool no3key = false;//本次插入为非3key的标志
	while (!index && no3key)
	{
		//若为1key结点，直接插入
		if (pos->keyNum == 1)
		{
			if (k > pos->keys[0])
			{
				pos->keys[1] = k;
			}
			else
			{
				pos->keys[1] = pos->keys[0];
				pos->keys[0] = k;
			}
			pos->keyNum++;
			no3key = true;
		}
		//若为2key结点，直接插入
		else if (pos->keyNum == 2)
		{
			//0 1
			if (k > pos->keys[1])
			{
				pos->keys[2] = k;
			}
			else if (k > pos->keys[0])
			{
				pos->keys[2] = pos->keys[1];
				pos->keys[1] = k;
			}
			else
			{
				pos->keys[2] = pos->keys[1];
				pos->keys[1] = pos->keys[0];
				pos->keys[0] = k;
			}
			pos->keyNum++;
			no3key = true;
		}
		//若为3key结点
		else if (pos->keyNum == 3)
		{
			//先分裂
			Node* sp = split(pos);
			//调衡：将返回的根节点整体向上层插入
			insQ.push(sp);//待插入结点入队
			pos = sp->father;//交付给上层父节点
			index++;
		}
		//当本次结点非3key，开始出队插入
		if (index && no3key)
		{
			pos = insQ.front();
			insQ.pop();
		}
	}
	return true;
}
//删除
bool delete234(Tree234& root, int k)
{
	Node* pos = find234(root, k);
	//查找失败，无法删除
	if (pos->keys[0] != k && pos->keys[1] != k && pos->keys[2] != k)
	{
		return false;
	}
	//查找成功，开始删除

	int flag0 = 1;//非叶子结点的循环标志
	while (flag0--)
	{
		//若为非叶子结点
		if (pos->ptrNum != 0)
		{
			//中序遍历拿到直接后继
			Node* nextNode = NULL;
			getNextInorder(root, pos, nextNode);
			//找到待删除key的索引
			int nowOrder = 0;
			for (int i = 0; i < pos->keyNum; i++)
			{
				if (pos->keys[i] == k)
				{
					nowOrder = i;
				}
			}
			//将此key后开始到后继1key所有结点前移
			switch (nowOrder)
			{
			case 0:
				pos->keys[0] = pos->keys[1];
			case 1:
				pos->keys[1] = pos->keys[2];
			default:
				pos->keys[pos->keyNum - 1] = nextNode->keys[0];
			}
			//交付给后继结点，对后继结点第1key执行删除
			pos = nextNode;
			k = nextNode->keys[0];
			flag0++;

		}
		//若为2key结点，直接删除
		else if (pos->keyNum == 2)
		{
			//0 1
			if (k == pos->keys[0])
			{
				pos->keys[0] = pos->keys[1];
			}
			else
			{
				pos->keys[1] = 0;
			}
			pos->keyNum--;
		}
		//若3key结点，直接删除
		else if (pos->keyNum == 3)
		{
			//0 1 2
			if (k == pos->keys[0])
			{
				pos->keys[0] = pos->keys[1];
				pos->keys[1] = pos->keys[2];
			}
			else if (k == pos->keys[1])
			{
				pos->keys[1] = pos->keys[2];
				pos->keys[2] = 0;
			}
			else
			{
				pos->keys[2] = 0;
			}
			pos->keyNum--;
		}
		//若为1key结点
		else if (pos->keyNum == 1)
		{
			int flag11 = 1;//父1key,兄1key的循环标志
			while (flag11--)
			{
				int fk = pos->father->keyNum;
				if (fk == 1)
				{
					int broOrder = (pos->father->ptrs[0] == pos ? 1 : 0);//判定左/右兄弟，决定平移方向
					int brok = pos->father->ptrs[broOrder]->keyNum;

					//父1key,兄2/3key：f—>bro平移平替
					if (brok == 2 || brok == 3)
					{
						pos->keys[0] = pos->father->keys[0];//f1key—>now1key
						pos->father->keys[0] = pos->father->ptrs[broOrder]->keys[broOrder ? 0 : brok - 1];//bro1key或2/3key—>f1key
						//若为右兄弟，兄弟内部调整
						if (broOrder)
						{
							pos->father->ptrs[broOrder]->keys[0] = pos->father->ptrs[broOrder]->keys[1];
							pos->father->ptrs[broOrder]->keys[brok - 2] = pos->father->ptrs[broOrder]->keys[brok - 1];
						}
						pos->father->ptrs[broOrder]->keyNum--;
					}
					//父1key,兄1key：f∪bro，重复
					else if (brok == 1)
					{
						if (broOrder == 0)//若为左兄，父结点内部调整
						{
							pos->father->keys[1] = pos->father->keys[0];
						}
						pos->father->keys[broOrder ? 1 : 0] = pos->father->ptrs[broOrder]->keys[0];
						pos->father->keyNum++;
						pos = pos->father;//交付给父结点
						pos->ptrs[0] = pos->ptrs[1] = NULL;
						pos->ptrNum = 0;
						flag11++;
					}
				}
				else if (fk == 2 || fk == 3)
				{
					int nowOrder = 0;//当前结点索引
					int broOrder = 1;//兄弟结点索引
					int brok = 1;//兄弟结点key数
					if (pos->father->ptrs[0] == pos)
					{
						nowOrder = 0;
						broOrder = 1;
					}
					else if (pos->father->ptrs[1] == pos)
					{
						nowOrder = 1;
						broOrder = (pos->father->ptrs[0]->keyNum == 3 ? 2 : 0);
					}
					else if (pos->father->ptrs[2] == pos)
					{
						nowOrder = 2;
						broOrder = (pos->father->ptrs[1]->keyNum == 3 ? 3 : 1);
					}
					brok = pos->father->ptrs[broOrder]->keyNum;

					//父2/3key,兄1/2key：f某key↓∪bro
					if (brok == 1 || brok == 2)
					{
						//默认f某key向右交付至bro
						if (broOrder != 0)
						{
							//父结点向右交付
							pos->father->ptrs[broOrder]->keys[2] = pos->father->ptrs[broOrder]->keys[1];
							pos->father->ptrs[broOrder]->keys[1] = pos->father->ptrs[broOrder]->keys[0];
							pos->father->ptrs[broOrder]->keys[0] = pos->father->keys[broOrder - 1];
							pos->father->ptrs[broOrder]->keyNum++;
							//删除目标结点
							switch (nowOrder)
							{
							case 0:
								pos->father->ptrs[0] = pos->father->ptrs[1];
							case 1:
								pos->father->ptrs[1] = pos->father->ptrs[2];
							case 2:
								pos->father->ptrs[2] = pos->father->ptrs[3];
							default:
								pos->father->ptrs[3] = NULL;
								pos->father->ptrNum--;
							}
							//父结点内部调整
							switch (broOrder - 1)
							{
							case 0:
								pos->father->keys[0] = pos->father->keys[1];
							case 1:
								pos->father->keys[1] = pos->father->keys[2];
							default:
								pos->father->keyNum--;
							}
						}
						//当兄弟结点在最左侧
						else
						{
							//父结点向左交付
							pos->father->ptrs[0]->keys[brok] = pos->father->keys[1];
							pos->father->ptrs[0]->keyNum++;
							pos->father->keys[0] = pos->father->keys[1];
							pos->father->keys[1] = pos->father->keys[2];
							pos->father->keyNum--;
						}
					}
					//父2/3key,兄3key：f某key↓单结点，bro第2key↑∪f
					else if (brok == 3)
					{
						//f:0 1 [2] bro:0 1 2
						int fOrder = (nowOrder + broOrder) / 2;//f中下移key的索引
						//f：下移key覆盖待删除结点
						pos->keys[0] = pos->father->keys[fOrder];
						//bro：邻近删除结点端的key合并至待删除结点
						if (nowOrder > broOrder)
						{
							pos->keys[1] = pos->keys[0];
						}
						pos->keys[nowOrder < broOrder ? 1 : 0] = pos->father->ptrs[broOrder]->keys[nowOrder < broOrder ? 0 : 2];
						pos->keyNum++;
						//bro:第二key向上合并至f
						pos->father->keys[fOrder] = pos->father->ptrs[broOrder]->keys[1];
						if (nowOrder < broOrder)//若为右兄，兄结点内部调整
						{
							pos->father->ptrs[broOrder]->keys[0] = pos->father->ptrs[broOrder]->keys[2];
						}
						pos->father->ptrs[broOrder]->keyNum = 1;
					}
				}
			}
		}
	}
}
int main()
{
	Tree234 t234;
	create234(t234, NULL);
	insert234(t234, 9);
	delete234(t234, 11);
	system("pause");
	return 0;
}