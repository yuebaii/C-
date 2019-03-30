#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
//面向过程  C
//C中struct
//
/*
面向对象 OOP
面对对象思想的三大特征：
封装  继承  多态（静多态 动多态）
封装
封装与隐藏
访问限定符
 1.public:  任意位置都能访问
 2.protected: 继承派生 子类可以访问父类的保护成员
 3.private: 只有在类中才能访问 
this:CGoods* const this
系统给出的函数：
1.公用的
2.内联的
1.构造函数和析构函数
构造函数：
初始化对象的内存地址空间
析构函数：
释放对象的内存空间所占资源
实例化一个对象
1.分配对象内存空间
2.调用对象的构造函数
没有实现构造函数
系统会给出默认的构造函数
自己出构造函数 系统就不会提供默认的构造函数
实例化一个不带参数的对象
后面不加括号
2.拷贝构造函数
用一个已经存在的对象初始化相同类型新对象
调用的拷贝构造函数
必须传引用
防止实参和形参递归构造
系统提供的拷贝构造函数   浅拷贝
多次释放同一资源
3.赋值运算符重载函数
//void operator=() //运算符重载
用已存在的对象给另一个已存在的对象赋值
系统提供的赋值运算符重载函数 浅拷贝
多次释放同一资源
内存泄漏
1.防止自赋值
2.释放旧资源
3.开辟新资源进行初始化

思考
CStack这个类中
为什么可以在MAXSIZE定义的位置之前  访问MAXSIZE
*/

#pragma warning(disable:4996)
class CStack
{
public:
	CStack()
	{
		mtop = 0;

	}
	~CStack(){}
	CStack(const CStack& rhs)
	{
		for (int i = 0; i < rhs.mtop; ++i)
		{
			mval[i] = rhs.mval[i];
		}
		mtop = rhs.mtop;

	}
	void operator=(const CStack& rhs)
	{
		if (this == &rhs)
		{
			return;
		}
		for (int i = 0; i < rhs.mtop; ++i)
		{
			mval[i] = rhs.mval[i];
		}
		mtop = rhs.mtop;

	}
	void Push(int data)
	{
		if (mtop < MAXSIZE)
		{
			mval[mtop++] = data;
		}	
	}
	int Pop()
	{
		if (mtop == 0)
			throw("Stack Empty!");
		return mval[--mtop];
	}
	int Top()
	{
		if (mtop == 0)
			throw("Stack Empty!");
		return mval[mtop-1];	
	}
	void Show()
	{
		for (int i = 0; i < mtop; ++i)
		{
			cout << mval[i] << " ";
		}
		cout << endl;
	}
private:
	enum{ MAXSIZE = 20 };
	int mval[MAXSIZE];
	int mtop;
};

int main()
{
	CStack st;
	for (int i = 0; i < 19; ++i)
	{
		st.Push(i+1);
	}
	st.Show();
	int a = st.Pop();
	st.Show();
	cout << a << endl;
	return 0;
}
#if 0
class CGoods
{
public:
	CGoods()
	{
		_name = new char[1];
		cout << this <<":CGoods()" <<endl;
	}
	CGoods(char* name, int amount, int price)
	{
		cout << this << ":CGoods()" << endl;
		this->_name = new char[strlen(name) + 1];
		strcpy(_name, name);
		this->_amount = amount;
		this->_price = price;
	} 
	CGoods(const CGoods& rhs)
	{
		/*this->_name = rhs._name;
		this->_amount = rhs._amount;
		this->_price = rhs._price;*/
		_name = new char[strlen(rhs._name) + 1];
		strcpy(_name, rhs._name);
		_amount = rhs._amount;
		_price = rhs._price;
	}
	//good1  == > good3
	//good3 = good1;
	void operator=(const CGoods& rhs)
	{  
		//_name = rhs._name;
		//_amount = rhs._amount;
		//_price = rhs._price;
		if (this == &rhs)
		{
			return;
		}
		delete[]_name;
		_name = new char[strlen(rhs._name) + 1];
		strcpy(_name, rhs._name);
		_amount = rhs._amount;
		_price = rhs._price;
	}
	~CGoods()
	{
		cout << this << ":~CGoods()" << endl;
		delete[] _name;
		_name = NULL;
	}
	void Show();

