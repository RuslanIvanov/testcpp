// lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MyString2.h"

void mystop()
{
        std::cout << "\nPause\n";
        getchar();
}

#define  stop  {mystop();}


int main()
{
    std::cout << "Hello World!\n";
    MyString2 str("ABC");
    MyString2 str2("ABC2");
    MyString2 str3("ABC3");
    MyString2 str4("ABC3");
    MyString2 str5("ABC3");

    	std::cout<<str;
     	std::cout<<str2;
 	std::cout<<str3;
	std::cout<<str4;
	std::cout<<str5;

    stop

        
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
