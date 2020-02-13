#pragma once
template <typename T> void Swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
	//std::cout << "\n swap for T";
}


// swap для string
class MyString;
template <> void Swap <MyString>(MyString& t1, MyString& t2) 
{
	//std::cout << "\n swap for Mystring";

	//std::swap(t1, t2);// тоже самое:
	MyString tmp = std::move(t1);
	t1 = std::move(t2);
	t2 = std::move(tmp);

}