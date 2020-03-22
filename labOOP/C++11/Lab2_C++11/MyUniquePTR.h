#pragma once
#include <vector>
#include <algorithm>
#include <string.h>
#include <iterator>
#include <utility>
#include <initializer_list>

template<typename T>
class MyUniquePTR
{
	T* m_p;
	protected:
	MyUniquePTR (const MyUniquePTR&){}
	MyUniquePTR& operator=(const MyUniquePTR&){ return *this; }

	public:
	
	MyUniquePTR(MyUniquePTR&& r)
	{ 
		m_p = r.m_p; 
		r.m_p = nullptr; 
	}

	MyUniquePTR& operator=(MyUniquePTR&& r)
	{ 
		if(this==&r) return *this; 		

		delete [] m_p;

		m_p = r.m_p; 
		r.m_p = nullptr;
		
		return *this; 
	}

	MyUniquePTR(){ m_p = nullptr; }
	MyUniquePTR(T* p):m_p(p){}
	~MyUniquePTR(){delete m_p;}

	T* get() const { return m_p; }
	T* operator->() { return m_p; }
	T& operator*()	{ return *m_p; }

	explicit operator bool() const noexcept
	{
		if(get()==nullptr) return false;
		else return true;
	}
};
