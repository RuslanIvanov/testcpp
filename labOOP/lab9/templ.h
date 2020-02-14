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
//template <typename Q>
typename Q;
template <> void printCont<std::queue<Q>>(const <std::queue<Q>>& t)
{
    std::cout<<"\nContainer queue:";
    while(!t.empty()) 
    {
        std::cout<<t.top();
	t.pop()
    }

}

#endif // TEMPL_H
