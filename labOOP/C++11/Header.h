#pragma once

template <typename T> void printCont(const T& t)
{
	std::cout << "\nContainer:\n";
	for (typename T::const_iterator i = t.begin(); i != t.end(); ++i)
	{
		std::cout << *i << " ";
	}

}

template <typename T> void PrintAnyCont(const T& t) 
{
	
	std::cout << "\n";
	for (auto& tt : t) 
	{
		std::cout <<"| "<< tt <<" |";
	}
}

class L
{
public:
	bool operator()(const char* x, const char* y)
	{
		return strcmp(x, y) < 0;
	}

};

class compareFirstCh4
{
	char m_ch;
public:
	compareFirstCh4(char ch)
	{
		m_ch = ch;
	}

	bool operator()(const char* stl)
	{

		if (stl[0] == m_ch)
		{
			return true;
		}

		return false;
	}
};

template<typename T> void NegateAll(T& t) 
{	
	for (auto& tt : t)
	{
		//int i = atoi(tt);
		//if (i != 0) { tt *= -1; }
		//else
		//tt = toupper(tt);*/
		//if (tt == 0) { tt *= -1; }

//		if (tt >= 'A' && tt <= 'Z') { tolower(tt); }
//		else if (tt >= 'a' && tt <= 'z') { toupper(tt); }
//		else { tt *= -1; }
	}
}
