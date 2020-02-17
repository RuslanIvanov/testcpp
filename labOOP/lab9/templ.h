#ifndef TEMPL_H
#define TEMPL_H
#include <iostream>

class classcomp_key
{

    public:
        classcomp_key() {}
        bool operator()(const char *x, const char *y) const
        {
            if((x!=nullptr) && (y!=nullptr))
                return x[0] < y[0];
            else
                return false;
        }

};


class L
{
    public:
    bool operator()(const char *x, const char *y)
   {
    return strcmp(x, y)<0;
   }

};

struct myless_str
{
    bool operator()(const char* l,const char* r) const
    {
       // std::cout<<"\n myless_str: '"<<l<<"'' '"<< r<<"'";
        return (strcmp(l,r)>=0);
    }

};

struct classcomp
{
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs>rhs;}

};


////////////////////////////////////////////////////////////////////////
template <typename T> void printCont(const T& t)
{
    std::cout<<"\nContainer: \n";
    for(typename T::const_iterator i = t.begin(); i != t.end(); ++i)
    {
        std::cout<< *i << " ";
    }

}

template <typename T,typename TT,typename C> void printCont(std::map<T,TT,C>& t)
{
    std::cout<<"\nContainer map: \n";
    for(typename std::map<T,TT>::const_iterator i = t.begin(); i != t.end(); ++i)
    {
       std::cout<<"|"<< (*i).first << " : "<< (*i).second;
    }

}

template <typename T,typename TT> void printCont(std::map<T,TT>& t)
{
    std::cout<<"\nContainer map: \n";
    for(typename std::map<T,TT>::const_iterator i = t.begin(); i != t.end(); ++i)
    {
       std::cout<<"|"<< (*i).first << " : "<< (*i).second;
    }

}

template <typename T> void printCont(/*const*/ std::queue<T>& q)
{
   std::cout<<"\nContainer QUEUE is: ";

   if(q.empty()==true)
   {
       std::cout<< "EMPTY";
       return ;
   }
   std::cout << '\n';

    while(!q.empty())
    {
        std::cout<<"|"<<q.front();
        q.pop();
    }

}

template <typename T> void printCont( std::priority_queue<T*,std::vector<T*>,myless_str>& q )
{
   std::cout<<"\nContainer_vector priority QUEUE & less is: ";

   if(q.empty()==true)
   {
       std::cout<< "EMPTY";
       return ;
   }

   std::cout << "\n q.size() = " << q.size()<< "\n";

   while(!q.empty())
   {
        std::cout<<"|"<<q.top();
        q.pop();
   }

}

template <typename T> void printCont(std::queue<T*,std::list<T*>>& q )
{
   std::cout<<"\nContainer_list QUEUE is: ";

   if(q.empty()==true)
   {
       std::cout<< "EMPTY";
       return ;
   }

   std::cout << "\n q.size() = " << q.size()<< "\n";

   while(!q.empty())
   {
        std::cout<<"|"<<*q.front();
        q.pop();
   }

}//*/

template <typename T> void printCont(/*const*/ std::stack<T>& s)
{
    std::cout<< "\nContainer STACK is: ";
    if(s.empty()==true)
    {
        std::cout<< "EMPTY";
        return ;
    }

    std::cout << '\n';
    while(!s.empty())
    {
        std::cout <<"|"<<s.top()<<"|";
        s.pop();
    }

}

template <typename T> void printCont(/*const*/  std::priority_queue<T>& pq)
{
    std::cout<< "\npriority_queue is: ";
    if(pq.empty()==true)
    {
        std::cout<< "EMPTY";
        return ;
    }

    std::cout<< "\n";
    while(!pq.empty())
    {
        std::cout <<"|"<<pq.top();
        pq.pop();
    }

}

///////////////////////////////////////////////////////
template<typename T> void print_queue(T& q)
{
     std::cout<< "\nQUEUE is ";
    if(q.empty()==true)
    {
        std::cout<< "EMPTY";
        return ;
    }
    std::cout << '\n';
    while(!q.empty())
    {
        std::cout <<"|"<<q.front();
        q.pop();
    }

}

template <typename T>void print_stack(T& s)
{
    std::cout<< "\nSTACK is: ";
    if(s.empty()==true)
    {
        std::cout<< "EMPTY";
        return ;
    }

    std::cout << '\n';
    while(!s.empty())
    {
        std::cout <<"|"<<s.top();
        s.pop();
    }


}

template <typename T>void print_priority_queue(T& pq)
{

    std::cout<< "\npriority_queue is: ";
    if(pq.empty()==true)
    {
        std::cout<< "EMPTY";
        return ;
    }

    std::cout<< "\n";
    while(!pq.empty())
    {
        std::cout <<"|"<<pq.top();
        pq.pop();
    }


}
////////////////////////////////////////////////////////////
#endif // TEMPL_H