	void SetName(char* name)
	{
		if (_name == NULL)
		{
			_name = new char[strlen(name) + 1];
		}
		strcpy(_name, name);
	}
	void SetAmount(int amount){ _amount = amount; }
	void SetPrice(float price){ _price = price; }

	void GetName(char* name){ strcpy(name, _name); }
	//char* GetName();
	//在函数设计时  尽量避免返回成员变量的指针或者引用
	int GetAmount(){ return _amount; }
	float GetPrice(){ return _price; }
	void release()
	{
		delete[] _name;
		_name = NULL;
	}
private:
	char* _name;
	int _amount;
	float _price;
};
void CGoods::Show()
{
	cout << "name:" << _name << endl;
	cout << "amount:" << _amount << endl;
	cout << "price:" << _price << endl;
}

int main()
{	

	//
	CGoods good1;//系统给出的默认的构造函数
	CGoods good2("good2",20,25.6);
	good2.Show();
	CGoods good3 = good2;//拷贝构造函数
	good3 = good2;//赋值运算符的重载函数
    //
	/*
		初始化：定义的同时赋值
		赋值：  定义后，在赋值
	*/

	return 0;
}
//
//struct Node1
//{	
//};

//类中定义
//函数调用时 当inline函数处理
//类外定义
//函数调用时和普通函数一样
//thiscall
class CGoods;

class CGoods
{
public:
	
	void Register(char* name, int amount, int price)
	{
		this->_name = new char[strlen(name) + 1];
		strcpy(_name, name);
		this->_amount = amount;
		this->_price = price;
	}
	void Show();

	void SetName(char* name)
	{
		if (_name == NULL)
		{
			_name = new char[strlen(name) + 1];
		}
		strcpy(_name, name);
	}
	void SetAmount(int amount){ _amount = amount; }
	void SetPrice(float price){ _price = price; }

	void GetName(char* name){ strcpy(name, _name); }
	//char* GetName();
	//在函数设计时  尽量避免返回成员变量的指针或者引用
	int GetAmount(){ return _amount; }
	float GetPrice(){ return _price; }
	void release()
	{
		delete[] _name;
		_name = NULL;
	}
private:
	char* _name;
	int _amount;
	float _price;
};
void CGoods::Show()
{
	cout << "name:" << _name << endl;
	cout << "amount:" << _amount << endl;
	cout << "price:" << _price << endl;
}
CGoods ggood;
int main()
{
	CGoods good1;
	CGoods good2;
	good1.Register("good1",20,16.8);
	//void Register(CGoods *const this,char* name, int amount, int price)
	//this = &ggood;
	//good1.Register(&good1,"good1",20,16.8);
	return 0;
}
int main()
{
	
	
	CGoods good1;
	good1.Register("mianbao",20,25.5);
	

	//CGoods* 
	//good1.Register(&good1,"mianbao",20,25.5);
	good1.Show();
	//Node1 node;
	//cout << sizeof(Node1) << endl;
	//int a = node.sum();
	//cout << a << endl;
	//CGoods good;
	//good._price = 10;
	return 0;
}


typedef struct Stu
{
	char* pname;
	int age;
	float score;
	void (*init)(Stu*, char*, int, float);
	void (*show)(Stu*);
	void (*release)(Stu*);
}Stu;

void init(Stu* stu, char* name, int age, float score)
{
	stu->pname = (char*)malloc(strlen(name)+1);
	strcpy(stu->pname, name);
	stu->age = age;
	stu->score = score;
}
void show(Stu* stu)
{
	printf("name:%s\nage:%d\nscore:%f\n", 
		stu->pname, stu->age, stu->score);
}
void release(Stu* stu)
{
	free(stu->pname);
	stu->pname = NULL;
}
//inline 
int main()
{
	Stu stu;
	stu.init = init;
	stu.show = show;
	stu.release = release;

	stu.init(&stu,"zhangsan",22,78.5);
	stu.show(&stu);
	stu.release(&stu);
	//Stu stu;
	//init(&stu, "zhangsan", 22, 78.5);
	//show(&stu); 
	return 0;
}
#endif