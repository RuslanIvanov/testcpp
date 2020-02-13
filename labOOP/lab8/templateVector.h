 #pragma once
#include <iostream>
#include <typeinfo>

template <typename T> void printParamCont(const T& t)
{
	std::cout << "\n------------------------------------------------";
    std::cout << "\nContainer '"<< typeid(t).name() << "' params:";
	std::cout << "\n name: " << typeid(t).name();
	std::cout << "\n size: "<< t.size();
	std::cout << "\n capacity: " << t.capacity();
	std::cout << "\n max_size: " << t.max_size();
	std::cout << "\n------------------------------------------------";
}

template <typename P> void printCont(const P& p)
{
	std::cout << "\nContainer '"<< typeid(p).name() << "' contains:";
	if (p.empty())
	{
		std::cout << "  IS EMPTY!";
		return;
	}
	std::cout << "\n";
	for (size_t i = 0; i < p.size(); i++)
	{
		std::cout << " | " << p[i];
	}
}

class Point;
template <>
void printCont<std::vector<Point*>>(const std::vector<Point*>& p)
{
    std::cout << "\nContainer '" << typeid(p).name() << "' contains:";
	if (p.empty())
	{
		std::cout << "  IS EMPTY!";
		return;
	}
	std::cout << "\n";
	for (size_t i = 0; i < p.size(); i++)
	{
		if (p[i] == nullptr) continue;
		
		//p[i]->print();
		//std::cout << "\n" << p[i];
		std::cout << " | " << *p[i];
	}
	
}

template <typename TT>
void printContAny(const TT& t)
{
    std::cout << "\nContainer '" << typeid(t).name() << "' contains:\n";
	if (t.empty())
	{
		std::cout << "  IS EMPTY!";
		return;
	}

    typename TT::const_iterator iter;
	for (iter = t.begin(); iter != t.end(); iter++)
	{
		std::cout << " | " << *iter;
    }
}

template <typename U> 
void makeUniqOnlyEven(U& u)
{// нечетные не удаляет
    std::cout<<"\nmakeUniqAll";
    std::cout<<"\nsource: ";
    printCont(u);

    typename U::iterator itb = u.begin();
    typename U::iterator ite = u.end();

    for (size_t i = 0; i < u.size() /* itb!=ite */ ; i++)
    {
        if(*(itb) == *(itb+1))
        {
            //std::cout<<"\nerase i  =  " <<i  << " del: " << *(itb);
            //std::cout<<"\nerase i+1=  " <<i+1<< " del: " << *(itb+1);
			if ((itb + 2) == u.end())
				break;
            itb = u.erase(itb,itb+2);// itb_next = erase(first,last); [first,next)
            if(itb==u.end()) break;
        }else { ++itb; }

        //std::cout<<"\n i = " <<i<< " element next: " << *(itb);
        //std::cout<< "\nsize: "<< u.size();
    }

    std::cout<<"\nafter delete:";

    printCont(u);
}


template <typename U>
void makeUniqAll(U& u)
{// интервал убрать// делает тоже что и deleteAllDuplicate
    std::cout<<"\nmakeUniqAll";
    std::cout<<"\nsource_err1: ";
    printCont(u);

    typename U::iterator itb = u.begin();
    typename U::iterator ite = u.end();
    typename U::iterator itmp = u.begin();
	typename U::iterator itmp2 = u.begin();
	int count = 0; size_t n = u.size(); 
    for (size_t i = 0; i<n ; i++)// itb != ite
    {
		if (itb == u.end())  break;

		itmp = itb;		
        itmp2 = itb+1;
        size_t nn = u.size();
        for(size_t ii = 0;ii < nn;ii++)// itmp2 != ite; 
        {
			//if (itmp2 == u.end())  break;
            if( (itmp2 != u.end()) && (*(itmp2) == *(itmp)))
            {
                
                 ++itmp2;
                count++;
            }else
            {
                if(count>0)
                {
                    itb = u.erase(itmp + 1, itmp2);
					
					break;
                }
          
				count = 0;

            }
        }

		if (count == 0)
		{
			++itb; count = 0;
		}
		int a = 0;
       	 
        //std::cout<<"\n i = " <<i<< " element next: " << *(itb);
        //std::cout<< "\nsize: "<< u.size();
    }

    std::cout<<"\nafter delete:";
    printCont(u);
}//*/

template <typename U>
void deleteAllDuplicate(U& u)
{
	
    std::cout<<"\ndeleteAllDuplicate";
    std::cout<<"\nsource: ";
    printCont(u);

    typename U::iterator itb = u.begin();
    typename U::iterator ite = u.end();
    typename U::iterator itmp = u.begin();

   // for (size_t i = 0; itmp!=ite  ; i++) ///i<u.size()
	for (size_t i = 0; i < u.size(); i++)
    {
		itb = itmp+1;

       // for (;itb!=ite;)
		for(int ii = 0 ; ii<u.size();ii++)
        {
            //std::cout<<"\n' " <<*itb<<" ',find is ' " << *itmp <<" '";
			if (itb == u.end()) break;

            if(*(itmp) == *(itb))
            {
                //std::cout<<"\n del: " <<*itb;
				if (itb == u.end()) break;

                itb = u.erase(itb);

                if(itb==u.end()) break;

                //std::cout<<"\nnext: " <<*itb;
            }else
            {
                ++itb;
                if(itb==u.end()) break;
                //std::cout<<"\nnext. " <<*itb;
            }

            //std::cout<< "\nsize: "<< u.size() << "first: " << *u.begin();
        }

        itmp++;

        if(itmp==u.end()) break;

        //std::cout<< "\nsize: "<< u.size()<< "first: " << *u.begin();
    }
	
    std::cout<<"\nafter delete:";
    printCont(u);

}

/*template<typename T> bool predPointTempl(const T& l);
template<> bool predPointTempl<Point>(const Point& l)
{
    std::cout<<"\npredPointTempl:";

    return ((l.GetX()<0) || (l.GetY()<0));
}//*/

bool predPoint(const Point& l)
{
    //std::cout<<"\npredPoint:";

    return ((l.GetX()<0) || (l.GetY()<0));
}
