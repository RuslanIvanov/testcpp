#include <iostream>
#include "List.h"

List::Node::Node() : pPrev(nullptr), pNext(nullptr) {}
List::Node::Node(const Circle& r, Node* tail, Node* head): m_Data(r)
{//если head = &Head

	if (head && tail == nullptr)
	{
		pPrev = head;//для нового элемента pPrev дается &Head
		pNext = head->pNext;//следующий стал хвостом т.е. &Tail

		head->pNext = this; //в голове присваивается pNext адрес вставл. элемента
		pNext->pPrev = this; // хвосту дается адрес встраиваемого эл.
	}
	else if (head == nullptr && tail)
	{
		pNext = tail;// хвост след
		pPrev = tail->pPrev;/// то что  было у хвоста предыдущим
		pPrev->pNext = this;// tail->pPrev->pNext = this;// тому у кого был  хвост следующим
		
		tail->pPrev = this;// у хвоста стал предыдущим

	}
	else
	{
		//?? 
		//так как Node(конструкор) private можно не обрабатывать ветку
	}
}

List::Node::Node(Node&& r)
{
	m_Data = r.m_Data;
	pNext = r.pNext;
	pPrev = r.pPrev;

	r.pNext = nullptr;
	r.pPrev = nullptr;
}

List::Node::~Node()
{
	//если есть сосед права
	if (pPrev)
	{//соседу справа уст  адрес следующего то который у удаляемого прописан был
		pPrev->pNext = this->pNext;
	}

	if (pNext)
	{// соседу слева уст. адресс предыдущего , который был прописан у удуляемого
		pNext->pPrev = this->pPrev;
	}
}

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

List& List::operator=(const List& l)//  эффект.
{
	if (this == &l) { return *this; }

	//так как не чистим свой список
	//Head.pNext = &Tail;
	//Tail.pPrev = &Head;

	Node* pOther = l.Head.pNext;
	Node* pThis = Head.pNext;

	if (m_size >= l.m_size)
	{
		for (size_t ii = 0; ii < m_size; ii++)
		{			
			if (ii < l.m_size)
			{
				pThis->m_Data = pOther->m_Data;		
				pThis = pThis->pNext;
				pOther = pOther->pNext;
			}
			else 
			{
				pThis = pThis->pNext;
				delete pThis->pPrev;
			}	
			
		}
	}
	else 
	{//m_size < l.m_size
		
		for (size_t ii = 0; ii < l.m_size; ii++)
		{
			if (ii < m_size)
			{
				pThis->m_Data = pOther->m_Data;
				pThis = pThis->pNext;
				pOther = pOther->pNext;
			}
			else
			{
				AddTail(pOther->m_Data);
				//pThis = new Node(pOther->m_Data, pOther, nullptr);//??
				pOther = pOther->pNext;
			}

		}
	}
		
	m_size = l.m_size;
	
	return *this;
}

/*
List& List::operator=(const List& l)// не эффект.
{
	if (this == &l) { return *this; }

	m_size = l.m_size;
	//////////////////////////////
	Cleaning();
	/////////////////////////////
	Head.pNext = &Tail;
	Tail.pPrev = &Head;

	Node* pOther = l.Head.pNext;
	Node* pThis = &Head;

	for (size_t i = 0; i < m_size; i++)
	{
		pThis = new Node(pOther->m_Data, nullptr, pThis);
		pOther = pOther->pNext;

	}

	return *this;
}*/

List::List(List&& l)
{//нужно пройтис по скоированным адресам

	Head.pNext = l.Head.pNext;
	Head.pPrev = l.Head.pPrev;
	Tail.pNext = l.Tail.pNext;
	Tail.pPrev = l.Tail.pPrev;

	pHead = l.pHead;
	m_size = l.m_size;
	/////////////////////////////////
	l.Head.pNext->pPrev = &Head;
	l.Tail.pPrev->pNext = &Tail;
	/////////////////////////////////
	
	l.Head.pNext = nullptr;//&l.Tail;
	l.Head.pPrev = nullptr;
	l.Tail.pPrev = nullptr;
	l.Tail.pNext = nullptr;
	l.m_size = 0;
	l.pHead = nullptr;
}

