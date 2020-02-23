#pragma once
#include <iostream>
class Rect
{
	int m_left, m_right, m_top, m_bottom;
public:
	Rect();
	Rect(int left,int right,int top, int bottom);
	Rect(const Rect& r);
	virtual
		~Rect();
	void Normalize();
	void Normalize(int l,int r,int t,int b);
	void InflateRect(int dl, int dr, int dt, int db);
	void InflateRect(int dh = 1, int dv = 1);
	void SetAll(int l, int r, int t, int b);
	void GetAll(int* pl, int* pr, int* pt, int* pb) const;

	int getTop();
	int getLeft();
	int getRight();
	int getBottom();

	void setTop(int);
	void setLeft(int);
	void setRight(int);
	void setBottom(int);

	Rect BoundingRect(const Rect& r1);
        void print();
        void Inflate(int);

        bool operator<(const Rect& r) const;
        bool operator>(const Rect& r) const;
        bool operator==(const Rect& r) const;

        friend std::ostream& operator<<(std::ostream& os, const Rect& );
	};

/////////////////////////////////////////////////
Rect BoundingRect2(Rect& r1, Rect& r2);
Rect BoundingRect(Rect r1, Rect r2);
std::ostream& operator<<(std::ostream& os, const Rect& );


