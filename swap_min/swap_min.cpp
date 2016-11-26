#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int ** create_array2d(const int& rows, const int& cols) 
{
	int **m = new int* [rows];
	m[0] = new int [rows*cols];
	for(int i=1;i!=rows;i++)
	{m[i] = m[i-1]+cols;}

	return m;
}

void destroy(int** m_, const int& rows)
{
	delete[] m_[0];
	delete[] m_;
} 

void swap_min(int *m[], unsigned rows, unsigned cols)
{
    /* ... */
	int min=m[0][0];
	int rmin=0;
	for (int i = 0; i < rows; i++) 
    {
       	for (int j = 0; j < cols; j++)
       	{
				if(m[i][j]<min){min = m[i][j]; rmin=i;}
		}
    }

	//cout<<"addr: "<<m[0]<<" "<<m[rmin]<<endl;
	int *p=m[0];
	m[0] = m[rmin];
	m[rmin]=p;
	//cout<<"addr: "<<m[0]<<" "<<m[rmin]<<endl;
	//cout<<"min="<<min<<" rmin="<<rmin<<endl;
}

int rows;
int cols;
int main(int argc, char *argv[])
{
	srand(time(NULL));
	//rows=rand()%5;
	//cols=rand()%5;

	if(!rows) rows = 6;
	if(!cols) cols = 4;

	int **m = create_array2d(rows, cols);
	
    for (int i = 0; i < rows; ++i) 
    {
       	for (int j = 0; j < cols; ++j)
       	{m[i][j] = rand()%10;}
    }

	cout<<"m"<<"["<<rows<<","<<cols<<"]"<<endl;
	
	int *p = m[0];
	for(int i=0,j=0;i<rows*cols;i++)
	{cout<<*(p+i)<<" "; if(++j==cols){j=0; cout<<endl;}} cout<<endl;

	swap_min(m,rows,cols);

	cout<<"mnew:"<<endl<<endl;

	/*p = m[0];
	for(int i=0,j=0;i<rows*cols;i++)
	{cout<<*(p+i)<<" "; if(++j==cols) {j=0; cout<<endl; } }cout<<endl; error!!!
	*/

	for (int i = 0; i < rows; ++i) 
    {
       	for (int j = 0; j < cols; ++j)
       	{cout<<m[i][j]<<" ";}
		cout<<endl;
    }

	destroy(m, rows);
    
	cout<<endl<<"Press any key...";	
	getchar();
	return 0;
}


