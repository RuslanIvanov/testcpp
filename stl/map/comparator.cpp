#include <iostream>
#include <vector>
#include <initializer_list>

struct ByLength : public std::binary_function<string, string, bool>
{
    bool operator()(const string& lhs, const string& rhs) const
    {
        return lhs.length() < rhs.length();
    }
};

int main(int, char**)
{
    typedef map<string, string, ByLength> lenmap;
    lenmap mymap;

    mymap["one"] = "one";
    mymap["a"] = "a";
    mymap["fewbahr"] = "foobar";

    for( lenmap::const_iterator it = mymap.begin(), end = mymap.end(); it != end; ++it )
        cout << it->first << "\n";

	return 0;
}
