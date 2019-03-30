#include<iostream>
using namespace std;

/*
对象的生存周期
	显示生成一个临时对象
形参  返回值
*/
/*
浅拷贝：
实现自己的构造，析构，拷贝构造，赋值运算符的重载
*/
#pragma warning(disable:4996)

class CObject
{
public:
	CObject()
	{
		mname = new char[1];
		cout << this << ":" << mname << ":CObject()" << endl;
	}
	CObject(int num)
	{
		mname = new char[1];
		mnum = num;
		cout << this << ":" << mname << ":CObject(int)" << endl;
	}
	CObject(char* name, int num)
	{
		mname = new char[strlen(name) + 1];
		strcpy(mname,name);
		mnum = num;
		cout << this << ":" << mname << ":CObject(char* ,int)" << endl;
	}
	CObject(const CObject& rhs)
	{
		mname = new char[strlen(rhs.mname) + 1];
		strcpy(mname, rhs.mname);
		mnum = rhs.mnum;
		cout << this << ":" << mname << ":CObject(const CObject&)" << endl;
	}
	void operator=(const CObject& rhs)
	{
		if (this == &rhs)
		{
			return;
		}
		delete[] mname;
		mname = new char[strlen(rhs.mname) + 1];
		strcpy(mname, rhs.mname);
		mnum = rhs.mnum;
		cout << this << ":" << mname << ":void operator=()" << endl;
	}
	~CObject()
	{
		cout << this << ":" << mname << ":~CObject()" << endl;
		delete[] mname;
		mname = NULL;
	}
private:
	char* mname;
	int mnum;
};

/*
	临时量产生的类型：
	   1.内置类型，产生的临时量  常量
	   2.类类型，产生的临时量   变量
	      1.隐式产生的临时量  也是常量
	赋值运算符的重载函数：
	   1.修饰形参不能改变
	   2.接收隐式产生的临时量
*/
/*
explicit  只能修饰构造函数 
*/
CObject gobject1;
int main()
{
	CObject object1;
	CObject object2("object2",2);

	CObject object3;
	object3 = CObject("object3", 2);
	CObject object4 = CObject("object3", 2);

	CObject object5 = (CObject)("object3", 2);
	//                    CObject(2);
	CObject object6 = 2;
	object1 = 2;

	CObject* pobject7 = &CObject("pobject", 1);
	CObject &pobject8 = CObject("pobject", 1);
	return 0;
}
CObject gobject2;
#if 0
int main()
{
	CObject object = CObject(20);
	//object = 20;
	return 0;
}

void func1(CObject rhs)
{
}
void func2(CObject& rhs)
{
}
void func3(CObject* rhs)
{

}


int main()
{
	//CObject object1;
	//CObject object2("object2",2);
	////;  , ?
	///*
	//  临时对象生成周期：
	//    表达式中
	//*/
	//object1 = CObject("object1", 2);
	//cout << "--------------------------------" << endl;

	//CObject object1;
	//CObject object2("object2", 2);
	////编译器优化
	//CObject object3 = CObject("object3", 2);
	//cout << "--------------------------------" << endl;
	///*
	//	临时量的作用：
	//	  临时量的生成 构造 object3
	//	优化：
	//	  以构造临时量的方式  构造 object3	
	//*/ 

	//逗号表达式
	//CObject object1 = CObject("object1", 2);
	//CObject object2;
	//object2 = (CObject)("object2", 2);
	//cout << "---------------------------------" << endl;
	//object2 = CObject(2);
	//CObject object3 = 3;

	//int arr[2][2] = { { 1, 2 }, { 3, 4 } };
	//int arr[2][2] = {2,4}
	//cout << "arr[0][1]:" << arr[0][1] << endl;
	//cout << "arr[1][1]:" << arr[1][1] << endl;

	//CObject object1 = CObject("object1", 2);
	//CObject object2 = (CObject)("object2", 2);
	//cout << "---------------------------------" << endl;
	//        const CObject&
	//// 隐式生成临时对象
	//object1 = 2;
	//cout << "---------------------------------" << endl;

	//cout << "---------------------------------" << endl;
	////        const CObject&
	//// 隐式生成临时对象
	//CObject object2  = 2; 
	//cout << "---------------------------------" << endl;

	//cout << "---------------------------------1" << endl;
	//CObject* pobject = &CObject("pobject", 1);
	//cout << "---------------------------------" << endl;
	//cout << "---------------------------------2" << endl;
	//CObject& pobject = CObject("pobject", 1);
	//cout << "---------------------------------" << endl;
	///*
	//	引用一个临时对象，
	//	临时对象的生成周期就变成引用这个对象的生成周期
	//*/
	/*
		void func1(CObject rhs){}
	*/
	//
	//func1(object1);
	//func1(CObject("pobject", 1));

	/*
	void func2(CObject& rhs)
	{
		rhs.mnum = 10;
	} 
	*/
	CObject object1;
	func2(object1);
	func2(CObject("pobject", 1));
	//cout << "--------------------------------" << endl;
	
	/*
	void func3(CObject* rhs)
	{
		rhs.mnum = 10;
	}
	*/
	//CObject object1;
	//func3(&object1);
	func3(&CObject("pobject", 1));
	return 0;
}

int main()
{
	CObject* pobject = new CObject("pobject",1);
	CObject object("object", 1);
	//生成一个临时对象
	//显示生成
	CObject("pobject", 1);
	return 0;
}

CObject gobject1("gobject1",20);
static CObject gobject3("gobject3", 20);
int main()
{	
	cout << "-----------------------------" << endl;
	static CObject gobject4("gobject4", 20);//.data

	CObject* pobject = new CObject("pobject", 30);
	CObject object1;
	CObject object2("object2",2); 

	return 0;
}

CObject gobject2("gobject2",10);
#endif