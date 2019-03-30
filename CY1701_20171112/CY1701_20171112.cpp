#include<iostream>
using namespace std;

#pragma warning(disable:4996)
/*
��ʼ���б�

�½ڿ����ݣ�
const ���εĳ�Ա����
��Ա����&
static ���εĳ�Ա����
static ���εĳ�Ա����
������

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
	CDate mdate;//��Ա����
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
1.ʵ�κ��β����ͺ͸����Ƿ�ƥ��
2.���õ�ķ������ͺ� ������������ʱ�ķ���ֵ�����Ƿ�ƥ��
3.ͨ������ֵȷ�����ط�ʽ

1.�������β�ʹ������Ч�ʸ�
2.����ֵʹ����ʱ�����Ч�ʸ�

������ʱ�������ͣ�
1.�������Ͳ�������ʱ��  ����
2.������ ��������ʱ�� ����
3.��ʽ���ɵ���ʱ��   ����

����һ������ֵ�������û�ָ��ָ��ķ�ʽ��
��������
��������ʱ��
�Զ�����
��������ʱ�� ����
*/


/*
char short int unsigned long float double
*/
typedef struct Data
{
	int a;
}Data;

// ���ܷ��ؾֲ���ָ���������
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