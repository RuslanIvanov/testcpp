#include "Point.h"
#include <iostream>
//Globals:///////////////////////////////////////////////////////////
Point& operator+=(Point& rl, int i) 
{
	rl.m_x += i;
	rl.m_y += i;

	return rl;
}

Point& operator-(Point& rl, int i)
{
	rl.m_x -= i;
	rl.m_y -= i;

	return rl;
}

Point& operator-(Point& rl, const Point& rr)
{
	rl.m_x -= rr.m_x;
	rl.m_y -= rr.m_y;

	return rl;
}

//??
Point& operator+(int i, Point& r)
{
	r.m_x += i; 
	r.m_y += i;
	return r;
}
//Point& operator+(int i , Point& rr) {	return rr;}
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

Point& Point::operator+(const Point& r)
{
	m_x += r.m_x;
	m_y += r.m_y;

	return *this;
}
/*
Point& Point::operator-(const Point& r)
{
	m_x -= r.m_x;
	m_y -= r.m_y;

	return *this;
}//*/

Point& Point::operator+(int i)
{
	m_x += i;
	m_y += i;

	return *this;
}

Point& Point::operator+() 
{
	m_x += 1;
	m_y += 1;
	return *this;
}

Point& Point::operator-()
{
	m_x -= 1;
	m_y -= 1;
	return *this;
}

void Point::print()
{
	std::cout << "\npoint: m_x = " << m_x << " m_y = " << m_y;
}