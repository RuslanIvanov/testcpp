#pragma once

//template <typename T,size_t> class MyStack2;
//declaration
//template <typename T,size_t m_n>
//std::ostream& operator<<(std::ostream& os, const MyStack2<T,m_n>& );

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
        else throw ErrorStack2(i, m_index);// throw std::out_of_range;
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

    void print_reverse()
    {
    }

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
};

//definition
/*template <typename T,size_t m_n>
std::ostream& operator<<(std::ostream& os, const MyStack2<T,m_n>& s)
{
   // const  MyStack2<T,m_n>::Node* p = s.m_head;

   // while (p)
   // {       
    //     os<<"\n"<<p->m_t;

//         p = p->m_next;
//    }

    return os;
}*/
