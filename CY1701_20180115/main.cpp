#include<iostream>
#include<string>
using namespace std;

class A
{
public:
	int ma;
};
class B : public A
{
public:
	int mb;
};
class C : public A
{
public:
	int mc;
};
class D : public B, public C
{
public:
	int md;
};
int main()
{
	D d;
	d.C::ma;
	return 0;
}
#if 0
class Base
{
public:
	Base(int data = 0) :ma(data)
	{
		cout << "Base::Base()" << endl;
	}
	virtual ~Base()
	{
		
		cout << "Base::~Base()" << endl;
	}
	virtual void Show()
	{
		cout << "Base::Show()" << endl;
	}
	void Show(int data)
	{
		cout << "Base::Show(int)" << endl;
	}
private:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) : mb(data)
	{
		cout << "Derive::Derive()" << endl;
	}
	~Derive()
	{
		cout << "Derive::~Derive()" << endl;
	}
private:
	void Show()
	{
		cout << "Derive::Show()" << endl;
	}
private:
	int mb;
};
int main()
{
	Base* p = new Derive(10);
	p->Show();
	/*
		call eax //编译期间 访问限定符的限制  编译
		eax 运行
	*/
	delete p;
	return 0;
}
class Brid
{
public:
	Brid(string name) :mname(name){ cout << "Brid::Brid()" << endl; }
	virtual void fly(int height) = 0;
	~Brid()
	{
		cout << "Brid::~Brid()" << endl;
	}
protected:
	string mname;
};
class Penguin : public Brid
{
public:
	Penguin(string name):Brid(name)
	{
		cout << "Penguin::Penguin()" << endl;
	}
	void fly(int height)
	{
		cout << mname << "can not fly" << endl;
	}
};
class Eagle : public Brid
{
public:
	Eagle(string name) : Brid(name)
	{
		cout << "Eagle::Eagle()" << endl;
	}
	void fly(int height)
	{
		cout << mname << "can fly" << height<<"m"<<endl;
	}
};

void ShowFly(Brid* brid)
{
	/*if (typeid(*brid) == typeid(Penguin))
	{
		cout << "can not fly" << endl;
		cout << "fly 0m" << endl;
	}
	else
	{
		brid->fly(10);
	}*/
	/*
		brid 这个实参所指向的vftable中的RTTI和传入的类型实参进行比较
		如果相同转换
		不同  转换  NULL
	*/
	Penguin* pen = dynamic_cast<Penguin*>(brid);
	if (pen == NULL)
	{
		brid->fly(10);
	}
	else
	{
		cout << "can not fly" << endl;
		cout << "fly 0m" << endl;
	}

}
int main()
{
	Penguin* pen = new Penguin("Penguin");
	Eagle* eagle = new Eagle("Eagle");
	ShowFly(pen);
	ShowFly(eagle);
	return 0;
}
/*
	用于纯虚函数的类 叫做 抽象类
	抽象类能不能实例化一个对象？
		不能  只能做指针或者引用
*/
class Animal
{
public:
	Animal(string name = "") :mname(name){}
	virtual void bark() = 0;//纯虚函数
protected:
	string mname;
};
class Dog : public Animal
{
public:
	Dog(string name) :Animal(name){}
	void bark()
	{
		cout << mname <<":WANG WANG WANG!" << endl;
	} 
};
class Cat : public Animal
{
public:
	Cat(string name) :Animal(name){}
	void bark()
	{
		cout << mname << ":MIAO MIAO MIAO!" << endl;
	}
}; 

