#pragma once
class Counter;
class MyString2
{
	Counter* m_pMyCounter;
public:
	MyString2(const char*);
	~MyString2();
	MyString2(const MyString2&);
	MyString2& operator=(const MyString2 &);
	friend std::ostream& operator<<(std::ostream& os, const MyString2& s);

};

std::ostream& operator<<(std::ostream& os, const MyString2& s);

