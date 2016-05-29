//输入一个数，打印出它的所有连续和序列，至少包含两个数
#include<iostream>
using namespace std;
void PrintNumsOfSum(int num)
{
	if (num <= 0)
		return;
	int begin = 1;
	int end = 2;
	int mid = (num + 1) / 2;
	int sum = begin + end;
	while (begin < mid)
	{
		if (sum == num)
		{
			for (int i = begin; i <= end; ++i)
				cout << i;
			cout << endl;
		}
		while (sum>num&&begin < mid)
		{
			sum -= begin;
			++begin;
			if (sum == num)
			{
				for (int i = begin; i <= end; ++i)
					cout << i;
				cout << endl;
			}
		}
		++end;
		sum += end;
	}
}
void Test1()
{
	int sum = 15;
	PrintNumsOfSum(sum);
}