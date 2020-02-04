#pragma once
#define GLOB
#ifdef GLOB
template <typename T,size_t> class MyStack2;
//declaration
template <typename T,size_t m_n>
std::ostream& operator<<(std::ostream& os, const MyStack2<T,m_n>& );
#endif

struct ErrorStack2
{
    size_t m_n;
    size_t m_i;

    ErrorStack2(size_t i, size_t n)
    {
        m_n = n;
        m_i = i;
    }

};


template <typename T, size_t m_n = 10> class MyStack2
{
    struct Node
    {
        Node() : m_next(nullptr) { }
        Node(const T& t) : m_t(t), m_next(nullptr) { }
        ~Node()
        {
           m_t.~T();
        }
        // Значение узла
        T m_t;
        // size_t m_numNode;
        // Указатель на следующий узел
        Node* m_next;
    };


    // Голова односвязного списка
    Node* m_head;

    size_t m_index;// кол объектов в екторе до m_n

public:

    MyStack2(): m_head(nullptr) 
    {
        m_index = 0;
    }

    ~MyStack2()
    {
        while (m_head)
        {
                Node* p = m_head->m_next;
                delete m_head;
                m_head = p;
                m_index--;
        }
    }


	MyStack2(const MyStack2& st )
	{		
		size_t i = 0;
		for (; i < st.m_index && i<m_n; i++)// скопировать то что можно
		{
			//m_p[i] = st.m_p[i];
		}

		m_index = i;

	}

	MyStack2& operator=(const MyStack2& st)
	{
		if (this == &st) return *this;

		size_t i = 0;
		for (; i < st.m_index && i < m_n; i++)// скопировать то что можно
		{	
			if(i<m_index)
				{}
			else
			{
				try 
				{
					//push(st.m_p[i]);
				}
				catch (const char* e)
				{
					//std::cout << e;
					throw e;
				}
			}

		}
		m_index = i;
		
		return *this;

	}

	MyStack2( MyStack2&& st)
    {
       m_index = st.m_index;
	   
       st.m_index = 0;
	   std::cout<< "\nrun constr move&& ";

	   stop
    }

	MyStack2& operator=(MyStack2&& st)
	{
		if (this == &st)
		{
			return *this;
		}


		std::cout<< "\nrun oper move&& ";
	    stop
		return *this;
	}	
/*
MyStack2.h: In member function ‘T& MyStack2<T, <anonymous> >::operator[](size_t) [with T = int; unsigned int m_n = 4u; size_t = unsigned int]’:
MyStack2.h:87:5: warning: control reaches end of non-void function [-Wreturn-type]
*/
    T& operator[](size_t i)
    {

        if (i < m_index) // только сколько внесено
        {
            size_t ii = 0;
            Node* p = m_head;
            while (p)
            { 
                if (ii == i)
                {
                    return p->m_t;
                }
                else p = p->m_next;
                ii++;
            }
            if (p == nullptr)
            {
                throw "\nError.  Stack is empty!";
            }
        }
        else { throw ErrorStack2(i, m_index); } // throw std::out_of_range;
    }

    void push(const T& p) // вставялть
    {
        if (m_index < m_n)//голова - это последний который вставили
        {
           Node* pNode = nullptr;
           try
           {
                pNode = new Node(p);
           }
           catch (std::bad_alloc&  e) { std::cout << e.what(); throw ; } //перебрасывает объект исключения типа std :: length_error;

           if (m_head)
           {
                pNode->m_next = m_head;// вставка перед головой
                m_head = pNode;// текущий становится головой
           }
           else { m_head = pNode; }

           m_index++;
        }
        else
        {
            throw "\nError push. Exit  of size stack!";
        }
    }

    void pop() // выталкивать
    {
        if (m_index > 0 && m_index <= m_n)
        {
            if (m_head)// удалять с головы, потом прерназначить новую голову
            {
               m_index--;
              
               Node* p = m_head->m_next;
               delete m_head;
               m_head = p;
            }
        }
        else
        {
            throw "\nError pop. Exit  of size stack!";
        }

    }

    bool empty() { return (m_index == 0); }
    size_t size() { return m_index; }
	Node* getHead() { return m_head; }

    void print_reverse(struct Node* pHead)
    {
		if(pHead==nullptr) return;
		print_reverse(pHead->m_next);
		std::cout<<"\n" << pHead->m_t;
    }

	#ifdef GLOB
	friend  std::ostream& operator<< <> (std::ostream& os, const MyStack2& s);
	#else
    friend  std::ostream& operator<< (std::ostream& os, const MyStack2& s)
    {
		const  MyStack2::Node* p = s.m_head;
		while (p)
    	{
        	os<<"\n"<<p->m_t;
			p = p->m_next;
    	}
    	return os;
   }
	#endif
};

//definition
#ifdef GLOB

template <typename T,size_t m_n>
std::ostream& operator<<(std::ostream& os, const MyStack2<T,m_n>& s)
{
   const class /*typename*/ MyStack2<T,m_n>::Node* p = s.m_head;

   while (p)
   { 
        os<<"\n"<<p->m_t;
        p = p->m_next;
   }

   return os;
}
#endif
