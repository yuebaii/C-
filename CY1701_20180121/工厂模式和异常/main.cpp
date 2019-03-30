#include<iostream>
#include<exception>
#include<string>
using namespace std;

/*
	����ָ��
	auto_ptr
	shared_ptr
	weak_ptr
	->
*/
void Show(int a)
{
	auto_ptr<int> p(new int[10]);
	
	if (a < 0)
	{
		throw exception("a < 0");
		cout << "ERROR!" << endl;
	}
	//delete []p;
}
int main()
{
	try{
		Show(-1);
	}
	catch (exception &err)
	{
		cout << err.what() << endl;
	}
	return 0;
}
#if 0
/*
	�쳣��
		try   �����쳣
		throw �׳��쳣
	    	catch �����쳣
		finally C++��֧��
*/
/*
	int  

*/
class BaseException
{
public:
	BaseException(string name) :mname(name){}
	virtual void deal()
	{
		cout << mname << endl;
	}
	virtual  ~BaseException(){}
protected:
	string mname;
};
class StackFullException : public BaseException
{
public:
	StackFullException(string name) :BaseException(name)
	{
	}
	void deal()
	{
		cout << "StackFull" << endl;
	}
};
class StackEmptyException : public BaseException
{
public:
	StackEmptyException(string name) :BaseException(name)
	{
	}
	void deal()
	{
		cout << "StackEmpty" << endl;
	}
};
template<typename T,int SIZE>
class Stack
{
public:
	Stack()
	{
		arr = new T[SIZE];
		top = 0;
	}
	~Stack()
	{
		delete [] arr;
		arr = NULL;
	}
	bool IsFull()
	{
		return top == SIZE;
	} 
	/*
		�����������throw
		nothrow
	*/
	void* operator new(size_t size) throw(bad_alloc())
	{
		int* p = (int*)malloc(size);
		if (p == NULL)
			throw bad_alloc();  //exception;
		return p;
	}
	void Push(T val)
	{
		if (IsFull())
		{
			throw StackFullException("Stack Full");
		}
		arr[top++] = val;
	}
	/*
		catch(string & err)
		{
			
		} 
	*/
	bool IsEmpty()
	{
		return top == 0;
	}
	void Pop()
	{
		if (IsEmpty())
		{
			throw StackEmptyException("Stack Full");
		}
		--top;
	}
private:
	T* arr;
	int top;
};
int main()
{
	Stack<int,10> st;
	try{
		//st.Push(10);
		st.Pop();
	}
	catch (StackFullException &sfexception)
	{
		sfexception.deal();
	}
	catch (StackEmptyException &seexception)
	{
		//seexception.deal();
		throw;
	}

	return 0;
}
int CountLength(int a, int b, int c)
{
	if (a <= 0)
	{
		throw 1;
	}
	if (b <= 0)
	{
		throw 10.2;
	}
	if (c <= 0)
	{
		throw "all ERROR";
	}
	return a + b + c;
} 

int main()
{
	try
	{
		CountLength(-1,0, 20);
	} 
	catch (int a)
	{
		cout << "A::error" << a << endl;
	} 
	return 0;
}
/*
	���� 
	������ģʽ
	����ģʽ
	�۲���ģʽ
*/
/*
	
*/
class Singleton
{
public:
	static Singleton* getObject()
	{
		static Singleton sl;//data
		return &sl;
	}
private:
	Singleton(){}
};
/*
	���󹤳�ģʽ
*/
class A
{
public:
	A(string name = "") :mname(name){}
	~A(){}
	
	virtual void Operator() = 0;
protected:
	string mname;
};
class A1 : public A
{
public:
	A1(string name) :A(name){}
	void Operator()
	{
		cout << "A1::Operator()" << endl;
	}
};
class A2 : public A
{
public:
	A2(string name) :A(name){}
	void Operator()
	{
		cout << "A2::Operator()" << endl;
	}
};
class B
{
public:
	B(string name = "") :mname(name){}
	~B(){}

	virtual void Operator() = 0;
protected:
	string mname;
};
class B1 : public B
{
public:
	B1(string name) :B(name){}
	void Operator()
	{
		cout << "B1::Operator()" << endl;
	}
};
class B2 : public B
{
public:
	B2(string name) :B(name){}
	void Operator()
	{
		cout << "B2::Operator()" << endl;
	}
};

class Factory
{
public:
	virtual A* createA() = 0;
	virtual B* createB() = 0;
};
class Factory_1 : public Factory
{
public:
	A* createA()
	{
		return new A1("A1");
	}
	B* createB()
	{
		return new B1("B1");
	}
};
class Factory_2 : public Factory
{
public:
	A* createA()
	{
		return new A2("A2");
	}
	B* createB()
	{
		return new B2("B2");
	}
};

int main()
{
	Factory_2 f2;//������2�����ߣ�����һ����صĲ�Ʒ��
	A* pa = f2.createA();//2�����ߵ�A��������������һ����ز�Ʒ��
	pa->Operator();
	return 0;
}
/*

	��������ģʽ
*/

class Product
{
public:
	Product(string name = "") : mname(name){}
	virtual void Show() = 0;
	virtual ~Product(){}
protected:
	string mname;
};
class Product_A : public Product
{
public:
	Product_A(string name) :Product(name){}
	virtual void Show()
	{
		cout << "Product_A::name:" << mname << endl;
	} 
};
class Product_B : public Product
{
public:
	Product_B(string name) :Product(name){}
	virtual void Show()
	{
		cout << "Product_B::name:" << mname << endl;
	}
};
class Factory
{
public:
	virtual Product* create() = 0;
};
class Factory_A : public Factory
{
public:
	Product* create()
	{
		return new Product_A("A");
	}
};
class Factory_B : public Factory
{
public:
	Product* create()
	{
		return new Product_B("B");
	}
};
int main()
{
	Factory_A fa;//�൱�ڹ�����A������
	Product* pa = fa.create();//�൱��A�Ķ���
	Factory_B fb;//�൱�ڹ�����B������
	pa->Show();//�൱��B�Ķ���
	Product* pb = fb.create();
	pb->Show();
	delete p;
	return 0;
}

/*
	1.�򵥹���ģʽ	
*/
class Product
{
public:
	Product(string name = "") :mname(name)
	{
	} 
	virtual void Show() = 0;
	virtual ~Product(){}
protected:
	string mname;
};
class Product_A : public Product
{
public:
	Product_A(string name) :Product(name){}
	virtual void Show()
	{
		cout << "Product_A::name:" << mname << endl;
	}
};
class Product_B : public Product
{
public:
	Product_B(string name) :Product(name){}
	virtual void Show()
	{
		cout << "Product_B::name:" << mname << endl;
	}
};
class Factory
{
public:
	Factory(){}
	Product* create(int flag)
	{
		switch (flag)
		{
		case 1:
			return new Product_A("A");
			break;
		case 2:
			return new Product_B("B");
			break;
		default:
			break;
		} 
	}
};
int main()
{
	Factory fin;
	Product* fout = fin.create(2);
	fout->Show();
	delete fout;
	return 0;
}
#endif