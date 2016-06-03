//ÆË¿ËÅÆµÄË³×Ó 
#include<stdlib.h>
#include<iostream>
using namespace std;
int comp(const void*a,const void*b)
{
	return *(int*)a-*(int*)b;
}
bool IsContinuous(int* number,int length)
{
	if(number==NULL||length<1)
	{
		return false;
	}
	qsort(number,length,sizeof(int),comp);
	int numberOfZero=0;
	int numberOfGap=0;
	for(int i=0;i<length&&number[i]==0;++i)
	{
		++numberOfZero;
	}
	int small=numberOfZero;
	int big=small+1;
	while(big<length)
	{
		if(number[small]==number[big])
		{
			return false;
		}
		numberOfGap+=(number[big]-number[small]-1);
		small=big;
		++big;
	}
	return numberOfZero>=numberOfGap?true:false;
} 
int main()
{
	int arr[]={2,4,0,6,0};
	cout<<IsContinuous(arr,sizeof(arr)/sizeof(arr[0]))<<endl;
	
	int arr1[]={1,4,0,6,0};
	cout<<IsContinuous(arr1,sizeof(arr1)/sizeof(arr1[0]))<<endl;
	return 0;
}