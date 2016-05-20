////查找一个数组中出现次数超过一半数组长度的元素 
//#include <iostream>
//using namespace std;
///* run this program using the console pauser or add your own getch, system("pause") or input loop */
//bool CheckMoreThanHalf(int arr[],int size,int ret)
//{
//	if(arr==NULL||size<=0)
//	{
//		return false;
//	}
//	int time=0;
//	for(int i=0;i<size;++i)
//	{
//		if(arr[i]==ret)
//		{
//			++time;
//		}
//	}
//	if(time*2<=size)
//	{
//		return false;
//	}
//	return true;
//}
//void SearchMidNum(int arr[],int size) 
//{
//	if(arr==NULL||size<=0)
//	{
//		cout<<"this array isn't exist the mid num"<<endl; 
//		return;
//	}
//	int ret=arr[0];
//	int count=1;
//	for(int i=1;i<size;++i)
//	{
//		if(count==0)
//		{
//			ret=arr[i];
//			count=1;	
//		}
//		else if(arr[i]!=ret)
//		{
//			--count;
//		}
//		else
//		{
//			++count;
//		}
//	}
//	if(CheckMoreThanHalf(arr,size,ret))
//	{
//		cout<<ret<<endl;
//	}
//	else
//	{
//		cout<<"isn't exist more than half num"<<endl; 
//	}
//}
//void Test()
//{
//	int arr[]={5,4,5,6,7,5,5,3,5,5};
//	SearchMidNum(arr,sizeof(arr)/sizeof(arr[0]));
//	int arr1[]={5,4,5,6};
//	SearchMidNum(arr1,sizeof(arr1)/sizeof(arr1[0]));
//}
//int main(int argc, char** argv) 
//{
//	Test();
//	return 0;
//}


//采用排序将原数组排序，中位数即为超过一半的数
#include<iostream>
using namespace std;
bool CheckMoreThanHalf(int arr[], int size, int ret)
{
	if (arr == NULL || size <= 0)
	{
		return false;
	}
	int time = 0;
	for (int i = 0; i<size; ++i)
	{
		if (arr[i] == ret)
		{
			++time;
		}
	}
	if (time * 2 <= size)
	{
		return false;
	}
	return true;
}
int Partition(int* arr, int left, int right)
{
	if (arr == NULL)
		return -1;
	if (left >= right)
		return right;
	int key = arr[right];
	int begin = left;
	int end = right;
	while (begin<end)
	{
		while (begin < end&&arr[begin] <= key)
		{
			++begin;
		}
		if (begin < end)
		{
			arr[end--] = arr[begin];
		}
		while (begin < end&&arr[end] >= key)
		{
			--end;
		}
		if (begin < end)
		{
			arr[begin++] = arr[end];
		}
	}
	arr[begin] = key;
	return begin;
}
void QuickSort(int *arr, int left, int right)
{
	if (arr == NULL || left >= right)
		return;
	int mid = Partition(arr, left, right);
	QuickSort(arr, left, mid - 1);
	QuickSort(arr, mid + 1, right);
}
void SearchMidNum(int arr[], int size)
{
	if (arr == NULL || size <= 0)
		return;
	int mid = size >> 1;
	int begin = 0;
	int end = size - 1;
	int index = Partition(arr, begin, end);
	while (index != mid)
	{
		if (index > mid)
		{
			end = index - 1;
			index = Partition(arr, begin, end);
		}
		else
		{
			begin = index + 1;
			index = Partition(arr, begin, end);
		}
	}
	int ret = arr[index];
	if (CheckMoreThanHalf(arr, size, ret))
	{
		cout << ret << endl;
	}
	else
	{
		cout << "isn't exist more than half num" << endl;
	}
}
void Print(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	cout << endl;
}
void Test1()
{
	int arr[] = { 5, 4, 5, 6, 7, 5, 5, 3, 5, 5 };
	/*Print(arr, 10);
	QuickSort(arr, 0, 9);
	Print(arr, 10);*/

	SearchMidNum(arr, sizeof(arr) / sizeof(arr[0]));
	int arr1[] = { 5, 4, 5, 6 };
	SearchMidNum(arr1, sizeof(arr1) / sizeof(arr1[0]));
}