#include<iostream>
using namespace std;
/*
1.模板参数的默认值
2.模板接收返回值  auto
3.两种特例化
4.模板函数名字 
5.类模板
	1.类外定义模板成员方法
	2.友元
	3.类模板的选择性实例化
	4.typename这个关键字
	5.类模板的完全特例化
	6.类模板的部分特例化
*/
template<>
class CLink<char*>
{
public:
	CLink()
	{
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
	Node* CLinkQuery(T val)
	{
		
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
class CLink
{
public:
	CLink()
	{
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
	template<typename T>
	void InsertHead(T val)
	{
		Node* pNewNode = new Node(val);
		pNewNode->pnext = phead->pnext;
		phead->pnext = pNewNode;
	} 
	template<>
	void InsertHead(char* val)
	{
		Node* pNewNode = new Node(val);
		pNewNode->pnext = phead->pnext;
		phead->pnext = pNewNode;
	}

	class Node;
	Node* CLinkQuery(T val);
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
	cout << mdata << " ";
}
int main()
{
	CLink<int> link1;
	CLink<double> link2;
	CLink<char*> link3;

	return 0;
}

#if 0
int main()
{
	CLink<int> link1;
	for (int i = 0; i < 10; ++i)
	{
		link1.InsertHead(i + 1);
	}
	link1.Show();
	link1.CLinkQuery(11)->Show();

	return 0;
}

/*
构造函数和析构函数可以不加类型参数列表

友元关系

组合关系 have_a  a part of
继承关系 is_a    a kind of

class Date
class Stu
{
private:
Date mdate;
}

嵌套类：
class 
{
class 
} 

*/
/*
前置声明
*/
template<typename T>
class CLink;

template<typename T>
class Node
{ 
public:
	Node(T val = T()):mdata(val),pnext(NULL){}
	~Node(){}
private:
	T mdata;
	Node<T> *pnext;
	//template<typename E>
	//friend class CLink;
	friend class CLink<T>;
	/*
		CLink<int>
		Node<double>
	
	*/
};
template<typename T>
class CLink
{
public:
	CLink()
	{
		phead = new Node<T>();
	}
	~CLink()
	{
		Node<T>* pCur = phead;
		Node<T>* pNext = pCur;
		while (pCur->pnext != NULL)
		{
			pNext = pCur->pnext;
			delete pCur;
			pCur = pNext;
		}
		delete pCur;
		phead = NULL;
	}
	void InsertHead(T val);
	void InsertTail(T val);
	void Show()
	{
		Node<T>* pCur = phead->pnext;
		while (pCur != NULL)
		{
			cout << pCur->mdata << " ";
			pCur = pCur->pnext;
		}
		cout << endl;
	}
	Node<T>* LinkQuery(T val);
private:
	Node<T>* phead;
};
template<typename T>
void CLink<T>::InsertHead(T val)
{
	Node<T>* pNewNode = new Node<T>(val);
	pNewNode->pnext = phead->pnext;
	phead->pnext = pNewNode;
}
template<typename E>
void CLink<E>::InsertTail(E val)
{
	Node<T>* pCur = phead;
	while (pCur->pnext != NULL)
	{
		pCur = pCur->pnext;
	}
	Node<T>* pNewNode = new Node<T>(val);
	pCur->pnext = pNewNode;
}

//template<typename T>
//Node<T>* CLink<T>::LinkQuery(T val);
/*
类模板的选择性实例化
	类模板类成员方法只有在调用时才进行实例化
*/
int main()
{
	CLink<int> link1;
	for (int i = 0; i < 10; ++i)
	{
		link1.InsertHead(i + 1);
	}
	link1.Show();
	//link1.LinkQuery(10);
	return 0;
}

/*
double float  类类型
*/
template<typename T = char,typename E = int, int SIZE = 30>
T Max(E a, E b)
{
	return a > b ? a : b;
} 
/*
double Max(int a, int b)
{
	return a > b ? a : b; 
}
*/
int main()
{
	auto a = Max(10, 30);
	return 0;
}


template<typename T>
bool compare(const T a, const T b)
{
	cout << "compare<T>" << endl;
	return a > b;
} 
template<>
bool compare<int>(int a, int b)
{
	cout << "compare<int>" << endl;
	return a > b;
}

bool compare(int a, int b)
{
	cout << "compare" << endl;
	return a > b;
}
/*
bool compare(double a, double b)
{
	return a > b;
}
*/

int main()
{
	compare(10, 20);
	compare<>(10, 20);
	return 0;
}
#endif