//���1��n ��1���ֵĸ���
#include<iostream>
using namespace std;
int NumOfOneToN(int n)
{
	int count=0;
	int num=0;
	for(int i=1;i<=n;++i)
	{
		num=i;
		while(num)
		{
			if(num%10==1)
			{
				++count;
			}
			num/=10;
		}
	}
	return count;
}
int main()
{
	cout<<NumOfOneToN(12)<<endl;
	return 0;
}