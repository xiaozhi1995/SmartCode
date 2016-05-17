#include<iostream>
#include<assert.h> 
using namespace std;
void Swap(char* sc,char* dc)
{
	assert(sc&&dc);
	char tmp=*sc;
	*sc=*dc;
	*dc=tmp;
}
void _FP(char* str,char* begin)
{
	if(*begin=='\0')
	{
		cout<<str<<endl;
		return;
	}
	for(char* tmp=begin;*tmp!='\0';++tmp)
	{
		Swap(tmp,begin);//自定义交换函数
		_FP(str,begin+1); 
		Swap(tmp,begin);
	}
}
void FullPermutation(char* str)
{
	if(NULL==str)
	{
		return;
	}
	_FP(str,str);
}
void Test()
{
	char str[]="abc";
	FullPermutation(str);	
}
int main()
{
	Test();
	return 0;
}

