/*
template <class Predicate>
  void remove_if (Predicate pred);

Remove elements fulfilling condition
Removes from the container all the elements for which Predicate pred returns true. This calls the destructor of these objects and reduces the container size by the number of elements removed.

The function calls pred(*i) for each element (where i is an iterator to that element). Any of the elements in the list for which this returns true, are removed from the container.

Parameters

pred
    Unary predicate that, taking a value of the same type as those contained in the forward_list object, returns true for those values to be removed from the container, and false for those remaining.
    This can either be a function pointer or a function object.

*/

// list::remove_if
#include <iostream>
#include <list>

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};

int main (int,char**)
{
  int myints[]= {15,36,7,17,20,39,4,1};
  std::list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

  mylist.remove_if (single_digit);           // 15 36 17 20 39

  mylist.remove_if (is_odd());               // 36 20

  std::cout << "mylist contains:";
  for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
