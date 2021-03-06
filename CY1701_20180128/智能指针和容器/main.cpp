#include<iostream>
#include<vector>
#include<memory>
using namespace std;
/*
	C++ 容器都有哪些公有的接口
	insert
*/
template<typename T>
class Vector;
template<typename T>
class Iterator
{
public:
	Iterator(Vector<T>* p = NULL,int index = 0)
	{
		pvec = p;
		mindex = index;
	}
	bool operator!=(const Iterator<T>& rhs)
	{
		return mindex != rhs.mindex;
	}
	Iterator<T>& operator++()
	{
		++mindex;
		return *this;
	}
	T& operator*()
	{
		return (*pvec)[mindex];
	}
private:
	Vector<T>* pvec;
	int mindex;
};
template<typename T>
class Vector
{
public:
	typedef Iterator<T> iterator;
	Vector()
	{
		maxsize = 10;
		arr = new T[maxsize];
		size = 0;
	}
	Vector(int len)
	{
		maxsize = len;
		arr = new T[maxsize];
		size = 10;
		memset(arr, 0, sizeof(T)*maxsize);
	}
	~Vector()
	{
		delete arr;
	}
	T& operator[](int index)
	{
		return arr[index];
	}
	iterator begin()
	{
		return iterator(this, 0);
	}
	iterator end()
	{
		return iterator(this, size);
	}
private:
	T* arr;
	int size;//有效长度
	int maxsize;//最大长度
};
int main()
{
	Vector<int> vec1;
	Vector<int> vec2(10);
	int arr[] = { 15, 3, 16, 13, 13, 1, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	//vector<int> vec3(arr + 0, arr + len);
	Vector<int>::iterator it = vec2.begin();
	vec2[1] = 10;
	for (it; it != vec2.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	return 0;
}
#if 0
//C++98	
//	auto_ptr
//C++11
//	unique_ptr
//  shared_ptr
//  weak_ptr
//boost::
//scroped_ptr
//shared_ptr
//weak_ptr
class RefManage
{
public:
	/*
		插入
		1.存在 
			引用计数加1
		2.不存在
			插入到新的结点上
	*/
public:
	static RefManage& getIntance()
	{
		return rm;
	}
private:
	RefManage() :length(0){}
	RefManage(const RefManage&rhs) :length(0){}
public:
	void addRef(void* ptr)
	{
		cout << "add:" << endl;
		if (ptr != NULL)
		{
			int index = find(ptr);
			if (index < 0)
			{
				Node tmp(ptr);
				tmp.refcount++;
				node[length++] = tmp;
				cout << "	addr:  " << ptr << "  refcount:  " << tmp.refcount << endl;
			/*	node[length].refaddr = ptr;
				node[length].refcount++;
				length++;*/
			}
			else
			{
				node[index].refcount++;
				cout << "	addr:  " << ptr << "  refcount:  " << node[index].refcount<< endl;
			}
		}
	}
	/*
		1.引用计数--
	*/
	void delRef(void* ptr)
	{
		cout << "delRef" << endl;
		if (ptr != NULL)
		{
			int index = find(ptr);
			if (index < 0)
			{
				throw exception("addr not exsit!");
			}
			else
			{
				if (node[index].refcount != 0)
				{
					node[index].refcount--;
				}
				cout << "	addr:  " << ptr << "  refcount:  " << node[index].refcount << endl;
			}
		}
	}
	/*
		1.addr  
			不存在  -1
			NULL   0
			存在   引用计数
	*/
	int getRef(void *ptr)
	{
		if (ptr == NULL)
		{
			return 0;
		}
		int index = find(ptr);
		if (index < 0)
		{
			return -1;
		}
		return node[index].refcount;
	}
private:
	int find(void* ptr)
	{
		for (int i = 0; i < length; ++i)
		{
			if (node[i].refaddr == ptr)
			{
				return i;
			}
		}
		return -1;
	}
	class Node
	{
	public:
		Node(void* p = NULL) :refaddr(p), refcount(0){}
		void* refaddr;
		int refcount;
	};
	Node node[10];
	int length;//记录当前数组的有效长度
	static RefManage rm;
};	
RefManage RefManage::rm;
//智能指针类
template<typename T>
class Shared_ptr
{
public:
	Shared_ptr(T* p = NULL)
	{
		_ptr = p;
		AddRef();
	}
	Shared_ptr(const Shared_ptr<T>& rhs)
	{
		_ptr = rhs._ptr;
		AddRef();
	}
	Shared_ptr<T>& operator=(const Shared_ptr<T>& rhs)
	{
		if (this != &rhs)
		{
			DelRef();
			if (0 == GetRef())
			{
				delete _ptr;
			}
			_ptr = rhs._ptr;
			AddRef();
		}
		return *this;
	}
	T* GetPtr()const
	{
		return _ptr;
	}
	~Shared_ptr()
	{
		DelRef();
		if (0 == GetRef())
		{
			delete _ptr;
		}
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
	void AddRef()
	{
		rm.addRef(_ptr);
	}
	void DelRef()
	{
		rm.delRef(_ptr);
	}
	int GetRef()
	{
		return rm.getRef(_ptr);
	}
	T* _ptr;
	static RefManage &rm;
};
template<typename T>
RefManage& Shared_ptr<T>::rm = RefManage::getIntance();

class Test//被管理类
{
public:
	Test(int a = 0) :ma(a)
	{
		cout << "Test::Test()" << endl;
	}
	~Test()
	{
		cout << "Test::~Test()" << endl;
	}
private:
	int ma;
};

template<typename T>
class Weak_ptr
{
public:
	Weak_ptr(T* p = NULL)
	{
		_ptr = p;
	}
	Weak_ptr(const Shared_ptr<T>& rhs)
	{
		_ptr = rhs.GetPtr();//通过shared共享
	}
	Weak_ptr<T>& operator=(const Shared_ptr<T>& rhs)
	{
		_ptr = rhs.GetPtr();
		return *this;
	}
	~Weak_ptr()
	{
		_ptr = NULL;
	}
	
private:
	T* _ptr;
};
class B;
class A
{
public:
	A()
	{
		cout << "A::A()" << endl;
	}
	~A()
	{
		cout << "A::~A()" << endl;
	}
	//Shared_ptr<B> pa
	Weak_ptr<B> pa;//
};
/*
	A::
	  pa::
		_ptr = NULL
	B::
	  pb::
		_ptr = NULL
*/
class B
{
public:
	B()
	{
		cout << "B::B()" << endl;
	}
	~B()
	{
		cout << "B::~B()" << endl;
	}
	//Shared_ptr<A> pb
	Weak_ptr<A> pb;
};
int main()
{
	Shared_ptr<A> spa(new A());
	Shared_ptr<B> spb(new B());
	spa->pa = spb;
	spb->pb = spa;
	return 0;
}
int main()
{
	Test* p = new Test(10);
	Shared_ptr<Test> sp1(p);
	Shared_ptr<Test> sp2(p);
	Shared_ptr<Test> sp3(p);
	return 0;
}
#endif