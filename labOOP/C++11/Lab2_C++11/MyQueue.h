#pragma once
#include <algorithm>
#include <string.h>
#include <iterator>
#include <utility>
#include <initializer_list>
template<typename T>
class MyQueue
{
	T* m_pmass;
	size_t m_n;
	size_t m_cap;
	size_t m_first;
	size_t m_last;
public:

	MyQueue( std::initializer_list<T> );
	MyQueue(size_t n);
	MyQueue(size_t n, const T& );
	MyQueue();
	~MyQueue();

	MyQueue(const MyQueue&);
	MyQueue(MyQueue&&);
	MyQueue& operator=(const MyQueue&);
	MyQueue& operator=(MyQueue&&);

	void push(const T&);
	T pop();
	void printQueue();

	T* begin(){	return m_pmass;	}
	T* end() { return m_pmass + m_n; }
	size_t size() { return  m_n;  }

	friend  std::ostream& operator<< (std::ostream& os, const MyQueue& s)
	{
		for (size_t i = s.m_first; (i < s.m_n) && (i < s.m_last); ++i)
		{
			os << s.m_pmass[i] << "";
		}
		return os;
	}
	
};


template<typename T>
MyQueue<T>::~MyQueue()
{
	delete[] m_pmass;
}

template<typename T>
MyQueue<T>::MyQueue() 
{
	m_cap = 10;
	m_n = 0;
	m_first = 0;
	m_last = 0;
	try 
	{
		m_pmass = new T[m_cap];
	}
	catch (std::bad_alloc) 
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(size_t n, const T& t) 
{
	m_cap = 10;
	m_n = n;
	m_first = 0;
	m_last = 0;
	try
	{
		m_pmass = new T[m_cap + m_n];

                for(;m_last< m_n;m_last++)
		{
                        m_pmass[m_last] = t;
		}
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(size_t n)
{
	m_cap = 10;
	m_n = n;
	m_first = 0;
	m_last = 0;
	try
	{
		m_pmass = new T[m_cap + m_n];
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue( std::initializer_list<T> list )
{
	m_cap = 10;
	m_n = list.size();
	m_first = 0;
	m_last = 0;
	try
	{
		m_pmass = new T[m_cap+m_n];

		for (auto& l : list) 
		{
			m_pmass[m_last] = l;
			m_last++;
		}
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(const MyQueue& r) 
{
	m_n = r.m_n;
	m_first = r.m_first;
	m_last = r.m_last;
	m_cap = 10;
	
	try 
	{
		m_pmass = new T[m_n + m_cap];
                for (size_t i = 0; i < r.m_n; i++)
		{
			m_pmass[i] = r.m_pmass[i];
		}
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(MyQueue&& r)
{
	m_n=r.m_n;
	m_pmass = r.m_pmass;
	m_cap = 10;
	m_last = r.m_last;
	m_first = r.m_first;

	r.m_n = 0;
	r.m_pmass = nullptr;
	r.m_cap = 0;
	r.m_last = r.m_first = 0;
}

template<typename T> 
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& r)
{
	if (&r == this) return *this;

	m_first = 0;//r.m_first;
	m_last = r.m_n;//r.m_last;
	m_cap = 10;

	try
	{
		if (m_n < r.m_n)
		{
			m_n = r.m_n;
			T* p = new T[m_n + m_cap];
			size_t ind1 = r.m_first;
			for (size_t i = 0; i < r.m_n; i++)
			{
				p[i] = r.m_pmass[ind1%r.m_n];
				ind1++;
			}
			delete[] m_pmass;
			m_pmass = p;
		}
		else 
		{
			m_n = r.m_n;
			size_t ind1 = r.m_first;
			for (size_t i = 0; i < m_n; i++)
			{
				m_pmass[i] = r.m_pmass[ind1 % r.m_n];
				ind1++;
			}
		}

	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}

	return *this;
}

template<typename T> 
MyQueue<T>& MyQueue<T>::operator=(MyQueue<T>&& r)
{
	if (&r == this) return *this;

	m_n = r.m_n;
	delete[] m_pmass;
	m_pmass = r.m_pmass;
	m_cap = 10;
	m_last = r.m_last;
	m_first = r.m_first;

	r.m_n = 0;
	r.m_pmass = nullptr;
	r.m_cap = 0;
	r.m_last = r.m_first = 0;

	return *this;
}

template<typename T> 
void MyQueue<T>::push(const T& t) 
{
	
	if (m_last <( m_n+m_cap ) )
	{
		m_pmass[m_last] = t;
		m_last++;
		//if (m_last >= m_n) { m_n = m_last; }
	}else 
	{//РїРµСЂРµСЂР°СЃРїРµСЂРґ
		
		m_last = (m_first + m_n) % m_cap;
		m_pmass[m_last] = t;
	}
}
template<typename T>
T MyQueue<T>::pop()
{
	return m_pmass[m_first++];
}

template<typename T>
void MyQueue<T>::printQueue()
{
	std::cout << "\nPRINTF MyQueue: ";

	if (m_n==0 || m_pmass==nullptr)
	{
		std::cout << " EMPTY! "; return;
	}
	
	/*for (const auto& element : m_pmass)
	{
		std::cout << element << ",";
	}//*/

	for (size_t i = m_first; (i < m_n) && (i < m_last); ++i)
	{
		std::cout << m_pmass[i] << ".";
	}
}
