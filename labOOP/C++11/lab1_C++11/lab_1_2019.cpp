//Практика 1:
// enum class
// initializer_list и универсальные списки инициализации
// auto
// decltype
// lambda 

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
#include <utility>

enum class COLORS : int { RED, GREEN, BLUE, YELLOW, BLACK, WHITE };
enum class NUMBERS : unsigned char { ONE, TWO, FREE};

#include "Header.h"

template <typename T>
std::map<std::string, T> EnumMap<T>::m_eMap;

std::map<std::string, COLORS> EnumMap<COLORS>::m_eMap = { {"RED",COLORS::RED},{"GREEN",COLORS::GREEN}, {"BLUE",COLORS::BLUE},{"YELLOW",COLORS::YELLOW} ,{ "BLACK",COLORS::BLACK} };
std::map<std::string, NUMBERS> EnumMap<NUMBERS>::m_eMap = { {"ONE",NUMBERS::ONE},{"TWO",NUMBERS::TWO}, {"FREE",NUMBERS::FREE} };

using namespace std;

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

#if  _WIN32 
	setlocale(LC_CTYPE, ".UTF8");
	cout << "Привет, лаб1 C++11,14,17!";
#endif

	//Задание 1. 
	{
		enum class months:unsigned char { January, February, March/*...*/ };
		enum class weekDays { Monday, Tuesday /*...*/ };

		months m = months::January;
		//а) уберите проблемы (это значит, что КОМПИЛЯТОР не
		//должен позволять программисту осуществлять опасные
		//сравнения!)

		//if (m == Monday) { /* m - не отностися к облсати видимости  months */ }

		//б) оптимизируйте использование памяти
		months year[] = { months::January, months::February, months::March };
		size_t n = sizeof(year); //??? - 3б
		cout<<"\nmonths[] size = "<< n <<"";
		stop
	}


/**********************************************************/
	//Задание 2. Создайте и с помощью списка инициализации
	//заполните значениями вектор с элементами - string
	//С помощью range-based for преобразуйте все буквы в 	
	//верхний регистр а остальные символы должны остаться
	//неизменными
	{
		
		vector<string> v = { "1aaa1","bbb33","c22cc","e3e4e"};

		for (string& c : v)
		{
			//c[0] = (char)toupper(c[0]); //reference  operator[]( size_type pos );
			for(char& c2: c)
			{
				c2 = toupper(c2);
			}
		}

		printCont(v);
		stop
	}


/**********************************************************/
	///Задание 3. Создайте и заполните значениями
	//map таким образом, чтобы он содержал в качестве ключа
	//букву, а в качестве значения отсортированную по 
	//алфавиту совокупность слов (string), начинающихся с
	//этой буквы
	
	//3а. Проинициализируйте map "вручную" посредством списка инициализации
	//С помощью range-based for и structured binding
 	//распечатайте содержимое, например: A: any, apple, away
	{
		map<char, vector<string>> m{
			{'a', {"aaa", "aaaa"} },
			{'b', {"bbb","bbbbb"} },
			make_pair('l', vector<string>{ "ll", "lll" })
		};

		for (pair<const char, vector<string>>& p : m) //for "возвращает" по ссылке &p элемент контейнера m,  если обрать const char, то будет for делать копии пары!
		{
			//cout << "\n first " << p.first << "second " <<p.second;
			//pair<char, string> [x,y] = p;
			auto& [f, s] = p;
			for (string& str : s)
			{
				cout << "\n" << f << ": " << " " << str;
			}

		}

		for (auto& [f, s]: m) //for "возвращает" по ссылке &p элемент контейнера m,  если обрать const char, то будет for делать копии пары!
		{
			//cout << "\n first " << p.first << "second " <<p.second;
			//pair<char, string> [x,y] = p;
			
			for (auto& str : s)
			{
				cout << "\n" << f << ": " << " " << str;
			}

		}

		stop
	}

	//3б. Создайте пустой map и используйте заданный массив
	//для выполнения задания.
	//С помощью range-based for и structured binding
	//распечатайте содержимое, например: A: any, apple, away
	{
		//дано (например):
		const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };

		map<char, set<string>> m;
		size_t n = sizeof(s) / sizeof(char*);
		

		for (size_t i = 0; i < n; i++) 
		{			
			m[s[i][0]].insert(s[i]);

			stop
		}

		for (auto& p : m) 
		{
			auto& [first, two] = p;

			for (auto& str : two)
				cout << "\n" << first << ": " << " " <<  str;

		}
				
		stop
	}


