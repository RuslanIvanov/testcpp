#include <iostream>
#include <fstream>
#include "Circle.h"

Circle::Circle(int x, int y, int D,COLOR c):m_Point(x, y),Shape(c)
{
	m_D = D;
	m_x0 = x;
	m_y0 = y;

	square();
}

Circle::Circle(const Circle& r):m_Point(r.m_x0,r.m_y0),Shape(r)
{
	m_D = r.m_D;
	m_x0 = r.m_x0;
	m_y0 = r.m_y0;
	m_S = r.m_S;
	//std::cout << "\nI am in Circle's constr copy!";
}

Circle::~Circle()
{
	//std::cout << "\nNow I am in Circle's destructor!";
}

void Circle::WhereAmI()
{
	std::cout << "\nNow I am in class Circle";
}

void Circle::Inflate(int d) 
{
	std::cout << "\nCircle::Inflate";
	m_D += d;
}


//Circle& Circle::operator=(const Shape& c)
//{
//	const Circle* pR = dynamic_cast<const Circle*>(&c);
//	if (pR == 0) return *this;//иначе сам в себя скопирует
//
//	if (pR == &c) return *this;
//
//	Shape::operator=(c);
//
//	m_D = pR->m_D;
//	m_x0 = pR->m_x0;
//	m_y0 = pR->m_y0;
//	m_S = pR->m_S;
//	std::cout << "\nvirt recopy Circle";
//	return *this;
//}

Circle& Circle::operator=(const Circle& c)
{
	///Shape::operator=(c);

	if (this == &c) return *this;

	//const Circle* pR = dynamic_cast<const Circle*>(&c);
	//if (pR == 0) return *this;//иначе сам в себя скопирует
	Shape::operator=(c);
	m_D = c.m_D;
	m_x0 = c.m_x0;
	m_y0 = c.m_y0;
	m_S = c.m_S;
	std::cout << "\nrecopy Circle";
	return *this;
}

bool Circle::operator == (const Shape& c) const
{
	const Circle* pR = dynamic_cast<const Circle*>(&c);
	if (pR == 0) return false;

	if (pR->m_D == m_D && pR->m_x0 == m_x0 && pR->m_y0 == m_y0 && m_Point == pR->m_Point && Shape::operator==(c) ) // и цвет сравнить так  Shape::operator==(c) (т.е. явно вызвать оператор==() базового),  иначе будет бесконечная рекурсия т.к. будет вызоваться текущий Circle::operator == (const Shape& c) const
																												//Shape::operator==(c) 	- отмена полиморфизма
		return true;
	else
		return false;

}

bool Circle::operator !=(const Shape& c) const
{
	return	!operator==(c);
}

std::ostream& Circle::print(std::ostream& os)
{
	os << "\nCircle:";  os << "\ncolor " << getColorName();
	os << "\nx = " << m_x0 << "\ny = " << m_y0;
	os << "\nD = " << m_D << "\nS = " << m_S;
	return os;

}

std::ifstream& Circle::read(std::ifstream& in)
{
	char buf[BUFSIZ];
	in >> buf; 
	in >> buf;
	setColorName(buf);
	in >> buf; in >> buf;
	in >> m_x0;
	in >> buf; in >> buf;
	in >> m_y0;
	in >> buf; in >> buf;
	in >> m_D;
	in >> buf; in >> buf;
	in >> m_S;

	return in;
}
/*
std::ifstream& operator>>(std::ifstream& in, const Circle& c)
{
	char buf[100];
	in >> buf;
	c.setColorName(buf);
	in >> buf;
	in >> c.m_x0;
	in >> buf;
	in >> c.m_y0;
	in >> buf;
	in >> c.m_D;
	in >> buf;
	in >> c.m_S;

	return in;
}*/

int Circle::square() 
{
	//std::cout << "\nCircle S = ";
	m_S = static_cast<int>(3.14) * (m_D / 2.);
	//std::cout << m_S;
	return 	m_S;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

std::ostream& operator<<( std::ostream& os, const Circle& c)
{
	os << "x = " << c.m_x0 << " y = " << c.m_y0 << " ";
	os << "D = " << c.m_D << "";
	return os;
}

