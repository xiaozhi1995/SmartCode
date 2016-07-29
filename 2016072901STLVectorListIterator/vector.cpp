//
////#include"vector.h"
//#include<iostream>
//#include<stdlib.h>
//using namespace std;
//class A
//{
//public:
//	int a;
//	int b[3];
//	void f()
//	{
//		cout << "a" << endl;
//	}
//	static const int c=10;
//};
//class B :virtual public  A
//{
//public:
//	int b;
//	void f()
//	{
//		cout << "b" << endl;
//	}
//};
//class C :virtual public  A
//{
//public:
//	int c;
//	void f()
//	{
//		cout << "c" << endl;
//	}
//};
//class D :public  B,public  C
//{
//public:
//	int d;
//	void f()
//	{
//		cout << "d" << endl;
//	}
//};
//int main()
//{
//	/*D d;
//	d.B::a = 1;
//	d.C::a = 2;
//	d.b = 3;
//	d.c = 4;
//	d.d = 5;
//
//	B* pb = &d;
//	C* pc = &d;
//	D* pd = &d;
//	cout << sizeof(d) << endl;
//	
//	pb->f();
//	pc->f();
//	pd->f();
//
//	B lo;
//	A* pa = &lo;
//	cout << sizeof(lo) << endl;
//	pa->f();
//	lo.a = 7;
//	lo.b = 8;*/
//	//TestVector();
//	//TestSList();
//	//char ch[] = "hello\0world";
//	//cout << sizeof(ch) << " " << strlen(ch) << endl;
//	A ko;
//	ko.a = 0;
//	ko.f();
//	cout << ko.c << endl;
//	cout << sizeof(A) <<"  "<<sizeof(ko)<< endl;
//	system("pause");
//	return 0;
//}

#include"list.h"
#include"vector.h"
int main()
{
	TestSList();
	TestVector();
	system("pause");
	return 0;
}