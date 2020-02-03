#include <iostream>
using namespace std;

template<typename T> class A; 

template <typename T>
ostream& operator << (ostream& out, const A<T>& a)
{
    return out << a.elem << endl;
}

template <typename T> class A {
public:
    A() : elem (T()) {}
private:
    T elem;

public:
	template <typename T>
	friend ostream& operator<< <>(ostream& out, const A<T>& a);
};

int main(int argc, char* argv[])
{
    A<int> a;
    cout<<a;
    //cout << A<int>();
}
//friend ostream &operator <<<T> (ostream &, const A<T> &);
