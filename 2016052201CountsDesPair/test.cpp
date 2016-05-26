//采用归并思想
#include<iostream>
using namespace std;
int _Pair(int *arr,int* out,int begin,int end)
{
	if(begin==end)
	{
		out[begin]=arr[begin];
		return 0;
	}
	int mid=(end-begin)>>1;
	int leftNum=_Pair(arr,out,begin,begin+mid);
	int rightNum=_Pair(arr,out,begin+mid+1,end);
	int i=begin+mid;
	int j=end;
	int index=end;
	int count=0;//pair count
	while(i>=begin&&j>=begin+mid+1)
	{
		if(arr[i]>arr[j])
		{
			out[index--]=arr[i--];
			++count;
		}
		else if(arr[i]<arr[j])
		{
			out[index--]=arr[j--];
		}
	}
	for(;i>=begin;--i)
	{
		out[index--]=arr[i--];
	}
	for(;j>=begin+mid+1;--j)
	{
		out[index--]=arr[j--];
	}
	return leftNum+rightNum+count;
}
int CountDesPair(int*arr,int size)
{
	if(arr==NULL||size<=0)
	{
		return 0;
	}
	int *out=new int[size];
	for(int i=0;i<size;++i)
	{
		out[i]=arr[i];
	}
	int ret= _Pair(arr,out,0,size-1);
	delete[] out;
	return ret;
}
int main()
{
	int arr[]={7,5,6,4};
	cout<<CountDesPair(arr,sizeof(arr)/sizeof(arr[0]))<<endl;
	return 0;
}