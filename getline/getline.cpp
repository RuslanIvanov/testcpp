#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char *getline();

int main(int argc, char *argv[])
{
	char *prez = getline();

	//cout<<endl;

	//cout<<"\nrez: "<<prez<<endl;
	//printf("\nrez: %s",prez);

	delete [] prez;
	prez=0;

	return 0;
}

char *getline()
{
	int size=3;

	char *pout = new char[size+1];
	//cout<<"size = "<<size<<endl;

	int c=0; char cc;
	while(!cin.eof())
	{
		if(c>(size-1)) 
		{
			char *p = pout;
			int oldsize=size;	
			size+=size+1;
			//cout<<"new size = "<<size<<" c= "<<c<<endl;
			pout = new char[size];

			for(int i=0;i<oldsize; i++)
			{
				pout[i] = p[i];
			}
			//pout[oldsize]  = '\0';

			delete [] p; p=0;

		}

		//pout[c] = cin.get();
		//cin>>pout[c];
		cin.get(pout[c]);

		if(pout[c] == '\n')
		{
			//cout<<"[ c="<<c<<" ]"<<endl;
			break;
		}
		c++;
	}

	//cout<<"endsize = "<<size<<endl;
	pout[c]  = '\0';

	return pout;
}

