//求出1到n 中1出现的个数
//#include<iostream>
//using namespace std;
//int NumOfOneToN(int n)
//{
//	int count=0;
//	int num=0;
//	for(int i=1;i<=n;++i)
//	{
//		num=i;
//		while(num)
//		{
//			if(num%10==1)
//			{
//				++count;
//			}
//			num/=10;
//		}
//	}
//	return count;
//}
//int main()
//{
//	cout<<NumOfOneToN(12)<<endl;
//	return 0;
//}

//char*itoa(int value,char*string,int radix); 
//int value 被转换的整数，char *string 转换后储存的字符数组，int radix 转换进制数，如2,8,10,16 进制等
//返回值：与string参数相同，便于函数的嵌套调用
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
int PowerBase(unsigned int n)
{
	int result = 1;
	for (int i = 0; i<n; ++i)
	{
		result *= 10;
	}
	return result;
}
int NumberOf1(const char* str)
{
	if (!str || *str<'0' || *str>'9' || *str == '\0')
	{
		return 0;
	}
	int first = *str - '0';
	int length = strlen(str);
	if (length == 1 && first == 0)
	{
		return 0;
	}
	if (length == 1 && first>0)
	{
		return 1;
	}
	int numFirstDigit = 0;
	if (first>1)
	{
		numFirstDigit = PowerBase(length - 1);
	}
	else if (first == 1)
	{
		numFirstDigit = atoi(str + 1) + 1;
	}
	int numOtherDigit = first*(length - 1)*PowerBase(length - 2);
	int numRecursive = NumberOf1(str + 1);
	return numFirstDigit + numOtherDigit + numRecursive;
}
int NumberOf1ToN(int n)
{
	if (n <= 0)
	{
		return 0;
	}
	char str[50];
	itoa(n, str, 10);
	return NumberOf1(str);
}
void Test1()
{
	cout << NumberOf1ToN(22);
}
int main()
{
	Test1();
	return 0;
}