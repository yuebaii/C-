#include<iostream>
using namespace std;

/*
�������������
	��ʾ����һ����ʱ����
�β�  ����ֵ
*/
/*
ǳ������
ʵ���Լ��Ĺ��죬�������������죬��ֵ�����������
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
	��ʱ�����������ͣ�
	   1.�������ͣ���������ʱ��  ����
	   2.�����ͣ���������ʱ��   ����
	      1.��ʽ��������ʱ��  Ҳ�ǳ���
	��ֵ����������غ�����
	   1.�����ββ��ܸı�
	   2.������ʽ��������ʱ��
*/
/*
explicit  ֻ�����ι��캯�� 
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
	//  ��ʱ�����������ڣ�
	//    ���ʽ��
	//*/
	//object1 = CObject("object1", 2);
	//cout << "--------------------------------" << endl;

	//CObject object1;
	//CObject object2("object2", 2);
	////�������Ż�
	//CObject object3 = CObject("object3", 2);
	//cout << "--------------------------------" << endl;
	///*
	//	��ʱ�������ã�
	//	  ��ʱ�������� ���� object3
	//	�Ż���
	//	  �Թ�����ʱ���ķ�ʽ  ���� object3	
	//*/ 

	//���ű��ʽ
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
	//// ��ʽ������ʱ����
	//object1 = 2;
	//cout << "---------------------------------" << endl;

	//cout << "---------------------------------" << endl;
	////        const CObject&
	//// ��ʽ������ʱ����
	//CObject object2  = 2; 
	//cout << "---------------------------------" << endl;

	//cout << "---------------------------------1" << endl;
	//CObject* pobject = &CObject("pobject", 1);
	//cout << "---------------------------------" << endl;
	//cout << "---------------------------------2" << endl;
	//CObject& pobject = CObject("pobject", 1);
	//cout << "---------------------------------" << endl;
	///*
	//	����һ����ʱ����
	//	��ʱ������������ھͱ����������������������
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
	//����һ����ʱ����
	//��ʾ����
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