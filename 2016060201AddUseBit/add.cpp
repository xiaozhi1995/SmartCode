//写一个函数，不用+-*/，求两个数的加法
//位运算 
#include<iostream>
using namespace std;
int Sum(int val1,int val2)
{
	int sum,carry;
	do
	{
		sum=val1^val2;
		carry=(val1&val2)<<1;
		val1=sum;
		val2=carry;
	}while(val2!=0);
	return val1;
}
int main()
{
	cout<<Sum(6,9)<<endl;
	return 0;
}  