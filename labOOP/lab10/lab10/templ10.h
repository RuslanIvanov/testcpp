#pragma once

template <typename T> void printVect(const T& t)
{

    std::cout<<"\n|"<<t<<"|";

}

template <typename T=Point>
class changePPP
{
    int x;
    int y;
    T t;

    public:
    changePPP(int _x,int _y)
    {
        x = _x;
        y=_y;

    }

    changePPP()
    {
        x=0;y=0;
        t.SetX(0);
        t.SetY(0);
    }

    void operator()( Point& p )
    {
        p.SetX(x);
        p.SetY(y);
    }


};//changePPP(5,6);

class CMP_IF
{
    public:
    CMP_IF() {}

    bool operator()(const Point& l,const Point& r) const
    {
        return (l>r);
    }

};//Compare


class findRangePoint
{
    int n;
    int m;

    public:
    findRangePoint(int _n, int _m)
    {
        n =_n; m =_m;
    }

    bool operator()(const Point& p) const
    {
       return ( (p.GetX() >= n && p.GetX() <= m)  && (p.GetY() >= n && p.GetY() <= m) );

    }//findRangePoint.operator()(const Point& p)

};


template <typename T=Point> void changePoint(T& t)
{
   int x = t.GetX();
   int y = t.GetY();
   x++; y++;
   t.SetX(x);
   t.SetY(y);

}


template <typename T=Point> void changePoint2(T& t,int X, int Y)
{

   t.SetX(X);
   t.SetY(Y);

}

