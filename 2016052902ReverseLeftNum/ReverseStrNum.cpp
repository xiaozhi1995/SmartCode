//�õ�һ���ַ�������nλ����ַ���
//eg:abcdefgh,������λΪcdefghab
#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;
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

//������ת��
void ReverseNum(char* str, int num)
{
	assert(str);
	int len = strlen(str);
	if (num > len)
		return;
	_Reverse(str, str + len - 1);
	_Reverse(str, str + len - num - 1);
	_Reverse(str + len - num, str + len - 1);

}
void Test1()
{
	char str[] = "abcdefgh";
	cout << str << endl;
	ReverseNum(str, 2);
	cout << str << endl;
}