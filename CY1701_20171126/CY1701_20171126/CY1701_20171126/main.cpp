#include<iostream>
#include<stack>
#include<typeinfo>
using namespace std;
//#pragma warning(disable:4700)
template<typename T>
class Test
{
public:
	Test(T val = T()) :ma(val){}
	void Show()
	{
		cout << "Test::Show()" << endl;
	}
private:
	int ma;
};

template<typename T>
void Func(Test<T> a)
{
	cout << "Func()" << endl;
	a.Show();
}

template<>
void Func(Test<int> a)
{
	a.Show();
}


int main()
{
	Test<int> test1;
	Func(test1);
	/*
		test1 Test<int> ==> Test<int> 
	*/
	Func<int>(10);
	/*
		10  int ==> Test<T> ???类
	*/
	return 0;
}
#if 0
class Test
{
public:
	void Print(int a)
	{
		cout << "hello world!" << endl;
	}
	int Func2(int a, int b)
	{
		cout << "Func2()" << endl;
		cout << "a:" << a << endl;
		cout << "b:" << b << endl;
		return 0;
	}
};
class Test1
{
public:
	void Print(int a)
	{
		cout << "hello world!" << endl;
	}
	int Func2(int a, int b)
	{
		cout << "Func2()" << endl;
		cout << "a:" << a << endl;
		cout << "b:" << b << endl;
		return 0;
	}
};
template<typename T>
void Show(T a)
{
	cout << typeid(T).name() << endl;
}


void Func()
{
	cout << "Func()" << endl;
}
int Func2(int a, int b)
{
	cout << "Func2()" << endl;
	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	return 0;
}
template<typename T>
void CFunc(T cpfunc)
{
	cpfunc();
}
Test test1;
/*
void (Test::*)(int)
void (Test::*)(int,int)
*/



template<typename R,typename C,typename F,typename S>
void CPFunc(R (C::*cppfunc)(F,S),F a,S b)
{
	C c;
	//F a = F();
	//S b = S();
	(c.*cppfunc)(a,b);
} 

int main()
{
	CFunc(Func);
	CPFunc(&Test1::Func2,10,20);
	//Show(10);
	//Show("hello");
	//Show<char*>("hello");
	//Show(&Func);
	/*
		void (*)()
	*/

	//Show(Func);
	//Show(&Test::Print);

	/*
		void (_thicall Test::*)()
	*/

	return 0;
}

template<typename T = int, int SIZE = 20>
class MyVector
{
public:
	MyVector() :cursize(0), totalsize(SIZE)
	{
		cout << "MyVector()" << endl;
		arr = new T[SIZE];
	}
	//void push_front(T val);
	//insert(iterator,val)
	template<typename T, int SIZE = 20>
	friend class MyVector;
	/*
	MyVector<int> MyVector<double>
	*/
	/*
	MyVector<double>  <= MyVector<int>
	*/
	template<typename E>
	/*explicit*/ MyVector(const MyVector<E>& rhs)
	{
		cout << "MyVector<T>(MyVector<E>)" << endl;
		arr = new T[rhs.totalsize];
		for (int i = 0; i < rhs.cursize; ++i)
		{
			arr[i] = rhs.arr[i];
		}
		cursize = rhs.cursize;
		totalsize = rhs.totalsize;
	}
	void operator=(const MyVector<T>& rhs)
	{
		cout << "void operator=(<T>)" << endl;
		if (this == &rhs)
		{
			return;
		}
		delete[]arr;
		arr = new T[rhs.totalsize];
		for (int i = 0; i < rhs.cursize; ++i)
		{
			arr[i] = rhs.arr[i];
		}
		totalsize = rhs.totalsize;
		cursize = rhs.cursize;
	}
	void resize()
	{
		T* newArr = new T[totalsize + SIZE];
		for (int i = 0; i < totalsize; ++i)
		{
			newArr[i] = arr[i];
		}
		T* p = arr;
		arr = newArr;
		totalsize += SIZE;
		delete[]p;
	}
	void push_back(T val)
	{
		if (cursize == totalsize)
		{
			resize();
		}
		arr[cursize++] = val;
	}
	//void pop_front();	
	void pop_back()
	{
		if (!empty())
		{
			cursize--;
		}
	}
	int max_size(){ return totalsize; }
	int size(){ return cursize; }
	bool empty()
	{
		return cursize == 0;
	}
	void show()
	{
		for (int i = 0; i < cursize; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	~MyVector()
	{
		cout << "~MyVector()" << endl;
		delete[] arr;
		arr = NULL;
	}
private:
	T *arr;
	int cursize;//当前已存放的元素个数
	int totalsize;//总体能存放的元素个数
};
/*
模板的偏特化
*/
template<typename T,
		typename Conainter = MyVector<T>>
//template<typename T,template<typename E,int SIZE> class TEMP>
class Stack
{
public:
	Stack()
	{
		cout << "Stack<T,Conainter>()" << endl;
	}
	void push(T val)
	{
		mc.push_back(val);
	}
	void pop()
	{ 
		mc.pop_back();
	}
	bool empty()
	{
		return (mc.empty());
	}
	void show()
	{
		mc.show();
	}
private:
	Conainter mc;
	//TEMP<T,20> mc;
};
template<typename T>
	//template<typename T,template<typename E,int SIZE> class TEMP>
class Stack<T,MyVector<int>>
{
public:
	Stack()
	{
		cout << "Stack<T,MyVector<int>>()" << endl;
	}
	void push(T val)
	{
		mc.push_back(val);
	}
	void pop()
	{
		mc.pop_back();
	}
	bool empty()
	{
		return (mc.empty());
	}
	void show()
	{
		mc.show();
	}
private:
	MyVector<int> mc;
};
int main()
{
	Stack<double, MyVector<double>> st1;
	Stack<double, MyVector<int>> st2;
	Stack<int, MyVector<int>> st3;
	return 0;
}

int main()
{
	Stack<int, MyVector> st1;
	Stack<char*, MyVector> st2;
	st2.push("hello");
	//Stack<int> st;
	//st.push(56);
	//st.push(78);
	//st.push(21);
	//st.push(52);
	//st.show();
	//st.pop();
	//st.show();
	return 0;
}

template<typename T>
class Test
{
public:
	Test():ma(0){}

	int GetValue()const
	{
		return ma;
	}
	/*
		void operator=(const Test<int>& rhs)
	*/
	template<typename E>
	Test<T>(const Test<E>& rhs)
	{
		ma = rhs.ma;
		//ma = rhs.GetValue();
	} 
private:
	T ma;
	template<typename A>
	friend class Test;
};
int main()
{
	Test<int> test1;
	Test<double> test2;
	Test<double> test3(test1);
	test2 = test1;

	return 0;
}
#endif