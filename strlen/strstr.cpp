#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

char * _strstr(const char * str1,const char * str2)
{
	char *cp = (char *) str1;
	char *s1, *s2;
     
	if ( !*str2 )
           return((char *)str1);
     
        while (*cp)
        {
 	       s1 = cp;
               s2 = (char *) str2;
     
               while ( *s1 && *s2 && !(*s1-*s2) )
                  s1++, s2++;
     
               if (!*s2)
                  return(cp);
               cp++;
        }
     
        return(NULL);
     
}

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
	char *p = _strstr(str,s);
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
