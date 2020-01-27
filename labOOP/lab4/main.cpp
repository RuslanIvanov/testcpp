#include <iostream>
#include <fstream>

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
		std::cout << "\nlist2--------------";
		std::cout << list2;
		List ll = std::move(list2);
		std::cout << "\nList after move--------------";
		std::cout << ll;

		List lll;
		List list3;
		list3.AddTail(Circle(5, 5, 55));
		list3.AddTail(Circle(4, 4, 44));
		list3.AddHead(Circle(5, 5, 33));
		list3.AddHead(Circle(4, 4, 22));
		list3.AddHead(Circle(5, 5, 11));
		std::cout << "\nlist3--------------";
		std::cout << list3;
		lll = std::move(list3);
		std::cout << "\nList after copy move--------------";
		std::cout << lll;
		stop
	}
#else
	std::cout << "\nList after move--------------";
	test().out();
	std::cout << test();
#endif

	List list9;
	list9.AddTail(Circle(5, 5, 5));
	list9.AddTail(Circle(4, 4, 4));
	std::cout << "\nlist9--------------";
	std::cout << list9;
	List list7 = list9;
	list7.AddTail(Circle(5, 5, 5555));
	list7.AddTail(Circle(4, 4, 4444));
	list7.AddHead(Circle(5, 5, 3333));

	std::cout << "\nlist7--------------";
	std::cout << list7;

	List list6;
	list6.AddTail(Circle(5, 5, 55555));
	list6.AddTail(Circle(4, 4, 44444));
	list6.AddHead(Circle(5, 5, 43333));
	std::cout << "\nList6----------------------";
	std::cout << list6;
	list6 = list7;//list7 > list6
	std::cout << "\nList6 after copy--------------";
	std::cout << list6;
	std::cout << "\nList9--------------------";
	std::cout << list9;
	list6 = list9;//list9 < list6
	std::cout << "\nList6 after copy--------------";
	std::cout << list9;
	List list10;
	list10 = list9;//list9 > list10
	std::cout << "\nList10 after copy--------------";
	std::cout << list10;

	List list11;
	list11.AddTail(Circle(5, 5, 4455));
	list11.AddTail(Circle(4, 4, 5544));
	std::cout << "\nList11 ---------------------";
	std::cout << list11;
	list11 = list9;//равны
	std::cout << "\nList11 after copy--------------";
	std::cout << list11;
	stop
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

	return list4;
}
