#include<iostream>
using namespace std;
/*
1.成员变量引用
1.拷贝构造函数的问题
2.赋值运算符重载函数的问题
2.静态成员变量
1.存放位置
2.初始化不需要构造函数初始化
3.静态成员方法
1.不需要对象调用
2.调用约定不同
3.不能访问成员方法和成员函数
4.常对象和常成员方法
1.this指针的类型  Test* const this
2.几个指针转换的问题
3.常方法和普通方法的相互调用
4.常方法与static方法的相互调用
5.常方法中修改
6.常方法和普通方法返回指针类型的问题

const 修饰的成员变量  必须在构造函数的初始化列表里面初始化

(const修饰的成员变量)或者(成员变量是引用)
系统不提供赋值运算符的重载函数

静态的成员方法不能调用非静态的成员变量或者成员方法
*/
/*
int * => const int
const int* ==> int *
const int* ==> const int*
int** ==> const int**
普通成员方法能调用常成员方法    Test* const ==> const Test* const
常成员方法不能调用普通成员方法  const Test* const ==> Test* const

静态成员方法不能调用普通成员方法  没有this
普通成员方法能调用静态成员方法


*/
class Test
{
public:
	Test(int value = 10) :ma(value), mb(value)
	{
		/*
		int &ma = value;
		*/
	}
	Test(const Test& rhs)
	{
		ma = rhs.ma;
		mb = rhs.mb;
	}
	void operator=(const Test& rhs)
	{
		if (this == &rhs)
		{
			return;
		}
		ma = rhs.ma;
		mb = rhs.mb;
	}
	void Show()const
	{
		cout << "ma:" << ma << endl;
		cout << "mb:" << mb << endl;
	}
	//Test* const  ==> const Test* const
	void Func()
	{
		Show();
	}
	static void Func2()
	{
		cout << "Func2()" << endl;
	}
	//this->ma  this->mb  const == > const int *
	const int* GetValues()const
	{
		return &ma;
	}
private:
	int ma;
	int mb;
};
//_cdecl
void Show()
{
	cout << "hello world!" << endl;
}
int main()
{
	//void(*)()
	void(*pCFunc)() = &Show;
	pCFunc();
	(*pCFunc)();
	Test test(10);
	Test* test1 = new Test(20);
	void(Test::*pPFunc)() = &Test::Func;
	(test1->*pPFunc)();//.*  ->*


	return 0;
}
#if 0
int main()
{

	const Test test1;  //const Test  const int=>int*
	Test test2(20);
	//const Test* const  *this  Test
	test2.Func();
	return 0;
}

class Counter
{
public:
	Counter(int data = 10) :mnumber(data)
	{
		mcount++;
	}
	Counter(const Counter& rhs)
	{
		mnumber = rhs.mnumber;
		mcount++;
	}
	//_cdecl
	static void Show()
	{
		cout << "all object:" << mcount << endl;
		Func1();
	}
	static void Func1(){}
	//thiscall
	void Func()
	{

	}
private:
	int mnumber;
	static int mcount;
};
int Counter::mcount = 0;


void Show()
{
	cout << "hello world" << endl;
}

int main()
{
	Counter c1;
	Counter c2;
	Counter c3;
	Counter::Show();
	return 0;
}

int data = 10;//数据段
class Test
{
public:
	Test(int value = 10) :ma(data), mb(data)
	{
		/*
		int &ma = value;
		*/
	}
	Test(const Test& rhs) :ma(data)
	{
		//ma = rhs.ma;
		mb = rhs.mb;
	}
	void operator=(const Test& rhs)
	{
		if (this == &rhs)
		{
			return;
		}
		mb = rhs.mb;
	}
	void Show()
	{
		cout << "ma:" << ma << endl;
		cout << "mb:" << mb << endl;
	}
private:
	const int ma;
	int mb;
};

int main()
{
	Test test1;
	Test test2(test1);
	test1 = test2;

	test2.Show();
	return 0;
}
#endif
