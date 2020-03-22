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

#include "MyString.h"
#include "lab2_cpp11_14.h"
#include "MyVector.h"
#include "MyQueue.h"

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


int main(int, char**)
{

#if  _WIN32 
	setlocale(LC_CTYPE, ".UTF8");
        cout << "Привет лаб2 C++11,14,17!";
        stop
#endif
	MyVector<int> mv1;
	mv1.printVect();

	MyVector<int> mv2(1,8,{1,2,3,4,4,5,6,7,8,9,10,11,12,13,14,15});
	mv2.printVect();
	mv2.applyList(2, 55, { 9,8,7,7,6,55,5,5,4,4,3,2,1,0,10,33,12,13,66,77,88 });
	mv2.printVect();
	mv2.deleteList(0, 5,{1,2,3,4,5,6,7,8,9,10});
	mv2.printVect();
	mv2.sort(true);
	mv2.printVect();
	mv2.sort(false);
	mv2.printVect();

	///////////////////////////////////////////////////////////////////////////////////

        {
        std::cout << "\nMyQueue<int>:------------------------------------------------------------\n";
        MyQueue<int> mq = {0, 1, 2, 3, 4, 5, 8, 7, 8, 9 };

	std::cout <<"\nMyQueue: ";
        for (auto& el : mq) {std::cout << el << '_';}
        stop
        mq.push(10);
        mq.push(11);
        mq.push(12);
        mq.push(13);
       //mq.printQueueRaw();
       //stop
        mq.printQueue();
        stop
        size_t n = mq.size()+4;
        std::cout<<"\nnew size "<<n<<"\n";
        for(size_t i =0; i < 4; i++)
        {
             mq.push(i+n);
        }

        mq.printQueue();
        stop
        MyQueue<int> mq2 = mq;
        mq2.printQueue();
        stop

        MyQueue<int> mq3 { 5, 5, 5 };
        mq3.printQueue();
        stop
        mq3 = mq2;
        std::cout <<"\nmq3: \n";
        mq3.printQueue();
        stop

        try{
        size_t el[2];
        el[0] =  mq3.pop();
        el[1] =  mq3.pop();
        std::cout <<"\npop "<< el[0];
        std::cout <<"\npop "<< el[1];
        }catch(const char *e) {std::cout<<e; }
        mq3.printQueue();
        std::cout <<"\nMyQueue 3[.]: ";
        for (auto& el : mq3) {std::cout << el << '.';}
        stop
        mq3.push(22);
        mq3.push(23);
        mq3.push(24);
        mq3.push(25);
        mq3.push(26);
        mq3.push(27);
        mq3.push(28);

        mq3.printQueue();
        stop
        std::cout <<"\nMyQueue 3[,]: ";
        for (auto& el : mq3) {std::cout << el << ',';}
        stop
        mq3.push(29);
        mq3.push(30);
        mq3.printQueue();
        std::cout <<"\nMyQueue 3: ";
        for (auto& el : mq3) {std::cout << el << ':';}
        stop
        std::cout << "\nMyQueue<int>:------------------------------------------------------------\n";

        stop

        }
	//////////////////////////////////////////////////////////////////////////////////
	MyQueue<MyString>  q1{ MyString("AAA"), MyString("qwerty"), MyString("BBB"),  MyString("CCC")};

	std::cout << "\nMyQueue: ";
	for (auto& el : q1) { std::cout << el << ' '; }

	MyString s("abc");
	q1.push(s);
	q1.push(MyString("123"));
	MyString s1 = q1.pop();
	std::cout << "\ns1 = " << s1;
	q1.push("qqq");
	q1.printQueue();
        stop
	MyQueue < MyString >  q2 = q1;
	MyQueue < MyString >  q22 = std::move(q1);
        std::cout << "\nq1 after move ";
	q1.printQueue();
        std::cout << "\nq22 after move ";
        q22.printQueue();
        stop

	MyQueue < MyString >  q3{ 10, MyString("!") }; ///очередь должна содержать 10 элементов со строкой «!» 
	q3.printQueue();
	q1 = q3;
        q1.printQueue();
        stop

	q2 = MyQueue < MyString >(5, MyString(" ? "));
        std::cout << "\nq2 after move oper=()";
        q2.printQueue();

	q1 = { MyString("bbb"), MyString("ssss") };
        std::cout << "\nq1 after move oper=()";
        q1.printQueue();
	///////////////////////////////////////////////////////////////////////////////////
	stop
	return 0;
}
