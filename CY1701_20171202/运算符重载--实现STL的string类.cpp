#include<iostream>
#include<string>
using namespace std;
/*
ģ��
 .����ģ��  .��ģ��
һ.����ģ��
1.����ģ��
2.ģ���ʵ����
3.ģ�庯��
4.ģ���ʵ������
5.ģ������Ͳ���
6.ģ��ķ����Ͳ���
7.ģ���������
8.ģ�������
9.ģ���Ĭ��ֵ
   ����ģ���Ĭ��ֵ
	C++11
   ��ģ���Ĭ��ֵ
    C++99
10.����ģ�巵��ֵ�ķ�ʽ
	auto
��.��ģ��
1.��ģ���ѡ����ʵ����
2.typename
3.��ģ���������
4.��ģ������ڲ��ֳ�Ա������������
5.��ģ��Ĳ�ͬʵ���¿�������͸�ֵ������
	CLink<double> link1;
	CLink<int> link2(link1);
	link1 = link2;
6.��ģ���ƫ�ػ�
7.����ָ���ģ��
*/
��������غ���
/*
	1.����������Ҫ��һ���Զ������� 
	2.�����������������߼���ͬ
	3.���ܸı�����������ȼ� 
	4.���ܴ�������� 
*/
#pragma warning(disable:4996)
class CString;
class CIterator
{
public:
	CIterator(CString * p = NULL, int index = 0) :
		mstr(p), mindex(index){}
	bool operator!=(const CIterator& rhs);
	void operator++();
	char& operator*();
private:
	CString* mstr;
	int mindex; 
};
class CString
{
public:
	typedef CIterator iterator;
	iterator begin();
	iterator end();
	CString();
	CString(char* rhs);
	~CString();
	CString operator=(const CString& rhs);
	//char* operator+(char* p);
	bool operator==(const CString& rhs);
	bool operator!=(const CString& rhs);
	char& operator[](int index);
private:
	char* mpstring;
	int cursize;
	friend CString operator+(const CString&,
		const CString&);
	friend ostream& operator<<(ostream& out, const CString& rhs);
	friend istream& operator>>(istream&,CString&);
};
/*
	lhs   left hand side
	rhs   right hand side
*/
CString::CString()
{
	mpstring = new char[1];
	cursize = 0;
}
CString::CString(char* rhs)
{
	mpstring = new char[strlen(rhs) + 1];
	strcpy(mpstring,rhs);
	cursize = strlen(rhs);
}
CString::~CString()
{
	delete mpstring;
	mpstring = NULL;
}
CString CString::operator = (const CString& rhs)
{
	cout << "operator=" << endl;
	if (this != &rhs)
	{
		delete mpstring;
		mpstring = new char[strlen(rhs.mpstring) + 1];
		strcpy(mpstring, rhs.mpstring);
		cursize = rhs.cursize;
	} 
	return *this;
}
//char* operator+(char* p);
bool CString::operator==(const CString& rhs)
{
	cout << "operator==" << endl;
	return strcmp(mpstring,rhs.mpstring) == 0;
}
bool CString::operator!=(const CString& rhs)
{
	cout << "operator!=" << endl;
	//return strcmp(mpstring, rhs.mpstring) != 0;
	return !(*this == rhs);
}
char& CString::operator[](int index)
{
	cout << "operator[]" << endl;
	return mpstring[index];
}
CString operator+(const CString& lhs,
	const CString& rhs)
{
	cout << "operator+" << endl;
	int lhslen = strlen(lhs.mpstring);
	int rhslen = strlen(rhs.mpstring);
	int len = lhslen + rhslen + 1;
	//char* str = new char[len];
	char str[20] = "";
	strcat(str, lhs.mpstring);
	strcat(str, rhs.mpstring);
	CString str1(str);
	return CString(str);
}
ostream& operator<<(ostream& out, const CString& rhs)
{
	cout << "operator<<" << endl;
	out << rhs.mpstring << " ";
	return out;
}
istream& operator>>(istream& in, CString& rhs)
{
	cout << "operator>>" << endl;
	char p[20];
	in >> p;
	if (in)
	{
		delete rhs.mpstring;//
		rhs.mpstring = new char[strlen(p)+1];
		strcpy(rhs.mpstring, p);
		rhs.cursize = strlen(p);
	} 
	return in;
}
CIterator CString::begin()
{
	return CIterator(this,0);
}
CIterator CString::end()
{
	return CIterator(this, cursize);
}
int main()
{
	string str("hello world");
	string::iterator it = str.begin();
	for (it; it != str.end(); ++it)
	{
		*it = 'a';
		cout << *it << " ";
	} 
	cout << endl;


	return 0;
}
#if 0
int main()
{
	//char *p= new char[100];
	//cout << &p << endl;
	//cout << p+1 << endl;
	//char *q = "ghjhk";
	//
	//strcat(p, q);
	//cout << &p << endl;
	//delete p;
	CString str1;
	CString str2("hello");
	CString str3 = str2 + "world";
	CString str4 = "hello" + str2;
	str3 = str4;
	//(str1.operator=(str2)).operator=(str3);
		/*
		:: sizeof ?�� ��. ->
		/* �����º��� [] + * new delete 
		str2.operator+("world");
		oprerator+(char* p);
	*/
	if (str2 == str3)
	{
		/*
			str2.operator==(const string&)
		*/
		cout << str2 << endl;
		/*
			operator<<(ostream& out,const string&);
		*/
	}
	if (str1 == str3)
	{
		cout << str3[0] << endl;
		/*
			str3.operator[](int index);
			operator[](int)
		*/
	}
	//str1[0] = 'f';
	//cin >> str1;
	//cout << str1 << endl;
	return 0;
}
#endif