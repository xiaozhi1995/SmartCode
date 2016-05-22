//找到字符数组中第一个只出现出现的字符
//abaccdeff,应为b
#include<iostream>
#include<string.h> 
#include<stdlib.h>
using namespace std;
char FirstOneCountInArray(const char* str)
{
	if (str == NULL)
	{
		return 0;
	}
	char* countChar[256] = { 0 };
	int length = strlen(str);
	for (int i = 0; i<length; ++i)
	{
		++countChar[str[i]];
	}
	for (int i = 0; i<length; ++i)
	{
		int index = str[i];
		if ((int)countChar[index] == 1)
		{
			return str[i];
		}
	}
	return 0;//都是成对返回0 
}
void Test1()
{
	char* str = "abaccdeff";
	cout << FirstOneCountInArray(str) << endl;
	char* str1 = "ahohaklbk";
	cout << FirstOneCountInArray(str1) << endl;
}