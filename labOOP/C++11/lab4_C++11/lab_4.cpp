#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <iterator>
#include <set>
#include <stddef.h>
#include <type_traits>
#include <utility>//pair

using namespace std;
#include "Point.h"
#include "Header.h"
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
	
/***************************************************************/
//Задание 1.
	/*
	Реализуйте шаблон функции для печати любых последовательностей (vector, list, deque, set и встроенного массива), которые могут содержать:
	•	как объекты любого типа,
	•	так и указатели на объекты любого типа (указатели распечатывать неинтересно => в этом случае следует получать значение по адресу)
	Подсказки: if constexpr
	*/
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

		PRINTF3(point);
		PRINTF3(ar);
		PRINTF3(v);
		PRINTF3(l);
		PRINTF3(d);
		PRINTF3(s);
		PRINTF3(vs);
		//PRINTF3(ptrV);

		stop

		for (size_t i = 0; i < 3; i++)
		{
				delete point[i];
		}
	}

/***************************************************************/
//Задание 2.
	/* Реализуйте шаблон функции сложения двух значений.
	Если первое слагаемое является вектором, то все элементы вектора нужно увеличить на значение второго параметра. 
	При этом элементы вектора и второй параметр должны быть одного и того же типа.
	Подсказки: if constexpr, is_same
	*/
	{
		vector<int> v = { 1,2,3,4 };
		sumV(v, 1);
		PRINTF(v);
		int n = 2;
		sumV(n, 1);
		std::cout << "\nn = "<< n;
		stop
	}


	/***************************************************************/
//Задание 3.
	/* 	Реализуйте шаблон функции вывода на печать значений элементов любого адаптера (stack, queue, priority_queue)
	Подсказки: if constexpr, is_same
	Предусмотрите вывод значений, если в адаптере хранятся указатели.
	*/
	{
		std::queue<int> q1;
		q1.push(-1);
		q1.push(3);
		q1.push(-2);


		std::queue<Point*> ppq1;
		ppq1.push(new Point(1, 1));
		ppq1.push(new Point(1, 3));
		ppq1.push(new Point(1, 2));

		std::stack<char> st1;
		st1.push('A');
		st1.push('C');
		st1.push('B');

		std::priority_queue<Point> pq1;
		pq1.push(Point(1, 1));
		pq1.push(Point(1, 3));
		pq1.push(Point(1, 2));

		 PRINT_ADAPT(q1);
		 PRINT_ADAPT(st1);
		 PRINT_ADAPT(pq1);
		 PRINT_ADAPT(ppq1);

		 while (!ppq1.empty())
		 {
			 delete ppq1.front();
			 ppq1.pop();
		 }

		 stop
	}

