/*
 * Класс Cls определен точно таким образом:
 *
 * struct Cls {
 * Cls(char c, double d, int i);
 * private:
 *     char c;
 *     double d;
 *     int i;
 * };
 *
 */

#include <stdio.h>
#include <iostream>
using namespace std;

struct Cls 
{
	Cls(char c, double d, int i)
	{
		this->c = c;
		this->d = d;
		this->i = i;
	}

	private:
    char c;
    double d;
    int i;
};


// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    /* ... */
	 return *(char*)(&cls);
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    /* ... */
	return *(double*)((char*)(&cls) + 8);
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
    /* ... */
	return *(int*)((char*)(&cls) + 16);
}

int main()
{
	/*3*8=24*/
	
	cout<<"size struct Cls "<<sizeof(struct Cls)<<endl;
	cout<<"size char "<<sizeof(char)<<endl;
	cout<<"size double "<<sizeof(double)<<endl;
	cout<<"size int "<<sizeof(int)<<endl;

	//компилятор выравнивет по границе 8 байт (?)
	Cls cls('S',2.2,333);

	cout<<get_c(cls)<<endl;
	cout<<get_d(cls)<<endl;
	cout<<get_i(cls)<<endl;
	
	return 0;
}

/*
подсказака
char &get_c(Cls &cls) {
    return *(char*)(&cls);
}
 
 
double &get_d(Cls &cls) {
    return *(double*)((char*)(&cls) + 8);
}
 
 
int &get_i(Cls &cls) {
    return *(int*)((char*)(&cls) + 16);
}
*/