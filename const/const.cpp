#include <stdio.h>
#include <iostream>
using namespace std;

int a = 10;
const int * p1 = &a; // указатель на константу
int const * p2 = &a; // указатель на константу

const int ii(1);
int const jj(1);
int const kk=1;
/*
const char * a = "a";
a="b";// меняем адрес хранящейся в 'a' на адресс строки!

char const * c = "a";
c="b";// меняем адрес хранящейся в 'a' на адресс строки!

char * const g = "a";
g="b"; // <-- НЕ РАБОТАЕТ

*a = 'Y';// ситуация диаметрально противоположне, присваеваем значение
*/
int main()
{

//	*p1 = 20; // ошибка
	p2 = 0; // ОК
//-------------------------------
	int M = 10; int N = 4; 
	const int * const *m = new int*[N]; // а не const int** m; ( ? почему)
	for(int i=0;i<N;i++)
		m[i] = new int[M]; // error!


	for(int i=0;i<N;i++)
		for(int j = 0; j<M; j++)
			m[i][j] = i+j;

	for(int i = 0; i<N; i++)
		delete [] m[i];
	delete [] m;
	
	m=0;

	return 0;
}