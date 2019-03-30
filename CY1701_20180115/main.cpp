#include<iostream>
#include<string>
using namespace std;

class A
{
public:
	int ma;
};
class B : public A
{
public:
	int mb;
};
class C : public A
{
public:
	int mc;
};
class D : public B, public C
{
public:
	int md;
};
int main()
{
	D d;
	d.C::ma;
	return 0;
}
#if 0
class Base
{
public:
	Base(int data = 0) :ma(data)
	{
		cout << "Base::Base()" << endl;
	}
	virtual ~Base()
	{
		
		cout << "Base::~Base()" << endl;
	}
	virtual void Show()
	{
		cout << "Base::Show()" << endl;
	}
	void Show(int data)
	{
		cout << "Base::Show(int)" << endl;
	}
private:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) : mb(data)
	{
		cout << "Derive::Derive()" << endl;
	}
	~Derive()
	{
		cout << "Derive::~Derive()" << endl;
	}
private:
	void Show()
	{
		cout << "Derive::Show()" << endl;
	}
private:
	int mb;
};
int main()
{
	Base* p = new Derive(10);
	p->Show();
	/*
		call eax //�����ڼ� �����޶���������  ����
		eax ����
	*/
	delete p;
	return 0;
}
class Brid
{
public:
	Brid(string name) :mname(name){ cout << "Brid::Brid()" << endl; }
	virtual void fly(int height) = 0;
	~Brid()
	{
		cout << "Brid::~Brid()" << endl;
	}
protected:
	string mname;
};
class Penguin : public Brid
{
public:
	Penguin(string name):Brid(name)
	{
		cout << "Penguin::Penguin()" << endl;
	}
	void fly(int height)
	{
		cout << mname << "can not fly" << endl;
	}
};
class Eagle : public Brid
{
public:
	Eagle(string name) : Brid(name)
	{
		cout << "Eagle::Eagle()" << endl;
	}
	void fly(int height)
	{
		cout << mname << "can fly" << height<<"m"<<endl;
	}
};

void ShowFly(Brid* brid)
{
	/*if (typeid(*brid) == typeid(Penguin))
	{
		cout << "can not fly" << endl;
		cout << "fly 0m" << endl;
	}
	else
	{
		brid->fly(10);
	}*/
	/*
		brid ���ʵ����ָ���vftable�е�RTTI�ʹ��������ʵ�ν��бȽ�
		�����ͬת��
		��ͬ  ת��  NULL
	*/
	Penguin* pen = dynamic_cast<Penguin*>(brid);
	if (pen == NULL)
	{
		brid->fly(10);
	}
	else
	{
		cout << "can not fly" << endl;
		cout << "fly 0m" << endl;
	}

}
int main()
{
	Penguin* pen = new Penguin("Penguin");
	Eagle* eagle = new Eagle("Eagle");
	ShowFly(pen);
	ShowFly(eagle);
	return 0;
}
/*
	���ڴ��麯������ ���� ������
	�������ܲ���ʵ����һ������
		����  ֻ����ָ���������
*/
class Animal
{
public:
	Animal(string name = "") :mname(name){}
	virtual void bark() = 0;//���麯��
protected:
	string mname;
};
class Dog : public Animal
{
public:
	Dog(string name) :Animal(name){}
	void bark()
	{
		cout << mname <<":WANG WANG WANG!" << endl;
	} 
};
class Cat : public Animal
{
public:
	Cat(string name) :Animal(name){}
	void bark()
	{
		cout << mname << ":MIAO MIAO MIAO!" << endl;
	}
}; 

