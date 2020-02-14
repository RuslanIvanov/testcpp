#ifndef TEMPL_H
#define TEMPL_H

template <typename T> void printCont(const T& t)
{
    std::cout<<"\nContainer:";
    for(size_t i = 0; i < t.size(); i++)
    {
        std::cout<<t[i];
    }

}

template <class T> void printCont<queue>(const T& t)
{
    std::cout<<"\nContainer:";
    for(size_t i = 0; i < t.size(); i++)
    {
        std::cout<<t.top();
    }

}

#endif // TEMPL_H
