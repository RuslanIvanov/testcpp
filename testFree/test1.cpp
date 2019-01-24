#include <stdio.h>
#include <stdlib.h>

#define SQUARE(x) (x)*(x) //макроопределение
inline double Square(double x) { return x*x;} //встроенная функцияГлава 8
int x = 2.2;

#define SUM(x,y) x + y
#define SUM2(x,y) (x + y)

int main()
{
	int d = 9;
	int &r = d;

	int  a=0 ;
	if(a==0) printf("T ");
	if(a++>0) printf("T ");
	if(++a>0) printf("T");

	int b=0;
	printf("\nr=%i %d, %d\n",r,b++,++b);

	double res1 = SQUARE(x++);
	//параметр макроса будетинкрементирован дважды!
	double res2 = Square (x++); //параметр функции компиляторгарантированно модифицирует один раз!

	printf("\nres1 = %f, res2 =  %f",res1,res2);

	int aa=2; int bb=3;
	int c = SUM1(aa,bb) * 5; //X+Y*5
	int cc = SUM2(aa,bb) * 5; //(X+Y)*5

	printf("\nc=%d, %d",c,cc);

}
