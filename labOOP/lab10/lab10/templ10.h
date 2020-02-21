#pragma once

template <typename T> void printVect(const T& t)
{

    std::cout<<"|"<<t;

}
/*

template <> void printVect<int>(const int& t)
{

    std::cout<<"|"<<t;

}*/

template <typename T,typename TT> void changePoint(const T& t, TT t2)
{

   t = t2;

}
