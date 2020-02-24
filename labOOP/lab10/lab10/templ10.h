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
    return static_cast<unsigned char>(std::tolower(static_cast<int>(st)));

}//*/

 char mytolower_char( char st)
{
    return static_cast<char>(std::tolower(static_cast<int>(st)));

}//*/

 std::string& mytolowerString( std::string& st)
 {

     for (std::string::iterator it = st.begin() ; it != st.end(); it ++ )
         *it = std::tolower(*it);
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
           *it = std::tolower(static_cast<char>(*it));

       }
        m_st=st;
        return m_st;
    }

};//*/


class compareFirstCh
{
    std::vector<std::string> m_v;
    int count;
    public:
    compareFirstCh(std::vector<std::string> &v)
    {
      m_v=v;
      count=0;
      std::cout<<"\nm_v.size() = " << m_v.size();
    }

    bool operator()( std::string& stl )
    {// вызов по n = 8
        std::cout<<"\ninput oper() stl: " <<stl;
        for(size_t i=0;i<m_v.size();i++)
        {
            std::cout<<"\n#" <<i+1;
            if(stl[0]==m_v[i][0])
            {
                std::cout<<"-->> (stl[0]:" <<stl[0]<<" m_v "<<m_v[i][0]<<" is TRUE)  ";
                //return true;
                count++;
            }else  std::cout<<"-->> (stl[0]:" <<stl[0]<<" m_v "<<m_v[i][0]<<" is FALSE)  ";

        }

        if(count>0) return true;

        return false;
    }
};


class compareFirstCh2
{
   std::vector<std::string> m_v;
   public:
    compareFirstCh2(std::vector<std::string> &v)
    {
      m_v=v;
    }

    bool operator()(std::vector<std::string> &v )//std::string& stl/*,  std::string& str*/)
    {

        for(size_t i=0;i<m_v.size();i++)
        {
            for(size_t i=0;i<v.size();i++)
            if(v[i][0]>m_v[i][0])
            {
                std::cout<<"\n( stl[0]= " <<v[i][0]<<" m_v = "<<m_v[i][0]<<")";
                return true;
            }

        }

        return false;
    }
};

class compareFirstCh3
{
    char m_ch ;
    int cout;
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