/***************************************************************/
//Задание 4.
	{
		//Дан массив элементов типа string
		std::string strings[] = {"ccc","abc", "123", "qwerty", "#$%","321"};
		//До завершения фрагмента строки должны существовать в единственном экземпляре.
		//Требуется обеспечить манипулирование строками а) без копирования и б) без изменения порядка
		//элементов в массиве!
		
		//В std::set "складываем" по алфавиту обертки для строк, которые содержат только буквы 
		auto DelStr = [](string*) { std::cout << "\nDelStr"; };

		std::shared_ptr<string> s1[] = {shared_ptr<string>(&strings[0], DelStr), shared_ptr<string>(&strings[1], DelStr),
										shared_ptr<string>(&strings[2], DelStr),shared_ptr<string>(&strings[3], DelStr),
										shared_ptr<string>(&strings[4], DelStr) ,shared_ptr<string>(&strings[5], DelStr) };
		//
		std::set<std::shared_ptr<string>, SORT_SET> sp;
		//std::set < std::shared_ptr<string>, decltype(&cmp)>sp(cmp);
		//лямбда?

		std::copy_if((std::begin(s1)), (std::end(s1)), std::inserter(sp, sp.begin()), [](std::shared_ptr<string>& s)
		{
				if ((*s->begin() >= 'a' && *s->begin() <= 'z') || (*s->begin() >= 'A' && *s->begin() <= 'Z'))
					return true;
				else return false;
		}		
		);//*/
		
		//set уже упорядочен должен быть
		/*std::sort(sp.begin(), sp.end(), [](const std::shared_ptr<string>& l, const std::shared_ptr<string>& r) 
		{
				return (*l.get() > *r.get());
			//	return (*l->begin() > *r->begin());
		}
		);//*/
		
		//мой страшный вывод
		for (auto i = sp.begin(); i != sp.end(); ++i)
		{
			std::cout << "\nsp: ";
			for (size_t j = 0; j < (*i)->size(); j++)
			{
				std::cout << "" << *((*i)->begin()+j);
			}
		}

		stop
		/******************************************************************************************/

		//В std::vector "складываем" обертки для строк, которые содержат только цифры 
		//Выводим на экран
		//Находим сумму
		
		std::vector<std::shared_ptr <std::string>> v;
		std::copy_if((std::begin(s1)), (std::end(s1)), std::back_inserter(v), [](std::shared_ptr<string>& s)
			{
				if ((*s->begin() >= '0' && *s->begin() <= '9'))
					return true;
				else return false;
			}
		);

		for (auto i = v.begin(); i != v.end(); ++i)
		{
			std::cout << "\nv: "<< (*i)->c_str();			
		}

		int sum = 0;
		for (auto i = v.begin(); i != v.end(); ++i)
		{
			sum+=std::atoi((*i)->c_str());
		}
		std::cout << "\nsum: " << sum<<"\n";
		stop
		/******************************************************************************************/
		//сюда "складываем" обертки для строк, которые не содержат ни символов букв, ни символов цифр
		//и просто выводим

		ostream_iterator<std::shared_ptr <std::string>> out_it(cout, " ");
		//std::copy_if((std::begin(s1)), (std::end(s1)), out_it, [](std::shared_ptr<string>& s)
		std::vector<std::shared_ptr <std::string>> v2;
		std::copy_if((std::begin(s1)), (std::end(s1)), back_inserter(v2), [](std::shared_ptr<string>& s)
			{
				if ((*s->begin() >= '0' && *s->begin() <= '9') ||
					(*s->begin() >= 'a' && *s->begin() <= 'z') ||
					(*s->begin() >= 'A' && *s->begin() <= 'Z'))
					return false;
				else 
					return true;
			}
		);

		for (auto i = v2.begin(); i != v2.end(); ++i)
		{
			std::cout << "\nv2: "<< (*i)->c_str();	
		}

		stop
	}

	
/******************************************************************************************/
//Задание 5. 
	{
		//Дано:
		std::string ar[] = {"my","Hello", "World"};
		std::vector < std::shared_ptr<std::string>> v = {std::make_shared<std::string>("good"), std::make_shared<std::string>("bye")};
		//make_shared - соzдает динамичски => delete

		//а) Требуется добавить в вектор обертки для элементов массива, НЕ копируя элементы массива! 
		//б) Отсортировать вектор по алфавиту и вывести на экран
		//в) Обеспечить корректное освобождение памяти
		auto DelStr2 = [](string*) { std::cout << "\nDelStr2"; };
		
		for(size_t i = 0 ; i<sizeof(ar)/sizeof(ar[0]);i++)
			v.push_back(shared_ptr<string>(&ar[i], DelStr2));

		sort(v.begin(), v.end(), [](const std::shared_ptr<string>& l, const std::shared_ptr<string>& r)
		{
				return (*l.get() < * r.get());
		}
		);

		for (auto i = v.begin(); i != v.end(); ++i)
		{
			std::cout << "\nv sort: " << (*i)->c_str();
		}
		stop
	}
	stop
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


		std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


		//...
		stop
	}



//***************************************************************/
//Задание 7.

	/*Пользовательский deduction guide – для вывода типов параметров шаблона
	Задан шаблон класса, который инкапсулирует внедренный ограниченный массив известной
	размерности с элементами любого типа. */
	/*
	template<typename T, size_t size> class MyArray
	{
		T ar[size]; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
		…
	};

	//*/

//Требуется обеспечить работоспособность приведенных примеров использования.
	{
		MyArray<int, 5> ar1;//MyArray<int,5> //OK
		MyArray ar2{"ABC"}; //MyArray<char,4> //??
		
		int ar[] = { 1,2,3 };
		MyArray ar3{ ar };//OK
		MyArray ar6{ 6 };////variadic telmplate
		MyArray ar7{1,2,3};//variadic telmplate
		stop
	}
	{
		MyArray2<int, 5> ar1;//MyArray<int,5>
		MyArray2 ar2{ "ABC" }; //MyArray<char,4>
		int ar[] = { 1,2,3 };
		MyArray2 ar3{ ar };//разные варианты с ar3 выше
		MyArray2 ar4{ 4,5,6,7 };//variadic telmplate
		MyArray2 ar5{ 5 };//variadic telmplate
		stop
	}
//*/

	stop

}
