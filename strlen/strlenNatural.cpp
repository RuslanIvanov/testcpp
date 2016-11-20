#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{

	char s[BUFSIZ]   = "";
	char str[BUFSIZ] = "qwerty123456";

	if(argc == 3)
	{
		strcpy(s,argv[2]);
		strcpy(str,argv[1]);
	}

	cout<<endl;
	cout<<"text: '"<<str<<"', pattern: '"<<s<<"'"<<endl;
	char *p = strstr(str,s);
	if(p!= NULL)
	{
		cout<<"find: "<<p<<endl;
	}else
		{
			cout<<"no find: "<<s<<endl;
		}

	cout<<endl<<"Press any key...";
	getchar();

	return 0;
}
