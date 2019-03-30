#include<iostream>
#include<typeinfo>
using namespace std;
#include "test.h"//inline

/*
template + class 链表
template + 函数 
逻辑
class Node;

class Link;

*/

/*
	C++模板：
	C：泛型编程
	C++：模板就是泛型编程
	<<C++ templates>>
	
*/
//#pragma warning(disable:4996)
//#pragma warning(disable:4700)
/*
函数重载

模板：
1.函数模板 
2.模板的实例化 //（显示实例化，隐式实例化）
3.模板函数
4.模板的实参推演
5.模板类型参数 
6.模板的非类型参数
	1.常量
	2.不能使用double float
7.模板的特例化（专用化）
	模板的特例化必须和函数模板要表达的逻辑相同
8.模板函数的重载
	1.普通函数
	2.特例化版本
	3.实例化

9.类模板
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
	compare(1,2); //内置
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
	T temp = T();//零初始化  零构造
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
模板的特例化（专用化）
解决模板不能完全处理的有些类型的逻辑代码

*/
//template<>
//void Sort<char*>(char* arr[], int len)
//{   
//	cout << "template<> Sort()" << endl;
//	cout << typeid(arr[0]).name() << endl;
//	int i = 0;
//	int j = 0;
//	typedef char *ElemType;
//	char* temp = ElemType();//零初始化  零构造
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
//把类型参数化 T E  type element
/*
函数模板
*/
template<typename T>
bool compare(T a, T b);

template	<typename T>
void func()
{
	cout << "hello world！" << endl;
}
template<typename T,typename E>//class类 typename
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
模板函数
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
	//隐式实例化
	//sum<int>(10, 20); 
	//sum<double>(10.1, 20.1);
	//sum<float>(10.1f, 20.1f);
	/*
		模板的实参推演
	*/
	/*
		int  == 》 函数模板   实例化一份  模板函数
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