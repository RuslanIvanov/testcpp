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
	MARSHRUT(SVETOFOR*,STRELKA*,unsigned short a,unsigned short b)
	{
		 m_set[0] = a; m_set[1] = b;
		 std::cout << "MARSHRUT() <"<< m_set[0]<<" | "<< m_set[1] <<">\n";  
	}
	~MARSHRUT() { std::cout << "~MARSHRUT() ["<< m_set[0]<<" | "<< m_set[1] <<"]\n"; }

	MARSHRUT * GetObj()
	{
		std::cout<<" this = " << this <<'\n';
		return this;
	}

	void GetXy()
	{
		 std::cout<<" x "<<m_set[0] <<" y "<<m_set[1]<<'\n';
	}

	unsigned char GetStatus()  { return status; }
	unsigned char GetConnect() { return przmar; }
};

int main( )
{
    	//std::vector<int> c = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	//std::vector<int> c;
	//for(int i=0;i<10;i++)
	//c.push_back(i);

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

//	std::cout << '\n';

	std::vector<MARSHRUT> m;
	std::cout<<"PUSH========================================================"<<'\n';

	m.push_back(MARSHRUT(NULL,NULL,1,1));
	m.push_back(MARSHRUT(NULL,NULL,2,2));
	m.push_back(MARSHRUT(NULL,NULL,3,3));
	m.push_back(MARSHRUT(NULL,NULL,4,4));

	std::cout<<"OUT["<<m.size()<<"]========================================================"<<'\n';

	for(int i=0;i<m.size();i++)
	{
		MARSHRUT * p = (m.begin()+i)->GetObj();
   		std::cout<<" p = " << p <<'\n';

		(m.begin()+i)->GetXy();

		std::cout<<" i = "<<i<<"\n";
	}

	std::cout<<"ERACE======================================================"<<'\n';
	m.erase(m.begin()+2);

	std::cout<<"OUT["<<m.size()<<"]========================================================"<<'\n';
	for(int i=0;i<m.size();i++)
        {
                MARSHRUT * p = (m.begin()+i)->GetObj();
                std::cout<<"p = " << p <<'\n';

                (m.begin()+i)->GetXy();
        }


	std::cout<<"ERACE ALL ["<<m.size()<<"]====================================================="<<'\n';

	 m.erase(m.begin());
	 m.erase(m.begin()+1);
	 m.erase(m.begin()+2);

	std::cout<<"OUT["<<m.size()<<"]========================================================"<<'\n';


}
