#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
//�������  C
//C��struct
//
/*
������� OOP
��Զ���˼�������������
��װ  �̳�  ��̬������̬ ����̬��
��װ
��װ������
�����޶���
 1.public:  ����λ�ö��ܷ���
 2.protected: �̳����� ������Է��ʸ���ı�����Ա
 3.private: ֻ�������в��ܷ��� 
this:CGoods* const this
ϵͳ�����ĺ�����
1.���õ�
2.������
1.���캯������������
���캯����
��ʼ��������ڴ��ַ�ռ�
����������
�ͷŶ�����ڴ�ռ���ռ��Դ
ʵ����һ������
1.��������ڴ�ռ�
2.���ö���Ĺ��캯��
û��ʵ�ֹ��캯��
ϵͳ�����Ĭ�ϵĹ��캯��
�Լ������캯�� ϵͳ�Ͳ����ṩĬ�ϵĹ��캯��
ʵ����һ�����������Ķ���
���治������
2.�������캯��
��һ���Ѿ����ڵĶ����ʼ����ͬ�����¶���
���õĿ������캯��
���봫����
��ֹʵ�κ��βεݹ鹹��
ϵͳ�ṩ�Ŀ������캯��   ǳ����
����ͷ�ͬһ��Դ
3.��ֵ��������غ���
//void operator=() //���������
���Ѵ��ڵĶ������һ���Ѵ��ڵĶ���ֵ
ϵͳ�ṩ�ĸ�ֵ��������غ��� ǳ����
����ͷ�ͬһ��Դ
�ڴ�й©
1.��ֹ�Ը�ֵ
2.�ͷž���Դ
3.��������Դ���г�ʼ��

˼��
CStack�������
Ϊʲô������MAXSIZE�����λ��֮ǰ  ����MAXSIZE
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
	//�ں������ʱ  �������ⷵ�س�Ա������ָ���������
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
	CGoods good1;//ϵͳ������Ĭ�ϵĹ��캯��
	CGoods good2("good2",20,25.6);
	good2.Show();
	CGoods good3 = good2;//�������캯��
	good3 = good2;//��ֵ����������غ���
    //
	/*
		��ʼ���������ͬʱ��ֵ
		��ֵ��  ������ڸ�ֵ
	*/

	return 0;
}
//
//struct Node1
//{	
//};

//���ж���
//��������ʱ ��inline��������
//���ⶨ��
//��������ʱ����ͨ����һ��
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
	//�ں������ʱ  �������ⷵ�س�Ա������ָ���������
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