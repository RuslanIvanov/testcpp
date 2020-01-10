#pragma once
#include "myString.h"
class Data
{
public:
	enum Sex{ UNDEF, MALE, FMALE };
private:
	Sex sex;
	size_t tm_age;
	MyString m_job;
	float m_salary;

	//Data():tm_age(0), m_job("N/A"), m_salary(0) { sex = UNDEF; }
	/*Data(Sex _sex, size_t _tm_age, const char* str, float salary):m_job(str) 
	{
		_sex = sex; tm_age = _tm_age; m_salary = salary;
	}*/
};

