//求1+2+..+n,不能使用乘除法，for,while,if,else,switch,case等关键字及判断语句
/*#include<iostream>
using namespace std;
class Sum
{
	private:
		static int count;
		static int sum;
	public:
		static int GetSum()
		{
			return sum;
		}
		static void ReSet()
		{
			count=0;
			sum=0;
		}
		Sum()
		{
			++count;
			sum+=count;
		}
};
int Sum::count=0;
int Sum::sum=0;
void Test1()
{
	Sum::ReSet();
	int n=10;
	Sum* s=new Sum[n];
	cout<<Sum::GetSum()<<endl;
}
int main()
{
	Test1();
 	return 0;
} */

/*
#include<iostream>
using namespace std;
class A;
A *arr[2];//A arr[2]can not
class A
{
public:
	virtual int sum(int n)
	{
		return 0;//n=0
	}
};
class B:public A 
{
public:
	virtual int sum(int n)
	{
		return arr[!!n]->sum(n-1)+n;
	}
	
};
void Test1()
{
	A a;
	B b;
	arr[0]=&a;
	arr[1]=&b;
	int value=arr[1]->sum(10);
	cout<<value<<endl;
}
int main()
{
	Test1();
	return 0;
}*/

/*#include<iostream>
using namespace std;
typedef int (*fun)(int);
int Sum_fainal(int n)
{
	return 0;
}
int Sum_Mid(int n)
{
	static fun f[2]={Sum_fainal,Sum_Mid};
	return f[!!n](n-1)+n;
}
void  Test1()
{
	int value=Sum_Mid(10);
	cout<<value<<endl;
}
int main()
{
	Test1();
	return 0;
}*/

//n必须编译时确定，生成指定模版，开销大 
#include<iostream>
using namespace std;
template<int n>struct Sum
{
	enum Value{ N=Sum<n-1>::N+n};
};
template<>struct Sum<1>
{
	enum Value{
		N=1};
};
void Test1()
{
	Sum<10> s;
	cout<<s.N<<endl;
}
int main()
{
	Test1();
	return 0; 
}