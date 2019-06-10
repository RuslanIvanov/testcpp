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

	MARSHRUT() { std::cout << "MARSHRUT()\n";  m_set[0] = 0; m_set[1] = 0; status=przmar=0; }
	MARSHRUT(SVETOFOR*,STRELKA*,unsigned short a,unsigned short b)
	{
		 m_set[0] = a; m_set[1] = b; status=przmar=1;
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

	unsigned char GetStatus() { std::cout << "\nstatus"<<status;  return status; }
	unsigned char GetConnect(){ std::cout << "\nprzmar"<<przmar;  return przmar; }
	const unsigned short* GetSet() { return &m_set[0]; }
	void SetSet(unsigned char s1,unsigned char s2 ) { m_set[0]= s1; m_set[1] = s2; }

};

int main( )
{
    	//std::vector<int> c = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> c(10);
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

	MARSHRUT mTest (NULL,NULL,111,111);

	//mTest.GetSet()[0] = 112;

	std::cout<<"\n| "<<mTest.GetSet()[0]<<" : "<<mTest.GetSet()[1] << '\n';

	getchar();

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

	std::vector<MARSHRUT> mar(9);
	std::cout<<"OUT MAR["<<mar.size()<<"]========================================================"<<'\n';

	for(int i=0;i<mar.size();i++)
        {
                MARSHRUT * p = (mar.begin()+i)->GetObj();
                std::cout<<"p = " << p <<'\n';

                (mar.begin()+i)->GetXy();
        }


	for(int i =1 ; i<=2; i++)
	{
		//if(mar.size() == 0)
		//{	mar.push_back(MARSHRUT(NULL,NULL,5,5));
		//	std::cout<<"push";
		//}
		//else
		{
			mar[i-1] =  MARSHRUT(NULL,NULL,6+i,6+i);
		}
	}

	std::cout<<"OUT MAR["<<mar.size()<<"]========================================================"<<'\n';

	for(int i=0;i<mar.size();i++)
        {
                MARSHRUT * p = (mar.begin()+i)->GetObj();
                std::cout<<"p = " << p <<'\n';

                (mar.begin()+i)->GetXy();
        }

	MARSHRUT mm(NULL,NULL,9,9);
	mar[1] =  mm;

	std::cout<<"OUT MAR["<<mar.size()<<"]========================================================"<<'\n';

        for(int i=0;i<mar.size();i++)
        {
                MARSHRUT * p = (mar.begin()+i)->GetObj();
                std::cout<<"p = " << p <<'\n';

                (mar.begin()+i)->GetXy();
        }

	MARSHRUT *pm = (mar.begin()+0)->GetObj();
	pm->SetSet(100,100);

	//MARSHRUT m = mar[0];
	pm->GetXy();
}

