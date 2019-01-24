#include <typeinfo> // Для std::bad_cast
#include <iostream> // Для std::cerr и др.

class A
{
public:
	// Механизм динамической идентификации типа данных доступен только для полиморфных 
	// классов (т.е. классов, содержащих хотя бы одну виртуальную функцию-член)
	virtual void foo();

	// другие члены класса...
};

class B : public A
{
public:
	void methodSpecificToB();

	// другие члены класса...
};

void my_function(A& my_a)
{
	try
	{
		B& my_b = dynamic_cast<B&>(my_a);
		my_b.methodSpecificToB();
	}
	catch (const std::bad_cast& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Этот объект не является объектом типа B" << std::endl;
	}
}

int main()
{

	A my_a;
	my_function(my_a);
	return 0;
}
