//#include <string> //windows
#include <string.h>
#include "myString.h"
#include <iostream>

using namespace std;

// Определение конструктора.

MyString::MyString()
{
	m_pStr = nullptr;
	cout << "\nMyString::def constructor";
}

MyString::MyString(const char* pstr) 
{
	int n = strlen(pstr) + 1;
	m_pStr = new char[n];
	///////////////////////////////////////////////
	//strcpy(m_pStr, pstr);// почему не работате ??
	//strncpy(m_pStr, pstr, n);
	//strncpy_s(m_pStr, pstr, n);
	///////////////////////////////////////////////
	memcpy(m_pStr, pstr, n);
	cout << "\nMyString::constructor, param";
}

MyString::MyString(const MyString& r) 
{
	int n = strlen(r.m_pStr) + 1;
	m_pStr = new char[n];
	memcpy(m_pStr,r.m_pStr, n);

	std::cout << "\nMyString::constructor copy";
}

// Определение деструктора.
MyString::~MyString()
{
	delete[] m_pStr;

	cout << "\nMyString::~destuctor";
}


char* MyString::GetString() 
{
	return m_pStr;
}


void MyString::SetNewString(const char* pstr) 
{
	int n_new = strlen(pstr) + 1;
	int n = strlen(m_pStr) + 1;

	if (n_new <= n) 
	{
		memcpy(m_pStr,pstr,n_new);
		return;
	}

	delete[] m_pStr;

	m_pStr = new char[n_new];
	memcpy(m_pStr, pstr,n_new);

}
