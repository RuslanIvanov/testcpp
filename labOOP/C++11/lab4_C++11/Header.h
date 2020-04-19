#pragma once

template <typename TT>
 auto& VALIDATE(TT& tt) 
{
	if constexpr (std::is_pointer<TT>::value)
	{
		std::cout << "\nis_pointer ";
		return *tt;
	}
	else
	{
		std::cout << "\nno pointer ";
		return tt;
	}
}

template <typename T>
void PRINTF(const T& t) 
{
	std::cout << "\nPRINTF:\n";
	for (auto it = std::begin(t); it != std::end(t); ++it)
	{
		std::cout << "," << VALIDATE(*it) << " ";//OK
	}
	
}

template <typename T>
auto isPointer(const T& t) 
{
	if constexpr (std::is_pointer<T>::value)
	{
		return true;
	}
	else { return false; }
}

template<typename T>
void PRINTF3(const T& t)
{
	std::cout << "\nPRINTF3:";
	for ( auto& el: t) 
	{ 
		if constexpr (std::is_array<T>::value)
		{
			if constexpr (std::is_pointer<remove_all_extents<T>::type>::value)
			{
				std::cout << "\npoint3 " << *el << " ";
			}
			else
			{
				std::cout << "\nno point3 " << el << " ";
			}
		}
		else
		{
			if constexpr (std::is_pointer<T::value_type>::value)
			{
				std::cout << "\npoint3 " << *el << " ";
			}
			else
			{
				std::cout << "\nno point3 " << el << " ";
			}
		}
	}

}

template <typename T>
constexpr void PRINTF2(const T& t)
{
	std::cout << "\nPRINTF2:";
	for (auto it = std::begin(t); it != std::end(t); ++it)
	{
		
		if constexpr (std::is_pointer<remove_all_extents_t<T>>::value)
		{
			std::cout << "\npoint2' " << **it << "\ntype:  "<< typeid(t).name();
		}
		else
		{
			if constexpr (std::is_array<T>::value == false)
			{
				if  constexpr (std::is_pointer <T::value_type>::value)
				{
					std::cout << "\npoint2'' " << **it << "\ntype:  " << typeid(t).name();
				}
				else
					std::cout << "\nno point2'' " << *it << "\ntype:  " << typeid(t).name();
			}
			else
				std::cout << "\nno point2''' " << *it << "\ntype:  " << typeid(t).name();
		
		}//*/
	}

}

template <typename T,typename TT>
void sumV( T& t,TT tt ) 
{
	if constexpr (std::is_same<T, std::vector<TT>>::value)
	{
		std::cout << "\nsum elements vect on: " << tt;
		for (auto it = std::begin(t);it != std::end(t); ++it) 
		{
			*it += tt;
		}
	}
	else
	{
		std::cout << "\nsum on: " << tt;
		t += tt;
	}
}

template <typename T>
//void PRINT_ADAPT(const T& t) 
void PRINT_ADAPT(T t)
{

	if constexpr (std::is_same<T, std::queue<typename T::value_type>>::value)
	{
		std::cout << "\ncontainer_adapter queue ";
		if constexpr (std::is_pointer<typename T::value_type>::value)
		{
			std::cout << "(pointers): ";
			while (!t.empty())
			{
				std::cout << "," << *t.front()<<" ";
				t.pop();
			}
		}
		else
		{
			std::cout << ":";
		
			while (!t.empty())
			{
				std::cout << "." << t.front() << " ";
				t.pop();
			}
		}
	}

	if constexpr (std::is_same<T, std::priority_queue<typename T::value_type>>::value)
	{
		std::cout << "\ncontainer_adapter priority_queue ";

		if constexpr (std::is_pointer<typename T::value_type>::value)
		{
			std::cout << "(pointer) :";
			while (!t.empty())
			{
				std::cout << "," << *t.top() << " ";
				t.pop();
			}
		}
		else 
		{
			std::cout << ":";
			while (!t.empty())
			{
				std::cout << "." << t.top()<<" ";
				t.pop();
			}
		}
	}

	if constexpr (std::is_same<T, std::stack<typename T::value_type>>::value)
	{
		std::cout << "\ncontainer_adapter stack ";
		if constexpr (std::is_pointer<typename T::value_type>::value)
		{
			std::cout << "(pointer) :";
			while (!t.empty())
			{
				std::cout << "," << *t.top() << " ";
				t.pop();
			}
		}
		else 
		{
			std::cout << ":";
			while (!t.empty())
			{
				std::cout << "," << t.top() << " ";
				t.pop();
			}
		}
	}

	std::cout << "  end\n";
}

