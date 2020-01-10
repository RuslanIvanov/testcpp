#pragma once
class Point
{
	int m_x;
	int m_y;

	public:
		Point(int x = 0, int y = 0);
		Point(const Point& r);
		Point& operator=(const Point&);
		
		Point& operator+(const Point&);
		Point& operator+(int);
		//Point& operator-(const Point&);
	
		Point& operator+=(const Point&);

		Point& operator+();
		Point& operator-();

		friend Point& operator+=(Point&, int);
		friend Point& operator-(Point& rl, int i);
		friend Point& operator-(Point& rl, const Point& rr);
		friend Point& operator+(int, Point& r);
		void print();
};

Point& operator+=(Point&, int);
Point& operator-(Point& rl, int i);
Point& operator-(Point& rl, const Point& rr);
Point& operator+(int, Point& r);
