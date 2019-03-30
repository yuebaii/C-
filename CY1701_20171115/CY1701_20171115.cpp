#include<iostream>
using namespace std;
/*
1.��Ա��������
1.�������캯��������
2.��ֵ��������غ���������
2.��̬��Ա����
1.���λ��
2.��ʼ������Ҫ���캯����ʼ��
3.��̬��Ա����
1.����Ҫ�������
2.����Լ����ͬ
3.���ܷ��ʳ�Ա�����ͳ�Ա����
4.������ͳ���Ա����
1.thisָ�������  Test* const this
2.����ָ��ת��������
3.����������ͨ�������໥����
4.��������static�������໥����
5.���������޸�
6.����������ͨ��������ָ�����͵�����

const ���εĳ�Ա����  �����ڹ��캯���ĳ�ʼ���б������ʼ��

(const���εĳ�Ա����)����(��Ա����������)
ϵͳ���ṩ��ֵ����������غ���

��̬�ĳ�Ա�������ܵ��÷Ǿ�̬�ĳ�Ա�������߳�Ա����
*/
/*
int * => const int
const int* ==> int *
const int* ==> const int*
int** ==> const int**
��ͨ��Ա�����ܵ��ó���Ա����    Test* const ==> const Test* const
����Ա�������ܵ�����ͨ��Ա����  const Test* const ==> Test* const

��̬��Ա�������ܵ�����ͨ��Ա����  û��this
��ͨ��Ա�����ܵ��þ�̬��Ա����


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

int data = 10;//���ݶ�
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
