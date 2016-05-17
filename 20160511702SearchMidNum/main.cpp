//查找一个数组中出现次数超过一半数组长度的元素 
#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bool CheckMoreThanHalf(int arr[],int size,int ret)
{
	if(arr==NULL||size<=0)
	{
		return false;
	}
	int time=0;
	for(int i=0;i<size;++i)
	{
		if(arr[i]==ret)
		{
			++time;
		}
	}
	if(time*2<=size)
	{
		return false;
	}
	return true;
}
void SearchMidNum(int arr[],int size) 
{
	if(arr==NULL||size<=0)
	{
		cout<<"this array isn't exist the mid num"<<endl; 
		return;
	}
	int ret=arr[0];
	int count=1;
	for(int i=1;i<size;++i)
	{
		if(count==0)
		{
			ret=arr[i];
			count=1;	
		}
		else if(arr[i]!=ret)
		{
			--count;
		}
		else
		{
			++count;
		}
	}
	if(CheckMoreThanHalf(arr,size,ret))
	{
		cout<<ret<<endl;
	}
	else
	{
		cout<<"isn't exist more than half num"<<endl; 
	}
}
void Test()
{
	int arr[]={5,4,5,6,7,5,5,3,5,5};
	SearchMidNum(arr,sizeof(arr)/sizeof(arr[0]));
	int arr1[]={5,4,5,6};
	SearchMidNum(arr1,sizeof(arr1)/sizeof(arr1[0]));
}
int main(int argc, char** argv) {
	Test();
	return 0;
}
