#include <iostream>
#include "List.h"

List::List() 
{
	m_size = 0; // список пуст
	pHead = nullptr;
	Head.pNext = &Tail;
	Tail.pPrev = &Head;
}

List::~List() 
{
	for (size_t i = 0; i < m_size; i++)
	{
		delete Head.pNext;
	}
}

List::List(const List& l)
{
	m_size = l.m_size;
	//иниц_я Head & Tail так как не знают друг о друге изначально
	Head.pNext = &Tail;
	Tail.pPrev = &Head;

	Node* pOther = l.Head.pNext;// взять адресс следующего копируемого 
	Node* pThis = &Head;

	for (size_t i = 0; i < m_size; i++)
	{
		pThis = new Node(pOther->m_Data, nullptr, pThis);
		pOther = pOther->pNext; //взять адресс следующего для копирования и передачи в конструктор Node

	}
}

void List::AddHead(const Circle& c)
{// так как вставляем в голову., то адрес головы
	new Node(c, NULL, &Head); // &Head - указатель наначало списка
	m_size++;
}
void List::AddTail(const Circle&) {}
bool List::RemoveOne(const Circle& c) 
{
	// установка на начало списка
	Node* p = Head.pNext;
	while (p!=&Tail) //пока текущий следующий не равен хвосту
	{
		if (c == p->m_Data)
		{
			delete p; 
			m_size--;

			return true;
		}
		 
		p = p->pNext;// следующий елемент в списке

	}

	return false;
}

bool List::Cleaning() { return false;  }
int List::RemoveAll(const Circle&) { return 0; }

int List::Size()
{
	size_t i = 0;
	for (; i < m_size; i++)
	{

	}

	return i;
}

void List::Sort(){}

std::ostream& operator<<(std::ostream& os, const List& l)
{
	for (size_t i = 0; i < l.m_size; i++)
	{
		os << "#" << i + 1 << l.Head;
	}

	return os;
}