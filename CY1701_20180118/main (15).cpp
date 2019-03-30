#include<iostream>
using namespace std;

/*
	异常处理   
	工厂模式
		1.简单工厂模式
		2.工厂方法模式
		3.抽象工厂模式  
*/
class Base
{
protected:
	int ma;
};
class Derive : virtual public Base
{
	/*
		vbptr
		Base::
			ma
	*/
};
int main()
{
	Base* pBase = new Derive();
	delete pBase;
	return 0;
}
//class BaseA
//{
//public:
//	int ma;
//	virtual void Show(){}
//};
//class BaseB
//{
//public:
//	int mb;
//	virtual void Show(){}
//};
//class Derive : public BaseA, public BaseB
//{
//
//public:
//	int md;
//	void Show(){}
//};
#if 0
#pragma vtordispe(off)
#pragma vtordisp(off)
class A
{
public:
	A(int data) :ma(data)
	{
		cout << "A::A(int)" << endl;
	}
	
	~A()
	{
		cout << "A::~A()" << endl;
	}
protected:
	int ma;
};
class B : virtual public A
{
public:
	B(int data) :mb(data), A(data)
	{
		cout << "B::B(int)" << endl;
	}  
	virtual void Show(){}
	~B()
	{
		cout << "B::~B()" << endl;
	} 
protected:
	int mb;
};
class C : virtual public A
{
public:
	C(int data) :mc(data), A(data)
	{
		cout << "C::C(int)" << endl;
	} 
	~C()
	{
		cout << "C::~C()" << endl;
	}
protected:
	int mc;
};
class E
{
public:
	E(int data) :me(data)
	{
		cout << "E::E(int)" << endl;
	}
	~E()
	{
		cout << "E::~E()" << endl;
	}
protected:
	int me;
};
class D :public B,public C ,virtual public E
{
public:
	D(int data) : A(data), B(data), C(data), E(data)
	{
		cout << "D::D(int)" << endl;
	}
	void Show()
	{
		cout << ma << endl;
	}
	~D()
	{
		cout << "D::~D()" << endl;
	}
protected:
	int md;
};
/*
构造顺序：
 A()
 B() 
 A()
 C() 
 D()  
     
*/
int main()
{
	D d1(10);
	d1.Show();
	return 0;
}
#endif