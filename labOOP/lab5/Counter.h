#pragma once
class Counter
{
	char* m_pStr;
	size_t m_nOwners;
	Counter* pNext;

	static Counter* pHead;
	static unsigned int m_curCounters;//счетчик указателей

	Counter(const char*);
	~Counter();
	void AddUser();
	void RemoveUser();
	friend class MyString2;
};

