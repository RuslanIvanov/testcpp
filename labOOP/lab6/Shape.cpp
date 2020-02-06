#include <iostream>
#include <fstream>
#include <string.h>
#include "Shape.h"

SORT Shape:: m_sortType = SQ;

Shape::Shape(COLOR c)
{
	m_S = 0;
	m_color = c;
	
	//std::cout << "\nI am in Shape's constr!";
}

Shape::Shape(const Shape& r)
{
	m_S = r.m_S;
	m_color = r.m_color; //доступ к privat того же тип объекта разрешен

	//std::cout << "\nI am in Shape's constr copy!";
}

Shape::~Shape()
{
	//std::cout << "\nNow I am in Shape's destructor!";
}

const char* Shape::getColorName() 
{
	switch (m_color)
	{
		case RED:return		"RED";
		case GREEN:return	"GREEN";
		case BLUE:return	"BLUE";
		case YELLOW:return	"YELLOW";
		case BLACK:return	"BLACK";
		case WHITE: return  "WHITE";
		default: return "";
	}
}

void Shape::setColorName(const char* name) 
{
	if (strcmp(name, "RED") == 0) { m_color = RED; }
	else
		if (strcmp(name, "GREEN") == 0) { m_color = GREEN; }
		else
			if (strcmp(name, "BLUE") == 0) { m_color = BLUE; }
			else
				if (strcmp(name, "YELLOW") == 0) { m_color = YELLOW; }
				else
					if (strcmp(name, "BLACK") == 0) { m_color = BLACK; }
					else
						if (strcmp(name, "WHITE") == 0) { m_color = WHITE; }
						else m_color = RED;

}

void Shape::WhereAmI()
{
	std::cout << "\nNow I am in class Shape";
}
