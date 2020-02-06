// lab6 RTTI

#include <iostream>
#include <fstream>

void mystop()
{
        std::cout << "\nPause\n";
        getchar();
}

#define  stop  {mystop();}

#include "myRect.h"
#include "Circle.h"
#include "List.h"

List test();
int main(int argc, char* argv[])
{
	List list;

	list.AddHead(&Circle(1, 1, 1, RED));
	list.AddHead(&Circle(10, 10, 10, RED));
	list.AddHead(&Circle(10, 10, 100, GREEN));
	list.AddHead(&Rect(2,2,2,2,GREEN));
	list.AddTail(&Rect(3, 3, 3, 3, GREEN));
	list.AddTail(&Rect(3, 3, 3, 3, BLUE));
	list.AddTail(&Rect(3, 3, 3, 3, BLACK));
	list.AddTail(&Rect(3, 3, 3, 3, BLACK));

	std::cout << "\nlist:--------------------------";
	std::cout<<list;

	list.RemoveOne(&Rect(3, 3, 3, 3, GREEN));
	std::cout << "\nlist after remove:--------------------";
	std::cout << list;

	List list2;
	list2 = list;

	std::cout << "\nlist2:--------------------------";
	std::cout << list2;

	list2.Sort();
	std::cout << "\nSort list by square:-----------------------";
	std::cout << list2;

	std::ofstream fout("list.txt");
	fout << "\nsort list:\n" << list2 << std::endl;
	fout.close();

	List list3 = list;
	std::cout << "\nlist3:--------------------------";
	std::cout << list3;

	list3.RemoveAll(&Rect(3, 3, 3, 3, BLACK));
	std::cout << "\nlist3 after all remove:------------------------";
	std::cout << list3;

	list3.Cleaning();
	std::cout << "\nlist3 after cleaning:--------------------------";
	std::cout << list3;

	List list5 = test();

	std::cout << "\nlist5 after move:--------------------------";
	std::cout << list5;

	List list6;
	list6 = test();

	std::cout << "\nlist6 after copy move:--------------------------";
	std::cout << list6;

	List l;
	std::ifstream fin;
	fin.open("..\\lab6\\list.txt");

	if (fin.is_open())
	{
		std::cout << "\nfile is opened";
		while (!fin.eof())
		{			
			fin >> l;			
		}
	}
	else std::cout << "\nfile open is error";

	fin.close();
	std::cout <<"\nList read--------------------\n";
	std::cout << l << "";

	std::cout << "\nList source: size ="<< list5.Size() <<"";
	std::cout << list5 << "";
	l = list5;
	std::cout << "\nList copy: size =" << l.Size() << "";
	std::cout << l << "";

	l.Sort(COL);
	std::cout << "\nSort list by color:-----------------------";
	std::cout << l;

	List l1;

	l1.AddTail(&Circle(1, 1, 1, RED));
	l1.AddTail(&Rect(10, 10, 10,10, RED));
	l1.AddTail(&Circle(10, 10, 100, GREEN));
	l1.AddTail(&Circle(10, 10, 100, GREEN));

	List l2;

	l2.AddHead(&Circle(12, 12, 112, RED));
	l2.AddHead(&Rect(11, 11,111, 111, RED));
	l2.AddHead(&Rect(11, 11, 111,111, GREEN));
	l2.AddHead(&Rect(11, 11, 111, 111, BLUE));
	l2.AddHead(&Rect(11, 11, 111, 111, YELLOW));
	std::cout << "\nl2 :-----------------------";
	std::cout << l2;
	l1 = l2;
	std::cout << "\nl1 after copy:-----------------------";
	std::cout << l1;


	return 0;
}//endmain

List test()
{
	List list4;
	list4.AddTail(&Circle(5, 5, 555));
	list4.AddTail(&Circle(4, 4, 444));
	list4.AddHead(&Rect(5, 5,5, 5));
	list4.AddHead(&Rect(5, 5, 5, 5,BLACK));
	list4.AddHead(&Rect(4, 4, 4, 4));
	list4.AddHead(&Circle(5, 5, 111));
	list4.AddHead(&Circle(5, 5, 111,GREEN));

	return list4;
}
