#include <iostream>
using namespace std;

template<typename T,size_t m_n> class A;

template <typename T,size_t m_n> //declaration
	ostream& operator << (ostream& out, const A<T,m_n>&);


template <typename T,size_t m_n=10> class A {
public:
    A() : elem (T()) { m_nn = m_n; }
private:
    T elem;
    size_t m_nn;
    struct AA
    {
	T aa;
	AA () {aa = T();}
    };

//template <typename T>
	friend ostream& operator<< <>(ostream& out, const A& a);
	//or
	//friend ostream& operator<< <>(ostream& out, const A<T,m_n>& a);

};

//definition
template <typename T,size_t m_n>
ostream& operator << (ostream& out, const A<T,m_n>& a)
{
//    out << A<T,m_n>::AA::aa;
    return out <<" a = " <<a.elem <<" "<< "m_n = "<<a.m_nn<<  endl;
}

int main(int argc, char* argv[])
{

    const size_t n = 5;
    A<int,n> a;
    cout<<a;
    cout << A<int>();
}

