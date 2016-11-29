#include <stdio.h>
#include <iostream>
using namespace std;

class point
{
    double x;
    double y;
    char* name;//??
public:
    point() { x=0;y=0; cout<<"I'm default construcror for point"<<endl; name = "pointDef";}
    point(double x,double y) { this->x=x; this->y=y; cout<<"I'm construcror for point"<<endl;name = "point"; }
    void print() { cout<<"x = "<<x<<"y= "<<y<<" name = "<<name<<endl; }

    point& operator=(const point& r)
    {
	cout<<"I'm oper=() for point"<<endl;
	if(this==&r) return *this;

	x=r.x; y=r.y; name = r.name; 

	return *this;
	}
};

class line
{
    point p1;
    point p2;
    public:
    line(double x1,double y1,double x2,double y2):p1(x1,y1),p2(x2,y2)
    {
	cout<<"I'm constructor for line"<<endl;
    }

    line(double x1,double y1,double x2,double y2,bool)
    {
        cout<<"I'm constructor for line (bool)"<<endl;
	p1 = point(x1,y1);p2 = point(x2,y2);
    }


    void printL() { p1.print(); p2.print(); }
};

int main(int argc, char* arcv[])
{

	if(argc==2)
	{line l(1,2,3,4,false);l.printL(); }
	else
	{line l(1,2,3,4); l.printL(); }

	return 0;
}
