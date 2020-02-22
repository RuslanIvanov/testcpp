#pragma once

template <typename T> void printVect(const T& t)
{

    std::cout<<"|"<<t;

}
template <typename T>
struct changePPP
{
    int x;
    int y;
    changePPP(int _x,int _y)
    {
        x = _x;
        y=_y;
        t.SetX(x);
        t.SetY(y);
    }

    changePPP()
    {
        x=0;y=0;
        t.SetX(0);
        t.SetY(0);
    }

    void operator()(int _x,int _y)
    {
        t.SetX(_x);
        t.SetY(_y);
    }

    void operator()(int d)
    {
        t.SetX(x+d);
        t.SetY(y+d);
    }

    T t;
};

class Point;
template <typename T=Point> void changePoint(T& t)
{
   int x = t.GetX();
   int y = t.GetY();
   x++; y++;
   t.SetX(x);
   t.SetY(y);

}

class Point;
template <typename T=Point> void changePoint2(T& t,int X, int Y)
{

   t.SetX(X);
   t.SetY(Y);

}

