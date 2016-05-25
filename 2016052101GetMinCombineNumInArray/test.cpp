//把数组排成最小的数
//输入一个整形数组，把书祖中所以数字排列起来形成一个数，并打印出来
//eg{3,32,321},则应打印321323 
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
const int g_MaxLength = 10;
char* str1Num = new char[g_MaxLength * 2 + 1];
char* str2Num = new char[g_MaxLength * 2 + 1];
//比较组合后两个数字的大小
int Compare(const void* str1, const void* str2)
{
	strcpy(str1Num, *(const char**)str1);
	strcat(str1Num, *(const char**)str2);
	strcpy(str2Num, *(const char**)str2);
	strcat(str2Num, *(const char**)str1);
	return strcmp(str1Num, str2Num);
}
void PrintMinNumber(int* number, int length)
{
	if (number == NULL || length <= 0)
	{
		return;
	}
	char** strNum = (char**)(new int[length]);
	for (int i = 0; i<length; ++i)
	{
		strNum[i] = new char[g_MaxLength + 1];
		itoa(number[i], strNum[i], 10);
	}
	//调用库函数
	qsort(strNum, length, sizeof(char*), Compare);
	for (int i = 0; i<length; ++i)
	{
		cout << strNum[i];
	}
	cout << endl;
	for (int i = 0; i<length; ++i)
	{
		delete[] strNum[i];
	}
	delete[] strNum;
}
void Test1()
{
	int arr[] = { 3, 32, 321 };
	PrintMinNumber(arr, sizeof(arr) / sizeof(arr[0]));
}
int main()
{
	Test1();
	return 0;
}