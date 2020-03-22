#pragma once
#include <algorithm>
#include <string.h>
#include <iterator>
#include <utility>
#include <initializer_list>
template<typename T>
class MyQueue
{
	T* m_pmass;
        size_t m_n;// kol-vo elementov v buf
        size_t m_cap;// razmer buf        
	size_t m_first;
	size_t m_last;
        const size_t MAX_RESIZE = 5;
        const size_t RESIZE = 5;
public:

	MyQueue( std::initializer_list<T> );
	MyQueue(size_t n);
	MyQueue(size_t n, const T& );
	MyQueue();
	~MyQueue();

	MyQueue(const MyQueue&);
	MyQueue(MyQueue&&);
	MyQueue& operator=(const MyQueue&);
	MyQueue& operator=(MyQueue&&);

	void push(const T&);
	T pop();
	void printQueue();
        void printQueueRaw();

       T* begin()
        {
            return &m_pmass[m_first];
        }
        T* end()
        {
            return &m_pmass[(m_first+m_n)%m_cap];
        }//*/
       // T* begin(){return m_pmass;}
      //  T* end() { return m_pmass + m_n;}

        size_t size() { return  m_n;}
        size_t capacity() { return m_cap;}

	friend  std::ostream& operator<< (std::ostream& os, const MyQueue& s)
	{
                for (size_t i = s.m_first; (i < s.m_n); ++i)
		{
                        os << s.m_pmass[i%s.m_n] << "";
		}
		return os;
	}
	
};


template<typename T>
MyQueue<T>::~MyQueue()
{
	delete[] m_pmass;
}

