#include<iostream>
#include<assert.h>
using namespace std;
int findLeftIndex(int *arr,int size,int num)
{
	int begin=0;
	int end=size-1;
	int mid;
	while(begin<=end)
	{
		mid=begin+((end-begin)>>1);
		if(arr[mid]==num)
		{
			if(mid==0||mid>0&&arr[mid-1]!=num)
			{
				return mid;
			}
			else
			{
				end=mid-1;
			}
		}
		else if(arr[mid]>num)
		{
			end=mid-1;
		}
		else
		{
			begin=mid+1;
		}	
		
	}
	return -1;
}
#include<iostream>
#include<assert.h>
using namespace std;
int findRightIndex(int *arr,int size,int num)
{
	int begin=0;
	int end=size-1;
	int mid;
	while(begin<=end)
	{
		mid=begin+((end-begin)>>1);
		if(arr[mid]==num)
		{
			if(mid==size-1||mid<size-1&&arr[mid+1]!=num)
			{
				return mid;
			}
			else
			{
				begin=mid+1;
			}
		}
		else if(arr[mid]>num)
		{
			end=mid-1;
		}
		else
		{
			begin=mid+1;
		}	
		
	}
	return -1;
}
int CountOfNum(int *arr,int size,int num)
{
	assert(arr);
	if(size<1)
	{
		return 0;
	}
	int leftIndex=findLeftIndex(arr,size,num);
	int  rightIndex=findRightIndex(arr,size,num);
	if(leftIndex!=-1&&rightIndex!=-1)
	{
		return rightIndex-leftIndex+1;
	}
}
int main()
{
	int arr[]={0,1,3,4,4,4,4,4,6,7,8};
	//cout<<findRightIndex(arr,sizeof(arr)/sizeof(arr[0]),4)<<endl;
	
	cout<<CountOfNum(arr,sizeof(arr)/sizeof(arr[0]),4)<<endl;
	return 0;
}