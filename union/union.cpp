#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
void binary (unsigned char ch) 
{
    union 
    {
        unsigned char ss;              
        struct 
        {
            unsigned a0:1;
            unsigned a1:1;
            unsigned a2:1;
            unsigned a3:1;
            unsigned a4:1;
            unsigned a5:1;
            unsigned a6:1;
            unsigned a7:1;
        } byte;
    } cod;

	cod.ss = ch;      //занесение в объединение значения параметра
    	cout <<"  bity =  ";
                                         // вывод бит
	cout <<" "<<cod.byte.a7<<" "<<cod.byte.a6  
        <<" "<<cod.byte.a5<<" "<<cod.byte.a4 
        <<" "<<cod.byte.a3<<" "<<cod.byte.a2 
        <<" "<<cod.byte.a1<<" "<<cod.byte.a0<<endl;

	cod.byte.a7=~cod.byte.a7;

	    cout<<"invert 8 bit: ";

	cout <<" "<<cod.byte.a7<<" "<<cod.byte.a6  
        <<" "<<cod.byte.a5<<" "<<cod.byte.a4 
        <<" "<<cod.byte.a3<<" "<<cod.byte.a2 
        <<" "<<cod.byte.a1<<" "<<cod.byte.a0<<endl;


}

int main()
{

	binary(0x33);
	return 0;
}
