#include <stdio.h> 
#include <iostream>
using namespace std;

struct Expression
{
    double evaluate() const = 0;
};

struct Number : Expression
{
    Number(double value) : value(value)
    {}

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

    { }

private:

    Expression const * left;

    Expression const * right;

    char op;

};

int main(int argc, char * argv[])
{
	return 0;
}
