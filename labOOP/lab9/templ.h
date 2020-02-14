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
/*
template <typename Q> void printCont<std::queue<Q>>(const std::queue<Q>& t)
{
    std::cout<<"\nContainer queue:";
    while(!t.empty())
    {
        std::cout<<t.front();
        t.pop();
    }

}*/

/*template <typename Q> void printCont<std::queue<Q>>(const std::queue<Q>& t)
{
    std::cout<<"\nContainer queue:";
    while(!t.empty()) 
    {
        std::cout<<t.top();
        t.pop();
    }

}*/


template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

#endif // TEMPL_H
