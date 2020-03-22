//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86

#include <iostream>

class FooBar 
{
  public:
    explicit operator bool() const {
        return true;
    }
};

int main(int,char**)
{
    FooBar foo;
    FooBar bar;
    
    if (foo) std::cout << "foo\n";
    if (foo && bar) std::cout << "foo && bar\n";

	return 0;
}
