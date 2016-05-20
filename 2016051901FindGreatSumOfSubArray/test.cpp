//连续子数组的最大和
//{ 1, -2, 3, 10, -4, 7, 2, -5 };//最大子数组18
#include<iostream>
using namespace std;
bool g_InValid = false;
int FindGreatSumOfSubArray(int* arr, int size)
{
	if (arr == NULL || size <= 0)
		g_InValid = true;
	g_InValid = false;
	int curSum = 0;
	int greatSum = 0x80000000;
	for (int i = 0; i < size; ++i)
	{
		if (curSum <= 0)
		{
			curSum = arr[i];
		}
		else
			curSum += arr[i];
		if (curSum>greatSum)
			greatSum = curSum;
	}
	return greatSum;
}
void Test1()
{
	int arr[] = { 1, -2, 3, 10, -4, 7, 2, -5 };//最大子数组18
	if (!g_InValid)
	{
		cout << FindGreatSumOfSubArray(arr, sizeof(arr) / sizeof(arr[0])) << endl;
	}
}