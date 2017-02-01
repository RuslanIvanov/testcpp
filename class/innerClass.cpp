#include <iostream>
using namespace std;

class A
{
    class B{
    public:
        int r;
        B() :r(67){}
        B(int t):r(t)
 	{
        }
    };

public:
    B obj1;
    B obj2;
        B obj3;
    A() {
        B obj1();//конструктор без параметров
                B obj2();
    }
    A(int t)
    {
                B obj1(t);
        B obj2(t);//конструктор с параметром почему ошибка?
    }
    void funk(){
        B obj3(78); //конструктор с параметром
    }
};
int main()
{
    A i;
}
