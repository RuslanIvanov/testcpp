#pragma once
#include "Circle.h"
#include "List.h"

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
	~Node();//деструктор должен «исключать» уничтожаемый Node из списка

	friend class List; //все методы класса List имеют права доступа к Node
	friend std::ostream& operator<<(std::ostream& os, const Node& n);
};

std::ostream& operator<<(std::ostream& os, const Node& n);



