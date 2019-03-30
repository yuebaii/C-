#include<iostream>
using namespace std;
const int MEM_POOL_SIZE = 10;
template<typename T> //int  double 
class CMemPool
{
public:
	void* alloc(size_t size);
	void del(void* ptr);
	static CMemPool& getIntance()
	{
		return single;
	}
private:
	CMemPool(){}
	CMemPool(const CMemPool<T>& rhs){}
	class Node
	{
	public:
		char p[sizeof(T)]; //对象要使用
		Node* pnext;      //管理内存池静态链表的指针
	};
	static Node* pool;//?

	static CMemPool<T> single;
};
template<typename T>
CMemPool<T> CMemPool<T>::single;

template<typename T>
typename CMemPool<T>::Node* CMemPool<T>::pool = NULL;
template<typename T>
void* CMemPool<T>::alloc(size_t size)
{
	if (pool == NULL)
	{
		int allocsize = (size + 4)*MEM_POOL_SIZE;
		pool = (Node*)new char[allocsize];
		Node* pCur = pool;
		for (pCur; pCur < pool + MEM_POOL_SIZE - 1; ++pCur)
		{
			pCur->pnext = pCur + 1;
		}
		pCur->pnext = NULL;
	}
	Node* rt = pool;
	pool = pool->pnext;
	return rt;
}
template<typename T>
void CMemPool<T>::del(void* ptr)
{
	if (ptr == NULL)
		return;
	Node* deleteptr = (Node*)ptr;
	deleteptr->pnext = pool;
	pool = deleteptr;
}
class CStu
{
public:
	CStu(int id = 0, int age = 18, float score = 0.0f)
		:mid(id), mage(age), mscore(score){}
	void* operator new(size_t size)
	{
		return mpool->alloc(size);
	}
	void operator delete(void* ptr)
	{
		mpool->del(ptr);
	}
private:
	int mid;
	int mage;
	float mscore;
	static CMemPool<CStu> *mpool;
};
CMemPool<CStu>* CStu::mpool = &CMemPool<CStu>::getIntance();
int main()
{
	CStu* st1 = new CStu(10);
	CStu* st2 = new CStu(10);
	CStu* st3 = new CStu(10);
	CStu* st4 = new CStu(10);
	CStu* st5 = new CStu(10);
	CStu* st6 = new CStu(10);
	return 0;
} 
#if 0
const int MEM_POOL_SIZE = 10;
template<typename T>
class Queue
{
public:
	Queue();
	~Queue();
	void push(T val);
	bool pop();
	T top();
	bool isEmpty();
	void Show();
private:
	class QueueItem
	{
	public:
		QueueItem(T val = T());
		T mdata;
		QueueItem* pnext;
		void* operator new(size_t size);
		void operator delete(void* ptr);
	};
	QueueItem* pfront;
	QueueItem* prear;
    static QueueItem* pool;
};
template<typename T>
typename Queue<T>::QueueItem* Queue<T>::pool = NULL;
template<typename T>
Queue<T>::QueueItem::QueueItem(T val = T()):
mdata(val), pnext(NULL)
{}
template<typename T>
void* Queue<T>::QueueItem::operator new(size_t size)
{
	/*  内存池中内存的管理   静态链表
	*/
	if (pool == NULL)
	{
		int allocsize = size*MEM_POOL_SIZE;
		pool = (QueueItem*)new char[allocsize];
		QueueItem* pCur = pool;
		for (pCur; pCur < pool + MEM_POOL_SIZE - 1; ++pCur)
		{
			pCur->pnext = pCur + 1;
		}
		pCur->pnext = NULL;
	}
	QueueItem* rt = pool;
	pool = pool->pnext;
	return rt;
}
template<typename T>
void Queue<T>::QueueItem::operator delete(void* ptr)
{
	if (ptr == NULL)
		return;
	QueueItem* deleteptr = (QueueItem*)ptr;
	deleteptr->pnext = pool;
	pool = deleteptr;
}
template<typename T>
Queue<T>::Queue()
{
	pfront = prear = new QueueItem();
}
template<typename T>
Queue<T>::~Queue()
{
	QueueItem* pCur = pfront;
	while (pCur->pnext != prear)
	{
		pfront = pfront->pnext;
		delete pCur;
		pCur = pfront;
	}
	delete prear;
}
template<typename T>
void Queue<T>::push(T val)
{
	QueueItem* pNewNode = new QueueItem(val);
	prear->pnext = pNewNode;
	prear = pNewNode;//prear = prear->pnext;
} 
template<typename T>
bool Queue<T>::pop()
{
	bool rt = false;
	if (!isEmpty())
	{
		QueueItem* pDelete = pfront->pnext;
		pfront->pnext = pDelete->pnext;
		delete pDelete;
		rt = true;
	}
	return rt;
}

template<typename T>
T Queue<T>::top()
{
	if (isEmpty())
		throw exception("Queue is Empty");
	return pfront->pnext->mdata;
}
template<typename T>
bool Queue<T>::isEmpty()
{
	return pfront == prear;
}
template<typename T>
void Queue<T>::Show()
{
	QueueItem* pCur = pfront->pnext;;
	while (pCur != NULL)
	{
		cout << pCur->mdata << " ";
		pCur = pCur->pnext;
	}
	cout << endl;
}
int main()
{
	Queue<int> que1;
	que1.push(20);
	que1.push(19);
	que1.push(18);
	que1.push(17);
	que1.push(16);
	que1.push(15);
	que1.push(14);
	que1.Show();
	que1.pop();
	que1.Show();
	return 0;
}
void* operator new(size_t size)
{
	char* p = (char*)malloc(size);
	if (NULL == p)
		throw bad_alloc();
	return p;
	//return malloc(size);
} 
void operator delete(void* ptr)
{
	cout << "delete addr:" << ptr << endl;
	if (NULL == ptr)
		return;
	free(ptr); 
}
void* operator new[](size_t size)
{
	cout << "size" << size << endl;
	char* p = (char*)malloc(size);
	if (NULL == p)
		throw bad_alloc();
	return p;
}
void operator delete[](void* ptr)
{
	if (NULL == ptr)
		return;
	free(ptr);
}
int main()
{
	int *p = new int[10];
	cout << "new [] addr:" << p << endl;
	delete (p+1);
	return 0;
}
#endif