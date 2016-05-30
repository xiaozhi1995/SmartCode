//输入n个骰子，求出现所有点数的概率 
#include<iostream>
#include<math.h>
using namespace std;
int g_val=6;//骰子点数 
void _Ps(int orig,int cur,int sum,int* posb)
{
	if(cur==1)
	{
		++posb[sum-orig];
	}
	else
	{
		for(int i=1;i<=g_val;++i)
		{
			_Ps(orig,cur-1,i+sum,posb);
		}
	}
}
void PrintPossiblity(int n)
{
	if(n<=0)
	{
		return;
	}
	int size=n*g_val-n+1;
	int* posb=new int[size];
	for(int i=0;i<size;++i)
	{
		posb[i]=0;
	}
	for(int i=1;i<=g_val;++i)
	{
		_Ps(n,n,i,posb);
	}
	int total=pow((double)g_val,n);
	double ratio=0.0;
	for(int i=0;i<size;++i)
	{
		ratio=(double)posb[i]/total;
		cout<<i+n<<"ratio"<<ratio<<"  ";
	}
	delete[] posb;
}
int main()
{
	int n=1;//骰子个数 
	PrintPossiblity(n); 
	int n1=2;//骰子个数 
	PrintPossiblity(n1); 
	return 0;
}