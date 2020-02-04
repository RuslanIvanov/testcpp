#pragma once
template <typename T> void Swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}