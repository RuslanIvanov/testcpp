#include <cstddef>
#include <string.h>
#include "Counter.h"

Counter* Counter::pHead = nullptr;
unsigned int Counter::m_curCounters;
Counter::Counter(const char* str) :m_nOwners(1)
{
	size_t n = strlen(str) + 1;
	m_pStr = new char[n];
	strcpy(m_pStr,str);
	pNext = nullptr;
	m_curCounters++;
	if (m_curCounters == 1)
	{
		pHead = this;
		pHead->pNext = nullptr;
	}
	else 
		//if(m_curCounters==2){Head->pNext = this;}else 
		//нужно проверить есть ли еще такая строка
		{
			Counter* p =pHead;
			for (int i = 1; ; i++)
			{
				if ((p->pNext) != nullptr)
				{
					p = p->pNext;
				}
				else 
					{ 
							p->pNext = this; 
							break; 
					}
			}
		}
			
}

Counter::~Counter() 
{ 
	//delete[] m_pStr;

	if (m_curCounters >=1)
	{
		m_curCounters--;
		delete[] m_pStr;
	}

	if (m_curCounters == 1)
	{
		//delete pHead;
		pHead = nullptr;
		m_curCounters = 0;
	}
	
	
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
