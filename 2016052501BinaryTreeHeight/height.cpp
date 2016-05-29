#include<iostream>
#include<stack>
using namespace std;
struct BinaryNode
{
	int _data;
	BinaryNode*  _left;
	BinaryNode*  _right;
	BinaryNode(int& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
private:
	BinaryNode* _CreateBinaryTree(int& index, int* arr, const int size)
	{
		BinaryNode* root = NULL;
		if (index < size&&arr[index] != '#')
		{
			root = new BinaryNode(arr[index]);
			root->_left = _CreateBinaryTree(++index, arr, size);
			root->_right = _CreateBinaryTree(++index, arr, size);
		}
		return root;
	}
	BinaryNode* _CopyBinaryTree(BinaryNode* root)
	{
		if (root == NULL)
			return NULL;
		BinaryNode* ret = NULL;
		ret = new BinaryNode(root->_data);
		ret->_left = _CopyBinaryTree(root->_left);
		ret->_right = _CopyBinaryTree(root->_right);
		return ret;
	}
	void _Clear(BinaryNode* root)
	{
		if (root == NULL)
			return;
		_Clear(root->_left);
		_Clear(root->_right);
		delete root;
	}
	int _Height(BinaryNode* root)
	{
		if (root == NULL)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(int* arr, int size)
	{
		if (arr == NULL || size <= 0)
		{
			_root = NULL;
			return;
		}
		int index = 0;
		_root = _CreateBinaryTree(index, arr, size);
	}
	BinaryTree(BinaryTree& bt)
	{
		_root = _CopyBinaryTree(bt._root);
	}
	/*BinaryTree& operator=(BinaryTree& bt)
	{
	if (this == &bt)
	return *this;
	_Clear(_root);
	_root = _CopyBinaryTree(bt._root);
	return *this;
	}*/
	BinaryTree& operator=(BinaryTree bt)
	{
		swap(_root, bt._root);
		return *this;
	}
	~BinaryTree()
	{
		_Clear(_root);
		_root = NULL;
	}
	int Height()
	{
		if (_root == NULL)
			return 0;
		return _Height(_root);
	}
	//·ÇµÝ¹éºóÐò±éÀú
	void PostOrder()
	{
		if (_root == NULL)
		{
			cout << "NULL" << endl;
			return;
		}
		BinaryNode* cur = _root;
		BinaryNode* prev = NULL;
		BinaryNode* top = NULL;
		stack<BinaryNode*> s;
		while (!s.empty() || cur)
		{
			while (cur)//is not cur->_left
			{
				s.push(cur);
				cur = cur->_left;
			}
			top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << " ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}

private:
	BinaryNode* _root;
};
void Test1()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree b(arr, sizeof(arr) / sizeof(arr[0]));
	b.PostOrder();
	cout << b.Height() << endl;

	int arr1[] = { 1, 2, 4, '#', '#', 5, '#', '#', 3, 6, 7, '#', '#', '#', 8 };
	BinaryTree bt1(arr1, sizeof(arr1) / sizeof(arr1[0]));
	bt1.PostOrder();
	cout << bt1.Height();
}