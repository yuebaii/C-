#include<iostream>
#include<typeinfo>
using namespace std; //using ָʾ��

/*
���ֿռ�������
��������
*/

namespace MyName
{
	int gdata = 11;
	int sum()
	{
		return 10;
	}
}
namespace MyName
{
	int gdata1 = 11;
}
int gdata = 12;
int main()
{
	using namespace MyName;
	using std::cout;
	using std::endl;

	int gdata = 10;
	int data = sum();
	cout << data << endl;
	return 0;
}


#if 0
// new delete  
// malloc free()
// ��λ new ?



int main()
{
	int*pc = (int*)malloc(sizeof(int));
	cout << *pc << endl;
	free(pc);

	//�أ����ȷ������һ����Դ
	// �û�̬  -��  �ں�̬
	// malloc (4096) 
	// malloc brk  mmap()
	int *pcpp = new int(50);	
	/*
	1.���ٿռ�
	2.��ʼ�� ���� ���ù��캯��
	*/
	cout << *pcpp << endl;
	delete pcpp;

	int *pc1 = (int *)malloc(sizeof(int)* 10);
	free(pc1);

	int *pcpp1 = new int[100]();
	delete []pcpp1;
	
	int **p = (int **)malloc(sizeof(int*)*3);
	for (int i = 0; i < 3; ++i)
	{
		p[i] = (int *)malloc(sizeof(int)*4);
	}
	
	int **pcpp2 = new int*[3];
	for (int i = 0; i < 3; ++i)
	{
		pcpp2[i] = new int[4];
	}
	for (int i = 0; i < 3; ++i)
	{
		delete[] pcpp2[i];
	}
	delete[] pcpp2;

	if (pc == NULL)
	{
		exit(0);
	}
	//���������

	int *pcpp3 = new int(); // bad_alloc()

	delete pcpp3;

	const int *pcpp4 = new const int();
	//const int *pcpp5 = new const int[100]();

	return 0;
}
/*
const �� һ��ָ��Ľ��

const �� ���������õĽ��
��ͨ����  ����  ��ͨ����
��ͨ����  ����  ����   ����
��ͨ����  ����  ������ ����
������    ����  ��ͨ����/����
������    ����  ������  
 һ��ָ��ָ�������

const �� ����ָ��Ľ��

const �� �β��б�Ľ��

const �� ����ֵ ָ��  ���õĽ��

const 

Ȩ�ޱ�С û������
int * ==> const int*
Ȩ�ޱ��   ������
const int* ==> int*

int ** ==>const int **
*/
/*
<= 4 eax
>4 <=8 eax ecx
>8  push
*/
//���ܷ��ؾֲ�������ָ�������
int& sum()
{
	static int temp = 10; //.data
	return temp;
}
int main()
{
	int &a = sum();//

	//int &b = sum();//eax int* const a = 10


	//int *const&p = sum();
	//int *const*p = &sum();
	//int &b = *sum(); // temp
	// int *&b = sum();
	// int * temp = 0x00FF1844
	//int *const &b = temp;
	//const int *p = &sum();//&10;
	//int b = *sum();
	return 0;
}


void func(const int* a)
{
	cout << typeid(a).name() << endl;
}
void func(int* const a)
{
	cout << typeid(a).name() << endl;
}
void func(int* a)
{
	cout << typeid(a).name() << endl;
}
//
int main()
{
	int a = 10;
	func(&a);
	return 0;
}

int main()
{
	int a = 10;
	//a = 11;
	const int *p = &a;
	//*p = 100;
	const int **q = &p;
	//��Ӳ���  �з��� �������
	//ֱ�Ӳ���
	return 0;
}

int main()
{
	//const int a = 10; 
	//const int *const p = &a; // ebp - 8

	//const int a = 10;
	//int const &b = a;
	//cout << typeid(b).name() << endl;

	//const int &b = 10;
	//cout << &b << endl;
	
	//int a = 10;
	//const int &b = a;// (*b)
	////const int * const p = &a;

	//const int a = 10;
	//const int *const p = &a;
	//const int *const &q = p;
	//int **q = &p;
	return 0;
}
#endif