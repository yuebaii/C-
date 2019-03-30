#include<iostream>
#include<typeinfo>
using namespace std;
#include "test.h"//inline

/*
template + class ����
template + ���� 
�߼�
class Node;

class Link;

*/

/*
	C++ģ�壺
	C�����ͱ��
	C++��ģ����Ƿ��ͱ��
	<<C++ templates>>
	
*/
//#pragma warning(disable:4996)
//#pragma warning(disable:4700)
/*
��������

ģ�壺
1.����ģ�� 
2.ģ���ʵ���� //����ʾʵ��������ʽʵ������
3.ģ�庯��
4.ģ���ʵ������
5.ģ�����Ͳ��� 
6.ģ��ķ����Ͳ���
	1.����
	2.����ʹ��double float
7.ģ�����������ר�û���
	ģ�������������ͺ���ģ��Ҫ�����߼���ͬ
8.ģ�庯��������
	1.��ͨ����
	2.�������汾
	3.ʵ����

9.��ģ��
*/

template<typename T,int SIZE>
bool compare(const T a, T b)
{
	cout << typeid(T).name() << endl;
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << "compare<T>(char*,char*)" << endl;
	return a > b;
} 
template<>
bool compare<char*>( char* const a,char* b)
{
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << "compare<>(char*,char*)" << endl;
	return strcmp(a, b) == 0;
} 
bool compare1(char* a, char* b)
{
	cout << "compare()" << endl;
	return strcmp(a,b);
}
int main()
{
	char* p = "hello";
	char* q = "world";
	compare(p,q);
	return 0;
}
#if 0
template<typename T>
bool compare(T a, T b)
{
	cout << typeid(T).name() << endl;
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << "compare<T>(char*,char*)" << endl;
	return a > b;
}
template<>
bool compare<char*>(char* a, char* b)
{
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << "compare<>(char*,char*)" << endl;
	return strcmp(a, b) == 0;
}
/*
bool compare(int,int)
*/

int main()
{
	compare<int>('a','b');
	compare<char*>("hello","world");
	char* p = "hello";
	char* q = "world";
	//compare<int>
	//compare<char*>
	compare("hello", "world");//==>const char*
	//compare<const char*>
	compare(p, q); //==> char*
	/*
		compare<const char*>
	*/
	const int a = 1;
	cout << "---------------------------" << endl;
	cout << typeid(a).name() << endl;
	cout << "---------------------------" << endl;
	int b = 2;
	compare(1,2); //����
	compare(a, b);
	return 0;
}


class Test
{
public:
	int ma;
};


int main()
{
	int a = int();
	double b = double();
	typedef char *Char;
	char *p;
	Test test = Test();

	cout << p << endl;
	return 0;
}

template<typename T,int SIZE>
void Sort(T arr[])
{
	cout << "template<T> Sort()" << endl;
	cout << typeid(T).name() << endl;
	int i = 0;
	int j = 0;
	T temp = T();//���ʼ��  �㹹��
	for (i = 0; i < SIZE - 1; ++i)
	{
		for (j = 0; j < SIZE - i - 1; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}	
}
/*
ģ�����������ר�û���
���ģ�岻����ȫ�������Щ���͵��߼�����

*/
//template<>
//void Sort<char*>(char* arr[], int len)
//{   
//	cout << "template<> Sort()" << endl;
//	cout << typeid(arr[0]).name() << endl;
//	int i = 0;
//	int j = 0;
//	typedef char *ElemType;
//	char* temp = ElemType();//���ʼ��  �㹹��
//	for (i = 0; i < len - 1; ++i)
//	{
//		for (j = 0; j < len - i - 1; ++j)
//		{
//			if (strcmp(arr[j],arr[j + 1]) > 0)
//			{
//				temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;	
//			}
//		}
//	}
//}
int main()
{
	int arr[] = { 15, 1321, 65, 13, 13, 13, 1 };
	char* arr1[] = { "hdllo", "hbrld", "hcst", "bain" };
	int len = sizeof(arr) / sizeof(arr[0]);
	Sort<int,7>(arr);
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i] << endl;
	}
	return 0;
}

//int sum(int a = 0, int b = 0)
//{
//	return a + b;
//} 
//double sum(double a, double b)
//{
//	return a + b;
//}
//double sum(int a, double b)
//{
//	return a + b;
//}
//�����Ͳ����� T E  type element
/*
����ģ��
*/
template<typename T>
bool compare(T a, T b);

template	<typename T>
void func()
{
	cout << "hello world��" << endl;
}
template<typename T,typename E>//class�� typename
T sum(T a, E b)
{
	return a + b;
} 
/*
int sum(int a, double b)
{
	return a + b;
}	
*/
/*
ģ�庯��
int sum<int>(int a, int b)
{
	return a + b;
} 

double sum<double>(double a, double b)
{
	return a + b;
}
float sum<float>(float a, float b)
*/
int main()
{
	sum<int, int>(10, 30);
	sum(10, 30.1);
	/*
		int  ==> T
		double ==> E
	*/
	return 0;
}

int main()
{
	compare<int>(10, 20); //UND
	compare(10, 20.1);
	return 0;
}

int main()
{
	//��ʽʵ����
	//sum<int>(10, 20); 
	//sum<double>(10.1, 20.1);
	//sum<float>(10.1f, 20.1f);
	/*
		ģ���ʵ������
	*/
	/*
		int  == �� ����ģ��   ʵ����һ��  ģ�庯��
	*/
	/*
		int double
	*/
	sum<int>(10, 30.1);
	//sum(30.9, 20.9);//50.2  
	//sum(10, 20.1);
	return 0;
}
#endif