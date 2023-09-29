//https://defuse.ca/exploiting-cpp-vtables.htm
#include <cstdlib>
#include <cstdio>
#include <cstring>
class Foo {
     public:
         void nv()
         {
             printf("Hello from a NON-VIRTUAL method in Foo!\n");
         }

         virtual void v()
         {
             printf("Hello from a VIRTUAL method in Foo!\n");
         }
};

class FooBar : public Foo {
     public:
        void nv()
         {
             printf("Hello from a NON-VIRTUAL method in FooBar!\n");
         }

         virtual void v()
         {
             printf("Hello from a VIRTUAL method in FooBar!\n");
         }
};

class cBaseThread
{
	public:

	cBaseThread(){ printf("\n cBaseThread \n"); }
	virtual void task()=0;
};

class c_socket: public  cBaseThread
{
	public:

	c_socket(){ printf("\n c_socket \n"); }
	void task()=0;
};

class c_can: public c_socket
{
	public:

	c_can(){ printf("\n c_can \n"); }
	void task() { printf("\n task \n"); }
};


int main(int argc, char **argv)
{
    FooBar foobar;
    Foo foo;
 
     foobar.nv();    // FooBar::nv()
     foobar.v();     // FooBar::v()

     Foo *fooptr = (Foo *)&foobar;
     fooptr->nv();   // Foo::nv()    <--- here's the difference
     fooptr->v();    // FooBar::v()

     printf("---------\n");

     // FooBar is just a pointer to the FooBar vtable.
     // Foo is just a pointer to the Foo vtable.
     printf("sizeof(foobar) = %d, sizeof(foo) = %d\n", sizeof(foobar), sizeof(foo));

     long *foobarAsLong = (long *)&foobar;
     long *fooAsLong = (long *)&foo;
     printf("FooBar vtable pointer: %p\n", foobarAsLong[0]);
     printf("Foo vtable pointer: %p\n", fooAsLong[0]);

     long **foobarVtable = (long **)&foobar;
     long **fooVtable = (long **)&foo;
     // This is the address of FooBar::v()
     printf("First entry of FooBar VTABLE: %p\n", foobarVtable[0][0]);
	     // This is the address of  Foo::v()
     printf("First entry of Foo VTABLE: %p\n", fooVtable[0][0]);

     // If FooBar had more than one virtual method, then you would access the
     // second's address with foobarVtable[0][1], the third's with
     // foobarVtable[0][2], and so on.


	c_can can;

	cBaseThread *pth = new c_can;

	pth->task();

	delete pth;

	can.task();
}
