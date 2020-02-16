#ifndef TEMPL_H
#define TEMPL_H
#include <iostream>

////////////////////////////////////////////////////////////////////////
template <typename T> void printCont(const T& t)
{
    std::cout<<"\nContainer:";
    for(typename T::const_iterator i = t.begin(); i != t.end(); ++i)
    {
        std::cout<< *i << " ";
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
        std::cout<<"|"<<q.front()<<"|";
        q.pop();
    }

}

template <typename T> void printCont(std::queue<T*,std::list<T*>>& q )
{
   std::cout<<"\nContainer* QUEUE is: ";

   if(q.empty()==true)
   {
       std::cout<< "EMPTY";
       return ;
   }

   std::cout << "\n q.size() = " << q.size()<< " ";

  // size_t n =q.size();
   size_t i=0;
   while(!q.empty())
   {
        std::cout<<"|"<<*q.front()<<"|";
        q.pop();

        i++;
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
        std::cout <<"|"<<pq.top()<<"|";
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
        std::cout <<"|"<<q.front()<<"|";
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
        std::cout <<"|"<<s.top()<<"|";
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
        std::cout <<"|"<<pq.top()<<"|";
        pq.pop();
    }


}
////////////////////////////////////////////////////////////
#endif // TEMPL_H
