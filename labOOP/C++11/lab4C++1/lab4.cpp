#include <stdlib.h>

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string.h>
#include <list>
#include <queue>
#include <stack>
#include <iterator>
#include <set>
#include <stddef.h>
#include <type_traits>

using namespace std;

#include "human.h"
#include "Header.h"

#if  _WIN32

#define	  stop __asm nop
#include <tchar.h>

#else

#define _tmain main
#define _TCHAR char 

void mystop()
{//Linux
	std::cout << "\nPause\n";
	getchar();
}

#define  stop  {mystop();}
#endif


int main(int,char**)
{
	std::string strings[] = {"ccc","abc", "123", "qwerty", "#$%","321"};
	auto DelStr = [](string*) { std::cout << "\nDelStr"; };

	std::shared_ptr<string> s1[] = {shared_ptr<string>(&strings[0], DelStr), shared_ptr<string>(&strings[1], DelStr),
										shared_ptr<string>(&strings[2], DelStr),shared_ptr<string>(&strings[3], DelStr),
										shared_ptr<string>(&strings[4], DelStr) ,shared_ptr<string>(&strings[5], DelStr) };
	std::shared_ptr<string> sh(&strings[0], DelStr);
	std::weak_ptr<string> wps(sh);

	{
		Point* point[3] = { new Point(0,0),new Point(0,0) ,new Point(0,0) };
		size_t ar[] = { 1,3,6,7,4,5,2 };
		vector<int> v = { 11,22,33,44,55 };
		list<string> l = {"s6","s7","s8","s9","s10"};
		deque<char> d = {'A','B','C'};
		set<short> s = {33,44,55};

		std::vector<std::string*> vs = { new std::string("aa"), new std::string("bb"), new std::string("cc") };


		std::unique_ptr<std::string* []>ptrV = make_unique<std::string* []>(3);
		ptrV[0] = new string("s1");
		ptrV[1] = new string("s11");
		ptrV[2] = new string("s111");

		PRINTF(point);
		PRINTF(ar);
		PRINTF(v);
		PRINTF(l);
		PRINTF(d);
		PRINTF(s);
		PRINTF(vs);
		//PRINTF(ptrV);//??

		PRINTF2(point);
		PRINTF2(ar);
		PRINTF2(v);
		PRINTF2(l);
		PRINTF2(d);
		PRINTF2(s);
		PRINTF2(vs);

		//PRINTF(ptrV);
		stop

		for (size_t i = 0; i < 3; i++)
		{
			delete point[i];
		}
	}

	/***************************************************************/
	//Задание 6. shared_ptr и weak_ptr
	//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
	//имя - string
	//возможно признак: жив или уже нет...
	//родители - shared_ptr (родители не всегда известны...)
	//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

	//Методы класса human:
	//конструктор - для инициализации имени и признака
	//конструктор копирования, оператор присваивания, move ???
	//статический метод child() - 
	//				должен создать создать и вернуть обертку для родившегося человека
	//				+ сформировать все связи ребенка с родителями и наоборот

	//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


		//...
		stop
	}

	return 0;
}
