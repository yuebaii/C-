#include<iostream>
using namespace std;

#pragma warning(disable:4996)
/*
初始化列表

下节课内容：
const 修饰的成员变量
成员变量&
static 修饰的成员变量
static 修饰的成员函数
常对象

*/
class Test
{
public:
	Test(int input) :mb(input), ma(mb)
	{
		
	}
	void Show()
	{
		cout << "a:" << ma << endl;
		cout << "b:" << mb << endl;
	}
private:
	int &mb;
	int ma; 
};

int main()
{ 
	Test test(30);
	test.Show();
	return 0;
}
#if 0
class CDate
{
public:
	//CDate(){}
	CDate(int year,int month, int day)
	{
		myear = year;
		mmonth = month;
		mday = day;
	} 
	void Show()
	{
		cout << "year:" << myear << endl;
		cout << "month:" << mmonth << endl;
		cout << "day:" << mday << endl;
	}
private:
	int myear;
	int mmonth;
	int mday;
};
class CStu
{
public:

	CStu(char* name, int age, float score
		,int year,int month,int day):
		mdate(year, month, day), 
		mage(age), mscore(score)
	{
		/*
		   char* mname;
		   int mage = age;
		   float mscore;
		   CDate mdate;

		   CDate mdate(int,int,int);
		*/
		mname = new char[strlen(name) + 1];
		strcpy(mname, name);
	}
	void Show()
	{
		cout << "name:" << mname << endl;
		cout << "age:" << mage << endl;
		cout << "score:" << mscore << endl;
		mdate.Show();
	}
	~CStu()
	{
		delete[] mname;
		mname = NULL;
	}
private:
	char* mname;
	int mage;
	float mscore;
	CDate mdate;//成员对象
};
int main()
{   
	CStu student("zhangsan",22,88.5f,2017,11,11);
	student.Show();
	return 0;
}

class Test
{ 
public:
	 Test()
	 {
		 cout << this << "Test()" << endl;
	 }
	 Test(int data)
	{
		cout << this << "Test(int)" << endl;
		mvalue = data;
	}
	~Test()
	{
		cout << this << "~Test()" << endl;
	}
	Test(const Test& rhs)
	{
		cout << this << "Test(const Test&)" << endl;
		mvalue = rhs.mvalue;
	}
	void operator=(const Test& rhs)
	{
		cout << this << "void operator=(const Test&)" << endl;
		if (this == &rhs)
			return;
		mvalue = rhs.mvalue;
	}
	void Show()
	{
		cout << mvalue << endl;
	}
private:
public:
	int mvalue;
};


/*
1.实参和形参类型和个数是否匹配
2.调用点的返回类型和 函数声明或定义时的返回值类型是否匹配
3.通过返回值确定返回方式

1.类类型形参使用引用效率高
2.返回值使用临时对象的效率高

产生临时量的类型：
1.内置类型产生的临时量  常量
2.类类型 产生的临时量 变量
3.隐式生成的临时量   常量

接收一个返回值（以引用或指针指向的方式）
内置类型
不产生临时量
自定义类
产生的临时量 变量
*/


/*
char short int unsigned long float double
*/
typedef struct Data
{
	int a;
}Data;

// 不能返回局部的指针或者引用
Data& sum()
{
	Data tmp = { 10 };
	return tmp;
}

int main()
{
	Data &b = sum();
	//Data *p = &sum();
	cout << b.a << endl;
	Test test(20);
	cout << b.a << endl;
	return 0;
}

Test func1(Test rhs)
{
	int value = rhs.mvalue;
	Test tmp(value);
	return tmp;
}
Test func2(Test& rhs)
{
	int value = rhs.mvalue;
	Test tmp(value);
	return tmp;
}
Test func3(Test* rhs)
{
	int value = rhs->mvalue;
	Test tmp(value);
	return tmp;
}
Test func4(Test& rhs)
{
	int value = rhs.mvalue;
	return Test(value);
}

int main()
{
	Test test1;
	Test test2(20);
	test1 = func4(test2);
	cout << "------------------" << endl;
	return 0;
}

int main()
{
	Test test1(10);
	Test test2 = test1;
	Test test3(test1);
	return 0;
}
#endif