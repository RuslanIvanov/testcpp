#pragma once
#include <iostream>
#include <stdlib.h>
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

        int getTop() const;
        int getLeft() const;
        int getRight() const;
        int getBottom() const;

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
        Rect operator-(const Rect& r) const;
         Rect operator-(Rect& r) ;

        friend std::ostream& operator<<(std::ostream& os, const Rect& );
        friend Rect operator-(const Rect& rl, const Rect& rr);// const; ???
        friend Rect operator-(Rect& rl,  Rect& rr);
        friend bool operator<(const Rect& r,const Rect& l);// const;
	};

/////////////////////////////////////////////////
Rect BoundingRect2(Rect& r1, Rect& r2);
Rect BoundingRect(Rect r1, Rect r2);
std::ostream& operator<<(std::ostream& os, const Rect& );
Rect operator-(const Rect& rl, const Rect& rr); //const ???
Rect operator-( Rect& rl, Rect& rr);
bool operator<(const Rect& r,const Rect& l); //const;


