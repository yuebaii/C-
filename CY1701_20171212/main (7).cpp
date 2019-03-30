#include<iostream>
#include<complex>
using namespace std;

/*
	友元关系
*/
/*
封装  
	深度探讨CPP模型
 private:
 1.进行类型检查 安全检查  降低效率
友元 
 优点。编译器不进行类型检查 安全检查  提高效率
 缺点。破坏封装  运行时可能有隐患
建议：能不用友元就不要用，除非不得不用再用

1.普通函数做类的友元函数
	1.单向
2.类A 做 类B 的友元类
	类A中的this指针是指向类B的。需要传入类B的对象
	类A中的成员方法可以访问类B的所有东西
	友元关系是不可以继承
	父亲的朋友 不是儿子的朋友 
3.类A成员函数 做类B的友元函数 
	类A的这个成员函数是类B的友元函数
*/

/*
stack   系统开辟  系统释放
heap    设计人员开辟   设计人员销毁

设计人员开辟   系统释放

auto_ptr  lowest
class Test
{
public:
	Test( int* ptr = new int):p(ptr)
	{}
	~Test()
	{
		delete p;
	}
private:
	int *p;
}
int main()
{
	int *p = new int;
	Test test1(p);
	return 0;
} 
智能指针
	auto_ptr
  void  Func()
  {
	int *p = new int;
	*p = 11;
	if(*p != 10)
	{
		return;
	}

  }

*/
class Boy;
class Girl
{
public:
	Girl(int id = 0, int age = 18) :
		mid(id), mage(age){}
	void Show(const Boy &rhs);

private:
	int mid;
	int mage;
	 //void Show(const Boy&);
};
class Boy
{
public:
	Boy(int id = 0, int age = 18) :
		mid(id), mage(age){}
private:
	int mid;
	int mage;
	friend void Show(const Boy&);
	friend void Girl::Show(const Boy&);
	//friend class Girl;
};
void Girl::Show(const Boy& rhs)
{
	cout << rhs.mid << endl;
	cout << rhs.mage << endl;
} 
//class kid :public Boy
//{
//};


void Show(const Boy& rhs)
{
	cout << rhs.mid << endl;
	cout << rhs.mage << endl;
}
int main()
{
	Boy boy;
	Girl girl;
	girl.Show(boy);
	return 0;
}

#if 0
/*
	模拟实现STL中的list  不要空间配置器
	  template   lei  迭代器  运算符重载   
	1.描述  
	2.代码  
*/
/* int i = 10; 
	类成员方法：
		（） 仿函数  []  -> *
	: ?: :: . 
*/


class CInt
{
public:
	CInt(int val = 0):mvalue(val){}
	bool operator <(int rhs)
	{
		return mvalue < rhs;
	}
	CInt& operator ++()
	{
		++mvalue;
		return *this;
	}
	const CInt operator ++(int)
	{
		int tmp = mvalue;
		++mvalue;
		return CInt(tmp);
	}
	int& operator[](int* arr)
	{
		return arr[mvalue];
	}
private:
	friend ostream& operator <<(ostream& out, const CInt& rhs);

	int mvalue;
};
ostream& operator <<(ostream& out, const CInt& rhs)
{
	out << "value:" << rhs.mvalue << endl;
	return out;
}
int main()
{
	int arr[] = { 6, 96, 6, 6, 3, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	CInt i = 0;
	int j = 0;
	/*
		i.operator<(len);
	*/
	cout << i++ << endl;
	 //i.operator++(int)
	cout << ++i << endl;
	//for (i; i < len; ++i)
	//{
	//	cout << i[arr] << " ";
	//	//arr[i]  *(arr+i)
	//	//i[arr]  *(i+arr)
	//} 
	cout << endl;
	return 0; 
}
class CComplex
{
public:
	CComplex(int real = 0, int image = 0);
	const CComplex operator+(int rhs);
	const CComplex operator+(int rhs)const;
	/*operator int()
	{
		return mreal;
	}*/ 
	ostream& operator<<(ostream& out)
	{
		out << "real:" << mreal << endl;;
		out << "image:" << mimage << endl;
		return out;
	} 
private:
	int mreal;
	int mimage;
	friend const CComplex operator+(const CComplex&, const CComplex&);
};
CComplex::CComplex(int real, int image) :mreal(real), mimage(image)
{	
}
const CComplex CComplex::operator+(const int rhs)
{
	return CComplex(mreal + rhs);
}
const CComplex CComplex::operator+(const int rhs)const 
{
	return CComplex(mreal + rhs);
}
const CComplex operator+(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}

int main()
{
	int a = 10;
	int b = 20;
	CComplex comp1;
	CComplex comp2 = comp1 + 10 + 10;
	////comp1 + 10 = 30;
	////    CComplex * const   const CComplex *
	////(comp1.operator+(10)).operator+(10);
	////comp1 + 10 = 20;
	//comp1.operator+(10);
	CComplex comp3 = 10 + comp2;//
	// 10+ (comp2.operator int();)
	//               30;
	comp3 = comp1 + comp2;
	//      comp1.operator+(const CComplex&)
	//otsream&
	//cout << comp3;
	comp3 << cout;
	//comp3.operator<<(cout);
	return 0;
}
#endif 