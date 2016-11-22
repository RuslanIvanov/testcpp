#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

unsigned strlen(const char *str)
{
	/* ... */
	int i=0;
	while(1)
	{
		if(str[i]==0) break;
		i++;
	}
	return i;
}

void _strcat(char *to, const char *from)
{
    /* ... */
	int i=0;
	for(;;)
	{
		if(to[i]=='\0') break;
		i++;
	}
	int j=0;
	for(;;)
	{
		to[i+j] = from[j];
		if(from[j]== '\0') break;

		j++;
	}
}

int _strstr(const char *text, const char *pattern)
{
	int i=0;
	int j=0;
	int ind=-1;

	int len;
	for(len=0;;len++)
	{if(pattern[len] == '\0') break;}

	cout<<"len pattern: "<<len<<endl;

	if(len==0) return 0;


	for(;;)
	{
			if(pattern[j] == text[i])
			{
				if(j==0) 
				{	ind = i; 
					cout<<" mem index "<<ind;
				}
				cout<<"[j="<<j<<",i= "<<i<<"]"<<endl;
				j++;i++;
			}else
			{
				i++; j=0; ind=-1;
				cout<<"[ no ]"<<endl;
			}


			if(j==(len)) 
			{
				cout<<" return ind "<<ind<<endl; 
				return ind;
			}
			if(pattern[j] == '\0' || text[i]== '\0') 
			{
				cout<<" return '0': [i="<<i<<", j= "<<j<<"]"<<endl; 
				return -1;
			}
	}
	return -1;
}

int main(int argc, char* argv[])
{

	cout<<"strlen "<<strlen("aaa")<<endl;

	char a[80] = "where are you";
	_strcat(&a[0]," from?");
	cout<<a;

	char s[BUFSIZ]   = "hello";
	char str[BUFSIZ] = "hhello";

	if(argc == 3)
	{
		strcpy(s,argv[2]);
		strcpy(str,argv[1]);
	}

	cout<<endl;
	cout<<"text: '"<<str<<"', pattern: '"<<s<<"'"<<endl;
	int ind=_strstr(str,s);
	if(ind==-1)
	{
		cout<<"Not found: "<<s<<endl;
	}else
		{
			cout<<"index '"<<s<<"' is "<<ind<<endl;
		}

	cout<<endl<<"Press any key...";
	getchar();

	return 0;
}