/*
	通过传入的对象
	打印对象的叫声
*/
void PrintBark(Animal* animal)
{
	animal->bark();
} 
int main()
{
	Dog* dog = new Dog("dog");
	Cat* cat = new Cat("cat");
	/*                             vftable
		vfptr          vfptr       class Cat
		mname          mname           0
		                           bark();
	*/
/*	int *p1 = (int*)dog;
	int *p2 = (int*)cat;
	int tmp = p1[0];
	p1[0] = p2[0];
	p2[0] = tmp;*/ 

	dog->bark();//动态
	cat->bark();//动态 

	cout << "dog::" << typeid(*dog).name() << endl;
	cout << "cat::" << typeid(*cat).name() << endl;

	PrintBark(dog);
	PrintBark(cat);
	delete dog;
	delete cat;
	return 0;
}
#endif
#if 0
class Base
{
public:
	Base(int data = 0) :ma(data)
	{
		cout << "Base::Base()" << endl;
		Show(); //动态绑定？静态的绑定
		//clear();//vfptr = 0x00000000

	} 
	void clear()
	{
		memcpy(this,0,sizeof(*this));
	}
	virtual ~Base()
	{
		Show();//静态绑定
		cout << "Base::~Base()" << endl;
	}
	void Show()
	{
		cout << "Base::Show()" << endl;
	}
	void Show(int data)
	{
		cout << "Base::Show(int)" << endl;
		//对象是完整
		this->Show();
	}
private:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) : mb(data)
	{
		cout << "Derive::Derive()" << endl;
	}
	~Derive()
	{
		cout << "Derive::~Derive()" << endl;
	}
	virtual void Show()
	{
		cout << "Derive::Show()" << endl;
	}
	//virtual void Show(int data)
	//{
	//	cout << "Derive::Show(int)" << endl;
	//}
private:
	int mb;
};
/*
	基类中没有任何的虚函数
	派生类中有一个Show函数是虚函数

	基类的指针指向派生类内存
	派生类内存在堆内存上开辟   基类中用虚析构函数
*/
int main()
{
	Base* pb = new Derive(10);
	/*
		vfptr    new     0x100   0x100  12
		Base::  
		  ma     delete  0x104 
		mb

		Base::
			vfptr
			ma
		mb
	*/
	delete pb;
	return 0;
} 
#endif
#if 0
/*
	基类中有一个Show是虚函数  
	在内存上实例化了一个派生类的对象
*/
int main()
{
	Base* pb = new Derive(10);
	pb->Show();
	delete pb;// 
	//pb->~Base();
	/*
		call eax ==》 ~Derive();
		call ~Base();
		/*
			析构函数  继承与派生来说  这个相当于一个特殊的同名函数
	*/
	return 0;
}

int main()
{
	Base *p = new Base(10);
	p->Show(10);//
	delete p;
	return 0;
}

/*
	虚表的生成时机
*/
int main()
{
	//Base* p = new Base(10);
	//p->Show();//0x0

	//Derive* pd = new Derive(10);
	//pd->Show();
	return 0;
}
#endif
/*
	1.基类和派生类中都没虚函数
		1.派生类的内存布局
		2.Show()同名的函数关系
			overload  重载
				1.相同作用域
			overhide  隐藏 同名函数
			override  覆盖 同名而且参数列表也相同
		3.Show的调用时一个动态的绑定
	Base::
		ma
	mb
	静态的绑定   
	2.基类中有虚函数   派生类中没有虚函数
		1.
		Base::       RTTI class Derive    
			vfptr        0
			ma       &Derive
		vfptr
		mb 
		2.
		3.
	3.基类中没有虚函数  派生类中有虚函数
		1.
		    vfptr
			Base::
			  ma
			mb
		2.隐藏
		3.
*/
#if 0
int main()
{
	/*
		基类中有虚函数   派生中也有存在一个基类中没有的虚函数
		&Base::Show      &Derive::Show
		                 &Derive::Show_int
	*/
	Base* pb = new Derive();
	pb->Show();
	/*
		不是虚函数
		call Base::Show
	*/
	/*
		语法分析 Show
		Show ==> virtual  call  eax
	*/
	Derive *pd = new Derive();
	pd->Show();
	return 0;
}
#endif