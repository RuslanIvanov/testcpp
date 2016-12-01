#include <iostream>

struct Cls {
  Cls(char c, double d, int i) : c( c ), d( d ), i( i ) {}
  private:
      char c;
      double d;
      int i;
  };



 struct B {
  B(char c, double d, int i) : c1( c ), d1( d ), i1( i ) {}
  public:
      char c1;
      double d1;
      int i1;
 };

char &get_c( Cls &cls ) 
{
    void *p = &cls;

    B *pb = static_cast<B *>( p );

    return pb->c1 = 'A';;
}


int main()
{
    Cls cls('h', 2.0, 3);
    char ch = get_c( cls) ;
    std::cout << ch << std::endl;

} 