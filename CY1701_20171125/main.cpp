#include<iostream>
#include<vector>
using namespace std;

/*
类模板的完全特例化
类模板的部分特例化
类模板实现一个容器
友元关系
	类中：
		拷贝构造函数和赋值运算符重载函数
		要求是相同的类型
类模板的的模板类型参数

*/
#pragma warning(disable:4996)
template<typename T = int,int SIZE = 20>
class MyVector
{
public:
	MyVector() :cursize(0), totalsize(SIZE)
	{
		cout << "MyVector()" << endl;
		arr = new T[SIZE];
	}
	//void push_front(T val);
	//insert(iterator,val)
	template<typename T,int SIZE = 20>
	friend class MyVector;
	/*
		MyVector<int> MyVector<double>
	*/
	/*
		MyVector<double>  <= MyVector<int>
	*/
	template<typename E>
	/*explicit*/ MyVector(const MyVector<E>& rhs)
	{
		cout << "MyVector<T>(MyVector<E>)" << endl;
		arr = new T[rhs.totalsize];
		for (int i = 0; i < rhs.cursize; ++i)
		{
			arr[i] = rhs.arr[i];
		}
		cursize = rhs.cursize;
		totalsize = rhs.totalsize;
	}
	void operator=(const MyVector<T>& rhs)
	{
		cout << "void operator=(<T>)" << endl;
		if (this == &rhs)
		{
			return;
		}
		delete[]arr;
		arr = new T[rhs.totalsize];
		for (int i = 0; i < rhs.cursize; ++i)
		{
			arr[i] = rhs.arr[i];
		}
		totalsize = rhs.totalsize;
		cursize = rhs.cursize;
	}
	void resize()	
	{
		T* newArr = new T[totalsize + SIZE];
		for (int i = 0; i < totalsize; ++i)
		{
			newArr[i] = arr[i];
		} 
		T* p = arr;
		arr = newArr;
		totalsize += SIZE;
		delete []p;
	}   
	void push_back(T val)
	{
		if (cursize == totalsize)
		{
			resize();
		}
		arr[cursize++] = val;
	}
	//void pop_front();	
	void pop_back()
	{
		if (!empty())
		{
			cursize--;
		}
	}
	int max_size(){ return totalsize; }
	int size(){ return cursize; }
	bool empty()
	{
		return cursize == 0;
	}
	void show()
	{
		for (int i = 0; i < cursize; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	~MyVector()
	{
		cout << "~MyVector()" << endl;
		delete[] arr;
		arr = NULL;
	}
private:
	T *arr;

	int cursize;
	int totalsize;
};
/*
MyVector<int>
MyVector<double>
*/
int main()
{
	MyVector<int> vec1;
	MyVector<double> vec2;
	MyVector<double> vec3(vec1);
	/* 
		MyVector<double>*      MyVector<int>
		vec3.MyVector<double>(
		     MyVector<double>* const this,
			 MyVector<double>& rhs)
	*/
	//MyVector<double>   MyVector<int>
	/* void operator = (
			MyVector<double>* const this,
			MyVector<double>& rhs
	)
	*/
	cout << "---------------" << endl;
	vec2 = vec1;
	MyVector<double> vec4 = vec1;
	cout << "------------" << endl;;
	return 0;
}
#if 0
int main()
{
	MyVector<int> mvec;
	for (int i = 0; i < 100; ++i)
	{
		mvec.push_back(i + 1);
	}
	mvec.show();
	mvec.pop_back();
	mvec.show();
	return 0;
}


template<typename T>
class CLink
{
public:
	CLink()
	{
		cout << "CLink<T>()" << endl;
		phead = new Node();
	}
	~CLink()
	{
		Node* pCur = phead;
		Node* pNext = pCur;
		while (pCur->pnext != NULL)
		{
			pNext = pCur->pnext;
			delete pCur;
			pCur = pNext;
		}
		delete pCur;
		phead = NULL;
	}
	void InsertHead(T val)
	{
		Node* pNewNode = new Node(val);
		pNewNode->pnext = phead->pnext;
		phead->pnext = pNewNode;
	}
	class Node;

	Node* CLinkQuery(T val);

	template<typename T>
	Node* CLinkQuery(T val)
	{
		cout << "CLinkQuery<T>()" << endl;
		Node* pCur = phead->pnext;
		while (pCur != NULL)
		{
			if (pCur->mdata == val)
			{
				return pCur;
			}
			pCur = pCur->pnext;
		}
		return NULL;
	}
	template<>
	Node* CLinkQuery<char*>(char* val)
	{
		cout << "CLink<char*>()" << endl;
		Node* pCur = phead->pnext;
		while (pCur != NULL)
		{
			if (strcmp(pCur->mdata, val) == 0)
			{
				return pCur;
			}
			pCur = pCur->pnext;
		}
		return NULL;
	}
	void Show()
	{
		Node* pCur = phead->pnext;
		while (pCur != NULL)
		{
			pCur->Show();
			pCur = pCur->pnext;
		}
		cout << endl;
	}
private:
	class Node
	{
	public:
		Node(T val = T()) :mdata(val), pnext(NULL)
		{
		}
		T mdata;
		Node* pnext;
		void Show();
	};
	Node* phead;
};
template<typename T>
typename CLink<T>::Node* CLink<T>::CLinkQuery(T val)
{
	cout << "CLinkQuery()" << endl;
	Node* pCur = phead->pnext;
	while (pCur != NULL)
	{
		if (pCur->mdata == val)
		{
			return pCur;
		}
		pCur = pCur->pnext;
	}
	return NULL;
}
template<typename T>
void CLink<T>::Node::Show()
{
	cout << this->mdata << " ";
}
/*
template<typename T>
void Sum(T a, Tb)
{
 OPDJAJDLAKS
}
template<>
void Sum<int>(int a, int b)
{
	fshasjjkskjak
} 
*/
///////////////////////////////////////
/*
完全特例化
	小部分对于一些类型有逻辑上的错误
	完全特例化版本
		工作量太大
	   只需要处理这些小部分的代码
部分特例化
*/
//template<>
//class CLink<char*>
//{
//public:
//	CLink()
//	{
//		cout << "CLink<char*>()" << endl;
//		phead = new Node();
//	}
//	~CLink()
//	{
//		Node* pCur = phead;
//		Node* pNext = pCur;
//		while (pCur->pnext != NULL)
//		{
//			pNext = pCur->pnext;
//			delete pCur;
//			pCur = pNext;
//		}
//		delete pCur;
//		phead = NULL;
//	}
//	void InsertHead(char* val)
//	{
//		Node* pNewNode = new Node(val);
//		pNewNode->pnext = phead->pnext;
//		phead->pnext = pNewNode;
//	}
//	class Node;
//	Node* CLinkQuery(char* val);
//
//	
//	void Show()
//	{
//		Node* pCur = phead->pnext;
//		while (pCur != NULL)
//		{
//			pCur->Show();
//			pCur = pCur->pnext;
//		}
//		cout << endl;
//	}
//private:
//	class Node
//	{
//	public:
//		Node(char* val = "") :pnext(NULL)
//		{
//			mdata = new char[strlen(val) + 1];
//			strcpy(mdata, val);
//		}
//		~Node()
//		{
//			delete []mdata;
//		}
//		char* mdata;
//		Node* pnext;
//		void Show();
//		
//	};
//	Node* phead;
//};
//
//CLink<char*>::Node* CLink<char*>::CLinkQuery(char* val)
//{
//	Node* pCur = phead->pnext;
//	while (pCur != NULL)
//	{
//		if (strcmp(pCur->mdata,val) == 0)
//		{
//			return pCur;
//		}
//		pCur = pCur->pnext;
//	}
//	return NULL;
//}
//void CLink<char*>::Node::Show()
//{
//	cout << this->mdata << " ";
//}
///////////////////////////////////////
int main()
{
	//CLink<double> link1;
	//link1.InsertHead(10);
	//link1.InsertHead(11);
	//link1.CLinkQuery(10);
	CLink<char*> link2;
	char* p = "hello";
	link2.CLinkQuery<char*>(p);
	//char*  char*
	/*
		1.非模板函数
		2.特化版本
		3.实例化版本
	*/ 
	return 0;
}

int main()
{
	CLink<int> link;
	CLink<int>::Node *p = link.CLinkQuery(10);
	if (p != NULL)
	{
		(*p).Show();
	}
	/*
		NULL->Show();
		this = NULL;
		this->mdata;
		0000 0000 //Rerved
	
	*/
	return 0;
}
#endif