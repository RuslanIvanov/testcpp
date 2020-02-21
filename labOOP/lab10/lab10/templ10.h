#pragma once

template <typename T> void printVect(const T& t)
{

    std::cout<<"|"<<t;

}
template <typename T>
struct changePPP
{
    change(int x,int y)
    {
  //      x = 0;,y=0;
        t.SetX(x);
        t.SetY(y);
    }
    void operator()(int x,int y) {  t.SetX(x);
                                    t.SetY(y); }

    T t;
};

class Point;
template <typename T=Point> void changePoint(const T& t)//,int x,int y)
{
   int x = t.GetX();
   int y = t.GetY();
   x++; y++;
   t.SetX(x);
   t.SetY(y);

}
