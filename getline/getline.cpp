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
	int size=10;

	char *pout = new char[size];
	cout<<"size = "<<size<<endl;

	int c=0; char cc;
	while(cin.get(cc))
	{
		if(c>=size) 
		{
			char *p = pout;
			int oldsize=size;	

			size+=size;//size = size+size;
			char *pout = new char[size];

			for(int i=0;i<oldsize; i++)
			{
				pout[i] = p[i];
			}
			pout[oldsize]  = '\0';

			delete [] p;

		} 
		
		pout[c] = cc;

		if(pout[c] == '\n')
		{
			pout[c]  = '\0';
			cout<<"nesize = "<<size<<endl;
			break;
		}

		c++;
	}

	return pout;
}

