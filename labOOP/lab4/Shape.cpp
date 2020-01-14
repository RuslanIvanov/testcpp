#include "Shape.h"
#include <iostream>

Shape::Shape(COLOR c)
{
	m_color = c;
	std::cout << "\nI am in Shape's constr!";
}

Shape::Shape(const Shape& r)
{
	m_color = r.m_color; //доступ к privat того же тип объекта разрешен
	//r.m_color = RED; - нельзя т.к. const
	std::cout << "\nI am in Shape's constr copy!";
}

Shape::~Shape()
{
	std::cout << "\nNow I am in Shape's destructor!";
}

void Shape::printColor()
{
	std::cout << "\nmy color is: ";
	switch (m_color)
	{
	case RED:
		std::cout << "RED";
	break;
	case GREEN:
		std::cout << "GREEN";
	break;
	case BLUE:
		std::cout << "BLUE";
	break;
	}
}

void Shape::WhereAmI()
{
	std::cout << "\nNow I am in class Shape";
}