#pragma once
class MyString
{
    char* m_pStr;	//строка-член класса
   
public:
    MyString();
    MyString(const char* pstr);
    MyString(const MyString&);
    ~MyString();
    char* GetString();
    void SetNewString(const char* pstr);
};
