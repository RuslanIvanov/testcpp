#include <iostream>
using namespace std;

template<typename T,size_t> class A;

template <typename T,size_t m_n> //declaration
	ostream& operator << (ostream& out, const A<T,m_n>&);


template <typename T,size_t m_n=10> class A {
public:
    A() : elem (T()) { m_nn = m_n; }
private:
    T elem;
    size_t m_nn;

//template <typename T>
	friend ostream& operator<< <>(ostream& out, const A<T,m_n>& a);
};

//definition
template <typename T,size_t m_n>
ostream& operator << (ostream& out, const A<T,m_n>& a)
{
    return out <<" a = " <<a.elem <<" "<< "m_n = "<<a.m_n<<  endl;
}

int main(int argc, char* argv[])
{
    A<int,10> a;
    cout<<a;
    //cout << A<int>();
}
//friend ostream &operator <<<T> (ostream &, const A<T> &);
