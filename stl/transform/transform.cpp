#include <set>
#include <list>
#include <algorithm>
#include <iostream>

template <typename T> void printCont(const T& t)
{
    std::cout<<"\nContaine_r: \n";
    for(typename T::const_iterator i = t.begin(); i != t.end(); ++i)
    {
        std::cout<< *i << " ";
    }

}


int modify(int i)
{
 return 2*i;
}

int main (int args, char** argv)
{
  std::set<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);

  std::list<int> b;  // change to set here

 // std::transform(a.begin(), a.end(), b.begin(), modify);   // line 19
   std::transform(a.begin(), a.end(), std::inserter(b, b.begin()), modify);


  printCont(a);

  printCont(b);

}

//std::transform(a.begin(), a.end(), std::inserter(b, b.begin()), modify);
