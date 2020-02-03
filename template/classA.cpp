#include <iostream>
using namespace std;

template<typename T> class A; 

template <typename T> //declaration
	ostream& operator << (ostream& out, const A<T>&);


template <typename T> class A {
public:
    A() : elem (T()) {}
private:
    T elem;

//template <typename T>
	friend ostream& operator<< <>(ostream& out, const A& a);
};

//definition
template <typename T>
ostream& operator << (ostream& out, const A<T>& a)
{
    return out << a.elem << endl;
}

int main(int argc, char* argv[])
{
    A<int> a;
    cout<<a;
    //cout << A<int>();
}
//friend ostream &operator <<<T> (ostream &, const A<T> &);
