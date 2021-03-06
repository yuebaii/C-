#include<iostream>
#include<memory>
using namespace std;

/*
scoped_ptr
*/
/*
	auto_ptr  C++98
		一个智能指针对象智能管理一块内存
	unique_ptr
		数组 []
	scrope_ptr
		把拷贝构造和赋值运算符重载函数写在private:
	shared_ptr
		带有引用计数的一个智能指针
	weak_ptr
	
*/
/*
	stack  系统开辟   系统释放
	heap   手动开辟   手动释放

	手打开辟   系统释放
	class  析构函数

	外部手动开辟
	赋给一个类   智能指针
	scope_ptr
*/
class RefManage //带引用计数的智能指针
{
public:
	RefManage(){}
	~RefManage(){}
	void addRef(void* ptr = NULL)
	{
		if (ptr != NULL)
		{
			int index = Find(ptr);
			if (index < 0)
			{
				ref[length++].refaddr = ptr;
			}
			else
			{
				ref[index].refcount++;
			}			
		}
	}
	void delRef(void * ptr = NULL)//throw exception()
	{
		if (ptr != NULL)
		{
			int index = Find(ptr);
			if (index < 0)
			{
				throw exception("addr not exist!");
			}
			else
			{
				if (ref[index].refcount == 1)
				{
					delete ptr;
				}
				else
				{
					ref[index].refcount--;
				}
			}
		}
	}
private:
	int Find(void* ptr)
	{
		int retindex = -1;
		for (int i = 0; i < length; ++i)
		{
			if (ref[i].refaddr == ptr)
			{
				return i;
			}
		}
		return retindex;
	}
private:
	class Node
	{
	public:
		Node(void* ptr = NULL)
		{
			refaddr = ptr;
			refcount = 1;
		}
		void* refaddr;
		int refcount;
	};
	Node ref[10];
	static int length;
};

int RefManage::length = 0;
template<typename T>
class Shared_ptr
{
public:
	Shared_ptr(T* ptr = NULL)
	{
		_ptr = ptr;
		rm.addRef(ptr);
	}
	Shared_ptr(const Shared_ptr<T>& rhs)
	{
		_ptr = rhs._ptr;
		rm.addRef(_ptr);
	}
	Shared_ptr<T>& operator = (const Shared_ptr<T>& rhs)
	{
		if (this != &rhs)
		{
			rm.delRef(_ptr);
			_ptr = rhs._ptr;
			rm.addRef(_ptr);
		}
		return *this;
	}
	~Shared_ptr()
	{
		rm.delRef(_ptr);
		_ptr = NULL;
	}
private:
	T* _ptr;
	static RefManage rm;
};
template<typename T>
RefManage Shared_ptr<T>::rm;
int main()
{
	int *p = new int;
	Shared_ptr<int> sp(p);
	Shared_ptr<int> sp1(p);
	Shared_ptr<int> sp2(p);
	return 0;
}
#if 0
/*带标志位的智能指针。对auto_ptr改进，使多个智能指针可以管理一个内存*/
template<typename T>
class Smart_ptr 
{
public:
	Smart_ptr(T* ptr = NULL)
	{
		_ptr = ptr;
		owner = true;
	}
	Smart_ptr(Smart_ptr<T>& rhs)
	{
		_ptr = rhs._ptr;
		owner = rhs.owner;
		rhs.owner = false;
	}
	Smart_ptr<T>& operator = (Smart_ptr<T>& rhs)
	{
		if (this != &rhs)
		{
			if (owner)
			{
				delete _ptr;
			}
			_ptr = rhs._ptr;
			owner = rhs.owner;
			rhs.owner = false;
		} 
		return *this;
	}
	~Smart_ptr()
	{
		if (owner)
		{
			delete _ptr;
		}
		_ptr = NULL;
	}
	T& operator *()
	{
		return *_ptr;
	}
private:
	bool owner;
	T* _ptr;
};

void Test(Smart_ptr<int> lhs)
{
	
} 
int main()
{
	Smart_ptr<int> sp(new int);
	Smart_ptr<int> sp1(sp);
	*sp = 10;
	Test(sp1);
	*sp = 10;
	//auto_ptr<int> ap(new int);
	//auto_ptr<int> ap1(ap);
	//*ap = 10;
	return 0;
}
/*
auto_ptr
	只有一个对象来管理内存
*/
template<typename T>
class Auto_ptr//
{
public:
	Auto_ptr(T* ptr = NULL)
		:_ptr(ptr)
	{
		ptr = NULL;
	}
	Auto_ptr(Auto_ptr<T>& rhs)
	{
		_ptr = rhs._ptr;
		rhs._ptr = NULL;
	}
	Auto_ptr<T>& operator=(Auto_ptr<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		delete _ptr;
		_ptr = rhs._ptr;
		rhs._ptr = NULL;
		return *this;
	}
	~Auto_ptr()
	{
		delete _ptr;
		_ptr = NULL;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};
class Test
{
public:
	Test(int a = 10) :ma(a){}
	void Show()
	{
		cout << ma << endl;
	}
private:
	int ma;
};
int main()
{
	int* p = new int;
	Auto_ptr<int> ap(p); 
	//*ap1;

	Test* p1 = new Test(20);
	Auto_ptr<Test> ap1(p1);
	ap1->Show();
	Auto_ptr<Test> ap2(ap1);
	ap1->Show();

	/*
		ap1.operator->()    Test*->Show();
	*/
	return 0;
}

void Test(int a)
{
	int* p = new int();
	if (a <= 0)
	{
		throw exception("a < 0");
	}
	delete p;
}
int main()
{
	return 0;
}
#endif 