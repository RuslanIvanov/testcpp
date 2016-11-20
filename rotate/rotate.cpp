#include <stdio.h>
#include <iostream>
using namespace std;

void swap(int *pa, int *pb)
{
	int m = *pb;
	*pb = *pa;
	*pa = m;
}

void rotate(int a[], unsigned size, int shift)
{
	//cout<<"shift: "<<shift<<" size: "<<size<<endl;
	for(int s=1; s<=shift; s++)
	for(int i=0; i<(size-1); i=i+1)
	{ 
		swap(&a[i],&a[i+1]);
	}
}

int main()
{

    int a[] = {1,2,3,4,5,6};
    int shift = 3;
    unsigned int size = sizeof(a)/sizeof(a[0]);

    cout<<"size: "<<size<<" old mass:"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<a[i]<<',';
    }
	cout << endl; cout << endl;
    rotate(a,size,shift);

    for(int i=0;i<size;i++)
    {
	cout<<a[i]<<'.';
    }
    cout << endl;
    return 0;
}
