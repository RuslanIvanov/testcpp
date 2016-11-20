#include <iostream>
#include <stdio.h>
using namespace std;

/*
Sample Input:
15 26 1 42 0
Sample Output:
42 1 26 15
*/

void invert()
{
	int i; // исп. не char  т.к. работа с числами, а не символами
	cin>>i;

	if(i==0)
	{
		return;
	}


	invert();
	cout<<i<<" ";
}

int main()
{
	invert();
	return 0;
}
