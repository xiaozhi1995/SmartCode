//输入n个整数，找出最小的k个数
#include<iostream>
using namespace std;
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
void GetLeastNumber(int *inPut, int size, int* outPut, int k)
{
	if (inPut == NULL || outPut == NULL || k > size || size <= 0 || k <= 0)
		return;
	int begin = 0;
	int end = size - 1;
	int index = Partition(inPut, begin, end);
	while (index != k - 1)
	{
		if (index < k - 1)
		{
			begin = index + 1;
			index = Partition(inPut, begin, end);
		}
		else
		{
			end = index - 1;
			index = Partition(inPut, begin, end);
		}
	}
	for (int i = 0; i < k; ++i)
		outPut[i] = inPut[i];
}
void Print(int* arr, int size)
{
	if (NULL == arr || size <= 0)
		return;
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	cout << endl;
}
void QuickSort(int *arr, int left, int right)
{
	if (arr == NULL || left >= right)
		return;
	int mid = Partition(arr, left, right);
	QuickSort(arr, left, mid - 1);
	QuickSort(arr, mid + 1, right);
}
void Test1()
{
	int arr[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	//QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	//Print(arr, sizeof(arr) / sizeof(arr[0]));
	int k = 4;
	int *out = new int[k];
	GetLeastNumber(arr, sizeof(arr) / sizeof(arr[0]), out, k);
	Print(out, k);
	delete[] out;
}