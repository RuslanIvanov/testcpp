#ifndef TEMPL_H
#define TEMPL_H
#include <iostream>
#include <vector>
#include <queue>

template <typename T> void printCont(const T& t)
{
    std::cout<<"\nContainer:";
    for(typename T::const_iterator i = t.begin(); i != t.end(); ++i)
    {
        std::cout<< *i << " ";
    }

}

template </*typename Q*/> void printCont<std::queue<int>>(const std::queue<int>& t)
{
    std::cout<<"\nContainer queue: ";
    while(!t.empty())
    {
        std::cout<<t.front();
        t.pop();
    }

}

/*template <typename Q> void printCont<std::queue<Q>>(const std::queue<Q>& t)
{
    std::cout<<"\nContainer queue:";
    while(!t.empty()) 
    {
        std::cout<<t.top();
        t.pop();
    }

}*/


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

#endif // TEMPL_H
