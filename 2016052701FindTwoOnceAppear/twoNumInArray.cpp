//��������ֻ����һ�ε�������

#include<iostream>
using namespace std;
int FindOneBit(int value)
{
	if (value == 0)
		return -1;
	for (int i = 0; i < 32; ++i)
	{
		if (((value >> i) & 1) == 1)
		{
			return i;
		}
	}
}
void FindTwoNumOnceAppear(int arr[], int size)
{
	if (arr == NULL || size <= 0)
		return;
	int value = 0;//�洢�������������
	for (int i = 0; i < size; ++i)
		value ^= arr[i];
	int bit = FindOneBit(value);
	int num1 = 0;
	for (int i = 0; i < size; ++i)
	{
		if (((arr[i] >> bit) & 1) == 1)
			num1 ^= arr[i];
	}
	int num2 = value^num1;
	cout << "the two num  " << num1 << "  " << num2 << endl;
}
void Test1()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 4, 1, 2, 3 };
	FindTwoNumOnceAppear(arr, sizeof(arr) / sizeof(arr[0]));
}