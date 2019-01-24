#include <iostream>

class A { virtual void func() {} };
class B : public A { };

int main()
{
   try
   {
       A a;
       B* b = dynamic_cast< B * >(&a);

       if( b )
           std::cout << "1";

       std::cout << "2";

       B & bRef = dynamic_cast< B & >(a);
       std::cout << "3";
   }
   catch( ... )
   {
   }

   return 0;
}
