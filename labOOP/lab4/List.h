#pragma once
#include "Node.h"
class Node;
class List
{
	//встроенное объявление класса Node

	//данные
	Node Head;	// фиктивный элемент, который является признаком начала списка
	Node Tail;	// фиктивный элемент, который является признаком конца списка
	Node* pHead;
	size_t m_size;	//количество элементов
public:
	List(); //сформировать Head, Tail и m_size 
	~List();
	List(const List&);
	//	…
	void AddHead(const Circle&);
	void AddTail(const Circle&);
	bool RemoveOne(const Circle&);
	bool Cleaning();
	int  RemoveAll(const Circle&);
	int  Size();
	void Sort();

	friend std::ostream& operator<<(std::ostream& os, const List& l);

	};

std::ostream& operator<<(std::ostream& os, const List& l);