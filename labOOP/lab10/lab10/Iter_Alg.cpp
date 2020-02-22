// Iter_Alg.cpp : Defines the entry point for the console application.
//
//Итераторы. Стандартные алгоритмы. Предикаты.

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <string.h>
#include <typeinfo>
#include "Point.h"
#include "templ9.h"
#include "templ10.h"
//#include "templateVector.h"
using namespace std;	

#if  _WIN32 
#define	  stop __asm nop
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


int _tmain(int argc, _TCHAR* argv[])
{

#if  _WIN32 
	setlocale(LC_CTYPE, ".UTF8");
	cout << "Привет, Мир!";
#endif
///////////////////////////////////////////////////////////////////

	//Задание 1. Итераторы

	//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
	//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
	//являются копиями элементов set, но упорядочены по убыванию
    {
        set<Point> sp;

	for (size_t i = 0; i < 5; i++)
		sp.insert(Point(i, i));

        set<Point>::reverse_iterator spit = sp.rbegin();
        printCont(sp);

        vector<Point> v(spit,sp.rend());
        v.reserve(sp.size());
        printCont(v);
        //std::copy(v.rbegin(), v.rend(), std::inserter(sp, spit));
        /*for(size_t i = 0;i<5;i++)
        {
        v.push_back(*spit);
        ++spit;
        }
         printCont(v);*/
	stop


	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.
        cout<<"\niter ostream:";
        ostream_iterator<Point> out_it (cout,"\n| ");
        copy(v.begin(),v.end(), out_it );
        ostream_iterator<Point> out_it2 (cout,"\n: ");
        copy(sp.begin(),sp.end(), out_it2 );
        stop

	//Итераторы вставки. С помощью возвращаемых функциями:
	//back_inserter()
	//front_inserter()
	//inserter()
	//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
	//какие из итераторов вставки можно использовать с каждым контейнером.
        back_insert_iterator<vector<Point>> itv = back_inserter(v);
        *itv = Point(66,66);

        //error: ‘class std::vector<Point>’ has no member named ‘push_front’
        //front_insert_iterator<vector<Point>> itvf = front_inserter(v);
        //*itvf = Point(77,77);

        insert_iterator<vector<Point>> itvi = inserter(v,v.begin());
        *itvi = Point(88,88);

        cout<<"\niter ostream v:";
        copy(v.begin(),v.end(), out_it );

        //set не имеет метод push_back
       //back_insert_iterator<set<Point>> itspb = back_inserter(sp);
       //set не имеет метод front
       // front_insert_iterator<set<Point>> itspf = front_inserter(sp);
        insert_iterator<set<Point>> itspi = inserter(sp,sp.begin());
        *itspi = Point(99,99);
        cout<<"\niter ostream sp:";
        copy(sp.begin(),sp.end(), out_it2 );

        stop
        }
///////////////////////////////////////////////////////////////////

	//Задание 2. Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

	// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
	//(массив, vector, list...)
	//С помощью алгоритма for_each в любой последовательности с элементами любого типа
	//распечатайте значения элементов
	//Подсказка : неплохо вызываемую функцию определить как шаблон

        {
            cout<<"\nfor_each v:";
            vector<int> v{1,2,3,4,5};
            for_each(v.begin(),v.end(),printVect<int>);

             cout<<"\nfor_each l:";
            list<int> l{1,2,3,4,5};
            for_each(l.begin(),l.end(),printVect<int>);

        }

	stop

	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
	//как шаблон) и выведите результат с помощью предыдущего предиката

    {
        vector<Point> v{Point(2,3),Point(4,5)};
        cout<<"\nfor_each point v:";
        for_each(v.begin(),v.end(),changePPP<Point>(44,55));
        //for_each(v.begin(),v.end(),changePoint<Point>);
        for_each(v.begin(),v.end(),printVect<Point>);
        stop
    }


	//С помощью алгоритма find() найдите в любой последовательности элементов Point
	//все итераторы на элемент Point с указанным значением.



	
	
	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
	////По умолчанию алгоритм сортирует последовательность по возрастанию.
	//Что должно быть определено в классе Point?
	// Замечание: обобщенный алгоритм sort не работает со списком, так как
	//это было бы не эффективно => для списка сортировка реализована методом класса!!!
	



	
	//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
	//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
	//[-n, +m].



	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
	//располагая прямоугольники по удалению центра от начала координат.
	






	{//transform
		//Напишите функцию, которая с помощью алгоритма transform переводит 
		//содержимое объекта string в нижний регистр.
		//Подсказка: класс string - это "почти" контейнер, поэтому для него
		// определены методы begin() и end()


		//Заполните list объектами string. С помощью алгоритма transform сформируте
		//значения "пустого" set, конвертируя строки в нижний регистр
	



		stop
	}
	
	{//copy_if
		//Дан вектор с элементами типа string. С помощью copy_if() требуется
		//вывести сначала строки, начинающиеся с буквы "А" или "а", затем с "Б"...
		//При этом порядок строк в исходном векторе менять не нужно!



		stop

		//Дан multimap, содержаций пары: "месяц - количество денй в месяце"
		//pair<string, int>. С помощью copy_if сформируйте ДВА map-а: первый -
		//с парами, содержащими четное количество дней, 2-ой - нечетное.
		std::multimap<string, int> month {
			{"January", 31}, {"February", 28}, {"February", 29}, { "March", 31},
			{"April", 30}, {"May",31}, {"June", 30}, {"July", 31}, {"August",31},
			{"September",30}, {"October", 31}, {"November",30}, {"December",31}
		};



		stop

		//Распечатайте multimap и map-ы, используя написанный вами ранее шаблон
		//функции, выводящей элементы ЛЮБОГО контейнера на печать.
		//Что нужно сделать дополнительно для вывода пары?


	
		stop
	}

	return 0;
}