/*
	ͨ������Ķ���
	��ӡ����Ľ���
*/
void PrintBark(Animal* animal)
{
	animal->bark();
} 
int main()
{
	Dog* dog = new Dog("dog");
	Cat* cat = new Cat("cat");
	/*                             vftable
		vfptr          vfptr       class Cat
		mname          mname           0
		                           bark();
	*/
/*	int *p1 = (int*)dog;
	int *p2 = (int*)cat;
	int tmp = p1[0];
	p1[0] = p2[0];
	p2[0] = tmp;*/ 

	dog->bark();//��̬
	cat->bark();//��̬ 

	cout << "dog::" << typeid(*dog).name() << endl;
	cout << "cat::" << typeid(*cat).name() << endl;

	PrintBark(dog);
	PrintBark(cat);
	delete dog;
	delete cat;
	return 0;
}
#endif
#if 0
class Base
{
public:
	Base(int data = 0) :ma(data)
	{
		cout << "Base::Base()" << endl;
		Show(); //��̬�󶨣���̬�İ�
		//clear();//vfptr = 0x00000000

	} 
	void clear()
	{
		memcpy(this,0,sizeof(*this));
	}
	virtual ~Base()
	{
		Show();//��̬��
		cout << "Base::~Base()" << endl;
	}
	void Show()
	{
		cout << "Base::Show()" << endl;
	}
	void Show(int data)
	{
		cout << "Base::Show(int)" << endl;
		//����������
		this->Show();
	}
private:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) : mb(data)
	{
		cout << "Derive::Derive()" << endl;
	}
	~Derive()
	{
		cout << "Derive::~Derive()" << endl;
	}
	virtual void Show()
	{
		cout << "Derive::Show()" << endl;
	}
	//virtual void Show(int data)
	//{
	//	cout << "Derive::Show(int)" << endl;
	//}
private:
	int mb;
};
/*
	������û���κε��麯��
	����������һ��Show�������麯��

	�����ָ��ָ���������ڴ�
	�������ڴ��ڶ��ڴ��Ͽ���   ������������������
*/
int main()
{
	Base* pb = new Derive(10);
	/*
		vfptr    new     0x100   0x100  12
		Base::  
		  ma     delete  0x104 
		mb

		Base::
			vfptr
			ma
		mb
	*/
	delete pb;
	return 0;
} 
#endif
#if 0
/*
	��������һ��Show���麯��  
	���ڴ���ʵ������һ��������Ķ���
*/
int main()
{
	Base* pb = new Derive(10);
	pb->Show();
	delete pb;// 
	//pb->~Base();
	/*
		call eax ==�� ~Derive();
		call ~Base();
		/*
			��������  �̳���������˵  ����൱��һ�������ͬ������
	*/
	return 0;
}

int main()
{
	Base *p = new Base(10);
	p->Show(10);//
	delete p;
	return 0;
}

/*
	��������ʱ��
*/
int main()
{
	//Base* p = new Base(10);
	//p->Show();//0x0

	//Derive* pd = new Derive(10);
	//pd->Show();
	return 0;
}
#endif
/*
	1.������������ж�û�麯��
		1.��������ڴ沼��
		2.Show()ͬ���ĺ�����ϵ
			overload  ����
				1.��ͬ������
			overhide  ���� ͬ������
			override  ���� ͬ�����Ҳ����б�Ҳ��ͬ
		3.Show�ĵ���ʱһ����̬�İ�
	Base::
		ma
	mb
	��̬�İ�   
	2.���������麯��   ��������û���麯��
		1.
		Base::       RTTI class Derive    
			vfptr        0
			ma       &Derive
		vfptr
		mb 
		2.
		3.
	3.������û���麯��  �����������麯��
		1.
		    vfptr
			Base::
			  ma
			mb
		2.����
		3.
*/
#if 0
int main()
{
	/*
		���������麯��   ������Ҳ�д���һ��������û�е��麯��
		&Base::Show      &Derive::Show
		                 &Derive::Show_int
	*/
	Base* pb = new Derive();
	pb->Show();
	/*
		�����麯��
		call Base::Show
	*/
	/*
		�﷨���� Show
		Show ==> virtual  call  eax
	*/
	Derive *pd = new Derive();
	pd->Show();
	return 0;
}
#endif