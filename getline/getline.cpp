#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char *getline();

int main(int argc, char *argv[])
{
	char *prez = getline();

	cout<<endl;

	cout<<"\nrez: "<<prez<<endl;

	delete [] prez;
	prez=0;

	return 0;
}

char *getline()
{
	int size=3;

	char *pout = new char[size];
	cout<<"size = "<<size<<endl;

	int c=0; char cc;
	while(/*cin.get(cc)*/!cin.eof())
	{
		if(c>=(size-1)) 
		{
			char *p = pout;
			int oldsize=size;	

			size+=size;
			cout<<"new size = "<<size<<" c= "<<c<<endl;
			char *pout = new char[size];

			for(int i=0;i<oldsize; i++)
			{
				pout[i] = p[i];
			}
			//pout[oldsize]  = '\0';

			delete [] p; p=0;

		} 
		
		pout[c] = cin.get();//cc;

		if(pout[c] == '\n' /*|| cin.eof()*/)
		{cout<<"[ c="<<c<<" ]"<<endl; break;}

		c++;
	}

	cout<<"endsize = "<<size<<endl;
	pout[c]  = '\0';

	return pout;
}

