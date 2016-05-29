//判断一颗二叉树是不是平衡二叉树？,左右子树高度不超过1
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
	//效率低
	/*bool _balance(BinaryNode* root)
	{
	if (root == NULL)
	return true;
	int leftHeight = _Height(root->_left);
	int rightHeight = _Height(root->_right);
	int count = leftHeight - rightHeight;
	if (count<-1 || count>1)
	return false;
	return _balance(root->_left) && _balance(root->_right);
	}*/
	bool _balanceS(BinaryNode* root, int& depth)
	{
		if (root == NULL)
		{
			depth = 0;
			return true;
		}
		int leftDepth = 0;
		int rightDepth = 0;
		if (_balanceS(root->_left, leftDepth) && _balanceS(root->_right, rightDepth))
		{
			int count = leftDepth - rightDepth;
			if (count <= 1 && count >= -1)
			{
				depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
				return true;
			}
		}
		return false;
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
	//非递归后序遍历
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
	bool balance()
	{
		if (_root == NULL)
			return true;
		//return _balance(_root);
		int depth = 0;
		return _balanceS(_root, depth);
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
	cout << b.balance() << endl;

	int arr1[] = { 1, 2, 4, '#', '#', 5, '#', '#', 3, 6, 7, 8, '#', '#', '#', '#', 9 };
	BinaryTree bt1(arr1, sizeof(arr1) / sizeof(arr1[0]));
	bt1.PostOrder();
	cout << bt1.Height() << endl;
	cout << bt1.balance() << endl;
}