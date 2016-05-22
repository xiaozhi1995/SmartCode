//��Ŀ�����ǰ�ֻ��������2��3��5�����������������С�����˳��ĵ�1500��������eg6,8�ǳ�������14���ǣ�������7
//��һ������
//#include<iostream>
//using namespace std;
//bool Ugly(int num)
//{
//	while (num % 2 == 0)
//	{
//		num /= 2;
//	}
//	while (num % 3 == 0)
//	{
//		num /= 3;
//	}
//	while (num % 5 == 0)
//	{
//		num /= 5;
//	}
//	return (num == 1) ? true : false;
//}
//int NUgly(int n)
//{
//	if (n <= 0)
//	{
//		return 0;
//	}
//	int count = 0;
//	int i = 0;
//	while (count<n)
//	{
//		++i;
//		if (Ugly(i))
//		{
//			++count;
//		}
//	}
//	return i;
//}
//void Test1()
//{
//	cout << NUgly(2) << endl;
//	cout << NUgly(3) << endl;
//	cout << NUgly(4) << endl;
//	cout << NUgly(100) << endl;//1600
//}

//������Ч
#include<iostream>
using namespace std;
int Min(int p2, int p3, int p5)
{
	int min = (p2 < p3) ? p2 : p3;
	min = (min < p5) ? min : p5;
	return min;
}
int GetUglyNum(int n)
{
	if (n <= 0)
		return 0;
	int *pUgly = new int[n];
	pUgly[0] = 1;//��1��ʼ
	int nextIndex = 1;
	int* p2 = pUgly;
	int* p3 = pUgly;
	int* p5 = pUgly;
	while (nextIndex < n)
	{
		int min = Min(*p2 * 2, *p3 * 3, *p5 * 5);
		pUgly[nextIndex] = min;
		while (*p2 * 2 <= pUgly[nextIndex])
			++p2;
		while (*p3 * 3 <= pUgly[nextIndex])
			++p3;
		while (*p5 * 5 <= pUgly[nextIndex])
			++p5;
		++nextIndex;
	}
	int ugly = pUgly[nextIndex - 1];
	delete[] pUgly;
	return ugly;
}
void Test1()
{
	cout << GetUglyNum(2) << endl;
	cout << GetUglyNum(3) << endl;
	cout << GetUglyNum(4) << endl;
	cout << GetUglyNum(100) << endl;//1600
}