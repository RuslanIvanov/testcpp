#pragma once
#include "myRect.h"
#include "Circle.h"
class List
{
	//встроенное объявление класса Node
	class Node
	{
		//Данные:
		Node* pPrev;		//указатель на предыдущий элемент
		Node* pNext;		//указатель на следующий элемент
		Shape* m_Data;		//указатель на свою (динамическую) копию данных

		//Методы:
		Node();//скорее всего понадобится для создания вспомогательных оберток – «стражей» (Head, Tail)
		Node(const Shape*, Node* next, Node* prev);
		Node(Node&&);
		Node& operator=(Node&&);
		~Node();//деструктор должен «исключать» уничтожаемый Node из списка

		friend class List; //все методы класса List имеют права доступа к Node
	public:
		friend std::ostream& operator<<(std::ostream& os, const Node& n)
		{ // virtual prinf() или RTTI
			//os << n.m_Date; //??
			//os <<
			n.m_Data->print(os);
			return os;
		}

		friend std::ifstream& operator>>(std::ifstream& in, /*const*/ Node& n)
		{ 			
			n.m_Data->read(in);
			return in;
		}
		
		Node* getNext() const { return pNext; }
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
	List& operator=(const List&);
	//	…
	void AddHead(const Shape*);
	void AddTail(const Shape*);
	bool RemoveOne(const Shape*);
	int Cleaning();
	int RemoveAll(const Shape*);
	int  Size();
	void Sort(SORT sortType=SQ);
	void out();
	bool compare(const Shape*, const Shape*);
	friend std::ostream& operator<<(std::ostream& os, const List& l);
	friend std::ifstream& operator>>(std::ifstream& in,/* const*/ List& l);
	};

std::ostream& operator<<(std::ostream& os, const List& l);
std::ifstream& operator>>(std::ifstream& in,/* const*/ List& l);