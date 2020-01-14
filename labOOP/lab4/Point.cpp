#include <iostream>
#include "Point.h"

//Globals:///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "m_x = " << p.m_x << " m_y = " << p.m_y;
	
	return os;
}

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




//Point:////////////////////////////////////////////////////////////////////////////
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

bool Point::operator==(Point& r) const
{
	if (r.m_x == m_x && r.m_y == m_y)
		return true;
	else
		return false;
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
{//сам себя 
	return *this;
}
Point operator-(const Point& r)
{
	return Point(-r.m_x,-r.m_y);
}

void Point::print()
{
	std::cout << "\npoint: m_x = " << m_x << " m_y = " << m_y;
}