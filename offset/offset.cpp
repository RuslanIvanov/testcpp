#include <iostream>
#include <cstddef>
struct S 
{
    char c;
    double d;
};

int main()
{
    std::cout << "the first element is at offset " << offsetof(S, c) << '\n'
              << "the double is at offset " << offsetof(S, d) << '\n';
}


/*

Возвращает смещение члена относительно начала его родительской структуры.

*/
