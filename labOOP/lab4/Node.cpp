#include <iostream>
#include "Node.h"

Node::Node(): pPrev(nullptr), pNext(nullptr) {}
Node::Node(const Circle& c, Node* next, Node* prev) 
{//если prev = &Head
	pPrev = prev;//для нового элемента pPrev дается &Head
	pNext = prev->pNext;//следующий стал хвостом т.е. &Tail

	prev->pNext = this; //в голове присваивается pNext адрес вставл. элемента
	pNext->pPrev = this; // хвосту дается адрес встраиваемого эл.
}
Node::~Node() 
{
	//если есть сосед права
	if (pPrev)
	{//соседу справав уст  адрес следующего то который у удаляемого прописан был
		pPrev->pNext = this->pNext;
	}

	if (pNext)
	{// соседу слева уст. адресс предыдущего , который был прописан у удуляемого
		pNext->pPrev = this->pPrev;
	}
}

std::ostream& operator<<(std::ostream& os, const Node& n)
{
	os << n.m_Data;
	return os;
}
