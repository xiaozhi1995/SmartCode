#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;
//·­×ª×Ö·û´®I am a student.Îªstudent. a am I

void _Reverse(char* begin, char* end)
{
	assert(begin&&end);
	while (begin < end)
	{
		swap(*begin, *end);
		++begin;
		--end;
	}
}
//1.
//void Reverse(char* str)
//{
//	assert(str);
//	int len = strlen(str);
//	_Reverse(str, str + len - 1);
//	int begin = 0;
//	int end = 0;
//	for (; str[end] != '\0'; ++end)
//	{
//		if (str[end] == ' ')
//		{
//			_Reverse(str + begin, str + end - 1);
//			begin = end + 1;
//		}
//		else if (str[end + 1] == '\0')
//		{
//			_Reverse(str + begin, str + end);
//		}
//	}
//}
//2.
void Reverse(char* str)
{
	assert(str);
	int len = strlen(str);
	_Reverse(str, str + len - 1);
	int begin = 0;
	int end = 0;
	for (; str[begin] != '\0'; ++end)
	{
		if (str[end] == ' ' || str[end] == '\0')
		{
			_Reverse(str + begin, str + end - 1);
			begin = end;
		}
	}
}
void Test1()
{
	char str[] = "I am a student";
	cout << str << endl;
	Reverse(str);
	cout << str << endl;
}