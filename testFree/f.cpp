#include <iostream> 
using namespace std; 

void f(double) { cout << "f1" << endl; } 

void f(const int ) { cout << "f2" << endl; } 

//void f( int & ) { cout << "f3" << endl; } //  неоднозначность при попытке вызова

int main() {
   int n = 1;
   double b = 2;
   f(n);
   f(b);

   	int a = 3; int c = 2;
   	a*=b+=c; //b=b+c = 4; a=a+b; 3*4 =12

	cout << "a="<<a<< endl;

	return 0;
}