/*********************************************************/
	//Задание 4. создать функцию для вывода на печать
	//элементов последовательностей, заданных ниже:
	{
		std::vector<double> vd = { 1.1,2.2,3.3 };
		PrintAnyCont(vd);

		std::string s("abc");
		PrintAnyCont(s);

		int ar[] = { 1, 2, 3 };
		PrintAnyCont(ar);

		std::initializer_list<int> il{ 3,4,5 };
		PrintAnyCont(il);		

		stop
	}


/********************************************************/
	///Задание 5. 	
	//Cоздать функцию для "отрицания" значений, например:
	//было: {1, -2, 5}, стало: {-1, 2, -5})
	//изменение объектов типа std::string может выглядеть "aBc1" -> "AbC1"
	//элементов последовательностей, заданных ниже:
	{
		vector <string> vtest{ "aBc", "Qwerty", "n12" };
		vector <double> vdtest{ 1.1,2.2,3.3 };
		for (string& s : vtest)
		{
			
			for (char& c : s) 
			{
				if (c >= 'A' && c <= 'Z') { c = tolower(c); }
				else if (c >= 'a' && c <= 'z') {c = toupper(c); }
			}
		}

		for (double& s : vdtest)
		{
			//std::size(s,s+size(s));
			s *= -1;		
		}

		PrintAnyCont(vtest);
		PrintAnyCont(vdtest);
		///////////////////////////////////////////////////////////////////
		stop
		std::vector<double> vd{ 1.1,2.2,3.3 };
		NegateAll(vd);

		std::list<std::string> ls{ "aBc", "Qwerty", "n12" };
		NegateAll(ls);
		
		int ar[]{ 1, 2, 3 };
		NegateAll(ar);
		
		stop

		PrintAnyCont(vd);
		PrintAnyCont(ls);
		PrintAnyCont(ar);

		stop

	}

	
/********************************************************/
	//Задание 6. Реализовать функцию сортировки по модулю
	//элементов последовательностей, заданных ниже
	//Собственно для сортировки можно использовать обобщенный
	//алгоритм sort(), а для задания условия - лямбда-функцию
	{
		std::vector<double> vd = { -3.3,  2.2, -1.1 };
		absSort(vd);
		PrintAnyCont(vd);

		int ar[] = { -3, 2, -1 };
		absSort(ar);
		PrintAnyCont(ar);
		stop
	}


/********************************************************/
	//Задание 7.
	//Напишите функцию, которая будет формировать и
	//возвращать вектор, каждый элемент 
	//которого является суммой элементов двух 
	//последовательностей РАЗНОЙ длины
	//и с элементами РАЗНОГО типа.

	//Подсказка 1: так как последовательности могут быть
	//разной длины, логично сделать размер результирующего
	//вектора максимальным из двух
	 
	//Подсказка 2: подумайте о возможности использования
	//алгоритмов copy() и transform(), в котором 
	//трансформирующее действие удобно в свою очередь
	//задавать лямбда-функцией

	//например:
	{
		
		//std::vector<int> v { 1,   2,   3   ,4,5,6,7 };
		std::vector<int> v{ 1,   2,   3 };
		std::list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5 };
		
		auto a = SumCont(v, l);

		std::list<int> ll{ 1, 2, 3, 4, 5, 6, 7, 8 };
		double ar[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		auto aa = SumCont(ar, ll);
		
		std::set<std::string> s{ "abc", "qwerty", "my"};
		std::deque<const char*> d{ "111", "22" };
		auto aaa =  SumCont(s, d);

		cout << "\nsource:-------------------------------------";
		PrintAnyCont(s);
		PrintAnyCont(d);
		auto S = SUM(s,d);
		cout << "\nresult:";
		PrintAnyCont(S);

		cout << "\nsource:-------------------------------------";
		PrintAnyCont(ar);
		PrintAnyCont(ll);
		auto SS = SUM(ar, ll);
		cout << "\nresult:";
		PrintAnyCont(SS);
		cout << "\nsource:-------------------------------------";
		PrintAnyCont(v);
		PrintAnyCont(l);
		auto SSS = SUM(v, l);
		cout << "\nresult:";
		PrintAnyCont(SSS);

		cout << "\nresult SumCont():";
		PrintAnyCont(a);
		PrintAnyCont(aa);
	    PrintAnyCont(aaa);
		stop
	}


