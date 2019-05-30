#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
typedef struct
{
    const static int d = 2;
} FOO3; */


struct FOO2
{
    const static int d = 2;
};

struct Foo
{
    const static int d = 2;
};

//int Foo::d = 0;
Foo foo;
FOO2 foo2;
//FOO3 foo3;
int main()
{

	int a = Foo::d;
	int b = FOO2::d;
	//int c = FOO3::d;
	printf("Hello world %d %d", a, b);
	return 1;
}
