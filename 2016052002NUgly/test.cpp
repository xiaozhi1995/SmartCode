#include<iostream>
using namespace std;
bool Ugly(int num)
{
	while(num%2==2)
	{
		num/=2;
	}
	while(num%3==3)
	{
		num/=3;
	}	
	while(num%5==5)
	{
		num/=5;
	}
	return num==1?true:false;
}
int NUgly(int n)
{
	int count=0;
	int i=1;
	while(count<n)
	{
		if(Ugly(i))
		{
			++count;
		}
		++i;
	}
	return i;
}
int main()
{
	cout<<NUgly(2);
	return 0;
}