#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h> 
#include "List.h"
#define COMPARE
List::Node::Node() : pPrev(nullptr), pNext(nullptr),m_Data(nullptr) {}
List::Node::Node(const Shape* r, Node* tail, Node* head)
{//если head = &Head

	if (head && tail == nullptr)
	{
		pPrev = head;//для нового элемента pPrev дается &Head
		pNext = head->pNext;//следующий стал хвостом т.е. &Tail

		head->pNext = this; //в голове присваивается pNext адрес вставл. элемента
		pNext->pPrev = this; // хвосту дается адрес встраиваемого эл.

		// RTTI или :
		m_Data = r->clone(); //динамическая копия
	}
	else if (head == nullptr && tail)
	{
		pNext = tail;// хвост след
		pPrev = tail->pPrev;/// то что  было у хвоста предыдущим
		pPrev->pNext = this;// tail->pPrev->pNext = this;// тому у кого был  хвост следующим
		
		tail->pPrev = this;// у хвоста стал предыдущим

		// RTTI:

		const Rect* pR = dynamic_cast<const Rect*>(r);
		if(pR!=0)	
		{ m_Data = new Rect(*pR); }
		else 
			{ m_Data = new Circle(*(dynamic_cast<const Circle*>(r))); }
	}
	else
	{
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
	r.m_Data = nullptr;
}

List::Node& List::Node::operator=(Node&& r)
{
	if (this == &r) return *this;

	delete m_Data;

	m_Data = r.m_Data;
	pNext = r.pNext;
	pPrev = r.pPrev;

	r.pNext = nullptr;
	r.pPrev = nullptr;
	r.m_Data = nullptr;
}

List::Node::~Node()
{
	delete this->m_Data;

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
bool List::compare(const Shape* a, const Shape* b)
{
	if (typeid(*a) == typeid(*b))
	{
		if (typeid(*a) == typeid(Rect))
		{
			if (*dynamic_cast<const Rect*>(a) == *dynamic_cast<const Rect*>(b)) 
			{
				return true;
			}
			else return false;
		}
		else
			if (typeid(*a) == typeid(Circle))
			{
				if (*dynamic_cast<const Circle*>(a) == *dynamic_cast<const Circle*>(b))
				{
					return true;
				}
				else return false;
			}
			else return false;
	}
	else return false;

}
List& List::operator=(const List& l)//  эффект.
{
	if (this == &l) { return *this; }

	Node* pOther = l.Head.pNext;
	Node* pThis = Head.pNext;
	// цикл по наименьш. size , исп typeid
	if (m_size >= l.m_size)
	{
		for (size_t ii = 0; ii < m_size; ii++)
		{///надо понимать какого типа объект и  если тако уже есть, то вставлять в подобный			
			if (ii < l.m_size)
			{
#ifdef COMPARE
				// в классах прегрузить oper= () и сделать их virt
				//ниже метод не эффект
				if (typeid(*pThis->m_Data) == typeid(*pOther->m_Data))
				{
					if (typeid(*pOther->m_Data) == typeid(Rect)) 
					{
						*dynamic_cast<Rect*>(pThis->m_Data) = *dynamic_cast<Rect*>(pOther->m_Data)  ;
					}
					else
					if (typeid(*pOther->m_Data) == typeid(Circle))
					{
						*dynamic_cast<Circle*>(pThis->m_Data) = *dynamic_cast<Circle*>(pOther->m_Data);
					}
				}
				else 
				{ 
					delete pThis->m_Data; 
					pThis->m_Data = pOther->m_Data->clone();
				}//*/
#else
				if (typeid(*pThis->m_Data) == typeid(*pOther->m_Data))
				{//совпадение типа - можно копировать
					//*pThis->m_Data = *pOther->m_Data;	//virtual oper=
					pThis->m_Data->operator=(*pOther->m_Data);
					//pThis = pThis->pNext;
					//pOther = pOther->pNext;
				}
				else
				{
					delete pThis->m_Data;
					pThis->m_Data = pOther->m_Data->clone();
				}//*/
#endif
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
#ifdef COMPARE				
				if (typeid(*pThis->m_Data) == typeid(*pOther->m_Data))
				{//ниже метод не эффект
					if (typeid(*pOther->m_Data) == typeid(Rect))
					{
						*dynamic_cast<Rect*>(pThis->m_Data) = *dynamic_cast<Rect*>(pOther->m_Data);
					}else
					if (typeid(*pOther->m_Data) == typeid(Circle))
					{
						*dynamic_cast<Circle*>(pThis->m_Data) = *dynamic_cast<Circle*>(pOther->m_Data);
					}
				}
				else
				{
					delete pThis->m_Data;
					pThis->m_Data = pOther->m_Data->clone();
				}//*/
#else
				if (typeid(*pThis->m_Data) == typeid(*pOther->m_Data))
				{//совпадение типа - можно копировать
					//*pThis->m_Data = *pOther->m_Data; //virtual oper=
					pThis->m_Data->operator=(*pOther->m_Data);
					//pThis = pThis->pNext;
					//pOther = pOther->pNext;
				}
				else
				{
					delete pThis->m_Data;
					pThis->m_Data = pOther->m_Data->clone();
				}//*/
#endif
			}
			else
			{
				AddTail(pOther->m_Data);
				pOther = pOther->pNext;
			}

		}
	}
		
	m_size = l.m_size;
	
	return *this;
}

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

void List::AddHead(const Shape* c)
{// так как вставляем в голову., то адрес головы
	new Node(c, nullptr, &Head); // &Head - указатель наначало списка
	m_size++;
}
void List::AddTail(const Shape* c) 
{
	new Node(c, &Tail,nullptr);
	m_size++;
}
bool List::RemoveOne(const Shape* c) 
{
	// установка на начало списка
	Node* p = Head.pNext;
	while (p!=&Tail) //пока текущий следующий не равен хвосту
	{
		if (*c == *p->m_Data)//??? вызов базового == только???  - работатет через virtual ==
		//if (typeid(*c) == typeid(*p->m_Data))
		//if(compare(c,p->m_Data))
		{

			delete p; //~Node () перекинул адреса
			m_size--;

			return true;
		}
		 
		p = p->pNext;// следующий елемент в списке

	}

	return false;
}
int List::RemoveAll(const Shape* c) 
{ // удаляет все дубли Circle !!! 
	int count = 0;
	List::Node* p = Head.pNext;
	while (p != &Tail) //пока текущий следующий не равен хвосту
	{
		Node* pnext = p->pNext;
		if (*c == *p->m_Data)
		//if (compare(c, p->m_Data))//так затратно
		{
			delete p;//оставить NN
			m_size--;
		
			count++;		
		}
		p=pnext;//NN
	}

	return count;
}

int List::Cleaning()
{ 
	Node* p = Head.pNext;
	int count = 0;
	while (p != &Tail) //пока текущий следующий не равен хвосту
	{
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

void List::Sort(SORT typeSort)
{
		Shape::setTypeSort(typeSort);
		std::cout<<"\n"<<Shape::getTypeSort();

		Node* p = Head.pNext;

		while (p != &Tail) 
		{//Поиск минимального из оставшихся значений
		
			Node* pMin = p;// Адрес мин на данный момент
			Node* p1 = p->pNext; // Адр следующего объекта
			while (p1 != &Tail)
			{// Сравнение миним с тек 
				if (*p1->m_Data < *pMin->m_Data)// Сравнение по S
				{// минимальный элемент найден, запоминаем адрес его Node
					pMin = p1; // Перенаправлени указ
				}
				p1 = p1->pNext;// Берем след адр для сравнения
			}
			//Обмен местами текущего с минимальным 
			
			//меняем адреса в узлах
			Shape *tmp = pMin->m_Data;//не эффект, надо менять узлы
			pMin->m_Data = p->m_Data;  //меняю адреса узлов
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

std::ifstream& operator>>(std::ifstream& in, /*const*/ List& l)
{

	const List::Node* p = l.Head.getNext();
	
	static const char* names[] = { "Rect:", "Circle:" };

	char buf[BUFSIZ] = "";
	in >> buf;

	for (int i = 0; i < (sizeof(names) / sizeof(names[0])); i++) 
	{
		if (strstr(buf, names[i]))
		{
			if (i == 0)
			{
				Rect r;		
				r.read(in);
				l.AddHead(&r);
			}

			if (i == 1) 
			{
				Circle c;
				c.read(in);
				l.AddHead(&c);
			}
		}
	}

	/*
	if (strstr(buf, "Rect:"))
	{
		 Rect r;		//создаl
		 r.read(in);	//заполнил 
		 l.AddHead(&r);	//добавил
	}
	else if(strstr(buf, "Circle:"))
	{
		Circle c;
		c.read(in);
		l.AddHead(&c);
	}*/

	return in;
}
