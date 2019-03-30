#include<iostream>
using namespace std;
#pragma warning(disable:4996);
class String
{
public:
	String(char* ptr = NULL)
		:mptr(new char[strlen(ptr) + 5])
	{
		mptr += 4;
		strcpy(mptr, ptr);
		getRefCount(mptr) = 1;
	}
	String(const String& rhs)
		:mptr(rhs.mptr)
	{
		++getRefCount(mptr);
	}
	String& operator=(const String& rhs)
	{
		if (this != &rhs)//浅拷贝
		{
			Release();
			mptr = rhs.mptr;
			++getRefCount(mptr);
		}
		return *this;
	}
	char& operator[](int index)
	{
		if (getRefCount(mptr) > 1)//深拷贝
		{
			char* ptr = mptr;
			--getRefCount(ptr);
			mptr = new char[strlen(ptr) + 5];
			mptr += 4;
			getRefCount(mptr) = 1;
			strcpy(mptr, ptr);
		}
		return mptr[index];
	}
	~String()
	{
		Release();
	}
private:
	void Release()
	{
		if (--getRefCount(mptr) == 0)
		{
			delete[] (mptr - 4);
		}
	}
	int& getRefCount(char* ptr)
	{
		return *(int*)(ptr - 4);
	}
	char* mptr;
};
int main()
{
	String str1("hello");
	String str2(str1);

	String str3("world");
	str3 = str1;
	str1[0] = 's';
	return 0;
}