#include <stdio.h>
#include <iostream>
using namespace std;

int N;
int a=2;
int b;
void log (int,int);
int main(int argc, char* argv[])
{
	cin>>N;

	for(int i=0;i<N;i++)
	{
		cin>>b;
		if(b<=0) continue;
		log(a,b);
	}

	return 0;
}

void log (int a,int b)
{	double rez=b; int i=0;
	for (;;)
	{
		rez=rez/a;
		if(rez>=1.0)
		{
			i++;
		}else break;
	}

	cout<<(i)<<endl;

}
