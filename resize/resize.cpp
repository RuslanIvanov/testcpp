#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char *resize(const char *str, unsigned size, unsigned new_size);

int main(int argc, char *argv[])
{
	int size=10;
	int newsize=11;

	if(argc == 3)
	{
		size = atoi(argv[1]);
		newsize = atoi(argv[2]);
	}

	cout<<"size = "<<size<<", newsize = "<<newsize<<endl;

	char *pstr = new char[size];
	memset(pstr, '*', size);
	char *prez = resize(pstr,size,newsize);

	cout<<endl;
	for(int i = 0; i<newsize; i++)
	{
		cout<<prez[i]<<",";
	}

	delete [] prez;
	prez=0;

	return 0;
}

char *resize(const char *str, unsigned size, unsigned new_size)
{
	/* ... */
	char *pnew = new char [new_size];

//	int n = (size<=new_size)?size:new_size;
	for(int i=0;( i<new_size && i<size );i++)
	{
		pnew[i] = str[i];
	}

	delete [] str;
	str = 0;

	return pnew;
}