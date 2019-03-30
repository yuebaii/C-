#include<iostream>
#include<typeinfo>
using namespace std; //using 指示符

/*
名字空间作用域
类作用域
*/

namespace MyName
{
	int gdata = 11;
	int sum()
	{
		return 10;
	}
}
namespace MyName
{
	int gdata1 = 11;
}
int gdata = 12;
int main()
{
	using namespace MyName;
	using std::cout;
	using std::endl;

	int gdata = 10;
	int data = sum();
	cout << data << endl;
	return 0;
}


#if 0
// new delete  
// malloc free()
// 定位 new ?



int main()
{
	int*pc = (int*)malloc(sizeof(int));
	cout << *pc << endl;
	free(pc);

	//池，事先分配出来一块资源
	// 用户态  -》  内核态
	// malloc (4096) 
	// malloc brk  mmap()
	int *pcpp = new int(50);	
	/*
	1.开辟空间
	2.初始化 或者 调用构造函数
	*/
	cout << *pcpp << endl;
	delete pcpp;

	int *pc1 = (int *)malloc(sizeof(int)* 10);
	free(pc1);

	int *pcpp1 = new int[100]();
	delete []pcpp1;
	
	int **p = (int **)malloc(sizeof(int*)*3);
	for (int i = 0; i < 3; ++i)
	{
		p[i] = (int *)malloc(sizeof(int)*4);
	}
	
	int **pcpp2 = new int*[3];
	for (int i = 0; i < 3; ++i)
	{
		pcpp2[i] = new int[4];
	}
	for (int i = 0; i < 3; ++i)
	{
		delete[] pcpp2[i];
	}
	delete[] pcpp2;

	if (pc == NULL)
	{
		exit(0);
	}
	//运算符重载

	int *pcpp3 = new int(); // bad_alloc()

	delete pcpp3;

	const int *pcpp4 = new const int();
	//const int *pcpp5 = new const int[100]();

	return 0;
}
/*
const 与 一级指针的结合

const 与 变量的引用的结合
普通引用  引用  普通变量
普通引用  引用  常量   不行
普通引用  引用  立即数 不行
常引用    引用  普通变量/常量
常引用    引用  立即数  
 一级指针指针的引用

const 与 二级指针的结合

const 与 形参列表的结合

const 与 返回值 指针  引用的结合

const 

权限变小 没有问题
int * ==> const int*
权限变大   有问题
const int* ==> int*

int ** ==>const int **
*/
/*
<= 4 eax
>4 <=8 eax ecx
>8  push
*/
//不能返回局部变量的指针和引用
int& sum()
{
	static int temp = 10; //.data
	return temp;
}
int main()
{
	int &a = sum();//

	//int &b = sum();//eax int* const a = 10


	//int *const&p = sum();
	//int *const*p = &sum();
	//int &b = *sum(); // temp
	// int *&b = sum();
	// int * temp = 0x00FF1844
	//int *const &b = temp;
	//const int *p = &sum();//&10;
	//int b = *sum();
	return 0;
}


void func(const int* a)
{
	cout << typeid(a).name() << endl;
}
void func(int* const a)
{
	cout << typeid(a).name() << endl;
}
void func(int* a)
{
	cout << typeid(a).name() << endl;
}
//
int main()
{
	int a = 10;
	func(&a);
	return 0;
}

int main()
{
	int a = 10;
	//a = 11;
	const int *p = &a;
	//*p = 100;
	const int **q = &p;
	//间接操作  有风险 编译避免
	//直接操作
	return 0;
}

int main()
{
	//const int a = 10; 
	//const int *const p = &a; // ebp - 8

	//const int a = 10;
	//int const &b = a;
	//cout << typeid(b).name() << endl;

	//const int &b = 10;
	//cout << &b << endl;
	
	//int a = 10;
	//const int &b = a;// (*b)
	////const int * const p = &a;

	//const int a = 10;
	//const int *const p = &a;
	//const int *const &q = p;
	//int **q = &p;
	return 0;
}
#endif