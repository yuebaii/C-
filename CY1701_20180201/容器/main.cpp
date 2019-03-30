#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<set>
#include<map>
#include<iterator>
#include<functional>
#include<algorithm>
using namespace std;

#pragma warning(disable:4996) 

template<typename Iterator, typename Compare>
void MySort(Iterator first, Iterator second, Compare& com)
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
			if (com(*j, *(j + 1)))
			{
				Iterator::value_type tmp = *j;
				*j = *(j + 1);
				*(j + 1) = tmp;
			}
		}
	}
}
template<typename Container>
void Show(Container& con)
{
	Container::const_iterator it = con.begin();
	for (it; it != con.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
template<typename Container>
class My_front_insert_iterator
{
public:
	My_front_insert_iterator(Container& con) :pcon(&con)
	{}
	My_front_insert_iterator<Container>& operator*()
	{
		return *this;
	}
	My_front_insert_iterator<Container>& operator=(
		const typename Container::value_type & val)
	{
		pcon->push_front(val);
		return *this;
	}
private:
	Container* pcon;
};
template<typename Container>
class My_back_insert_iterator
{
public:
	My_back_insert_iterator(Container &con) :pcon(&con)
	{}
	My_back_insert_iterator<Container>& operator*()
	{
		return *this;
	}
	My_back_insert_iterator<Container>& operator=(const typename Container::value_type &val)
	{
		pcon->push_back(val);
		return *this;
	}
private:
	Container* pcon;
};


template<typename Container>
class My_insert_iterator
{
public:
	My_insert_iterator(Container &con, typename Container::iterator& it) :pcon(&con), mit(it)
	{}
	My_insert_iterator<Container>& operator*()
	{
		return *this;
	}
	My_insert_iterator<Container>& operator=(const typename Container::value_type &val)
	{
		pcon->insert(mit,val);
		return *this;
	}
private:
	typename Container::iterator mit;
	Container* pcon;
};

template<typename Container>
My_back_insert_iterator<Container> 
My_back_inserter(Container& con)
{
	return My_back_insert_iterator<Container>(con);
}

template<typename Container>
My_front_insert_iterator<Container>
My_front_inserter(Container& con)
{
	return My_front_insert_iterator<Container>(con);
}
template<typename Container>
My_insert_iterator<Container>
My_inserter(Container& con,typename Container::iterator& it)
{
	return My_insert_iterator<Container>(con,it);
}
template < class InputIterator,
		   class OutputIterator >
OutputIterator
My_copy(InputIterator first1,
InputIterator last,
OutputIterator first2)
{
	for (first1; first1 != last; ++first1)
	{
		*first2 = *first1;
	}
	return first2;
}
int main()
{
	int arr[] = { 56, 13, 13, 13, 3, 3, 3, 3, 1, 4 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> vec(arr, arr + len);
	vector<int> vec1;
	ofstream file;
	file.open("text.txt");
	copy(istream_iterator<int>(cin),
		 istream_iterator<int>(),back_insert_iterator<vector<int>>(vec1));

	deque<int> dque(vec.begin(), vec.end());
	Show(vec);

	vector<int>::iterator it = find(vec.begin(), vec.end(), 1);
	if (it != vec.end())
	{
		/*My_insert_iterator<vector<int>> iit(vec,it);
		*iit = 100;*/
		My_inserter(vec,it) = 101;
	}
	Show(vec);
	//ofstream pfile("text.txt");
	My_copy(vec1.begin(), vec1.end(), ostream_iterator<int>(file,"."));
	file.close();
	/*back_insert_iterator<vector<int>>  biit(vec);
	*My_back_inserter(vec) = 400;
	*biit = 40;
	Show(vec);
	My_front_insert_iterator<deque<int>>  fiit(dque);
	*fiit = 50;
	My_front_inserter(dque) = 500;
	Show(dque);*/
	return 0;
}
#if 0
int main()
{
	int arr[] = { 56, 13, 13, 13, 3, 3, 3, 3, 1, 4 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> vec(arr, arr + len);
	vector<int>::iterator bit = vec.begin();
	vector<int>::iterator eit = vec.end();
	Show(vec);
	vec.push_back(30);
	vec.insert(vec.end(),40);
	Show(vec);
	vector<int>::reverse_iterator cbit = vec.rbegin();

	/*
		const int*
	*/
	vector<int>::const_iterator cit  = vec.begin();
	/*
		int* const
	*/
	const vector<int>::iterator it = vec.begin();

	//vector<int>::const_reverse_iterator 
	//++cit;
	//*eit = 20;
	return 0;
}
int main()
{
	int arr[] = { 56, 13, 13, 13, 3, 3, 3, 3, 1, 4 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> vec(arr,arr + len);
	Show(vec);
	deque<int> dque(vec.begin(), vec.end());
	sort(dque.begin(), dque.end(), greater<int>());
	Show(dque);
	return 0;
}
#endif