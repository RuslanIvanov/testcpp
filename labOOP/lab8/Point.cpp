#include <iostream>
#include "Point.h"

//Globals:///////////////////////////////////////////////////////////
Point& operator+=(Point& rl, int i) 
{
	rl.m_x += i;
	rl.m_y += i;

	return rl;
}

Point operator-(Point& rl, int i)
{

	return Point(rl.m_x-i, rl.m_y-i);
}

Point operator-(Point& rl, const Point& rr)
{
	
	return Point(rl.m_x - rr.m_x, rl.m_y - rr.m_y);
}

Point operator+(int i, Point& r)
{

	return Point(r.m_x + i, r.m_y + i);
}
///////////////////////////////////////////////////////////////////////////////////

Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

Point::Point(const Point& r)
{
	m_x = r.m_x;
	m_y = r.m_y;
}

Point& Point::operator=(const Point& r)
{
	if (this == &r) { return *this; }

	m_x = r.m_x;
	m_y = r.m_y;

	return *this;
}

Point& Point::operator+=(const Point& r)
{
	m_x += r.m_x;
	m_y += r.m_y;

	return *this;
}

Point Point::operator+(const Point& r)
{	
	
	return Point(m_x + r.m_x, m_y + r.m_y);
}


Point Point::operator+(int i)
{
	
	
	return Point(m_x + i, m_y + i);
}

Point Point::operator+() 
{//сам себя меняет
	
	return *this;
}
Point operator-(const Point& r)
{

	return Point(-r.m_x,-r.m_y);
}

std::ostream& Point::print(std::ostream& os)
{
	os << "\npoint: m_x = " << m_x << " m_y = " << m_y;
	return os;
}

void Point::print()
{
	std::cout << "\nPoint: m_x = " << m_x << " m_y = " << m_y;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "m_x = " << p.m_x << " m_y = " << p.m_y;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Point* p)
{
	if (p) 
	{
		os << "m_x = " << p->m_x << " m_y = " << p->m_y;
	}
	return os;
}