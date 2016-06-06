////判断一颗二叉树是不是平衡二叉树？,左右子树高度不超过1
//#include<iostream>
//#include<stack>
//using namespace std;
//struct BinaryNode
//{
//	int _data;
//	BinaryNode*  _left;
//	BinaryNode*  _right;
//	BinaryNode(int& x)
//		:_data(x)
//		, _left(NULL)
//		, _right(NULL)
//	{}
//};
//class BinaryTree
//{
//private:
//	BinaryNode* _CreateBinaryTree(int& index, int* arr, const int size)
//	{
//		BinaryNode* root = NULL;
//		if (index < size&&arr[index] != '#')
//		{
//			root = new BinaryNode(arr[index]);
//			root->_left = _CreateBinaryTree(++index, arr, size);
//			root->_right = _CreateBinaryTree(++index, arr, size);
//		}
//		return root;
//	}
//	BinaryNode* _CopyBinaryTree(BinaryNode* root)
//	{
//		if (root == NULL)
//			return NULL;
//		BinaryNode* ret = NULL;
//		ret = new BinaryNode(root->_data);
//		ret->_left = _CopyBinaryTree(root->_left);
//		ret->_right = _CopyBinaryTree(root->_right);
//		return ret;
//	}
//	void _Clear(BinaryNode* root)
//	{
//		if (root == NULL)
//			return;
//		_Clear(root->_left);
//		_Clear(root->_right);
//		delete root;
//	}
//	int _Height(BinaryNode* root)
//	{
//		if (root == NULL)
//			return 0;
//		int leftHeight = _Height(root->_left);
//		int rightHeight = _Height(root->_right);
//		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
//	}
//	//效率低
//	/*bool _balance(BinaryNode* root)
//	{
//		if (root == NULL)
//			return true;
//		int leftHeight = _Height(root->_left);
//		int rightHeight = _Height(root->_right);
//		int count = leftHeight - rightHeight;
//		if (count<-1 || count>1)
//			return false;
//		return _balance(root->_left) && _balance(root->_right);
//	}*/
//	bool _balanceS(BinaryNode* root,int& depth)
//	{
//		if (root == NULL)
//		{
//			depth = 0;
//			return true;
//		}
//		int leftDepth = 0;
//		int rightDepth = 0;
//		if (_balanceS(root->_left, leftDepth) && _balanceS(root->_right, rightDepth))
//		{
//			int count = leftDepth - rightDepth;
//			if (count <= 1 && count >= -1)
//			{
//				depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
//				return true;
//			}
//		}
//		return false;
//	}
//	
//public:
//	BinaryTree()
//		:_root(NULL)
//	{}
//	BinaryTree(int* arr, int size)
//	{
//		if (arr == NULL || size <= 0)
//		{
//			_root = NULL;
//			return;
//		}
//		int index = 0;
//		_root = _CreateBinaryTree(index, arr, size);
//	}
//	BinaryTree(BinaryTree& bt)
//	{
//		_root = _CopyBinaryTree(bt._root);
//	}
//	/*BinaryTree& operator=(BinaryTree& bt)
//	{
//		if (this == &bt)
//			return *this;
//		_Clear(_root);
//		_root = _CopyBinaryTree(bt._root);
//		return *this;
//	}*/
//	BinaryTree& operator=(BinaryTree bt)
//	{
//		swap(_root, bt._root);
//		return *this;
//	}
//	~BinaryTree()
//	{
//		_Clear(_root);
//		_root = NULL;
//	}
//	int Height()
//	{
//		if(_root == NULL)
//			return 0;
//		return _Height(_root);
//	}
//	//非递归后序遍历
//	void PostOrder()
//	{
//		if (_root == NULL)
//		{
//			cout << "NULL" << endl;
//			return;
//		}
//		BinaryNode* cur = _root;
//		BinaryNode* prev = NULL;
//		BinaryNode* top = NULL;
//		stack<BinaryNode*> s;
//		while (!s.empty() || cur)
//		{
//			while (cur)//is not cur->_left
//			{
//				s.push(cur);
//				cur = cur->_left;
//			}
//			top= s.top();
//			if (top->_right == NULL || top->_right == prev)
//			{
//				cout << top->_data << " ";
//				prev = top;
//				s.pop();
//			}
//			else
//			{
//				cur = top->_right;
//			}
//		}
//		cout << endl;
//	}
//	bool balance()
//	{
//		if (_root == NULL)
//			return true;
//		//return _balance(_root);
//		int depth = 0;
//		return _balanceS(_root, depth);
//	}
//private:
//	BinaryNode* _root;
//};
//void Test1()
//{
//	int arr[] = { 1, 2,3,'#', '#', 4, '#', '#', 5, 6 };
//	BinaryTree b(arr, sizeof(arr) / sizeof(arr[0]));
//	b.PostOrder();
//	cout<<b.Height()<<endl;
//	cout << b.balance()<<endl;
//
//	int arr1[] = { 1, 2, 4, '#', '#', 5, '#', '#', 3, 6, 7,8,'#', '#','#','#', 9 };
//	BinaryTree bt1(arr1, sizeof(arr1) / sizeof(arr1[0]));
//	bt1.PostOrder();
//	cout << bt1.Height()<<endl;
//	cout << bt1.balance() << endl;
//}



