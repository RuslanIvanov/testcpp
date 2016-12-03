#include <stdio.h>
#include <iostream>
using namespace std;

class A 
{
private:
	int x;
public:
	
A(int a) 
{
	x = a;
	cout << "A(int) // x=" << x << endl;
}
  
void f() 
{
    cout << "f() // x=" << x << endl;
}

void f() const 
{
    cout << "f() const // x=" << x << endl;
}

};

int main(int argc, char *argv[])
{
	A a1(1);
	a1.f();
	A const a2(2);
	a2.f();

	return 0;
}


