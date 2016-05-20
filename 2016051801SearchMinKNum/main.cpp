////输入n个整数，找出最小的k个数
//#include<iostream>
//using namespace std;
//int Partition(int* arr, int left, int right)
//{
//	if (arr == NULL)
//		return -1;
//	if (left >= right)
//		return right;
//	int key = arr[right];
//	int begin = left;
//	int end = right;
//	while (begin<end)
//	{
//		while (begin < end&&arr[begin] <= key)
//		{
//			++begin;
//		}
//		if (begin < end)
//		{
//			arr[end--] = arr[begin];
//		}
//		while (begin < end&&arr[end] >= key)
//		{
//			--end;
//		}
//		if (begin < end)
//		{
//			arr[begin++] = arr[end];
//		}
//	}
//	arr[begin] = key;
//	return begin;
//}
//void GetLeastNumber(int *inPut, int size, int* outPut, int k)
//{
//	if (inPut == NULL || outPut == NULL || k > size || size <= 0 || k <= 0)
//		return;
//	int begin = 0;
//	int end = size - 1;
//	int index = Partition(inPut, begin, end);
//	while (index != k - 1)
//	{
//		if (index < k - 1)
//		{
//			begin = index + 1;
//			index = Partition(inPut, begin, end);
//		}
//		else
//		{
//			end = index - 1;
//			index = Partition(inPut, begin, end);
//		}
//	}
//	for (int i = 0; i < k; ++i)
//		outPut[i] = inPut[i];
//}
//void Print(int* arr, int size)
//{
//	if (NULL == arr || size <= 0)
//		return;
//	for (int i = 0; i < size; ++i)
//		cout << arr[i] << " ";
//	cout << endl;
//}
//void QuickSort(int *arr, int left, int right)
//{
//	if (arr == NULL || left >= right)
//		return;
//	int mid = Partition(arr, left, right);
//	QuickSort(arr, left, mid - 1);
//	QuickSort(arr, mid + 1, right);
//}
//void Test1()
//{
//	int arr[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
//	//QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
//	//Print(arr, sizeof(arr) / sizeof(arr[0]));
//	int k = 4;
//	int *out = new int[k];
//	GetLeastNumber(arr, sizeof(arr) / sizeof(arr[0]), out, k);
//	Print(out, k);
//	delete[] out;
//}


#include<iostream>
using namespace std;
//构建大堆，可处理海量数据，堆排序
void AdjustDown(int *arr, int size, int parIndex)
{
	int childIndex = 2 * parIndex + 1;
	while (childIndex < size)
	{
		if (childIndex + 1 < size&&arr[childIndex + 1] > arr[childIndex])
		{
			++childIndex;
		}
		if (arr[childIndex]>arr[parIndex])
		{
			swap(arr[childIndex], arr[parIndex]);
			parIndex = childIndex;
			childIndex = 2 * parIndex + 1;
		}
		else
			break;
	}
}
void HeapSort(int* arr, int size)
{
	if (arr == NULL || size <= 0)
		return;
	for (int i = (size - 2) / 2; i >= 0; --i)
	{
		AdjustDown(arr, size, i);
	}
}
void GetLeastNumber(int *inPut, int size, int *outPut, int k)
{
	if (inPut == NULL || outPut == NULL || k > size || size <= 0 || k <= 0)
		return;
	for (int i = 0; i < k; ++i)
		outPut[i] = inPut[i];
	HeapSort(outPut, k);
	for (int i = k; i < size; ++i)
	{
		if (inPut[i]>outPut[0])
			continue;
		else
		{
			outPut[0] = inPut[i];
			AdjustDown(outPut, k, 0);
		}
	}
}
void Print(int* arr, int size)
{
	if (NULL == arr || size <= 0)
		return;
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	cout << endl;
}
void Test1()
{
	int arr[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	//HeapSort(arr, 8);
	//QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	//Print(arr, sizeof(arr) / sizeof(arr[0]));
	int k = 4;
	int *out = new int[k];
	GetLeastNumber(arr, sizeof(arr) / sizeof(arr[0]), out, k);
	Print(out, k);
	delete[] out;
}