#include <iostream>
#include <string.h>
#include "Counter.h"

Counter* Counter::Head = nullptr;
unsigned int Counter::m_curCounters;
Counter::Counter(const char* str) :m_nOwners(1)
{
	size_t n = strlen(str) + 1;
	m_pStr = new char[n];
	strcpy(m_pStr,str);

	m_curCounters++;
	if (m_curCounters == 1)
	{
		Head = this;
	}
	else 
		Head->pNext = this;
}

Counter::~Counter() 
{ 
	//delete[] m_pStr;

	if (m_curCounters > 0)
	{
		m_curCounters--;
		delete[] m_pStr;
	}

	if (m_curCounters == 1) 
			delete Head;  
	
	
}

void Counter::AddUser()
{
	m_nOwners++;
}

void Counter::RemoveUser()
{
	m_nOwners--;
	if (m_nOwners == 0)
	{
		delete this;
	}
}
