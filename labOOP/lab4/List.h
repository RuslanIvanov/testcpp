#pragma once

#include "Circle.h"
class List
{
	//встроенное объявление класса Node
	class Node
	{
		//Данные:
		Node* pPrev;		//указатель на предыдущий элемент
		Node* pNext;		//указатель на следующий элемент
		Circle m_Data;		//Замечание: здесь может быть встроенный объект или указатель на свою (динамическую) копию данных

	//Методы:
		Node();//скорее всего понадобится для создания вспомогательных оберток – «стражей» (Head, Tail)
	//	Node(/*…,*/ const Circle*);	//конструктор, посредством которого создаваемый Node «подключается» в список.
		Node(const Circle&, Node* next, Node* prev);
		Node(Node&&);
		~Node();//деструктор должен «исключать» уничтожаемый Node из списка

		friend class List; //все методы класса List имеют права доступа к Node
	public:
		friend std::ostream& operator<<(std::ostream& os, const Node& n)
		{
			os << n.m_Data;
			return os;
		}

		Node* getNext() const { return pNext; }
		Circle getData() const { return m_Data; }

	};

	//данные
	Node Head;	// фиктивный элемент, который является признаком начала списка
	Node Tail;	// фиктивный элемент, который является признаком конца списка
	Node* pHead;
	size_t m_size;	//количество элементов
public:
	List(); //сформировать Head, Tail и m_size 
	~List();
	List(const List&);
	List(List&&);
	List& operator=(List&&);
	//	…
	void AddHead(const Circle&);
	void AddTail(const Circle&);
	bool RemoveOne(const Circle&);
	int Cleaning();
	int RemoveAll(const Circle&);
	int  Size();
	void Sort();
	void out();


	friend std::ostream& operator<<(std::ostream& os, const List& l);
	};

std::ostream& operator<<(std::ostream& os, const List& l);
