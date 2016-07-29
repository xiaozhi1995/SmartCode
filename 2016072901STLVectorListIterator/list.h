#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<assert.h>
#include"iterator.h"
using namespace std;
template<class T>
struct __ListNode
{
	T _data;
	__ListNode<T>* _prev;
	__ListNode<T>* _next;
	__ListNode(const T& x = T())
		:_prev(NULL)
		, _next(NULL)
		, _data(x)
	{}
};

template<class T,class Ref,class Ptr>
struct __ListIterator
{
	typedef __ListIterator<T, Ref, Ptr> Self;
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef int DifferenceType;
	typedef T ValueType;
	typedef Ref Reference;
	typedef Ptr Pointer;

	__ListNode<T>* _node;
	__ListIterator()
	{}
	__ListIterator(__ListNode<T>* node)
		:_node(node)
	{}
	Reference operator*()
	{
		return _node->_data;
	}
	//当链表中存储结构体时，需要访问结构体成员变量
	Ptr& operator->()
	{
		//
		//return &(operator*());
		return &(_node->_data);
		//List<AA>::Iterator it=l.Begin();
		//cout<<it->_a<<endl;//编译器优化，按理说需要两个->->
	}
	bool operator==(const Self& s)
	{
		return _node == s._node;
	}
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	Self operator++(int)
	{
		Self tmp(*this);
		_node = _noode->_next;
		return tmp;
	}
	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	Self operator--(int)
	{
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
	DifferenceType Size()
	{
		return Distance(Begin(), End());
	}
	Reference operator+=(DifferenceType n)
	{
		while (n--)
		{
			++*this;
		}
		return *this;
	}
	Self operator+(DifferenceType n)
	{
		Self tmp(*this);
		tmp += n;
		return tmp;
	}
	Reference operator-=(DifferenceType n)
	{
		while (n--)
		{
			--*this;
		}
		return *this;
	}
	Self operator-(DifferenceType n)
	{
		Self tmp(*this);
		tmp -= n;
		return tmp;
	}
};


template<class T>
class List
{
	typedef __ListNode<T> Node;
	Node* _head;
public:
	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T,const T&,const T*> ConstIterator;
	typedef ReverseIterator<ConstIterator> ConstReverseIterator;
	typedef ReverseIterator<Iterator> ReverseIterator;
	typedef T ValueType;
	typedef T* Pointer;
	typedef const T* ConstPointer;
	typedef ValueType& Reference;
	typedef const ValueType& ConstReference;
	typedef int DifferenceType;
	
	List()
		:_head(new Node)
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	~List()
	{
		if (_head == NULL)
			return;
		while (1)
		{
			if (_head == NULL)
				break;
			else if (_head->_next = _head)
			{
				delete _head;
				_head = NULL;
			}
			else
			{
				Node* del = _head;
				_head = _head->_next;
				_head->_prev = NULL;
				delete del;
			}
		}
	}
	/*void PushBack(const T& x)
	{
		Node* tail = _head->_prev;
		Node* tmp = new Node(x);
		tmp->_next = _head;
		_head->_prev = tmp;
		tail->_next = tmp;
		tmp->_prev = tail;
	}*/
	void PushBack(const T& x)
	{
		Insert(End(), x);
	}
	void PushFront(const T&x)
	{
		Insert(Begin(), x);
	}
	void PopBack()
	{
		Erase(--End());
	}
	void PopFront()
	{
		Erase(Begin());
	}
	void Insert(Iterator pos, const T& x)
	{
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* tmp = new Node(x);

		tmp->_next = cur;
		cur->_prev = tmp;

		prev->_next = tmp;
		tmp->_prev = prev;
	}
	Iterator Erase(Iterator pos)
	{
		assert(pos!=End());
		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;

		Node* del = pos._node;
		prev->_next = next;
		next->_prev = prev;
		delete del;
		return Iterator(next);
	}
	Iterator Begin()
	{
		return Iterator(_head->_next);
	}
	Iterator End()
	{
		return _head;//explicit
		//return Iterator(_head);
	}
	ReverseIterator RBegin()
	{
		return ReverseIterator(End());
	}
	ReverseIterator REnd()
	{
		return ReverseIterator(Begin());
	}
	ConstReverseIterator RBegin()const
	{
		return ConstReverseIterator(End());//explicit
	}
	ConstReverseIterator REnd()const
	{
		return ConstReverseIterator(Begin());//explicit
	
	}
};
void TestSList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	List<int>::Iterator iter = l.Begin();
	while (iter != l.End())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;

	iter = l.Begin();
	while (iter != l.End())
	{
		List<int>::Iterator tmp = iter;
		++tmp;
		if (*iter % 2 == 0)
		{
			l.Erase(iter);
		}
		iter = tmp;
		/*if (*iter % 2 == 0)
		{
			iter = l.Erase(iter);
		}
		else
			++iter;*/
	}

	List<int>::ReverseIterator it = l.RBegin();
	
	while (it != l.REnd())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	cout << Distance(l.Begin(), l.End())<<endl;
}
//void TestVector()
//{
//	vector<int> v;
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(3);
//	v.push_back(4);
//	v.push_back(6);
//	v.push_back(5);
//
//	for (int i = 0; i < v.size(); ++i)
//	{
//		cout << v[i] <<" ";
//	}
//	cout << endl;
//	vector<int>::iterator iter = v.begin();
//	for (; iter != v.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
//}
//void TestList()
//{
//	list<int> l;//双向循环链表
//	l.push_back(1);
//	l.push_back(2);
//	l.push_back(3);
//	l.push_back(4);
//	l.push_back(6);
//	l.push_back(5);
//
//	list<int>::iterator iter = l.begin();
//	for (; iter != l.end(); ++iter)
//	{
//		cout << *iter <<" ";
//	}
//	cout << endl;
//}
//template<class K,int M>
//struct BPTreeNoneLeafNode
//{
//	K _keys[M];
//	//BPTreeNoneLeafNode<K, M>* _subs[M];
//	void* _subs[M];
//	size_t _size;
//	BPTreeNoneLeafNode<K, M>* _parent;
//};
//template<class K,class V,int M>
//struct BPTreeLeafNode
//{
//	K _keys[M];
//	BPTreeLeafNode<K, V, M>* _subs[M];
//	size_t _size;
//	BPTreeNoneLeafNode<K, M>* _parent;
//};
////另一种定义方式
//template<class K,class V,int M>
//struct BPTreeNode
//{
//	K _keys[M];
//	void* _subs[M];
//	BPTreeNode<K, V, M>* _parent;
//	size_t size;
//	bool _IsLeaf;
//};
//template<class K,class V,int M>
//class BPTree
//{
//public:
//	bool Insert(K& key, V& val);
//	bool Remove(K& key);
//	BPTreeLeafNode<K, V, M>* Find(K& key);
//private:
//	BPTreeNoneLeafNode<K, M>* _root;
//	BPTreeLeafNode<K, V, M>* _data;//链表
//};