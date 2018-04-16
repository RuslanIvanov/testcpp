#include <stdio.h>
#include <stdlib.h>

class AE
{
// ...
public:
	static const int c6 = 7;
    	static const int c7 = 31;

	static const char* namePkg[4]; //= {"0xbeef","Ethernet II","802.2","802.3"};
};

const int AE::c7;   // definition

const char* AE::namePkg[4] = {"0xbeef","Ethernet II","802.2","802.3"};


void p()
{
	for(int i=0;i<4;i++)
	printf("\n %s",AE::namePkg[i]);
}

int f()
{
//    const int* p1 = &AE::c6;    // error: c6 not an lvalue

    if(AE::c6 == 7) { printf("\nOK");}

    printf("\nc6 = %d",AE::c6);

    const int* p2 = &AE::c7;    // ok
    // ...
}

int main()
{
	f();
	p();
	return 0;
}
