#include <cstddef>
#include <iostream>
#include "MyString2.h"
#include "Counter.h"

MyString2::MyString2(const char* s) 
{
	m_pMyCounter = new Counter(s);
}
MyString2::~MyString2() 
{
	m_pMyCounter->RemoveUser();
	
}
MyString2::MyString2(const MyString2& s)
{
	m_pMyCounter = s.m_pMyCounter;
	m_pMyCounter->AddUser();
}

MyString2& MyString2::operator=(const MyString2& s)
{
	if (m_pMyCounter != s.m_pMyCounter)
	{
		m_pMyCounter->RemoveUser();
		m_pMyCounter = s.m_pMyCounter;
		m_pMyCounter->AddUser();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString2& s) 
{

        os << "\nString is:' " << s.m_pMyCounter->getString()<<" '";//m_pStr;
        return os;
}

