#include <iostream>
using namespace std;

template<typename T,size_t> class A;

template <typename T> //declaration
	ostream& operator << (ostream& out, const A<T,size_t>&);


template <typename T,size_t m_n=10> class A {
public:
    A() : elem (T()) { }
private:
    T elem;
    size_t m_n;

//template <typename T>
	friend ostream& operator<< <>(ostream& out, const A& a);
};

//definition
template <typename T>
ostream& operator << (ostream& out, const A<T,size_t>& a)
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
