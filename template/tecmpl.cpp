#include <iostream>
#include <unistd.h>
#include <stdlib.h>

template<typename T> void foo(T) { std::cout<<" 1 "; }  // 1
template<> void foo(int*) { std::cout<<" 2 ";  }         // 2
template<typename T> void foo(T*){ std::cout<<" 3 "; } // 3

template<typename T> void bar(T){ std::cout<<" 4 "; }  // 4
template<typename T> void bar(T*){std::cout<<" 5 "; } // 5
template<> void bar(int*){ std::cout<<" 6 "; }         // 6

void f();

int main (int,char**)
{
	f();

	return 0;
}

void f()
{
	int i;
	foo(&i);
	bar(&i);
}
