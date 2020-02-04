//Исключения

//Шаблоны: 
	//		шаблоны функций,
	//		шаблоны классов,

//#include <tchar.h>
#include <iostream>
//#include <stdexcept>
#include "templ.h"
#include "MyString.h"
#include "MyStack.h"
#include "MyStack2.h"

//#define stop __asm nop
void mystop()
{
        std::cout << "\nPause\n";
        getchar();
}

#define  stop  {mystop();}


int main(int argc, char* argv[])
{


	////////////////////////////////////////////////////////////////////////////
	//Тема. Шаблоны функций.
	//Создайте шаблон функции перестановки местами двух
	//значений - Swap(). Проверьте работоспособность созданного
	//шаблона с помощью приведенного ниже фрагмента кода.
	//Подсказка 1: объявление шаблона корректнее поместить в .h-файл.

	int iX = 1, iY = -1;
	Swap(iX, iY);

	stop

		double dX = 0.5, dY = -5.5;
	Swap(dX, dY);

	stop
		//Подсказка 2: подумайте, что нужно реализовать, для того,
		//			чтобы следующий вызов работал с объектами MyString
		//			не только корректно, но и эффективно
		MyString str1("One"), str2("Two");
	Swap(str1, str2);

	std::cout << "\ns1 = " << str1 << " s2 = " << str2;
	stop
		//*/
		/////////////////////////////////////////////////////////////////////

			//Тема. Шаблоны классов.
			//Задание 1.
			//Создайте шаблон класса MyStack для хранения элементов любого типа T.
			//Подсказка: 1.элементы нужно где-то хранить - простым и удобным средством
			//			для хранения последовательно расположенных в памяти элементов
			//			является массив, 
			//			2.для задания максимального размера стека может быть использован
			//			параметр-константа шаблона
			//			3.обязательными операциями со стеком являются "push" и "pop". Для
			//			того, чтобы гарантировать корректное выполнение этих операций 
			//			хорошо было бы генерировать исключение в аварийной ситуации
			//			4. дополнительно реализуйте operator[] таким образом, чтобы пользователь
			//			мог читать/изменять значения только тех элементов, которые он формировал


			//С помощью шаблона MyStack создайте стек из 5 элементов int - iStack и
			//стек из 10 элементов MyString - strStack и поэкспериментируйте с функциями
			//push() и pop(), operator[]
	{
		MyStack <int,10>st;
		try
		{
			for (int i = 0; i < 11; i++)
				st.push(i);
		}
		catch (const char* e)
		{
			std::cout << e;
		}

		std::cout << "\nread all stack:";
		for (int i = 0; st.size() > 0; i++)
			std::cout << "\n#" << i << ": " << st.pop();
		stop
		try
		{
			for (int i = 0; ; i++)
				std::cout << "\n#" << i << " : " << st.pop();
		}
		catch (const char* e)
		{
			std::cout << e;
		}

		try
		{
			st.push(33);
			std::cout << "\n#0: " << st[0];
			st[0] = 333;

			std::cout << "\noper[]:\n";
			std::cout << "\n#0: " << st[0];
			std::cout << "\n#12: " << st[12];
		}
		catch (ErrorStack & e)
		{
			std::cout << "\nout of range: index " << e.m_i << " size " << e.m_n;
		}
		catch (const char* e)
		{
			std::cout << e;
		}
	}
		stop

	{
		MyStack <MyString,10>st;
		try
		{

			for (int i = 0; i < 11; i++)
			{
				char str[2];

				str[0] = i + 'A';
				str[1] = 0;
				st.push(str);//в MyStrin разрешено неявноне преобразование ,  а то иначе st.push(MyString(str))
			}
		}
		catch (const char* e)
		{
			std::cout << e;
		}

		try
		{
			std::cout << "\noper[]:\n";
			std::cout << "\n#0: " << st[1];
			std::cout << "\n#2: " << st[2];
			st[2] = MyString("CCC");
			st[1] = MyString("BBB");
			std::cout << "\n#1new: " << st[1];
			std::cout << "\n#2new: " << st[2];
		}
		catch (ErrorStack & e)
		{
			std::cout << "\nout of range: index " << e.m_i << " size " << e.m_n;
		}

		std::cout << "\nread all stack:";
		for (int i = 0; st.size() > 0; i++)
			std::cout << "\n#" << i << ": " << st.pop();
		stop
		try
		{
			for (int i = 0; ; i++)
				std::cout << "\n#" << i << " : " << st.pop();
		}
		catch (const char* e)
		{
			std::cout << e;
		}

		try
		{
			st.push("A");
			std::cout << "\n#0: " << st[0];
			st[0] = "AAA";//в MyStrin разрешено неявноне преобразование

			std::cout << "\noper[]:\n";
			std::cout << "\n#0: " << st[0];
			std::cout << "\n#12: " << st[12];
		}
		catch (ErrorStack & e)
		{
			std::cout << "\nout of range: index " << e.m_i << " size " << e.m_n;
		}
		catch (const char* e)
		{
			std::cout << e;
		}
		stop
	}
		stop
		{//one two three four five six seven eight nine ten
			MyStack<MyString,10> st1;
			st1.push(MyString("one"));
			st1.push(MyString("two"));

			MyStack<MyString, 10> st2 = st1;

			std::cout << "\nread all stack:";

			for (size_t i = 0; i < st2.size(); i++)
				std::cout << "\n#" << i << ": " << st2[i];

			MyStack<MyString, 10> st3;
			st3.push(MyString("SSS"));

			st2.push(MyString("free"));
			st2.push(MyString("four"));

			st3 = st2;

			for (size_t i = 0; i < st3.size(); i++)
				std::cout << "\n#" << i << ": " << st3[i];
			stop

			{
				MyStack<MyString, 10> st33;
				st33.push(MyString("3333"));
				st33.push(MyString("4444"));
				MyStack<MyString, 10> st4 = std::move(st33);

				for (size_t i = 0; i < st4.size(); i++)
					std::cout << "\n#" << i << ": " << st4[i];

				st4 = std::move(st2);

				for (size_t i = 0; i < st4.size(); i++)
					std::cout << "\n#" << i << ": " << st4[i];
			}
				stop
		}

			stop


			//Задание 2. Реализуйте шаблон стека - MyStack2 таким образом, чтобы 
			//для хранения элементов использовался ОДНОСВЯЗНЫЙ список.
			//Реализуйте возможность распечатать элементы стека в том порядке, в котором их заносил (push())
			//пользователь

			{
			MyStack2<int, 4> st21;
			try {
				st21.push(1);
				st21.push(2);
				st21.push(3);
				st21.push(4);
				st21.push(5);
			}
			catch (const char* e)
			{ std::cout << e; }

			
			std::cout << "\nafter push: ";
			std::cout << st21;
			stop
			try
			{
				st21.pop();
				st21.pop();
			}
			catch (const char* e)
			{ std::cout << e; }
			std::cout << "\nafter pop: ";
			std::cout << st21;
			stop
				std::cout << "\nafter oper[i]: ";
				try {
				std::cout << "\n#0: " << st21[0];
				std::cout << "\n#1: " << st21[1];
			}
			catch (const char* e) { std::cout << e; }
			catch (ErrorStack2 & e)
			{
				std::cout << "\nout of range: index " << e.m_i << " size " << e.m_n;
			}
			stop

			st21.print_reverse(st21.getHead());

			stop
	}
	stop

	return 0;
}