class SORT_SET
{
public:
	SORT_SET() {}

	bool operator()(const  std::shared_ptr<string>&  l, const  std::shared_ptr<string>& r) const
	{
		return (*l->begin() < *r->begin());
	}

};

bool cmp(const  std::shared_ptr<string>& l, const  std::shared_ptr<string>& r)
{
	return (*l->begin() < *r->begin());
}

////////////////////////////////////////////////////////////////////////////////////////
//мой вариант
template<typename T, size_t size> 
class MyArray2
{

	T ar[size] = { T() }; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
	size_t m_n=size;
public:
	MyArray2() = default; // констр на тип Т*
	MyArray2(const MyArray2& r) // не надо
	{
		if (r.m_n <= m_n)
		{
			m_n = r.m_n;
			for (size_t i = 0; i < r.m_n; i++)
			{
				ar[i] = r.ar[i];
			}
		}
		else throw "error length!!";
	}

	//MyArray2(MyArray2&& r) 
	//{// нет смысла  ??
	//	ar = r.ar;
	//	m_n = r.m_n;
	//}

	MyArray2(const int& r, size_t n) 
	{
		m_n = n;
		for (size_t i = 0; i < m_n; i++)
		{
			ar[i] = r[i];
		}
	}

	MyArray2(const std::initializer_list<T>& l) 
	{
		if (l.size() <= m_n)
		{ 
			m_n = l.size();
			for (size_t i = 0; i < m_n; i++)
			{
				ar[i] = *(l.begin()+i);
			}
		}
		else throw "error length list!!";
	}//*/

};

template <typename First, typename... Rest> struct EnforceSame2 
{
	static_assert(std::conjunction_v<std::is_same<First, Rest>...>);
	using type = First;
};
template <typename First, typename... Rest> MyArray2(First, Rest...)
->MyArray2<typename EnforceSame2<First, Rest...>::type, 1 + sizeof...(Rest)>;
///////////////////////////////////////////////////////////////////////////////////

//более верная реализ:
template<typename T, size_t size>
class MyArray
{
	T ar[size] = { T() }; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
public:
	MyArray() = default;
	MyArray(const T(&_ar)[size])
	{
		for (size_t i = 0; i < size; i++)
		{
			ar[i] = _ar[i];
		}

	}

	MyArray(const initializer_list<T>& l)// for MyArray ar6{ 6 };
	{
		for (size_t i = 0; i < l.size(); i++)
		{
			ar[i] = *(l.begin()+i);
		}
	}

};

//My deduction guid
template<typename T, size_t size> 
MyArray(const T(&)[size])->MyArray<T, size>;
//template<typename T, size_t size> MyArray(const T(&ar)[size])->MyArray<T, size>;//MA
//////////////////////////////////////////////////////////////////////////////////

template <typename First, typename... Rest> struct EnforceSame
{
	static_assert(std::conjunction_v<std::is_same<First, Rest>...>);
	using type = First;
};
template <typename First, typename... Rest> MyArray(First, Rest...)
->MyArray<typename EnforceSame<First, Rest...>::type, 1 + sizeof...(Rest)>;//*/
////////////////////////////////////////////////////////////////////////////////////
//template<typename T,typename... size>
//MyArray(T)->MyArray<T, sizeof...(size)+1 >;// for MyArray ar6{ 6 };
////My deduction guid
//template<typename T, typename... size>
//MyArray(const initializer_list<T>&)->MyArray<T, sizeof...(size) + 1>;//??
///////////////////////////////////////////////////////////////////////////////////

