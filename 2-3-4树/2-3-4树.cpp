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
	//��ʼ��
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

	int keys[N - 1];	//key����
	Node** ptrs;	//ά��4����֧
	Node* father;	//ָ�򸸽ڵ�
	int keyNum;		//��¼key����
	int ptrNum;		//��¼��֧����
};
typedef Node* Tree234;
//����
void create234(Tree234& root, Node* f)
{
	root = new Node;
	root->father = f;
	cout << "key����" << endl;
	cin >> root->keyNum;
	if (root->keyNum < 1 || root->keyNum>3)
	{
		return;
	}
	cout << "key��";
	for (int i = 0; i < root->keyNum; i++)
	{
		cin >> root->keys[i];
	}
	cout << "��֧����" << endl;
	cin >> root->ptrNum;
	if (root->ptrNum < 1 || root->ptrNum>4)
	{
		return;
	}
	for (int i = 0; i < root->ptrNum; i++)
	{
		cout << "���" << root->keys[0] << "...\t��֧" << i + 1 << " ";
		create234(root->ptrs[i], root);
	}
}
//����
Node* find234(const Tree234& root, int k)
{
	//�ɹ����ؽ�㣬ʧ�ܷ����ٽ�λ��Ҷ���
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
//����
Node*& split(Node*& theNode)
{
	//����һ��3key��㣬����Ϊ����1key��㣬���ظ��ڵ�
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
//��ȡֱ�Ӻ�̣�����
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
//����
bool insert234(Tree234& root, int k)
{
	Node* pos = find234(root, k);
	//���ҳɹ����޷�����
	if (pos->keys[0] == k || pos->keys[1] == k || pos->keys[2] == k)
	{
		return false;
	}
	//����ʧ�ܣ���ʼ����

	int index = 0;//��¼3key���ķ��Ѵ���
	queue<Node*> insQ;//��¼3key�����Ѻ�Ĵ��������
	bool no3key = false;//���β���Ϊ��3key�ı�־
	while (!index && no3key)
	{
		//��Ϊ1key��㣬ֱ�Ӳ���
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
		//��Ϊ2key��㣬ֱ�Ӳ���
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
		//��Ϊ3key���
		else if (pos->keyNum == 3)
		{
			//�ȷ���
			Node* sp = split(pos);
			//���⣺�����صĸ��ڵ��������ϲ����
			insQ.push(sp);//�����������
			pos = sp->father;//�������ϲ㸸�ڵ�
			index++;
		}
		//�����ν���3key����ʼ���Ӳ���
		if (index && no3key)
		{
			pos = insQ.front();
			insQ.pop();
		}
	}
	return true;
}
//ɾ��
bool delete234(Tree234& root, int k)
{
	Node* pos = find234(root, k);
	//����ʧ�ܣ��޷�ɾ��
	if (pos->keys[0] != k && pos->keys[1] != k && pos->keys[2] != k)
	{
		return false;
	}
	//���ҳɹ�����ʼɾ��

	int flag0 = 1;//��Ҷ�ӽ���ѭ����־
	while (flag0--)
	{
		//��Ϊ��Ҷ�ӽ��
		if (pos->ptrNum != 0)
		{
			//��������õ�ֱ�Ӻ��
			Node* nextNode = NULL;
			getNextInorder(root, pos, nextNode);
			//�ҵ���ɾ��key������
			int nowOrder = 0;
			for (int i = 0; i < pos->keyNum; i++)
			{
				if (pos->keys[i] == k)
				{
					nowOrder = i;
				}
			}
			//����key��ʼ�����1key���н��ǰ��
			switch (nowOrder)
			{
			case 0:
				pos->keys[0] = pos->keys[1];
			case 1:
				pos->keys[1] = pos->keys[2];
			default:
				pos->keys[pos->keyNum - 1] = nextNode->keys[0];
			}
			//��������̽�㣬�Ժ�̽���1keyִ��ɾ��
			pos = nextNode;
			k = nextNode->keys[0];
			flag0++;

		}
		//��Ϊ2key��㣬ֱ��ɾ��
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
		//��3key��㣬ֱ��ɾ��
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
		//��Ϊ1key���
		else if (pos->keyNum == 1)
		{
			int flag11 = 1;//��1key,��1key��ѭ����־
			while (flag11--)
			{
				int fk = pos->father->keyNum;
				if (fk == 1)
				{
					int broOrder = (pos->father->ptrs[0] == pos ? 1 : 0);//�ж���/���ֵܣ�����ƽ�Ʒ���
					int brok = pos->father->ptrs[broOrder]->keyNum;

					//��1key,��2/3key��f��>broƽ��ƽ��
					if (brok == 2 || brok == 3)
					{
						pos->keys[0] = pos->father->keys[0];//f1key��>now1key
						pos->father->keys[0] = pos->father->ptrs[broOrder]->keys[broOrder ? 0 : brok - 1];//bro1key��2/3key��>f1key
						//��Ϊ���ֵܣ��ֵ��ڲ�����
						if (broOrder)
						{
							pos->father->ptrs[broOrder]->keys[0] = pos->father->ptrs[broOrder]->keys[1];
							pos->father->ptrs[broOrder]->keys[brok - 2] = pos->father->ptrs[broOrder]->keys[brok - 1];
						}
						pos->father->ptrs[broOrder]->keyNum--;
					}
					//��1key,��1key��f��bro���ظ�
					else if (brok == 1)
					{
						if (broOrder == 0)//��Ϊ���֣�������ڲ�����
						{
							pos->father->keys[1] = pos->father->keys[0];
						}
						pos->father->keys[broOrder ? 1 : 0] = pos->father->ptrs[broOrder]->keys[0];
						pos->father->keyNum++;
						pos = pos->father;//�����������
						pos->ptrs[0] = pos->ptrs[1] = NULL;
						pos->ptrNum = 0;
						flag11++;
					}
				}
				else if (fk == 2 || fk == 3)
				{
					int nowOrder = 0;//��ǰ�������
					int broOrder = 1;//�ֵܽ������
					int brok = 1;//�ֵܽ��key��
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

					//��2/3key,��1/2key��fĳkey����bro
					if (brok == 1 || brok == 2)
					{
						//Ĭ��fĳkey���ҽ�����bro
						if (broOrder != 0)
						{
							//��������ҽ���
							pos->father->ptrs[broOrder]->keys[2] = pos->father->ptrs[broOrder]->keys[1];
							pos->father->ptrs[broOrder]->keys[1] = pos->father->ptrs[broOrder]->keys[0];
							pos->father->ptrs[broOrder]->keys[0] = pos->father->keys[broOrder - 1];
							pos->father->ptrs[broOrder]->keyNum++;
							//ɾ��Ŀ����
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
							//������ڲ�����
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
						//���ֵܽ���������
						else
						{
							//��������󽻸�
							pos->father->ptrs[0]->keys[brok] = pos->father->keys[1];
							pos->father->ptrs[0]->keyNum++;
							pos->father->keys[0] = pos->father->keys[1];
							pos->father->keys[1] = pos->father->keys[2];
							pos->father->keyNum--;
						}
					}
					//��2/3key,��3key��fĳkey������㣬bro��2key����f
					else if (brok == 3)
					{
						//f:0 1 [2] bro:0 1 2
						int fOrder = (nowOrder + broOrder) / 2;//f������key������
						//f������key���Ǵ�ɾ�����
						pos->keys[0] = pos->father->keys[fOrder];
						//bro���ڽ�ɾ�����˵�key�ϲ�����ɾ�����
						if (nowOrder > broOrder)
						{
							pos->keys[1] = pos->keys[0];
						}
						pos->keys[nowOrder < broOrder ? 1 : 0] = pos->father->ptrs[broOrder]->keys[nowOrder < broOrder ? 0 : 2];
						pos->keyNum++;
						//bro:�ڶ�key���Ϻϲ���f
						pos->father->keys[fOrder] = pos->father->ptrs[broOrder]->keys[1];
						if (nowOrder < broOrder)//��Ϊ���֣��ֽ���ڲ�����
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