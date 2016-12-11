#include <stdio.h>
#include <iostream>
using namespace std;

#define ISWORK

void foo(char) { std::cout << "char" << std::endl; }
void foo(signed char) { std::cout << "signed char" << std::endl; }
void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }
//--------------------------------------------------------------------
#ifndef ISWORK
void promotion(char &) { std::cout << "char" << std::endl; }
void promotion(int  &) { std::cout << "int"  << std::endl; }
void promotion(long &) { std::cout << "long" << std::endl; }
#else
void promotion(short &) { std::cout << "short" << std::endl; }
#endif

int main()
{
	cout<<"foo('a'): "<<endl;
	foo('a');
	//cout<<"foo(97): "<<endl;
	//foo(97);

	//----------------------------------------------------------

	short sh = 10;
	promotion(sh); 
	
	return 0;
}