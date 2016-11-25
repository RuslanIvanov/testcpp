#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
int ** transpose(const int *m, unsigned rows, unsigned cols);
const int rows = 2;
const int cols = 3;
int main(int argc, char *argv[])
{
	int m[rows][cols] = { {1,2,3},{4,5,6} };

	cout<<"m:"<<endl;
	
	int *p = m[0];
	for(int i=0;i<rows*cols;i++)
	{
		cout<<*(p+i);
	}
	cout<<endl;

	int **T = transpose(&m[0][0],rows,cols);

	cout<<"mT:"<<endl<<endl;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			cout<<T[i][j];
		cout<<endl;		
	}

	delete [] T[0];
	delete [] T;

	cout<<endl<<"Press any key...";	
	getchar();
	return 0;
}

int ** transpose(const int* m, unsigned rows, unsigned cols)
{
    	/* ..a[i,j] = a[j,i].. */
		/*
		A = {1,2,3} 
			{4,5,6}  A^T =  {1, 4}
						    {2, 5}
							{3, 6}	
		*/
	/* in mem:
		A = {1,2,3,4|5,6,7,8}
	   AT= {1,5,2,6|3,7,4,8}
	*/
	int **T = new int* [rows];
	T[0] = new int [rows*cols];
	for(int i=1;i!=rows;i++)
	{
		T[i] = T[i-1]+cols; 
	}

	for(int mem=0;mem<(cols*rows)/2;mem++)
	{
		*T+mem = *(m+mem+cols);
	}

	//for(int a=0;a<rows;a++)
	//	for(int b=0;b<cols;b++)
	//{T[a][b] = *((m+a) + b);}

	return T;

	
}
