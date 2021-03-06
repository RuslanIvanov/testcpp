#include <iostream>

using namespace std;

struct A
{
 	A() { cout << "A()"; }
 	A(int) { cout << "A(int)"; }
 	void operator=(int) { cout << "="; }
};

struct B
{
 	A a, b;
 	B() : b(1) { a = 2; }
};

int main()
{
 	B b;
}

//Почему так происходит?
//члены класса инициализируются в порядке их объявления до входа в тело конструктора. Это значит, что при создании класса B сначала проинициализируется B::a
//с помощью конструктора A::A(), затем B::b - с помощью конструктора A::A(int), затем в теле конструктора B::B() вызовется operator=.
