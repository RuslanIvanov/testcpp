
#include <iostream> 
#include <array> 
#include <vector>
using namespace std; 

int main()
{
   array<int,5> a{1, 2, 3, 4, 5}; 
   for(auto& rit: a)
       ++rit;
   for(auto rit: a)
       cout << rit;

  vector<int> arr(10);
	copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
}
