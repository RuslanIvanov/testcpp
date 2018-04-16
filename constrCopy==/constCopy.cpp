#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
using namespace std;

struct A
{
	A();
	A(A& a);
	~A();
	size_t size;
};

struct B: public A
{
        B();
        B(B& b);
        ~B();
        size_t size;

};


A::A()
{
	size = 0;
	cout<<"A()"<<endl;

}

A::A(A& r)
{
	size=r.size;
	cout<<"A(A& r)"<<endl;
}

A::~A()
{
}

B::B()
{
        size = 0;
	cout<<"B()"<<endl;

}

B::B(B& r):A(r)// вызов конструктора копирования базового класса
{
        size=r.size;
 	cout<<"B(B& r)"<<endl;
}


B::~B() 
{
}

int main(int,char**)
{
	A a;
	B b;

	A aa = a;
	B bb = b;


	return 0;
}
