#include <iostream>
using namespace std;
/*����
	0   0   0   0   0   0
	0   3   0   0   0   0
	0   0   0   6   0   0
	0   0   9   0   0   0
	0   0   0   0   12  0*/
int main()
{
	int sparse[5][6] =
	{
		{5,6,4},		//���У����� ���� ����
		{1,1,3},		//ʣ�ࣺ�� �� ֵ
		{2,3,6},
		{3,2,9},
		{4,4,12}
	};
	cout << "ԭ����" << endl;
	for (int i = 0; i < sparse[0][0]; i++)
	{
		for (int j = 0; j < sparse[0][1]; j++)
		{
			if (i == sparse[i][0] && j == sparse[i][1])
			{
				cout << sparse[i][2] << " ";
			}
			else
			{
				cout << "0 ";
			}
		}
		cout << endl;
	}
	cout << "ϡ�����" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << sparse[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}