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

struct RectCmp
{
    bool operator()(const Rect& lhs, const Rect& rhs) const
    {
        return lhs.operator>(rhs);
    }
};


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

class removal_on_from_the_center
{
    int x0;
    int y0;
    Rect zerro;

    public:
    removal_on_from_the_center(int X0 = 0, int Y0 = 0):zerro(0,0,0,0)
    {
        x0=X0; y0 =Y0;
    }

    bool operator()(const Rect& l, const Rect& r) //const
    {
        return (l>r);

    }//removal_on_from_the_center.operator()(const Rect& )

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


unsigned char mytolower_uchar(unsigned char st)
{
    return static_cast<unsigned char>(tolower(static_cast<int>(st)));

}//*/

 char mytolower_char( char st)
{
    return static_cast<char>(tolower(static_cast<int>(st)));

}//*/

 std::string& mytolowerString( std::string& st)
 {

     for (std::string::iterator it = st.begin() ; it != st.end(); it ++ )
         *it = tolower(*it);
     return st;
 }

class predMytolower
{
    std::string m_st;

    public:
    predMytolower()
    {
        m_st="str";
    }

    std::string operator()( std::string& st )
    {
       for ( std::string::iterator it = st.begin() ; it != st.end(); ++it )
       {
           *it = tolower(static_cast<char>(*it));

       }
        m_st=st;
        return m_st;
    }

};//*/

class compareFirstCh3
{
    char m_ch;
    public:
    compareFirstCh3(char ch)
    {
      m_ch=ch;
    }

    bool operator()( std::string& stl )
    {// вызов по n = 8

       //std::cout<<"\ninput oper() stl: " <<stl;
       if(stl[0]==m_ch)
       {
           // std::cout<<"-->> stl[0]:" <<stl[0]<<" ch "<<m_ch<<" is TRUE)  ";
            return true;
       }

      // std::cout<<"-->> stl[0]:" <<stl[0]<<" m_ch "<<m_ch<<" is FALSE)  ";
       return false;
    }
};

class UnaryPredicateIsEven
{
    bool  m_b;
    public:
    UnaryPredicateIsEven(bool b)
    {
        m_b=b;
    }

     bool operator()(const std::pair<std::string,int>& r )
     {
         if((r.second % 2) == 0 )
         {
             return (m_b)?true:false;
         }

         return (m_b)?false:true;
     }
};

// перегрузка пары
////////////////////////////////////////////////////////////////////////////////////////////
/*template <typename T, typename TT>
std::ostream& operator <<(std::ostream& out, std::pair<T, TT>& p)
{
    out << p.first << " : ";
   for (typename TT::iterator i = p.second.begin(); i != p.second.end(); ++i)
       out << *i << ": ";
   return out;
}*/

template <typename T, typename TT>
std::ostream& operator <<(std::ostream& out, std::pair<T, TT>& p)
{
    out << "\n{ " << p.first << " : ";
    out << p.second << "}";

    return out;
}

template <typename T, typename TT> void printContM(std::multimap<T, TT>& t)
{
    std::cout << "\nContainer multimap,pair use operator<<:";
    for (typename std::multimap<T, TT>::iterator it = t.begin(); it != t.end(); ++it)
    {
        std::pair<T, TT> p = (*it);
        std::cout << p;
    }

}

template <typename T, typename TT> void printContM(std::map<T, TT>& t)
{
    std::cout << "\nContainer multimap, pair use operator<<:";
    for (typename std::multimap<T, TT>::iterator it = t.begin(); it != t.end(); ++it)
    {
        std::cout << *it;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////

