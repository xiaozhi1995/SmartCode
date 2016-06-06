#include<iostream>
using namespace std;
struct LinkNode
{
	int _data;
	LinkNode* _next;
	LinkNode(int x)
	:_data(x)
	,_next(NULL)
	{}
};
class List
{
	private:
		LinkNode* _head;
	public:
		List()
		:_head(NULL)
		{}
	void PushBack(int x)
	{
		if(_head==NULL)
		{
			_head=new LinkNode(x);
		}
		else
		{
			LinkNode* cur=_head;
			while(cur->_next!=NULL)
				cur=cur->_next;
			cur->_next=new LinkNode(x);
		}
	}
	void PopBack()
	{
		if(_head==NULL)
			return;
		if(_head->_next==NULL)
		{
			delete _head;
			_head=NULL;
		}
		else
		{
			LinkNode* cur=_head;
			while(cur->_next->_next)
			{
				cur=cur->_next;
			}
			LinkNode* del=cur->_next;
			delete del;
			cur->_next=NULL;
		}
	}
	void Erase(LinkNode* node)
	{
		if(node==NULL)
			return;
		if(node->_next!=NULL)/*不为尾接点*/
	    {
		
	   		node->_data=node->_next->_data;
			LinkNode* del=node->_next;
			node->_next=del->_next;
			delete del; 
	    }
		else
		{//尾删 
			if(_head->_next==NULL)
		    {
				delete _head;
				_head=NULL;
	 	    }
			else
			{
				LinkNode* cur=_head;
				while(cur->_next->_next)
				{
					cur=cur->_next;
				}
				LinkNode* del=cur->_next;
				delete del;
				cur->_next=NULL;
				}
		}
		 
		
	}
	LinkNode* Find(int x)
	{
		if(_head==NULL)
			return NULL;
		LinkNode* cur=_head;
		while(cur&&cur->_data!=x)
			cur=cur->_next;
		return cur;
	}
	LinkNode*  Joseph(int k)//0 1 2 3 4,删除第三个数，次序为2 0 4  1，剩3 ,环形buf解决问题 
	{
		int count=k-1;
		if(_head==NULL)
			return NULL;
		LinkNode* cur=_head;
		while(1)
		{
		
			count=k-1;
			while(count-->0&&cur->_next!=cur)
			{
				cur=cur->_next;
			}
			if(cur->_next==cur)
				break;
			cout<<"delete:"<<cur->_data<<"  ";
			LinkNode* del=cur->_next;
			cur->_data=del->_data;
			cur->_next=del->_next;
			delete del;
	    }
		_head=cur;//别的已删除 
		_head->_next=NULL;
		cout<<endl;
		return cur;
	}
	void Print()
	{
		if(_head==NULL)
			return;
		LinkNode* cur=_head;
		while(cur)
		{
			cout<<cur->_data<<" ";
			cur=cur->_next;
		}
		cout<<endl;
	}
};
void Test1()
{
	List l;
	l.PushBack(0); 
	l.PushBack(1); 	
	l.PushBack(2); 	
	l.PushBack(3); 	
	l.PushBack(4);
	l.Print();
	l.Find(4)->_next=l.Find(0);
	l.Joseph(3);
}
int main()
{
	Test1();
	return 0;
}






//2
#include<iostream>
using namespace std;
int lastRemain(int n,int m)
{
	if(n<1||m<1)
	return -1;
	int last=0;
	for(int i=2;i<=n;++i)
	{
		last=(last+m)%i;
		cout<<last<<" "	;
	}
	cout<<endl;
	return last;
}
void Test1()
{
	//Joseph(n,m);n=5 m=3,(0 1 2 3 4 ,3)
	cout<<lastRemain(5,3)<<endl;
}
int main()
{
	Test1();
	return 0;
}