template<typename T>
MyQueue<T>::MyQueue() 
{
        m_cap = MAX_RESIZE;
	m_n = 0;
	m_first = 0;
	m_last = 0;
	try 
	{
		m_pmass = new T[m_cap];
	}
	catch (std::bad_alloc) 
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(size_t n, const T& t) 
{	
	m_n = n;
        m_cap = n+MAX_RESIZE;
	m_first = 0;
	m_last = 0;
	try
	{
                m_pmass = new T[m_cap];

                for(;m_last< m_n;m_last++)
		{
                        m_pmass[m_last] = t;
                }
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(size_t n)
{
        m_cap =n+MAX_RESIZE;
	m_n = n;
	m_first = 0;
	m_last = 0;
	try
	{
                m_pmass = new T[m_cap];
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue( std::initializer_list<T> list )
{

        m_n = list.size();// count elements
        m_cap = m_n+MAX_RESIZE;
	m_first = 0;
	m_last = 0;
	try
	{
                m_pmass = new T[m_cap];

		for (auto& l : list) 
		{
			m_pmass[m_last] = l;
			m_last++;
		}
	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}
}

template<typename T>
MyQueue<T>::MyQueue(const MyQueue& r)
{
        m_n = r.m_n;
        m_first = 0;
        m_last = 0;
        std::cout<<"\nMyQueue(const MyQueue&): copy r.m_last = "<<r.m_last<<" r.m_n = "<<r.m_n;
        m_cap = r.m_n + MAX_RESIZE;

        try
        {
                m_pmass = new T[m_cap];
                size_t ind1 = r.m_first;
                for (size_t i = 0; i <r.m_n; i++)
                {
                        std::cout<<"\nm_pmass["<<i<<"] <- r.m_pmass["<<ind1%r.m_n<<"] = "<<r.m_pmass[ind1%r.m_n];
                        m_pmass[i] = r.m_pmass[ind1%r.m_n];
                        ind1++;m_last++;
                }

        }
        catch (std::bad_alloc)
        {
                m_pmass = nullptr;
                m_n = 0;
                m_cap = 0;
                std::cout<<"\nMyQueue(const MyQueue&): std::bad_alloc";
        }
}

template<typename T>
MyQueue<T>::MyQueue(MyQueue&& r)
{
        std::cout<<"\nMyQueue(MyQueue&& )\n";
	m_n=r.m_n;
	m_pmass = r.m_pmass;
        m_cap = r.m_n+MAX_RESIZE;
        m_last = r.m_last;//net perezapisi - ostavit indeksi kak est'
	m_first = r.m_first;

	r.m_n = 0;
	r.m_pmass = nullptr;
	r.m_cap = 0;
	r.m_last = r.m_first = 0;
}

template<typename T> 
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& r)
{
        std::cout<<"\nMyQueue::oper=()\n";

	if (&r == this) return *this;

        m_last = 0;
        m_first = 0;

	try
	{
		if (m_n < r.m_n)
		{
			m_n = r.m_n;
                        m_cap = r.m_n+MAX_RESIZE;
                        std::cout<<"\nresize";
                        T* p = new T[m_cap];
			size_t ind1 = r.m_first;
                        for (size_t i = 0; i < r.m_n; i++)
			{
                                std::cout<<"\np["<<i<<"] <- r.m_pmass["<<ind1%r.m_n<<"]"<<r.m_pmass[ind1%r.m_n];
                                p[i] = r.m_pmass[ind1%r.m_n];//go first to last
                                ind1++;m_last++;
                        }

			delete[] m_pmass;
			m_pmass = p;
		}
		else 
		{
                        m_n = r.m_n;
                        size_t ind1 = r.m_first;
                        for (size_t i = 0; i < r.m_n; i++)
			{
                                std::cout<<"\nm_pmass["<<i<<"]"<<m_pmass[i]<<" <- r.m_pmass["<<ind1%r.m_n<<"]"<<r.m_pmass[ind1%r.m_n];
				m_pmass[i] = r.m_pmass[ind1 % r.m_n];
                                ind1++;m_last++;

			}

		}

	}
	catch (std::bad_alloc)
	{
		m_pmass = nullptr;
		m_n = 0;
		m_cap = 0;
	}

	return *this;
}

template<typename T> 
MyQueue<T>& MyQueue<T>::operator=(MyQueue<T>&& r)
{
        std::cout<<"\nMyQueue::move oper=()\n";

	if (&r == this) return *this;

	m_n = r.m_n;
	delete[] m_pmass;
	m_pmass = r.m_pmass;
        m_cap = r.m_n+MAX_RESIZE;

        m_last = r.m_last;
        m_first = r.m_first;

	r.m_n = 0;
	r.m_pmass = nullptr;
	r.m_cap = 0;
	r.m_last = r.m_first = 0;

	return *this;
}

template<typename T> 
void MyQueue<T>::push(const T& t) 
{	
        std::cout << "\npush: m_n = "<<m_n<<" m_cap = "<<m_cap<<"";

        if (m_n <  m_cap )//count elements < capasity
	{                
                m_pmass[(m_first+m_n)%m_cap] = t;
                std::cout << " add in mass["<<(m_first+m_n)%m_cap<<"] = "<<m_pmass[(m_first+m_n)%m_cap];

                m_last++; //= (m_first+m_n)%m_cap;
                if(m_last>m_n){m_last=0;}
                m_n++;


	}else 
        {
                //m_last = (m_first + m_n) % m_cap;
                //m_pmass[m_last] = t;
                m_cap = m_cap+RESIZE;
                T* p = new T[m_cap];

                size_t ind1 = m_first;
                for (size_t i = 0;i<m_n;i++)
                {
                        p[i] = m_pmass[ind1%m_n];//
                        ind1++;//?

                        std::cout << "\nresize mass["<<i<<"] = "<<p[i];
                }
                m_last=m_n;//
                p[m_last] = t;
                std::cout << " add in mass["<<m_last<<"] = "<<p[m_last];
               // m_last= (m_first+m_n)%m_cap;
                m_n++;
                m_last++;// = (m_first+m_n)%m_cap;
                delete[] m_pmass;
                m_pmass = p;
	}
}

template<typename T>
T MyQueue<T>::pop()
{//error
    size_t ind1 = m_first;

    if(m_n==0){ throw "\nQueue is empty!\n"; }

    if(m_n<m_cap)
    {
        m_first++;
       // ind2 =(m_first+m_n)%m_cap;//position last
        std::cout << "\n[pop mass["<<ind1<<"] = "<<m_pmass[ind1]<<"] ";
        if(m_first>=m_n)
        {
            m_first=0;
        }
        m_n--;
        std::cout << " m_n = "<<m_n<<" m_first "<< m_first;
    }else { throw "\nQueue size is error!\n";  }

    return m_pmass[ind1];
}

template<typename T>
void MyQueue<T>::printQueueRaw()
{
        std::cout << "\nPRINTF RAW MyQueue: ";
        std::cout << " m_n "<<m_n<<" m_cap = "<<m_cap<<"";
        if (m_n==0 || m_pmass==nullptr)
        {
                std::cout << " is EMPTY! "; return;
        }

        for (size_t i = 0; (i < m_n); ++i)
        {
                std::cout <<"\nmass["<<i<<"] = "<< m_pmass[i];
        }
}

template<typename T>
void MyQueue<T>::printQueue()
{
	std::cout << "\nPRINTF MyQueue: ";
        std::cout << " m_n "<<m_n<<" m_cap = "<<m_cap<<"";
	if (m_n==0 || m_pmass==nullptr)
	{
                std::cout << " is EMPTY! "; return;
        }


        std::cout <<"\nfirst "<<m_first;
        std::cout <<" last "<<(m_first+m_n)%m_cap;//m_last;
        //size_t n = (m_first+m_n)%m_cap;
        size_t ind1 = m_first;
        for(size_t i = 0; i < m_n; ++i)
	{
             std::cout <<"\n#"<<i<<" mass["<<ind1%m_cap<<"] = "<< m_pmass[ind1%m_cap];
             ind1++;
              //  if((ind1%m_n) == m_last) { std::cout <<"\nend\n";break;}
           // if(m_last> m_n)
           // std::cout <<"\n#"<<ind1<<" mass["<<ind1%m_n<<"] = "<< m_pmass[ind1%m_n];
          //  else
          //  std::cout <<"\n#"<<ind1<<" mass["<<ind1%m_last<<"] = "<< m_pmass[ind1%m_last];
          //   ind1++;
        }
}
