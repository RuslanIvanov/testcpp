//Стандартная библиотека шаблонов - STL 
	//Контейнеры стандартной библиотеки - vector
	//Итераторы

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string.h>
#include "MyString.h"
#include "Point.h"
#include "templateVector.h"


#pragma warning(disable: 4786)


using namespace std;	

#if  _WIN32 
#define	  stop __asm nop
#else

void mystop()
{//Linux
	std::cout << "\nPause\n";
	getchar();
}

#define  stop  {mystop();}
#endif

int main(int arg, char** parg)
{
	// Контейнер стандартной библиотеки vector 

	//////////////////////////////////////////////////////////////////////
	//Создание векторов. 

	//Создайте следующие вектора:
	//---------------------------
	//пустой вектор целых чисел - vInt и проверьте с помощью функции size(),
	//что его размер нулевой. 

	std::vector<int> vInt;
	std::cout << "\nsize Vint: " << vInt.size();
	stop
    //Раскомментируйте следующий фрагмент, подумайте - все ли корректно
    //Если есть некорректности, - исправьте

    vInt.push_back(1);//добавляет элемент в конец вектора
	std::cout << "front " << vInt.front(); //возвращает ссылку на перый элемнт вектора
	//vInt.front()=2;
	stop

		//С помощью функции push_back() в цикле заполните вектор какими-либо значениями.
		//На каждой итерации цикла следите за размером вектора с помощью методов
		//size(), capacity(), max_size() и выводите значения элементов. 
		//
		//Подсказка: так как такая проверка понадобится Вам и в следующих заданиях,
		//напишите шаблон функции, которая для вектора, содержащего элементы любого типа
		//выводит его "реквизиты" и значения элементов на консоль.

		for (int i = 0; i < 10; i++)
		{
			vInt.push_back(i + 1);
			printParamCont(vInt);
			stop
		}

	printCont(vInt);

	stop

		//вектор вещественных - vDouble1 с заданным Вами начальным размером  и
		//проверьте результат с помощью созданного Вами шаблона. Как будут
		//проинициализированы элементы вектора?

		vector<double> vDouble1(10);

	printParamCont(vDouble1);
	printCont(vDouble1);
	stop
		//вектор объектов типа MyString с начальным размером - 5 элементов
		//и инициализацией каждого элемента строкой "A"
		//C помощью функции at() а также с помощью оператора
		//индексирования []  измените значения каких-либо элементов.
		//Попробуйте "выйти" за границы вектора с помощью at() и
		//с помощью []. 

		vector<MyString> vStr(5, "A");
	printCont(vStr);
	stop

		//вектор вещественных - vDouble3, который является копией элементов
		// [0,5) массива вещественных чисел dMas. Предворительно массив dMas 
		//нужно создать и проинициализировать!
		double dMas[] = { 0,1,2,3,4,5 };
	vector<double> vDouble3(dMas, dMas + (sizeof(dMas) / sizeof(dMas[0])));
	printCont(vDouble3);
	stop

		vector<double> vDouble33;
	for (size_t i = 0; i < sizeof(dMas) / sizeof(dMas[0]); i++)
	{
		vDouble33.insert(vDouble33.begin() + i, 1, dMas[i]);//вставляет копии элеметов из диапазона [i,j) перед эл. на котор. указ. итератор
	}

	printCont(vDouble33);
	stop
		vector<double> vDouble333(6);
	vDouble333.insert(vDouble333.begin() + 1, 4, 5.);//вставка 4 пятерок [1,5)
	printCont(vDouble333);
	stop

		//вектор вещественных - vDouble4, который является копией элементов
		// [2,5) вектора vDouble3. 

		vector<double> vDouble4(vDouble3.begin() + 2, vDouble3.begin() + 6);

	printCont(vDouble4);
	stop


		//вектор элементов типа Point - vPoint1 а) с начальным размером 3. Какой конструктор
		//будет вызван для каждого элемента?
		//b) vPoint2 с начальным размером 5 и проинициализируйте каждый элемент координатами (1,1).

		vector<Point> vPoint1;// вызван будет дефолтовый констр
	printCont(vPoint1);
	stop

		vector<Point> vPoint2(5, Point(1, 1));
	printCont(vPoint2);
	stop
		//вектор указателей на Point - vpPoint с начальным размером 5
		//Подумайте: как корректно заставить эти указатели "указывать" на объекты Point
	{
		//vector<Point*> vpPoint(5,nullptr);
		vector<Point*> vpPoint(5 ,nullptr);//если так new Point()) то - одним и тем же адресом иниц-ет
		vector<Point*> vpPoint2(5, nullptr);// new Point(0, 0));

		for (size_t i = 0; i < 5/*vpPoint.size()*/; i++)// с vpPoint.size() получается бесконечный цикл!!
		{
			//vpPoint.insert(vpPoint.begin() + i,new Point(i,i));// увеличит размер вектора
			//vpPoint.push_back(new Point(i, i));
			*(vpPoint.begin() + i) = new Point(i, i);
		}

		printCont<>(vpPoint);
		printCont(vpPoint2);
	stop
		//Подсказка: для вывода на печать значений скорее всего Вам понадобится
		//а) специализация Вашей шаблонной функции
		//б) или перегрузка operator<< для Point*

		for (size_t i = 0; i < vpPoint.size(); i++)
		{
			delete vpPoint[i];
			vpPoint[i] = nullptr;

		}

		for (size_t i = 0; i < vpPoint2.size(); i++)
		{
			delete vpPoint2[i];
			vpPoint2[i] = nullptr;
		}

	}//Какие дополнительные действия нужно предпринять для такого вектора?

		stop
		///////////////////////////////////////////////////////////////////////
		//Резервирование памяти.
		//Подумайте, всегда ли верны приведенные ниже проверки?

	{
	size_t n = 4;
	vector<int> v(n);
	v.resize(n / 2);
	if (v.capacity() == n) //true? yes, нет смысла перерасперделять емкость, а размер урезан
	{
		std::cout << "\nv.capacity() == n is true";
	}
	std::cout << "\nsize =" << v.size() << " cap " << v.capacity();
	}
		//*/
		stop

	{
	int n = 4;
	size_t m = 8;
	vector<int> v(n);
	v.reserve(m);
	if (v.capacity() == m) //true? да - перераспределение
	{
		std::cout << "\nv.capacity() == m is true";
	}
	std::cout << "\nsize =" << v.size() << " cap " << v.capacity();
	}
		//*/
		stop

	{
	vector<int> v(3,5);
	v.resize(4,10); //значения(5 5 5 10) //оставляет в векторе 4 первых элементов. Если размер вектора меньше 4, то добавляются недостающие элементы со значением 10
	v.resize(5); //значения (5 5 5 10 0)
	//оставляет в векторе 5 первых элементов.Если вектор содержит больше элементов, то его размер усекается до 5 элементов.Если размер вектора меньше 5, то добавляются недостающие элементы и инициализируются значением по умолчанию
	stop
	}
		//*/
		stop
		//Создайте два "пустых" вектора с элементами
		//любого (но одного и того же типа) типа. 
		//В первом векторе зарезервируйте память под 5 элементов, а потом заполните
		//его значениями с помощью push_back.
		//Второй вектор просто заполните значениями посредством push_back.
		//
		//Сравните размер, емкость векторов и значения элементов
	{
		vector<int> v1(5);
		vector<int> v2;

		for (int i = 0; i < 5; i++)
		{
			v1.push_back(i + 1);
			v2.push_back(i + 1);
		}
		std::cout << "\nsize v1 " << v1.size() << " cap " << v1.capacity();
		std::cout << "\nsize v2 " << v2.size() << " cap " << v2.capacity();
		stop //size v1 > size v2; cap v1 > cap v2


		//!!! shrink_to_fit - Уменьшение емкости вектора.
		//Для любого вектора из предыдущего задания требуется уменьшить емкость
		//до size.

			v2.shrink_to_fit();// c++11 До 0 освобождает capasity до  size память заним вектором 
			v1.resize(v1.size() / 2);
			stop
			v1.shrink_to_fit();// size = capacity
			stop
	}

		//Создание "двухмерного вектора" - вектора векторов
		//Задан одномерный массив int ar[] = {11,2,4,3,5};
		//Создайте вектор векторов следующим образом:
		//вектор vv[0] - содержит 11 элементов со значением 11
		//vv[1] - содержит 2,2
		//vv[2] - содержит 4,4,4,4
		//...
		//Распечатайте содержимое такого двухмерного вектора по строкам
	int ar[] = { 11,2,3,6,5 };
	vector<vector<int>> vv;
    for (size_t i = 0; i < (sizeof(ar) / sizeof(ar[0])); i++)
	{
		vector <int> tmp(ar[i], ar[i]);//создает вектор размера ar[i] заполняет знач ar[i]

		vv.push_back(tmp);
		stop
	}
    for (size_t i = 0; i < (sizeof(ar) / sizeof(ar[0])); i++)
	{
		printCont(vv[i]);
	}
	stop

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Вставка элемента последовательности insert().
	//В вектор vChar2 вставьте в начало вектора символ только при
	//условии, что в векторе такого еще нет.
	{
		char tmp[] = { 'a','b','c','c','d','e','f','f','a','b' };
		int n = sizeof(tmp) / sizeof(tmp[0]);
		vector<char> vChar2;
		for (int i = 0; i < n; i++)
		{
			if (vChar2.empty())
			{
				vChar2.insert(vChar2.begin(), tmp[0]);
			}
			else
			{
				int  k = vChar2.size();
				bool b = false;
				for (int j = 0; j < k; j++)
				{
					if (vChar2[j] == tmp[i])
					{
						b = true;
						break;
					}
				}
				if (!b) { vChar2.insert(vChar2.begin(), tmp[i]); }
				stop
			}
		}
		printCont(vChar2);
		stop

			//Вставьте перед каждым элементом вектора vChar2 букву 'W'
		vector<char>::iterator it = vChar2.begin();
		
		int s = vChar2.size();
		for (int i = 0; i < s ; i++)
		{
			it=vChar2.insert(it, 'W');// возвр.  итератор на вставленный эл
			++it; ++it; // i=0, W+f
		}
		printCont(vChar2);
		stop
	}
///////////////////////////////////////////////////////////////////
	//Напишите функцию, которая должна удалять только повторяющиеся последовательности.
	//Например: было - "qwerrrrty12222r3", стало - "qwety1r3"
	{
        char ar[] = "qwerrrrty12222r3";
		vector<char>var(ar, ar + sizeof(ar) - 1);
		
        makeUniqOnlyEven(var);
		//makeUniqAll(var);
	
	}
	stop

///////////////////////////////////////////////////////////////////

	//Удаление элемента последовательности erase()
	//Напишите функцию удаления из любого вектора всех дублей 
    {
        int array[] = {1,2,3,4,2,2,5,6,7,7,8,8,8,1,1,9,0,8,8,0,0};
        size_t n = (sizeof(array) / sizeof(array[0]));
        vector<int> vvv(array, array + n);
        deleteAllDuplicate(vvv);
        stop
    }

///////////////////////////////////////////////////////////////////
	//Создайте новый вектор таким образом, чтобы его элементы стали
	//копиями элементов любого из созданных ранее векторов, но расположены
	//были бы в обратном порядке

    {
        int array[] = {1,2,3,4,5,6,7,8};
        size_t n = (sizeof(array) / sizeof(array[0]));
        vector<int> v(array, array + n);
		std::cout << "\nreverse: ";
        vector<int> vr(v.rbegin(), v.rend());
        printContAny(vr);
        stop
    }




///////////////////////////////////////////////////////////////////

	//Задание 1. Списки. Операции, характерные для списков.
	//Создайте пустой список из элементов Point - ptList1 и наполните
	//его значениями с помощью методов push_back(),
	//push_front, insert()
	list<Point> ptList1;
	ptList1.push_back(Point(1, 1));
	ptList1.push_front(Point(2, 2));
	ptList1.insert(ptList1.begin(), Point(5, 5));

	//Напишите шаблон функции, которая будет выводить элементы
	//ЛЮБОГО КОНТЕЙНЕРА на печать. Проверьте работу шаблона на контейнерах
	//vector и list. Подсказка - хотелось бы увидеть тип контейнера.
    {
    printContAny(ptList1);
    int array[] = {1,2,2,3,4,4,4,5,6,7,7,7,8,8,8,8};
    size_t n = (sizeof(array) / sizeof(array[0]));
    vector<int> var(array, array + n);
	printContAny(var);
    std::cout<<"\nprintContAny";
    makeUniqAll(var);

    stop

    int array2[] = {1,2,2,3,4,4,4,5,6,7,7,7,8,8,8,8,9};
    n = (sizeof(array2) / sizeof(array2[0]));
    vector<int> var2(array2, array2 + n);
    printContAny(var2);
    std::cout<<"\nprintContAny";
    makeUniqAll(var2);

    stop
	//Сделайте любой из списков "реверсивным" - reverse()

    printContAny(ptList1);
    ptList1.reverse();
    std::cout<<"\nreverse";
    printContAny(ptList1);
    stop
    }
	//Создайте список ptList2 из элементов Point таким образом, чтобы он стал 
	//копией вектора элементов типа Point, но значения элементов списка располагались
	//бы в обратном порядке 

         vector<Point> tempPoint;
         for(size_t t = 0; t<6;t++)
         {
             tempPoint.insert(tempPoint.begin()+t,Point(t,t));

         }
         list<Point> ptList2 (tempPoint.rbegin(),tempPoint.rend());
         printContAny(ptList2);
         stop//*/

	//Отсортируйте списки  ptList1 и ptList2 - методом класса list - sort()
	//по возрастанию.
	//Подумайте: что должно быть перегружено в классе Point для того, чтобы
	//работала сортировка


        std::cout<<"\nSort list1:";
        ptList1.sort();
        printContAny(ptList1);
        stop
        std::cout<<"\nSort list2:";
        ptList2.sort();
        printContAny(ptList2);//*/

	stop

	//Объедините отсортированные списки - merge(). Посмотрите: что
	//при этом происходит с каждым списком.

        std::cout<<"\nMerge:";
        ptList1.merge(ptList2);
        printContAny(ptList1);
        stop
        //*/

	//Исключение элемента из списка - remove()
	//Исключите из списка элемент с определенным значением.
	//Подумайте: что должно быть перегружено в классе Point?

        ptList1.remove(Point(1,1)); // oper ==
        printContAny(ptList1);
        //*/
        stop

	//Исключение элемента из списка, удовлетворяющего заданному условию:
	//любая из координат отрицательна - remove_if(). 

        //pred:
        /*Removes from the container all the elements for which Predicate pred returns true.
         This calls the destructor of these objects and reduces the container size by the number of elements removed.
         The function calls pred(*i) for each element (where i is an iterator to that element).*/

     ptList1.push_back(Point(-1,0));
     ptList1.push_front(Point(1,-1));
     ptList1.push_front(Point(-1,-1));
     ptList1.push_front(Point(3,3));
     ptList1.push_front(Point(3,3));
     ptList1.push_front(Point(5,5));

     std::cout<<"\nList source:";
     printContAny(ptList1);

     std::cout<<"\nList remove_if:";
     ptList1.remove_if(predPoint);

     printContAny(ptList1);
     //*/
     stop

	//Исключение из списка подряд расположенных дублей - unique(). 
    ptList1.unique();
    printContAny(ptList1);
	stop

///////////////////////////////////////////////////////////////////
    /*
     * std::deque (двусторонняя очередь) представляет собой последовательный индексированный контейнер, который позволяет быстро вставлять и удалять элементы с начала и с конца. Кроме того, вставка и удаление с обоих концов двусторонней очереди оставляет действительными указатели и ссылки на остальные элементы.
       В отличие от std::vector, элементы deque не хранятся непрерывно: обычно реализован с помощью набора выделенных массивов фиксированного размера.
       Хранилище deque обрабатывается автоматически, расширяясь и сужаясь по мере необходимости. Расширение deque дешевле, чем расширение std::vector, потому что оно не требует копирования существующих элементов в новый участок памяти.
       Сложность (производительность) стандартных операций над двусторонней очередью следующая:

       Произвольный доступ - постоянная O(1)
       Вставка и удаление элементов с начала и с конца - амортизированная постоянная O(1)
       Вставка и удаление элементов - линейная O(n)
    */

	//Задание 2.Очередь с двумя концами - контейнер deque

	//Создайте пустой deque с элементами типа Point. С помощью
	//assign заполните deque копиями элементов вектора. С помощью
	//разработанного Вами в предыдущем задании универсального шаблона
	//выведите значения элементов на печать

    std::cout<<"\ndeque:";
    deque<Point> dp;
    dp.assign(tempPoint.begin(),tempPoint.end()); //заменяет содержимое с копиями тех, кто в диапазоне [first, last)
    printContAny(dp);
    stop

	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'

    deque<MyString> ds;
    ds.insert(ds.begin()+0,MyString("ABC"));
    ds.insert(ds.begin()+1,MyString("aabc"));
    ds.insert(ds.begin()+2,MyString("aaabc"));
    ds.insert(ds.begin()+3,MyString("ddd"));
    ds.push_back(MyString("CCC"));
    ds.push_back(MyString("ACC"));
    ds.push_back(MyString("AAC"));
    ds.push_front(MyString("BBB"));
    ds.push_front(MyString("BAC"));
    ds.push_front(MyString("aaa"));
    ds.push_front(MyString("A"));
    ds.push_front(MyString("aaA"));

    std::cout<<"\ndeque source:";
    printContAny(ds);
    std::deque<MyString>::iterator itb =  ds.begin();
    std::deque<MyString>::iterator ite =  ds.end();
    for(size_t i=0; i<=ds.size()/*itb!=ite */;i++)
    {
        if( (itb->GetString()[0] == 'A') || (itb->GetString()[0] == 'a'))
        {
              ds.erase(itb);
              i=0;
              itb =  ds.begin();
        }else  ++itb;

        //std::cout<<"\nbegin:"<<ds.begin()->GetString();
    }

    printContAny(ds);
    stop
	return 0;
}
