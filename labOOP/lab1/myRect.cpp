#include "myRect.h"
#include <iostream>

Rect::Rect()
{
	m_left = m_top = m_right = m_bottom = 0;
	std::cout << "\nRect::def constructor";
}

Rect::Rect(int left, int right, int top, int bottom)
{
		m_left = left;
		m_top = top;
		m_right = right;
		m_bottom = bottom;

		this->Normalize();

		//Normalize(left,right,top,bottom);
		std::cout << "\nRect::constructor, param";
}

Rect::~Rect()
{
	std::cout << "\nRect::~destuctor";
}

Rect::Rect(const Rect& r) 
{
	m_bottom = r.m_bottom;
	m_top = r.m_top;
	m_left = r.m_left;
	m_right = r.m_right;

	std::cout << "\nRect::constructor copy";
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

	return Rect(l,r,t,b);
}

void Rect::print()
{
	std::cout << "left = " << m_left << " right = " << m_right << "\n";
	std::cout << "top = " << m_top << " bottom = " << m_bottom << "\n";
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
		
	return Rect(vl2, vr2, vt2, vb2);
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

	return Rect(vl2, vr2, vt2, vb2);

	//return BoundingRect(r1,r2); // не эффект
}