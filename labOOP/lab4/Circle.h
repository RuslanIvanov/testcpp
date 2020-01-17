#pragma once
#include "Point.h"

class Circle
{
	int m_D;
	int m_x0;
	int m_y0;
	Point m_Point;

	public:

		Circle(const Circle&);
		Circle(int x=0, int y=0, int D=0);
		~Circle();
		void WhereAmI();
		void Inflate(int);
		void print();
		bool operator==( Circle&) const;
		bool operator<(const Circle&);
		friend std::ostream& operator<<( std::ostream& os, const Circle& c);
};

std::ostream& operator<<( std::ostream& os, const Circle& c);