List& List::operator=(List&& l) 
{
	if (this == &l) 
	{ 
		return *this; 
	}

	for (size_t i = 0; i < m_size; i++)//OK
	{
		delete Head.pNext;
	}

	Head.pNext = l.Head.pNext;
	Head.pPrev = l.Head.pPrev;
	Tail.pNext = l.Tail.pNext;
	Tail.pPrev = l.Tail.pPrev;

	l.Head.pNext->pPrev = &Head;
	l.Tail.pPrev->pNext = &Tail;

	pHead = l.pHead;
	m_size = l.m_size;

	l.Head.pNext = nullptr;
	l.Head.pPrev = nullptr;
	l.Tail.pPrev = nullptr;
	l.Tail.pNext = nullptr;
	l.m_size = 0;
	l.pHead = nullptr;

	return *this;
}

void List::AddHead(const Circle& r)
{// так как вставляем в голову., то адрес головы
	new Node(r, nullptr, &Head); // &Head - указатель наначало списка
	m_size++;
}
void List::AddTail(const Circle& r) 
{
	new Node(r, &Tail,nullptr);
	m_size++;
}
bool List::RemoveOne(const Circle& r) 
{
	// установка на начало списка
	Node* p = Head.pNext;
	while (p!=&Tail) //пока текущий следующий не равен хвосту
	{
		if (r == p->m_Data)
		{
			delete p; //~Node () перекинул адреса
			m_size--;

			return true;
		}
		 
		p = p->pNext;// следующий елемент в списке

	}

	return false;
}
int List::RemoveAll(const Circle& r) 
{ // удаляет все дубли Circle !!! 
	int count = 0;
	List::Node* p = Head.pNext;
	while (p != &Tail) //пока текущий следующий не равен хвосту
	{
		Node* pnext = p->pNext;
		if (r == p->m_Data)
		{
			delete p;//оставить NN
			m_size--;
			//p = p->pNext;//RR
			//delete p->pPrev;//RR
			count++;		
		}
		p=pnext;//NN
		//else p = p->pNext;// следующий елемент в списке//RR

	}

	return count;
}

int List::Cleaning()
{ 
	Node* p = Head.pNext;
	int count = 0;
	while (p != &Tail) //пока текущий следующий не равен хвосту
	{
		//delete p;
		m_size--;
		p = p->pNext;
		delete p->pPrev;
		count++;
	}
	return count;  
}


int List::Size()
{
	return m_size;
}

void List::Sort()
{
		Node* p = Head.pNext;
		while (p != &Tail) 
		{//Поиск минимального из оставшихся значений
		
			Node* pMin = p;// Адрес мин на данный момент
			Node* p1 = p->pNext; // Адр следующего объекта
			while (p1 != &Tail)
			{// Сравнение миним с тек 
				if (p1->m_Data < pMin->m_Data)// Сравнение D
				{// минимальный элемент найден, запоминаем адрес его Node
					pMin = p1; // Перенаправлени указ
				}
				p1 = p1->pNext;// Берем след адр для сравнения
			}
			//Обмен местами текущего с минимальным Circle
			Circle tmp = pMin->m_Data;//не эффект, надо менять узлы
			pMin->m_Data = p->m_Data; 
			p->m_Data = tmp; 
	
			p = p->pNext;
		}

}

void List::out()
{
	Node* p = Head.pNext;
	while (p != &Tail)
	{
		std::cout << "\nout: ";
		std::cout << p->m_Data;
		p = p->pNext;
	}
}

std::ostream& operator<<(std::ostream& os, const List& l)
{
	
	const List::Node* p =  l.Head.getNext();

	while (p != &l.Tail)
	{
		os << "\n";
		os << (*p);//Node.m_Data;
		p = p->getNext();
	}
		
	return os;
}
