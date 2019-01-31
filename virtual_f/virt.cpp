#include <stdio.h> 
#include <iostream>
using namespace std;

struct Expression
{
   virtual double evaluate() const = 0;
   virtual ~Expression(){ std::cout << "~Expression()" << std::endl; }
};

struct Number : Expression
{
    Number(double value): value(value)
    {std::cout << "Number()" << std::endl;}
	virtual ~Number(){ std::cout << "~Number()" << std::endl;  }
	virtual double evaluate() const { return value; }

private:
    double value;
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */

    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    {std::cout << "BinaryOperation()" << std::endl;}

	virtual ~BinaryOperation(){ delete left; delete right; std::cout << "~BinaryOperation()" << std::endl; }
	virtual double evaluate() const 
	{ 
		switch(op)
		{
			case '+': return left->evaluate() + right->evaluate();
			case '-': return left->evaluate() - right->evaluate();
			case '*': return left->evaluate() * right->evaluate();
			case '/': return left->evaluate() / right->evaluate();
			default: return 0.0;
		}
	}

private:

    Expression const * left;
    Expression const * right;
    char op;

};

bool check_equals(Expression const *left, Expression const *right)

{

    	// put your code here

    	return (sizeof(*left)==sizeof(*right));

//	int p  = reinterpret_cast<int>(&left->evaluate);
//	int p2 = reinterpret_cast<int>(&right->evaluate);

	 return p == p2;
//	 return &left->evaluate == &right->evaluate;

}

int main(int argc, char * argv[])
{
	// сначала создаём объекты для подвыражения 4.5 * 5
	Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
	// потом используем его в выражении для +
	Expression * expr = new BinaryOperation(new Number(3), '+', sube);

	// вычисляем и выводим результат: 25.5
	std::cout << expr->evaluate() << std::endl;

	// тут освобождаются *все* выделенные объекты
	// (например, sube будет правым операндом expr, поэтому его удалять не нужно)
	delete expr;

	if(check_equals(new BinaryOperation(new Number(4.5), '*', new Number(5)),new BinaryOperation(new Number(4.5), '*', new Number(5))))//new Number(5))) 

		std::cout << "TRUE" << std::endl;

	else std::cout << "FLSE" << std::endl;

	if(check_equals(new BinaryOperation(new Number(4.5), '*', new Number(5)), new Number(5))) 

		std::cout << "TRUE" << std::endl;

	else std::cout << "FLSE" << std::endl;

	std::cout << "Press any key..." << std::endl;

	getchar();
	return 0;
}
