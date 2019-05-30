#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

class SVETOFOR
{

};

class STRELKA
{

};

class MARSHRUT
{

	unsigned short m_set[2];
	unsigned char status;
	unsigned char przmar;
public:

	MARSHRUT() { std::cout << "MARSHRUT()\n"; }
	MARSHRUT(SVETOFOR*,STRELKA*,unsigned short a,unsigned short b) { std::cout << "MARSHRUT2()\n"; m_set[0] = a; m_set[1] = b; }
	~MARSHRUT() { std::cout << "~MARSHRUT()\n"; }

	MARSHRUT * GetObj()
	{
		std::cout<<"this = " << this <<'\n';
		return this;
	}

	void GetXy()
	{
		 std::cout<<"\nx "<<m_set[0] <<" y "<<m_set[1]<<'\n';
	}

	unsigned char GetStatus()  { return status; }
	unsigned char GetConnect() { return przmar; }
};

int main( )
{
    	//std::vector<int> c = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::vector<int> c;
	for(int i=0;i<10;i++)
	c.push_back(i);

    	/*for (auto &i : c)
	{
        	std::cout << i << " ";
    	}
    	std::cout << '\n';

    	c.erase(c.begin());

    	for (auto &i : c)
	{
        std::cout << i << " ";
    	}
    	std::cout << '\n';

    	c.erase(c.begin()+2, c.begin()+5);

    	for (auto &i : c)
	{
        	std::cout << i << " ";
    	}*/

	std::cout << '\n';

	std::vector<MARSHRUT> m;
	m.push_back(MARSHRUT(NULL,NULL,1,2));
	m.push_back(MARSHRUT(NULL,NULL,3,4));
	m.push_back(MARSHRUT(NULL,NULL,5,6));
	m.push_back(MARSHRUT(NULL,NULL,7,8));


	for(int i=0;i<m.size();i++)
	{
		MARSHRUT * p = (m.begin()+i)->GetObj();
   		std::cout<<"p = " << p <<'\n';

		(m.begin()+i)->GetXy();

	}
}
