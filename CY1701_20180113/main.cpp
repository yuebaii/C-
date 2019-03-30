#include<iostream>
using namespace std;


/*
1.继承   代码复用
2.三种不同形式的继承关系
              基类中
public        
protected 
private
3.继承关系下的构造顺序
4.同名函数
	1.函数重载
		1.作用域
		2.函数名称  形参不同
	2.隐藏
		1.不同作用
	3.覆盖
		1.不同作用域
5.四种类型转换的方式
static_cast
const_cast
reinterpret_cast
dynamic_cast   RTTI

6.基类和派生类的相同指向或者引用

派生类的指针指向基类的对象   N
基类的指针指向派生类的对象   Y
基类的引用引用派生类的对象   Y
派生类的引用引用基类的对象   N
*/
/*
虚析构  
  指向堆内存上的对象
  delete会导致派生类的析构函数没办法调用 从而产生资源没办法释放  
*/

/*
	纯虚函数
	animal  叫： void bark()=0; 
	带有纯虚函数的类：抽象类  不能生产对象  指针或者引用
	class dog   void bark(){}

	Dog dog;
	Cat cat;

	int* p1 = (int*)&dog;
	int* p2 = (int*)&cat;
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;


*/
class Base
{
public:
	Base(int  data = 0) :ma(data)
	{
		cout << "Base()" << endl;
	}
	void Show()
	{
		cout << "Base::Show()" << endl;
	} 
	void Show(int data)
	{
		cout << "Base::Show(int)" << endl;
	}
	void* operator new(size_t size)
	{
		int *p = (int*)malloc(size);
		cout <<"new::"<< p << endl;
		if (p == NULL)
		{
			throw bad_alloc();
		}
		return p;
	}
	void operator delete(void* ptr)
	{
		cout << "delete::"<<ptr << endl;
		free(ptr);
	}
	~Base()
	{
		cout << "~Base()" << endl;
	}
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int  data) :mb(data), Base(data)
	{
		cout << "Derive()" << endl;
	}
	virtual void Show()//编译器认为这个函数也是虚函数
	{
		cout << "Derive::Show()" << endl;
	}
	~Derive()
	{
		cout << "~Derive()" << endl;
	} 
private:
	int mb;
};
int main()
{

	Base *p = new Derive(10);
	/*
		vfptr
		Base::
		  ma
		mb
	*/
	p->Show();

	//p = (Base*)((int)p - 4);
	delete p;
	//(*p).~Base();
	/*
		void free(void *ptr);
	*/
	return 0;
}
#if 0
/*
虚函数
1.能取地址
2.对象

构造函数 不能
析构函数 可以
inline函数 不能
static函数 不能
*/
/*
	1.什么时候会产生运行时多态的编译或者调用
		指针指向或者引用时，调用虚函数
*/

int main()
{
	Base b(10);
	Derive d(20);
	
	b.Show();
	d.Show(); 

	Base *p1 = &b;
	p1->Show();

	Base *p2 = &d;
	p2->Show();

	Derive *p3 = &d;
	p3->Show();

	return 0;
}
int main()
{
	Derive d(10);
	Base* p = &d;
	p->Show();
	/*
	Base  编译阶段  静态的绑定 早绑定 静态的多态 call  Base::Show
		函数重载  模板  
	*/
	/*
		运行时==>动态的绑定  晚绑定     运行时的多态
		call  eax
		继承：虚函数 
	*/
	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << typeid(p).name() << endl;//class Base*
	cout << typeid(*p).name() << endl;//class Base
	return 0;
}
int main()
{
	Base b(10);
	Derive d(10);

	//Derive* p1 = &b; //??  派生类的指针  没办法指向基类的对象
	//Base* p2 = &d;//基类的指针  指向派生类的对象  

	//Derive &b1 = b;//派生类的引用  没办法引用基类对象
	Base &d1 = d;//基类的引用可以引用派生类的对象
	return 0;
}
#endif