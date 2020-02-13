#pragma once

#include <iostream>

#if  _WIN32 
#include <string>
#include <cstdarg>
#else
#include <cstddef>
#include <stdarg.h>
#include <string.h>
#endif

class MyString
{
    char* m_pStr;	//строка-член класса //explicit вроде бы надо
   
public:
    MyString();
    //explicit
        MyString(const char* pstr); //pstr ="" - тогда не надо MyString()
    MyString(const MyString&);
    MyString(MyString&& MoveSource);// конструктор перемещения
    ~MyString();

	MyString& operator=(const MyString& r);
    MyString& operator= ( MyString&& ); // Оператор присваивания при перемещении

    MyString operator+(const MyString& s); // унарный должен возвращать копию
    MyString& operator+=(const MyString& s);

	bool operator == (const char* k) const;

    const char* GetString();
    void SetNewString(const char* pstr);
    void ConcatString(const char* pstr); 
    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
	friend bool operator == (const char* k,const MyString&); //???
};
bool operator == (const char* k ,const  MyString& );
//////////////////////////////////////////////////////////////////////
MyString ApplyString(const char *p1, ...);
std::ostream& operator<<(std::ostream& os, const MyString& s);
MyString Concat(const char* p1, ...);
