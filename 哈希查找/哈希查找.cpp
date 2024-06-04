#include <iostream>
using namespace std;
#define HashSize 5

typedef struct hashNode
{
	int val;
	struct hashNode* next;
}HashNode;
typedef struct hashTable
{
	HashNode hash[HashSize];
	int count;
}HashTable;

int hash_mod(int k)
{
	return k % HashSize;
}
void insert_HashTable(HashTable*& ht, int k)
{
	int index = hash_mod(k);
	if (ht->hash[index].val == -1)
	{
		ht->hash[index].val = k;
		ht->count++;
		return;
	}
	HashNode* p = new HashNode;
	p->val = k;
	p->next = ht->hash[index].next;
	ht->hash[index].next = p;
	ht->count++;
}
void crtHashTable(int a[], int len, HashTable*& ht)
{
	ht = new HashTable;
	ht->count = 0;
	//³õÊ¼»¯¹þÏ£±í
	for (int i = 0; i < HashSize; i++)
	{
		ht->hash[i].val = -1;
		ht->hash[i].next = NULL;
	}
	for (int i = 0; i < len; i++)
	{
		insert_HashTable(ht, a[i]);
	}
}
int hashSearch(int a[], int len, int k)
{
	HashTable* ht;
	crtHashTable(a, len, ht);
	int index = hash_mod(k);
	HashNode* p = &ht->hash[index];
	while (p)
	{
		if (p->val == k)
		{
			return index;
		}
		p = p->next;
	}
	return -1;
}
int main()
{
	int a[] = { 19,14,23,1,68,20,84,27,55,11,10,79 };
	int len = sizeof(a) / sizeof(a[0]);
	hashSearch(a, len, 55);
	system("pause");
	return 0;
}