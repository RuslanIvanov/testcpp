#pragma once
#include "Point.h"
#include "Shape.h"

class Circle:public Shape
{
	int m_D;
	int m_x0;
	int m_y0;
	
	Point m_Point;

	public:
	
		Circle(const Circle&);
		Circle(int x=0, int y=0, int D=0,COLOR c = RED);
		~Circle();	
		int square();
		void WhereAmI();
		void Inflate(int);
		//void print();
		std::ostream& print(std::ostream& os);
		std::ifstream& read(std::ifstream& in);
		Shape* clone() const;
		bool operator==(const Shape&) const;
		bool operator!=(const  Shape&) const;
		//virtual Circle& operator=(const Shape&);
		Circle& operator=(const Circle&);
	//	bool operator<(const Shape&) const;
		friend std::ostream& operator<<( std::ostream& os, const Circle& c);
		//friend std::ifstream& operator>>(std::ifstream& os, const Circle& c);
};

std::ostream& operator<<( std::ostream& os, const Circle& c);
//std::ifstream& operator>>(std::ifstream& os, const Circle& c);
