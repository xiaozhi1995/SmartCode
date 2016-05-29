//找到递增数组中和为sum的任意两个数
#include<iostream>
using namespace std;
bool FindNumsWithSum(int arr[], int size, int sum, int& num1, int& num2)
{
	bool ret = false;
	if (arr == NULL || size <= 1)
		return false;
	int begin = 0;
	int end = size - 1;
	while (begin < end)
	{
		num1 = arr[begin];
		num2 = arr[end];
		if (num1 + num2 == sum)
			return true;
		else if (num1 + num2>sum)
			--end;
		else
			++begin;
	}
	return false;
}
void Test1()
{
	int arr[] = { 1, 2, 4, 7, 11, 15 };
	int num1 = 0;
	int num2 = 0;
	int sum = 15;
	if (FindNumsWithSum(arr, sizeof(arr) / sizeof(arr[0]), sum, num1, num2))
	{
		cout << num1 << " " << num2 << endl;
	}
	else
		cout << "not find" << endl;
}