#include<iostream>
using namespace std;


/*
1.�̳�   ���븴��
2.���ֲ�ͬ��ʽ�ļ̳й�ϵ
              ������
public        
protected 
private
3.�̳й�ϵ�µĹ���˳��
4.ͬ������
	1.��������
		1.������
		2.��������  �ββ�ͬ
	2.����
		1.��ͬ����
	3.����
		1.��ͬ������
5.��������ת���ķ�ʽ
static_cast
const_cast
reinterpret_cast
dynamic_cast   RTTI

6.��������������ָͬ���������

�������ָ��ָ�����Ķ���   N
�����ָ��ָ��������Ķ���   Y
�������������������Ķ���   Y
��������������û���Ķ���   N
*/
/*
������  
  ָ����ڴ��ϵĶ���
  delete�ᵼ�����������������û�취���� �Ӷ�������Դû�취�ͷ�  
*/

/*
	���麯��
	animal  �У� void bark()=0; 
	���д��麯�����ࣺ������  ������������  ָ���������
	class dog   void bark(){}

	Dog dog;
	Cat cat;

	int* p1 = (int*)&dog;
	int* p2 = (int*)&cat;
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;


*/
class Base
{
public:
	Base(int  data = 0) :ma(data)
	{
		cout << "Base()" << endl;
	}
	void Show()
	{
		cout << "Base::Show()" << endl;
	} 
	void Show(int data)
	{
		cout << "Base::Show(int)" << endl;
	}
	void* operator new(size_t size)
	{
		int *p = (int*)malloc(size);
		cout <<"new::"<< p << endl;
		if (p == NULL)
		{
			throw bad_alloc();
		}
		return p;
	}
	void operator delete(void* ptr)
	{
		cout << "delete::"<<ptr << endl;
		free(ptr);
	}
	~Base()
	{
		cout << "~Base()" << endl;
	}
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int  data) :mb(data), Base(data)
	{
		cout << "Derive()" << endl;
	}
	virtual void Show()//��������Ϊ�������Ҳ���麯��
	{
		cout << "Derive::Show()" << endl;
	}
	~Derive()
	{
		cout << "~Derive()" << endl;
	} 
private:
	int mb;
};
int main()
{

	Base *p = new Derive(10);
	/*
		vfptr
		Base::
		  ma
		mb
	*/
	p->Show();

	//p = (Base*)((int)p - 4);
	delete p;
	//(*p).~Base();
	/*
		void free(void *ptr);
	*/
	return 0;
}
#if 0
/*
�麯��
1.��ȡ��ַ
2.����

���캯�� ����
�������� ����
inline���� ����
static���� ����
*/
/*
	1.ʲôʱ����������ʱ��̬�ı�����ߵ���
		ָ��ָ���������ʱ�������麯��
*/

int main()
{
	Base b(10);
	Derive d(20);
	
	b.Show();
	d.Show(); 

	Base *p1 = &b;
	p1->Show();

	Base *p2 = &d;
	p2->Show();

	Derive *p3 = &d;
	p3->Show();

	return 0;
}
int main()
{
	Derive d(10);
	Base* p = &d;
	p->Show();
	/*
	Base  ����׶�  ��̬�İ� ��� ��̬�Ķ�̬ call  Base::Show
		��������  ģ��  
	*/
	/*
		����ʱ==>��̬�İ�  ���     ����ʱ�Ķ�̬
		call  eax
		�̳У��麯�� 
	*/
	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << typeid(p).name() << endl;//class Base*
	cout << typeid(*p).name() << endl;//class Base
	return 0;
}
int main()
{
	Base b(10);
	Derive d(10);

	//Derive* p1 = &b; //??  �������ָ��  û�취ָ�����Ķ���
	//Base* p2 = &d;//�����ָ��  ָ��������Ķ���  

	//Derive &b1 = b;//�����������  û�취���û������
	Base &d1 = d;//��������ÿ�������������Ķ���
	return 0;
}
#endif