////求数组中只出现一次的两个数
//
//#include<iostream>
//using namespace std;
//int FindOneBit(int value)
//{
//	if (value == 0)
//		return -1;
//	for (int i = 0; i < 32; ++i)
//	{
//		if (((value >> i) & 1) == 1)
//		{
//			return i;
//		}
//	}
//}
//void FindTwoNumOnceAppear(int arr[], int size)
//{
//	if (arr == NULL || size <= 0)
//		return;
//	int value = 0;//存储所有数字异或结果
//	for (int i = 0; i < size; ++i)
//		value ^= arr[i];
//	int bit = FindOneBit(value);
//	int num1 = 0;
//	for (int i = 0; i < size; ++i)
//	{
//		if (((arr[i] >> bit) & 1) == 1)
//			num1 ^= arr[i];
//	}
//	int num2 = value^num1;
//	cout << "the two num  " << num1 << "  " << num2 << endl;
//}
//void Test1()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6, 4, 1, 2, 3 };
//	FindTwoNumOnceAppear(arr, sizeof(arr) / sizeof(arr[0]));
//}

////找到递增数组中和为sum的任意两个数
//#include<iostream>
//using namespace std;
//bool FindNumsWithSum(int arr[], int size, int sum, int& num1, int& num2)
//{
//	bool ret = false;
//	if (arr == NULL || size <= 1)
//		return false;
//	int begin = 0;
//	int end = size - 1;
//	while (begin < end)
//	{
//		num1 = arr[begin];
//		num2 = arr[end];
//		if (num1 + num2 == sum)
//			return true;
//		else if (num1 + num2>sum)
//			--end;
//		else
//			++begin;
//	}
//	return false;
//}
//void Test1()
//{
//	int arr[] = { 1, 2, 4, 7, 11, 15 };
//	int num1 = 0;
//	int num2 = 0;
//	int sum = 15;
//	if (FindNumsWithSum(arr, sizeof(arr) / sizeof(arr[0]), sum, num1, num2))
//	{
//		cout << num1 << " " << num2 << endl;
//	}
//	else
//		cout << "not find" << endl;
//}


////输入一个数，打印出它的所有连续和序列，至少包含两个数
//#include<iostream>
//using namespace std;
//void PrintNumsOfSum(int num)
//{
//	if (num <= 0)
//		return;
//	int begin = 1;
//	int end = 2;
//	int mid = (num + 1) / 2;
//	int sum = begin + end;
//	while (begin < mid)
//	{
//		if (sum == num)
//		{
//			for (int i = begin; i <= end; ++i)
//				cout << i;
//			cout << endl;
//		}
//		while (sum>num&&begin < mid)
//		{
//			sum -= begin;
//			++begin;
//			if (sum == num)
//			{
//				for (int i = begin; i <= end; ++i)
//					cout << i;
//				cout << endl;
//			}
//		}
//		++end;
//		sum += end;
//	}
//}
//void Test1()
//{
//	int sum = 15;
//	PrintNumsOfSum(sum);
//}

