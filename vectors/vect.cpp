#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_UNION_MAR 4

class MARSHRUT;
typedef	struct
{
		void * m_mars[MAX_UNION_MAR];
}DISCRIPTOR_MAR;


/*
void SetAddrAD_AO_Global(void *p, int i)  
{
	if(i<MAX_UNION_MAR) 
	{ m_fd_mar.m_mars[i] = p;  } 
	else 
	{ m_fd_mar.m_mars[i] = NULL; } 
}*/

class SVETOFOR
{

};

class STRELKA
{

};

class MARSHRUT
{
	DISCRIPTOR_MAR m_fd_mar;
	unsigned short m_set[2];
	unsigned char status;
	unsigned char przmar;
public:

	MARSHRUT()
 	{ 
		std::cout << "MARSHRUT()\n";  m_set[0] = 0; m_set[1] = 0; status=przmar='a'; 
		m_fd_mar.m_mars[0]=NULL;m_fd_mar.m_mars[1]=NULL;m_fd_mar.m_mars[2]=NULL;m_fd_mar.m_mars[3]=NULL;
	}
	MARSHRUT(SVETOFOR*,STRELKA*,unsigned short a,unsigned short b)
	{
		 m_set[0] = a; m_set[1] = b; status=przmar='b';
		 std::cout << "MARSHRUT() <"<< m_set[0]<<" | "<< m_set[1] <<">\n";
		m_fd_mar.m_mars[0]=NULL;m_fd_mar.m_mars[1]=NULL;m_fd_mar.m_mars[2]=NULL;m_fd_mar.m_mars[3]=NULL;
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

	unsigned char GetStatus() { std::cout << "\nstatus "<<status<<std::endl;  return status; }
	unsigned char GetConnect(){ std::cout << "\nprzmar "<<przmar<<std::endl;  return przmar; }
	const unsigned short* GetSet() { return &m_set[0]; }
	void SetSet(unsigned char s1,unsigned char s2 ) { m_set[0]= s1; m_set[1] = s2; }

	void SetAddrAD_AO(void *p, int i) 
	{
		if(i<MAX_UNION_MAR) 
		{ m_fd_mar.m_mars[i] = p;  } 
		else 
		{ m_fd_mar.m_mars[i] = NULL;  std::cout<<"SetAddrAD_AO: is NULL i "<<i<<'\n'; } 
	}

	void f() 
	{	
		std::cout<<"F: 1 "<<'\n';
		MARSHRUT* p1 = (MARSHRUT*)m_fd_mar.m_mars[0];
		std::cout<<"F: 2 "<<'\n';
		MARSHRUT* p2 = (MARSHRUT*)m_fd_mar.m_mars[1];

		std::cout<<"F: 3 "<<'\n';
		if(p1!=NULL)
		p1->GetStatus();
		std::cout<<"F: 4 "<<'\n';
		if(p2!=NULL)
		p2->GetStatus();
		std::cout<<"F: 5 "<<'\n';
	}
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

	MARSHRUT *ppm  = &(*mar.begin());
	ppm->SetSet(77,77);
	ppm->GetXy();

	MARSHRUT *pppm  = &(*(mar.begin()+1));
        pppm->SetSet(88,88);
        pppm->GetXy();
	ppm->GetXy();


	std::cout<<"OUT MAR["<<mar.size()<<"]========================================================"<<'\n';

	if(mar.size()>2)
	{
		mar[2].SetAddrAD_AO(&(*(mar.begin())),0);
		mar[2].SetAddrAD_AO(&(*(mar.begin()+1)),1);
		std::cout<<"F: -1 "<<'\n';
	}
	if(mar.size()>3)
	{
		mar[3].SetAddrAD_AO(&(*(mar.begin())),0);
		mar[3].SetAddrAD_AO(&(*(mar.begin()+1)),1);
		std::cout<<"F: 0 "<<'\n';
	}
	std::cout<<"++++++++++++++++++++++++++========================================================"<<'\n';

	mar[2].f();
	std::cout<<"------------------------------------------------------------------------------------"<<'\n';
	mar[3].f();

	//MARSHRUT *p1  = (MARSHRUT*) m_fd_mar.m_mars[0];
	//MARSHRUT *p2  = (MARSHRUT*) m_fd_mar.m_mars[1];

	
	//p1->GetXy();
	//p2->GetXy();


	//if(NULL == 0) {printf("NULL == 0");}
}

