#include<vector>
#include<list>
#include<functional>
#include<algorithm>
#include<iostream>
using namespace std;

template<typename Container>
void Show(Container& con)
{
	Container::iterator it = con.begin();
	for (it; it != con.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
template<typename Iterator>
void MySort(Iterator first, Iterator second)
{
	int count = 0;
	Iterator i = first;
	Iterator j = first;
	Iterator last = second;
	//Iterator end = second;
	for (i; i < last - 1; ++i,++count)
	{
		for (j = first; j < last - count - 1; ++j)
		{
			if (*j > *(j + 1))
			{
				Iterator::value_type tmp = *j;
				*j = *(j + 1);
				*(j + 1) = tmp;
			}
		}
	}
}
template<typename T>
class Greater
{
public:
	bool operator()(const T& lhs, const T& rhs)
	{
		return lhs < rhs;
	}
};
template<typename T>
class Less
{
public:
	bool operator()(const T& lhs, const T& rhs)
	{
		return lhs > rhs;
	}
};
template<typename Iterator,typename Compare>
void MySort(Iterator first, Iterator second,Compare& com)
{
	int count = 0;
	Iterator i = first;
	Iterator j = first;
	Iterator last = second;
	//Iterator end = second;
	for (i; i < last - 1; ++i, ++count)
	{
		for (j = first; j < last - count - 1; ++j)
		{
			if (com(*j,*(j+1)))
			{
				Iterator::value_type tmp = *j;
				*j = *(j + 1);
				*(j + 1) = tmp;
			}
		}
	}
}
int main()
{
	int arr[] = { 2, 16, 3, 3, 33, 4, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> vec(arr, arr+len);
	/*
		排序时的函数对象
			1.less 升序
			2.greater 降序

		1.迭代器失效   
		2.back_insert_iterator
	*/
	list<int> list1(arr,arr + len);
	//MySort(vec.begin(), vec.end());
	sort(list1.begin(), list1.end(), Less<int>());
	//sort(vec.begin(), vec.end());
	Show(vec);
	return 0; 
}
#if 0
/*
	泛型算法  =  模板  +  迭代器  +  函数对象 
*/
template<typename Container>
void Show(Container& con)
{
	Container::iterator it = con.begin();
	for (it; it != con.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
/*
	void Show(vector<int>& con)
*/
template<typename Iterator, typename ValueType>
Iterator MyFind(Iterator first,
	Iterator second,
	const ValueType& val)
{
	for (first; first != second; ++first)
	{
		if (*first == val)
		{
			return first;
		}
	}  
	return second;
}

/*
函数对象  仿函数
*/
template<typename T>
class Comp
{
public:
	Comp(T data) :mval(data){}
	bool operator()(const T& rhs)
	{
		return mval > rhs;
	} 
private:
	T mval;
};
template<typename T>
class Comp1
{
public:
	Comp1(T data) :mval(data){}
	bool operator()(const T& rhs)
	{
		return mval < rhs;
	}
private:
	T mval;
};


template<typename Iterator,typename Compare>
Iterator MyFind2(Iterator first, Iterator second,
				Compare& com)
{
	for (first; first != second; ++first)
	{
		/*
			com.operator()(*first)
		*/
		if (  com(*first)    )
		{
			return first;
		}
	}
	return second;
}


int main()
{
	vector<int>  vec1;
	vector<int>  vec2(10);
	Show(vec2);

	vector<int>  vec3(10, 20);
	Show(vec3);

	int arr[] = { 15, 313, 3, 13, 1, 3, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> vec4(arr,arr + len);

	vector<int>::iterator it = vec4.begin();
	for (it; it != vec4.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "---------------------" << endl;

	vector<int>::reverse_iterator rit = vec4.rbegin();
	for (rit; rit != vec4.rend(); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;
	cout << "---------------------" << endl;

	vector<int>::iterator ret = MyFind(vec4.begin(), vec4.end(), 500);
	if (ret != vec4.end())
	{
		cout << *ret << endl;
	} 
	vector<int>::iterator ret1 = MyFind2(vec4.begin(), vec4.end(), Comp1<int>(10));
	if (ret1 != vec4.end())
	{
		cout << *ret1 << endl;
	}
	//vector<int> vec;
	//if (vec.empty())
	//{
	//	cout << "vec is Empty!" << endl;
	//}
	//cout << vec.size() << endl;
	//cout << vec.max_size() << endl;
	//return 0;
}
#endif