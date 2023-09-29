#include <string.h>
#include <iostream> 
#include "./include/crcSoft.h"
const char* p[] = {"CRC read:","witch ","soft: ",NULL};
using namespace std;

int main()
{
 	cout <<""<< p[0]<<p[1]<<p[2]<<endl;

	for(size_t i=0;i<(sizeof(pCrcSoft)/sizeof(pCrcSoft[0]));i++)
	cout <<pCrcSoft[i]<<endl;

	return 0;
}
