#include <iostream>
#include <fstream>
#include "myRect.h"

Rect::Rect():Shape(RED)
{
	m_left = m_top = m_right = m_bottom = m_S = 0;
	//std::cout << "\nRect::def constructor";
}

Rect::Rect(int left, int right, int top, int bottom,COLOR c):Shape(c)
{
		m_left = left;
		m_top = top;
		m_right = right;
		m_bottom = bottom;

		this->Normalize();
		square();
	//	std::cout << "\nRect::constructor, param";
}

Rect::~Rect()
{
	//std::cout << "\nNow I am in Rect's destructor!";
}

Rect::Rect(const Rect& r):Shape(r)
{
	m_bottom = r.m_bottom;
	m_top = r.m_top;
	m_left = r.m_left;
	m_right = r.m_right;

	//std::cout << "\nI am in Rect's constr copy!";
}

void Rect::Normalize()
{
	if (m_top > m_bottom)
	{
		int tmp = m_bottom;
		m_bottom = m_top;
		m_top = tmp;
	}

	if (m_left > m_right)
	{
		int tmp = m_left;
		m_left = m_right;
		m_right = tmp;
	}

}
void Rect::Normalize(int left, int right, int top, int bottom)
{
	if (top > bottom)
	{
		m_bottom = top;
		m_top = bottom;
	}
	else
	{
		m_bottom = bottom;
		m_top = top;
	}

	if (left > right)
	{
		m_left = right;
		m_right = left;
	}
	else
	{
		m_left = left;
		m_right = right;
	}
}
void Rect::InflateRect(int dl, int dr, int dt, int db) 
{	
	m_left -= dl;
	m_right += dr;
	m_top -= dt;
	m_bottom += db;

	Normalize();
}

void Rect::InflateRect(int dh,int dv)
{
	m_left -= dv;
	m_right += dv;
	m_top -= dh;
	m_bottom += dh;

	Normalize();
}

void Rect::SetAll(int l, int r, int t, int b)
{
	m_left = l;
	m_right = r;
	m_top = t;
	m_bottom = b;

	Normalize();
}

void Rect::GetAll(int* pl, int* pr, int* pt, int* pb) const
{
	*pl = m_left;
	*pr = m_right;
	*pt = m_top;
	*pb= m_bottom;
}

int Rect::getTop()
{
	return m_top;
}

int Rect::getLeft()
{
	return m_left;
}

int Rect::getRight()
{
	return m_right;
}

int Rect::getBottom()
{
	return m_bottom;
}

void Rect::setTop(int x) { m_top = x; }
void Rect::setLeft(int x) { m_bottom = x; }
void Rect::setRight(int x ) { m_right =x; }
void Rect::setBottom(int x) { m_bottom = x; }

Rect Rect::BoundingRect(const Rect& r1) 
{
	int l, t, r, b;
	GetAll(&l, &r, &t, &b);
	
	if (r1.m_left < m_left) { l = r1.m_left; }
	if (r1.m_top < m_top) { t = r1.m_top; }

	if (r1.m_right > m_right) { r = r1.m_right; }
	if (r1.m_bottom > m_bottom) { b = r1.m_bottom; }

	this->Normalize();

	return Rect(l,r,t,b,RED);
}

std::ostream& Rect::print(std::ostream& os)
{
	os << "\nRect:\n"; os << "color " << getColorName();
	os << "\nleft = " << m_left << "\nright = " << m_right;
	os << "\ntop = " << m_top << "\nbottom = " << m_bottom;
	os << "\nS = " << m_S;
	
	return os;
}

 std::ifstream& Rect::read(std::ifstream& in)
{
	 char buf[BUFSIZ];
	 in >> buf; in >> buf;
	 setColorName(buf);
	 in >> buf; in >> buf;
	 in >> m_left;
	 in >> buf; in >> buf;
	 in >> m_right;
	 in >> buf; in >> buf;
	 in >> m_top;
	 in >> buf; in >> buf;
	 in >> m_bottom;
	 in >> buf; in >> buf;
	 in >> m_S;

	 return in;
}
 /*
 std::ifstream& operator>>(std::ifstream& in, const Rect& r) 
 {
	 char buf[100];
	 in >> buf;
	 r.setColorName(buf);
	 in >> buf;
	 in >> r.m_left;
	 in >> buf;
	 in >> r.m_right;
	 in >> buf;
	 in >> r.m_top;
	 in >> buf;
	 in >> r.m_bottom;
	 in >> buf;
	 in >> r.m_S;

	 return in;
 }*/

