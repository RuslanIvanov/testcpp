#include<iostream>

using namespace std;

main() {
    int i;
    char s[] = "hello";

    for(i=0; s[i]; ++i);
    cout << i << endl;

    i=0;
    while(s[i++]);
    cout << i;
}
