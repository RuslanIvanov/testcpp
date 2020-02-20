// constructing maps
#include <iostream>
#include <map>
struct classcomp;
template <typename T,typename TT,typename C> void printCont(std::map<T,TT,C>& t)
{
    std::cout<<"\nContainer map: \n";
    for(typename std::map<T,TT>::const_iterator i = t.begin(); i != t.end(); ++i)
    {
       std::cout<<"|"<< (*i).first << " : "<< (*i).second;
    }

}


bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main (int,char**)
{
  std::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  std::map<char,int> second (first.begin(),first.end());

  std::map<char,int> third (second);


  std::map<char,int,classcomp> fourth;                 // class as Compare

 fourth['a']=10;
 fourth['b']=30;
 fourth['c']=50;
 fourth['d']=70;

  printCont(fourth);

  bool(*fn_pt)(char,char) = fncomp;
  std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

  return 0;
}