void Rect::WhereAmI()
{
	std::cout << "\nNow I am in class Rect";
}

void Rect::Inflate(int d) 
{
	std::cout << "\nRect::Inflate";
	m_left -= d;
	m_right += d;
	m_top -= d;
	m_bottom += d;
}

int Rect::square()
{
	//std::cout << "\nRect S= ";
	m_S = (m_right - m_left) * (m_bottom - m_top);
	//std::cout << m_S;
	return 0;
}

Shape* Rect::clone() const
{
	return new Rect(*this);
}

//Rect& Rect::operator=(const Shape& r)
//{
//	const Rect* pR = dynamic_cast<const Rect*>(&r);
//	if (pR == 0) return *this;//иначе сам в себя скопирует
//
//	if (pR == &r) return *this;
//
//	Shape::operator=(r);
//	m_bottom = pR->m_bottom;
//	m_top = pR->m_bottom;
//	m_left = pR->m_left;
//	m_right = pR->m_right;
//	std::cout << "\nvirt recopy Rect";
//	return *this;
//}

Rect& Rect::operator=(const Rect& r)
{
	//Shape::operator=(r);
	if (this == &r) return *this;

	//const Rect* pR = dynamic_cast<const Rect*>(&r);
	//if (pR == 0) return *this;//иначе сам в себя скопирует

	Shape::operator=(r);
	m_bottom = r.m_bottom;
	m_top = r.m_bottom;
	m_left = r.m_left;
	m_right = r.m_right;
	std::cout << "\nrecopy Rect";
	return *this;
}
bool Rect::operator == (const Shape& c) const
{
	const Rect* pR = dynamic_cast<const Rect*>(&c);
	if (pR == 0) return false;

	if (pR->m_left == m_left && pR->m_right == m_right && pR->m_top == m_top && pR->m_bottom == m_bottom && Shape::operator==(c)) 	
		return true;
	else
		return false;	
}
bool Rect::operator !=(const Shape&  c) const
{
	return  !operator==(c);	
}

//=================================================================
Rect BoundingRect(Rect r1, Rect r2)
{
	int vl1, vr1, vt1, vb1;
	r1.GetAll(&vl1, &vr1, &vt1, &vb1);

	int vl2, vr2, vt2, vb2;
	r2.GetAll(&vl2, &vr2, &vt2, &vb2);

	if (vl1 < vl2) { vl2 = vl1; }
	if (vt1 < vt2) { vt2 = vt1; }

	if (vr1 > vr2) { vr2 = vr1; }
	if (vb1 > vb2) { vb2 = vb1; }
		
	return Rect(vl2, vr2, vt2, vb2,RED);
}

Rect BoundingRect2(Rect& r1, Rect& r2)// ? вопрос
{
	//Rect r_rez;

	//return r_rez;

	int vl1, vr1, vt1, vb1;
	r1.GetAll(&vl1, &vr1, &vt1, &vb1);

	int vl2, vr2, vt2, vb2;
	r2.GetAll(&vl2, &vr2, &vt2, &vb2);

	if (vl1 < vl2) { vl2 = vl1; }
	if (vt1 < vt2) { vt2 = vt1; }

	if (vr1 > vr2) { vr2 = vr1; }
	if (vb1 > vb2) { vb2 = vb1; }

	return Rect(vl2, vr2, vt2, vb2,RED);

	//return BoundingRect(r1,r2); // не эффект
}