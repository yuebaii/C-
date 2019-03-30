#include<vector>
#include<list>
#include<deque>
#include<set>
#include<string>
#include<map>
#include<stack>
#include<queue>
#include<iterator>
#include<functional>
#include<algorithm>
#include<iostream>
#include<new>
#include<climits>
#include<cstddef>
#include<cstdlib>
using namespace std;

namespace CY1701
{
	template<typename _T>
	inline _T* MyAllocate(ptrdiff_t n, _T*)
	{
		set_new_handler(NULL);
		_T* tmp = (_T*)(::operator new((size_t)(n * sizeof(_T))));
		if (0 == tmp)
		{
			cout << "no memory alloc!" << endl;
			exit(0);
		}
		return tmp;
	}

	template<typename _T1, typename _T2>
	inline void MyConstruct(_T1* p, const _T2& value)
	{
		new (p)_T2(value);
	}
	template<typename _T1>
	inline void MyDeallocate(_T1* pd)
	{
		::operator delete(pd);
	}
	template<typename _T1>
	inline void MyDestruct(_T1* p)
	{
		p->~_T1();
	}

	template<typename _Ty>
	class CY1701_allocate
	{
	public:
		typedef _Ty value_type;
		typedef _Ty* pointer;
		typedef const _Ty* const_pointer;
		typedef _Ty& reference;
		typedef const _Ty& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<typename U>
		struct rebind
		{
			typedef CY1701_allocate<U> other;
		};

		pointer allocate(size_type n, const void* p = 0)
		{
			return MyAllocate((difference_type)(n), (pointer)(p));
		}
		void deallocate(pointer p,size_type n)
		{
			MyDeallocate(p);
		}
		void construct(pointer p, const_reference val)
		{
			MyConstruct(p, val);
		}
		void destroy(pointer p)
		{
			MyDestruct(p);
		}
		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer address(const_reference x)
		{
			return (const_pointer)&x;
		}

		size_type max_size()const
		{
			return size_type(-1) / sizeof(value_type);
		} 
	};
}

/*
	π€≤Ï’ﬂ
*/
class Test
{
public:
	Test(){ ma = 40; }
private:
	int ma;
	friend ostream& operator<<(ostream& out, const Test& rhs);
};
ostream& operator<<(ostream& out, const Test& rhs)
{
	out << rhs.ma << " ";
	return out;
}

int main()
{
	int a = 10;
	int *p = &a;
	char*q = new (p) char();
 /*   Test arr[10];
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<Test, CY1701::CY1701_allocate<Test>> vec(arr,arr+len);
	vector<Test, CY1701::CY1701_allocate<Test>>::iterator it = vec.begin();
	for (it; it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;*/

	/*int arr[] = { 156, 1, 231, 651, 31, 3, 16, 13 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int, CY1701::CY1701_allocate<int>> vec(arr,arr+len);
	vector<int, CY1701::CY1701_allocate<int>>::iterator it = vec.begin();
	for (it; it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;*/
	return 0;
}
#if 0
class Listener
{
public:
	Listener(string str) :mstr(str){}
	virtual void handleMessage(int iMessage)const = 0;
protected:
	string mstr;
};

class TestListener1:public Listener
{
public:
	TestListener1(string str) :Listener(str){}
	virtual void handleMessage(int iMessage)const
	{
		cout << "Listener name:" << mstr << endl;
		switch (iMessage)
		{
		case 1:
			cout << "1 resv!" << endl;
			break;
		case 2:
			cout << "2 resv!" << endl;
			break;
		case 3:
			cout << "3 resv!" << endl;
			break;
		default:
			break;
		}
	}
};
class TestListener2:public Listener
{
public:
	TestListener2(string str) :Listener(str){}
	virtual void handleMessage(int iMessage)const
	{
		cout << "Listener name:" << mstr << endl;
		switch (iMessage)
		{
		case 1:
			cout << "1 resv!" << endl;
			break;
		case 2:
			cout << "2 resv!" << endl;
			break;
		case 3:
			cout << "3 resv!" << endl;
			break;
		default:
			break;
		}
	}
};
class TestListener3:public Listener
{
public:
	TestListener3(string str) :Listener(str){}
	virtual void handleMessage(int iMessage)const
	{
		cout << "Listener name:" << mstr << endl;

		switch (iMessage)
		{
		case 1:
			cout << "1 resv!" << endl;
			break;
		case 2:
			cout << "2 resv!" << endl;
			break;
		case 3:
			cout << "3 resv!" << endl;
			break;
		default:
			break;
		}
	}
};

class Observe
{
public:
	static void registerMessage(const Listener* inListener,
		int iMessage)
	{
		map<int, vector<const Listener*>>::iterator it= mmap.find(iMessage);
		if (it == mmap.end())
		{
			mmap[iMessage].push_back(inListener);
		}
		else
		{
			it->second.push_back(inListener);
		}
	}
	static void handleMessage(int iMessage)
	{
		map<int, vector<const Listener*>>::iterator it = mmap.find(iMessage);
		if (it == mmap.end())
		{
			cout << "no  Listener interst!" << endl;
			return ;
		}
		vector<const Listener*>::iterator vit = it->second.begin();
		for (vit; vit != it->second.end(); ++vit)
		{
			(*vit)->handleMessage(iMessage);
		}
	}

private:
	static map<int, vector<const Listener*>>  mmap;
};
map<int, vector<const Listener*>> Observe::mmap;

int main()
{
	TestListener1 listener1("listener1");
	TestListener2 listener2("listener2");
	TestListener3 listener3("listener3");

	Observe ob;
	ob.registerMessage(&listener1, 1);
	ob.registerMessage(&listener1, 2);

	ob.registerMessage(&listener2, 1);
	ob.registerMessage(&listener2, 3);

	ob.registerMessage(&listener3, 2);
	ob.registerMessage(&listener3, 3);

	ob.handleMessage(1);
	return 0;
}

template<typename _Fn2>
class Mybinder2nd
{
public:
	Mybinder2nd(_Fn2& fn, const typename _Fn2::second_argument_type& val) :
		ob(fn), value(val){}
	bool operator()(const typename _Fn2::first_argument_type& left)
	{
		return ob(left,value);
	}
private:
	_Fn2 ob;
	//_Fn2::first_argument_type
	typename _Fn2::second_argument_type value;
};
template<typename _Fn2,
		typename _Ty>
Mybinder2nd<_Fn2>	 mybind2nd(_Fn2& fn, const _Ty& val)
{
	return Mybinder2nd<_Fn2>(fn, val);
}

template< class InputIterator, class Predicate >
InputIterator
my_find_if(InputIterator first,
InputIterator last, Predicate pred)
{
	for (first; first != last; ++first)
	{
		if (pred(*first))
		{
			return first;
		}
	}
	return last;
}
int main()
{
	int arr[] = { 65, 32, 156, 132, 1, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);

	vector<int> myVector(arr, arr + len);
	vector<int>::iterator &r = find_if(
		myVector.begin(), 
		myVector.end(), 
		not1(bind2nd(greater_equal<int>(), 100)));

	return 0;
}
#endif