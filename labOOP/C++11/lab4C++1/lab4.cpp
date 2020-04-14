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
