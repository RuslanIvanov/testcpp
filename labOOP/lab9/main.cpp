// Контейнеры STL: 
//stack, queue, priority_queue
//set, multiset, map, multimap

#include <stack>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <clocale>
#include <functional>

#include <iostream>
#include <string.h>
#include "Point.h"
#include "templ.h"
using namespace std;

#if  _WIN32 
#define   stop __asm nop
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


    //Напишите шаблон функции для вывода значений stack, queue, priority_queue
    //обратите внимание на то, что контейнеры предоставляют РАЗНЫЕ методы для
    //получения значений

    std::queue<int> q1;
    std::queue<int> q2;
    std::queue<int> q3;

    q1.push(3);
    q1.push(1);
    q1.push(4);
    q1.push(1);
    q1.push(5);
    printCont(q1);
    printCont(q2);

    q3.push(4);
    q3.push(5);
    q3.push(6);
    printCont(q3);

    stop
    std::stack<int> st1;
    st1.push(3);
    st1.push(1);
    st1.push(4);
    st1.push(1);
    st1.push(5);
    printCont(st1);

    stop
    priority_queue<int> pq1;
    pq1.push(3);
    pq1.push(1);
    pq1.push(4);
    pq1.push(1);
    pq1.push(5);
    printCont(pq1);
    //print_priority_queue(pq1);
    stop
    ////////////////////////////////////////////////////////////////////////////////////
    //stack

    //Создайте стек таким образом, чтобы
    //а) элементы стека стали копиями элементов вектора
    //б) при выводе значений как вектора, так и стека порядок значений был одинаковым
    {
        vector<int> v = {1,2,3,4,5};
        printCont(v);
        stop
        stack<int,vector<int>> s1(v);
        printCont(v);
        stop
	
    }

	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point,
	//при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?
	
    {
        list<Point*> v;
        v.push_back(new Point(1,1));
        v.push_back(new Point(2,2));
        v.push_back(new Point(3,3));
        v.push_back(new Point(4,4));
        v.push_back(new Point(5,5));
        std::cout<<"\n List: ";
        printCont(v);
        queue<Point*,list<Point*>> q(v); //list or deque а vector ??

        q.front() = new Point(0,0);// q.front() and q.back() - возвращают ссылки
        q.back() = new Point(6,6);;


        std::cout<<"\nQueue point: ";
        printCont(q);
        std::cout<<"\nvect size: " << v.size();
        int n = v.size();
        list<Point*>::const_iterator it = v.begin();
        for(int i = 0 ; i<n; i++)
        {

            std::cout<<"\ndel: "<<*it;
            delete *it;
            ++it;
        }
        stop

    }


	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?


        {
            const char* str[] = {"aa","bbb","cccc","ddddd","eeeeee","ffffffff"};
            priority_queue<const char*,vector<const char*>,myless_str> pq;

            for(size_t i = 0; i< (sizeof(str)/sizeof(char*));i++)
                pq.push(str[i]);

            printCont(pq);// лексеграф. сравнение при выводе с помощью pop
            stop
            priority_queue<const char*,vector<const char*>> pq2;
            for(size_t i = 0; i< (sizeof(str)/sizeof(char*));i++)

            pq2.push(str[i]);

            printCont(pq2);// по адресам сравнение при выводе с помощью pop
            stop

         }




	
	
	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом)
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...
	//г) Создайте два множества, которые будут содержать одинаковые значения
	//		типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого
	//	контейнера, например, элементов массива	(что происходит, если в массиве имеются дубли?)

        {
        std::cout<<"\n pair ";
        auto a = std::make_pair(1, 22);
        cout << "\nfirst: "<< a.first;
        cout << " second " << a.second;
        }

        {
            pair< set<Point>::iterator ,bool> ret;
            set<Point> sp;
            for(int i = 0; i<5; i++)
            {
                ret= sp.insert(Point(i,i));
                std::cout<<"\n second: "<<((ret.second==true)?" is insert ":" no insert ");
                std::cout<<", first: "<<*ret.first;
            }
            printCont(sp);
            stop
            set<Point> ::iterator i = sp.begin();
           // *i = Point(88,99);//нельзя, только insert, а итератор только для чтения
             std::cout<<"\nIter on Point: "<<*i;
        }

        {

         pair< set<int>::iterator ,bool> ret;
         int ar[] = {1,3,6,7,4,5,2};
         int n = sizeof(ar)/sizeof(ar[0]);
         set<int> sp1 (ar,ar+n);
        //set<int,classcomp> sp2 = {1,6,7,4,5};
         set<int,classcomp> sp2(ar,ar+n);

         printCont(sp1);
         printCont(sp2);

         sp1.insert(8);
         sp1.insert(9);
         sp1.insert(10);

         set<int>::iterator ii = sp1.begin();
         for(size_t i =0;i<sp1.size();i++)
         {
             ret = sp2.insert(*ii);
             std::cout<<"\n second: "<<((ret.second==true)?" is insert ":" no insert ");
             std::cout<<", first: "<<*ret.first;
             ++ii;
         }

         printCont(sp2);
         stop

        }
	////////////////////////////////////////////////////////////////////////////////////
	//map, multiset
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>,
	//	при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое

	//г) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")
        {// не допускает дубликатов

            typedef map<const char*,int> MAP;
            MAP m;
            MAP::iterator it= m.begin();

            m["Petrov"] = 1111;
            m["Sidorov"] = 2222;
            m["Ivanova"] = 3333;
            m.insert(it,MAP::value_type("Kirillov",4444));
            m.insert(it,MAP::value_type("Makarov",5555));
            printCont(m);
            int tel =  m["Ivanova"];
            m.erase("Ivanova");// удалить элемен по ключу
            m["Petrova"] = tel;
            printCont(m);
            stop
        }

	
		
		//д) Сформируйте любым способом вектор с элементами типа string.
		//Создайте (и распечатайте для проверки) map<string, int>, который будет
		//содержать упорядоченные по алфавиту строки и
		//количество повторений каждой строки в векторе
                {


                    vector<string> vstr;
                    vstr.push_back("baba");
                    vstr.push_back("mama");
                    vstr.push_back("mama");
                    vstr.push_back("mama");
                    vstr.push_back("mama");
                    vstr.push_back("papa");
                    vstr.push_back("tata");
                    vstr.push_back("papa");
                    vstr.push_back("tata");
                    vstr.push_back("cc");
                    vstr.push_back("bb");
                    vstr.push_back("aa");
                    printCont(vstr);
                    stop

                    map<string, int,classcomp_key> m;
                    map<string, int>::iterator it = m.begin();
                    pair< map<string, int> ::iterator ,bool> ret;
                    for(size_t i = 0;i<vstr.size();i++)
                    {

                        // it =  m.insert(it,map<string, int>::value_type(vstr[i],1));//не позволяет выяснить выполнена ли вставка
                        ret =  m.insert(map<string, int>::value_type(vstr[i],1));
                        if(ret.second == false)
                        {
                           //std::cout<<"\nno insert";
                           m[vstr[i]]= m[vstr[i]]+1;

                        }
                    }
                    //std::map::value_compare value_comp() const;
                    //std::map<char,int>::key_compare mycomp = mymap.key_comp();//Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
                   map<string,int,classcomp_key>::key_compare comp = m.key_comp();
                   map<string,int>::iterator itb = m.begin();

                  // do
                  // {
                     //   std::cout << itb->first << " => " << itb->second << '\n';
                  // }while ( comp( itb->first,++itb->first ) );

                   printCont(m);
                   stop
                }



		//е) 
		//задан массив:
		//const char* words[] = {"Abba", "Alfa", "Beta", "Beauty" ,...};
		//создайте map, в котором каждой букве будет соответствовать совокупность 
		//лексиграфически упорядоченных слов, начинающихся с этой буквы.
		//Подсказка: не стоит хранить дубли одной и той же строки
	
		//'A' -  "Abba" "Alfa"
		//'B' -  "Beauty" "Beta"  ...
		//...
		

		//ж)
		//создайте структуру данных, которая будет хранить информацию о студенческих группах.
		//Для каждой группы должны хранится фамилии студентов (по алфавиту). При этом 
		//фамилии могут дублироваться
		//Сами группы тоже должны быть упорядочены по номеру
		//
		//номера 




	////////////////////////////////////////////////////////////////////////////////////
	//multimap
	//а) создайте "англо-русский" словарь, где одному и тому же ключу будут соответствовать
	//		несколько русских значений - pair<string,string>, например: strange: чужой, странный...
	//б) Заполните словарь парами с помощью метода insert или проинициализируйте с помощью 
	//		вспомогательного массива пара (пары можно конструировать или создавать с помощью шаблона make_pair)
	//в) Выведите все содержимое словаря на экран
	//г) Выведите на экран только варианты "переводов" для заданного ключа. Подсказка: для нахождения диапазона
	//		итераторов можно использовать методы lower_bound() и upper_bound()




   

  stop

	return 0;
}