//#include<iostream>
//#include<assert.h>
//#include<string.h>
//using namespace std;
////翻转字符串I am a student.为student. a am I
//
//void _Reverse(char* begin, char* end)
//{
//	assert(begin&&end);
//	while (begin < end)
//	{
//		swap(*begin, *end);
//		++begin;
//		--end;
//	}
//}
////1.
////void Reverse(char* str)
////{
////	assert(str);
////	int len = strlen(str);
////	_Reverse(str, str + len - 1);
////	int begin = 0;
////	int end = 0;
////	for (; str[end] != '\0'; ++end)
////	{
////		if (str[end] == ' ')
////		{
////			_Reverse(str + begin, str + end - 1);
////			begin = end + 1;
////		}
////		else if (str[end + 1] == '\0')
////		{
////			_Reverse(str + begin, str + end);
////		}
////	}
////}
////2.
//void Reverse(char* str)
//{
//	assert(str);
//	int len = strlen(str);
//	_Reverse(str, str + len - 1);
//	int begin = 0;
//	int end = 0;
//	for (; str[begin] != '\0'; ++end)
//	{
//		if (str[end] == ' ' || str[end] == '\0')
//		{
//			_Reverse(str + begin, str + end - 1);
//			begin = end;
//		}
//	}
//}
//void Test1()
//{
//	char str[] = "I am a student";
//	cout << str << endl;
//	Reverse(str);
//	cout << str << endl;
//}

////得到一个字符串左旋n位后的字符串
////eg:abcdefgh,左旋两位为cdefghab
//#include<iostream>
//#include<string.h>
//#include<assert.h>
//using namespace std;
//void _Reverse(char* begin, char* end)
//{
//	assert(begin&&end);
//	while (begin < end)
//	{
//		swap(*begin, *end);
//		++begin;
//		--end;
//	}
//}
//
////三步旋转法
//void ReverseNum(char* str, int num)
//{
//	assert(str);
//	int len = strlen(str);
//	if (num > len)
//		return;
//	_Reverse(str, str + len - 1);
//	_Reverse(str, str + len-num-1);
//	_Reverse(str+len-num, str + len - 1);
//
//}
//void Test1()
//{
//	char str[] = "abcdefgh";
//	cout << str << endl;
//	ReverseNum(str, 2);
//	cout << str << endl;
//}

#include<iostream>
using namespace std;
volatile int in_valid = 1;
int my_atoi(char* str)
{
	if (str == NULL)
	{
		return 0;//非法
	}
	char* cur = str;
	while (*cur != '\0'&&*cur == ' ')
		++cur;
	if (*cur == '\0')
		return 0;//非法

	if (!(*cur == '+'||*cur == '-'||isdigit(*cur)))//int isdight(int ch);return not 0成功
		return 0;
	int ret = 0;
	int flag = 1;
	if (*cur == '-')
	{
		flag = -1;
		++cur;
	}
	else if (*cur == '+')
		++cur;
	while (*cur != '\0'&&isdigit(*cur))
	{
		ret=ret*10+flag*(*cur-'0');
		if (flag == 1 && ret > 0x7fffffff || flag == -1 && ret <= 0x8000000)
		{
			return 0;
		}
		++cur;
	}
	if (*cur == '\0')
	{
		in_valid = 0;
		cout<<in_valid<<endl;
		return ret;
	}
	return 0;
}
void Test1()
{
	//cout << my_atoi("1234") << "   "<< in_valid << endl;
	//cout << my_atoi("+1234") << "   " << in_valid << endl;
	//cout << my_atoi("-1234") << "   " << in_valid << endl;
	//cout << my_atoi("+") << "   " << in_valid << endl;
	//cout << my_atoi("-") << "   " << in_valid << endl;
	//cout << my_atoi("") << "   " << in_valid << endl;
	//cout << my_atoi("0") << "   " << in_valid << endl;
	//cout << my_atoi("12ss34") << "   " << in_valid << endl;
	//cout << my_atoi("12+34") << "   " << in_valid << endl;
	//cout << my_atoi("we34") << "   " << in_valid << endl;
	//cout << my_atoi("    1234") << "   " << in_valid << endl;
}
int main()
{
	Test1();
	return 0;
}