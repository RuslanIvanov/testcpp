#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARE(x) (x)*(x) //макроопределение
inline double Square(double x) { return x*x;} //встроенная функцияГлава 8
int x = 2.2;

#define SUM1(x,y) x + y
#define SUM2(x,y) (x + y)

void SetAddrAD_AO(void *p[2], int N) 
{ 	
	void *m_mars[2];
	memset(m_mars,0,sizeof(m_mars[0])*2);

//	for(int i=0;i<N;i++) { m_mars[i] = p[i]; }

	printf("\n%p %p", m_mars[0], m_mars[1]);
	printf("\n%s %s", (const char*)m_mars[0], (const char*)m_mars[1]);
}

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

	void *p[2] = {(void*)"aa",(void*)"bb"};
	SetAddrAD_AO(p, 2);
}
