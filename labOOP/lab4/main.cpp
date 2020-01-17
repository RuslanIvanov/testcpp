#include <iostream>
#include <fstream>
//#include <tchar.h>

#include "Circle.h"
#include "List.h"

void mystop()
{
	std::cout << "\nPause\n";
	getchar();
}

#define  stop  {mystop();}
//#define TEST
List test();
int main(int argc, char* argv[])
{
	List list;

	list.AddHead(Circle(1, 1, 1));
	list.AddHead(Circle(2, 2, 2));
	list.AddHead(Circle(3, 3, 3));

	std::cout << "\n---------------------------------";
	std::cout << list;

	list.AddTail(Circle(5, 5, 5));
	list.AddTail(Circle(4, 4, 4));
	list.AddHead(Circle(5, 5, 5));

	std::cout << "\n---------------------------------";
	std::cout << list;

	list.Sort();
	std::cout << "\nSort list:-----------------------";
	std::cout << list;

	std::ofstream fout("list.txt");
	fout << "\nsort list:\n" << list << std::endl;
	fout.close();

	list.RemoveAll(Circle(5, 5, 5));
	std::cout << "\n---------------------------------";
	list.RemoveAll(Circle(1, 1, 1));
	std::cout << list;

	list.Cleaning();

	std::cout << "\nCleaning:-------------------------";
	std::cout << list;
#ifndef TEST
	{
		List list2;
		list2.AddTail(Circle(5, 5, 5));
		list2.AddTail(Circle(4, 4, 4));
		list2.AddHead(Circle(5, 5, 3));
		list2.AddHead(Circle(4, 4, 2));
		list2.AddHead(Circle(5, 5, 1));

		List ll = std::move(list2);
		std::cout << "\nList after move1--------------";
		test().out();
		std::cout << ll;

		List lll;
		List list3;
		list3.AddTail(Circle(5, 5, 55));
		list3.AddTail(Circle(4, 4, 44));
		list3.AddHead(Circle(5, 5, 33));
		list3.AddHead(Circle(4, 4, 22));
		list3.AddHead(Circle(5, 5, 11));
		lll = std::move(list3);
		std::cout << "\nList after move2--------------";
		std::cout << lll;
		stop
	}
#else
	std::cout << "\nList after move--------------";
	test().out();
	std::cout << test();

	stop
#endif
	return 0;

}

List test()
{
	List list4;
	list4.AddTail(Circle(5, 5, 555));
	list4.AddTail(Circle(4, 4, 444));
	list4.AddHead(Circle(5, 5, 333));
	list4.AddHead(Circle(4, 4, 222));
	list4.AddHead(Circle(5, 5, 111));
	//List list5 = list4;
	return list4;
}
