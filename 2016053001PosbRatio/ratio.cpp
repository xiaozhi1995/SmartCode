//输入n个骰子，求出现所有点数的概率 
//1.
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
//2.
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;
int g_val=6;//骰子点数 
void PrintPossiblity(int n)
{
	if(n<1)
	{
		return;
	}
	int* pos[2];
	pos[0]=new int[g_val*n+1];
	pos[1]=new int[g_val*n+1];
	for(int i=0;i<g_val*n+1;++i)
	{
		pos[0][i]=0;
		pos[1][i]=0;
	}
	int flag=0;
	for(int i=1;i<=g_val;++i)
	{
		pos[flag][i]=1;
	}
	for(int k=2;k<=n;++k)
	{
		for(int i=0;i<k;++i)
		{
			pos[1-flag][i]=0;
		}
		for(int i=k;i<=g_val*k;++i)
		{
			pos[1-flag][i]=0;
			for(int j=1;j<=i&&j<=g_val;++j)
			{
				pos[1-flag][i]+=pos[flag][i-j]; 
			}
		}
		flag=1-flag;
	}
	int total=pow((double)g_val,n);
	double ratio=0.0;
	for(int i=n;i<=g_val*n;++i)
	{
		ratio=(double)pos[flag][i]/total;
		cout<<i<<"ratio"<<ratio<<"  ";
	}
	delete[] pos[0];
	delete[] pos[1];
}
int main()
{
	int n=1;//骰子个数 
	PrintPossiblity(n); 
	cout<<endl;
	int n1=2;//骰子个数 
	PrintPossiblity(n1); 
	return 0;
}