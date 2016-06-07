#include<iostream>
#include<stack>
using namespace std;
struct BinaryTreeNode
{
	int _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode(int x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}

};
class BinaryTree
{
private:
	BinaryTreeNode* _root;
private:
	void _Clear(BinaryTreeNode* root)
	{
		if (root == NULL)
			return;
		_Clear(root->_left);
		_Clear(root->_right);
		delete root;
	}
	BinaryTreeNode* _CreateBinary(int* arr, int& index, const int size)
	{
		BinaryTreeNode* ret = NULL;
		if (index < size&&arr[index] != '#')
		{
			ret = new BinaryTreeNode(arr[index]);
			ret->_left = _CreateBinary(arr, ++index, size);
			ret->_right = _CreateBinary(arr, ++index, size);
		}
		return ret;
	}
	BinaryTreeNode* _Find(BinaryTreeNode* root,int x)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == x)
			return root;
		BinaryTreeNode* leftRet = _Find(root->_left, x);
		if (leftRet)
			return leftRet;
		BinaryTreeNode* rightRet = _Find(root->_right, x);
		return rightRet;
	}
	BinaryTreeNode* _GetPath(BinaryTreeNode* root,const BinaryTreeNode* child1,const BinaryTreeNode* child2)
	{	
		if (root == NULL)
			return NULL;
		bool temp = isInclude(root, child1, child2);
		if (temp == NULL)
			return NULL;
		else
		{

			BinaryTreeNode* leftFind = _GetPath(root->_left, child1, child2);
			BinaryTreeNode* rightFind = _GetPath(root->_right, child1, child2);
			if (leftFind == NULL&&rightFind == NULL)
				return root;
			else if (leftFind == NULL&&rightFind)
				return rightFind;
			else
				return leftFind;
		}
	}
	bool isInclude(BinaryTreeNode* root,const BinaryTreeNode* child1,const BinaryTreeNode* child2)
	{
		if (root == NULL)
			return false;
		bool c1 = false , c2=false;
		if (root == child1)
			c1 = true;
		if (root == child2)
			c2 = true;
		if (c1&&c2)
			return true;
		else
		{
			if (isInclude(root->_left, child1, child2))
				return true;
			else if (isInclude(root->_right, child1, child2))
				return true;
			else
				return false;
		}

	}
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(int* arr, int size)
		:_root(NULL)
	{
		int index = 0;
		_root = _CreateBinary(arr, index, size);
	}
	~BinaryTree()
	{
		if (_root == NULL)
			return;
		_Clear(_root);
	}
	void PostOrder_NonR()
	{
		if (_root == NULL)
			return;
		stack<BinaryTreeNode*> s;
		BinaryTreeNode* cur = _root;
		BinaryTreeNode* prev= NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode* top = s.top();
			if (top->_right==NULL||prev&&prev == top->_right)
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
	BinaryTreeNode* Find(int x)
	{
		return _Find(_root, x);
	}
	BinaryTreeNode* LastCommonFather(BinaryTreeNode* child1, BinaryTreeNode* child2)
	{
		if (_root == NULL || child1 == NULL || child2 == NULL)
			return NULL;
		return _GetPath(_root, child1, child2);
	}
};
void Test1() 
{
	int arr[] = { 1, 2, 4, 8, '#', '#', '#', 5, '#', 9, '#', '#', 3, 6, '#', '#', 7 };
	BinaryTree bt(arr, sizeof(arr) / sizeof(arr[0]));
	bt.PostOrder_NonR();
	/*cout << bt.Find(9)->_data << endl;
	if (bt.Find(0))
		cout << bt.Find(0)->_data << endl;*/
	if (bt.LastCommonFather(bt.Find(9), bt.Find(7)))
		cout<<bt.LastCommonFather(bt.Find(9),bt.Find(7))->_data<<endl;
}