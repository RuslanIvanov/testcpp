#pragma once

struct ErrorStack
{
	size_t m_n;
	size_t m_i;

	ErrorStack(size_t i, size_t n) 
	{
		m_n = n;
		m_i = i;
	}

};


template <typename T, size_t m_n = 10> class MyStack
{	
	T m_p[m_n];
	size_t m_index;// кол объектов в екторе до m_n

public:

	MyStack()
	{
		m_index = 0;
		for (size_t  i=0; i < m_n; i++)
		{
			m_p[i] = T();
		}

	}

	MyStack(const MyStack& st )
	{		
		size_t i = 0;
		for (; i < st.m_index && i<m_n; i++)// скопировать то что можно
		{
			m_p[i] = st.m_p[i];
		}

		m_index = i;

	}

	MyStack( MyStack/*<T,m_n>*/&& st)
    {
       m_index = st.m_index;
	   //m_p = st.m_p;// для st.m_p деструктор отработает по m_n //??? m_p is const
	   std::swap(m_p,st.m_p); 
       st.m_index = 0;
	   std::cout<< "\nrun constr move&& ";

	   stop
    }

	MyStack& operator=(MyStack&& st)
	{
		if (this == &st)
		{
			return *this;
		}

//		for (size_t i = 0; i < m_n; i++)m_p[i].~T();

		m_index = st.m_index;
		//m_p = st.m_p; // для st.m_p деструктор отработает по m_n
		std::swap(m_p,st.m_p); 
		st.m_index = 0;

		std::cout<< "\nrun oper move&& ";
	    stop
		return *this;
	}	

	MyStack& operator=(const MyStack& st)
	{
		if (this == &st) return *this;

		size_t i = 0;
		for (; i < st.m_index && i < m_n; i++)// скопировать то что можно
		{	
			if(i<m_index)
				m_p[i] = st.m_p[i];
			else
			{
				try 
				{
					push(st.m_p[i]);
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

	~MyStack()
	{	//сколько сконструировал пользователь и по T(), столько и удаляю => m_n
		for (size_t i = 0; i < m_n; i++)
			m_p[i].~T();
	}

	T operator[](size_t i) const//для стека только читаtь
	{
		if (i < m_index) // только сколько внесено
		{
			return m_p[i];
		}
		else throw ErrorStack(i, m_index);// throw std::out_of_range;
	}

	T & operator[](size_t i) //для стека -> внести только те которые уже были внесены ренее пользователем
	{
		if (i < m_n && i < m_index)
		{
			return m_p[i];
		}
		else throw ErrorStack(i, m_index);// throw std::out_of_range;
		
	}

	void push(const T& p) // вставялть
	{		
		if (m_index < m_n)
		{
			m_p[m_index] = p;
			m_index++;
		}
		else 
		{
			throw "\nError push. Exit  of size stack!";
		}
	}

	T& pop() // выталкивать
	{
		
		if (m_index > 0 && m_index <= m_n)
		{
			m_index--;
			return  m_p[m_index];
		}
		else
		{
			throw "\nError pop. Exit  of size stack!";
		}

	}

	bool empty() { return (m_index == 0);  }
	size_t size() { return m_index; }// количество элементов в контейнере
};