/********************************************************/	
	//Задание 8. Реализуйте функцию, которая принимает следующие параметры:	
	//сформированную последовательность любого типа с элементами любого типа, 
	//два (пустых) контейнера любого типа из vector, list, deque, set 
	//с элементами того же типа, что и у сформированной последовательности 

	//Функция должна "разложить" значения заданной последовательности в два пустых контейнера 
	//согласно заданному условию. Условие задать лябда-функцией
	//Исходная последовательность при этом не меняется
	{
		//Например:
		std::vector<int> v{ 1,2,3,4,5 };
		std::list<int> l; //сюда четные
		std::deque<int> d; //а сюда нечетные
		Separate(v, l, d, [](int& x)->bool { return ((x % 2) == 0 ? true : false); });
		cout << "\nsource:";
		PrintAnyCont(v);
		cout << "\nresult";
		PrintAnyCont(l);
		PrintAnyCont(d);
		stop
	}


/********************************************************/
	//Задание 9. C помощью алгоритма for_each()!!! 
	//(а не count_if()) посчитать сколько букв в верхнем
	//регистре.
	//  Использовать лямбда функцию
	{
		char s[] = "Hello World!";
		size_t count = 0;
		for_each(begin(s), end(s), [&count](char c) { if (c >= 'A' && c <= 'Z') count++; });

		cout << "\n'" << s << "'" << "upper is " << count;
		stop
	}


/********************************************************/
	//Задание 10. Реализовать конвертацию enum в строковое представление  - enumToString
	// и наоборот - stringToEnum

	//Подсказки: 
	//***********
	//1. Соответствующие именованным константам строки все равно нужно где-то хранить =>
	//1.1 Именованные константы в перечислении должны быть уникальными => соответствующие строки
	//тоже должны быть уникальными, => уникальные строки могут быть использованы в качестве
	//ключа в std::map
	
	//1.2 а вот значения (соответствующие именованым константам)
	//могут быть любыми и даже могут повторяться (упрощаем задачу, считая, что значения НЕ повторяются) 
	//=> подходит контейнер std::map<string,<значение> >
	
	//1.3 Согласно стандарту С++11 переменные перечислимого типа могут быть разного размера и типа,
	//а хотелось бы обеспечить универсальную конвертацию 
	
	//***********
	//2. Так как типы перечислений разные, то enumToString и stringToEnum должны быть шаблонными
	//2.1 Пользователь может ошибиться или злонамеренно передать в функции значения, которым
	//   ничего не соответствует => защита!
	//2.2 В функциях enumToString и stringToEnum (в зависимости от типа перечисления) нужно будет
	//   анализировать соответствующий используемому типу перечисления контейнер
	
	//***********
	//3. Чтобы действия с map<string, <значение> > не зависили от типа перечисления, логично реализовать "обертку":
/*
template<typename T> struct EnumMap
{
	static std::map<std::string, T> m_eMap;
	static const auto& getMap() { return m_eMap; }
};
*/
	{
		
		// если будет запрещен конструктор, то иниц-я за пределами main
		//EnumMap<COLORS>  em1;
		//em1.m_eMap["RED"] = COLORS::RED;
		//em1.m_eMap["GREEN"] = COLORS::GREEN;
		//em1.m_eMap["BLUE"] = COLORS::BLUE;
		//em1.m_eMap["YELLOW"] = COLORS::YELLOW;
		//em1.m_eMap["BLACK"] = COLORS::BLACK;
		//stop
		//EnumMap<NUMBERS> em2; //  {{ "FREE",NUMBERS::FREE }};
		//em2.m_eMap["ONE"]=NUMBERS::ONE;
		//em2.m_eMap["TWO"] = NUMBERS::TWO;
		//em2.m_eMap["FREE"] = NUMBERS::FREE;
		//Например:

		COLORS c1;
		COLORS c2;
		NUMBERS n1,n2;
		try 
		{
			c1 = stringToEnum<COLORS>("BLUE");
			cout << "\nc1 " << static_cast<int>(c1);
			c2 = stringToEnum<COLORS>("CCC");
			cout << "\nc2 " << static_cast<int>(c2);
		}
		catch (const char* e)
		{
			cout << "\n"<<e;
		}

		try
		{
			n1 = stringToEnum<NUMBERS>("ONE");
			cout << "\nn1 " << static_cast<int>(n1);
			n2 = stringToEnum<NUMBERS>("SSSS");
			cout << "\nn2 " << static_cast<int>(n2);
		}
		catch (const char* e)
		{
			cout << "\n" << e;
		}
			
		auto Str1 = enumToString(c1);//*/
		auto Str2 = enumToString(n1);//*/

		cout << "\nStr1 " << Str1;
		cout << "\nStr2 " << Str2;
		stop
	}

	return 0;
}
