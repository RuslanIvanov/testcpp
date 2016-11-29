#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String 
{

	/* Реализуйте этот конструктор */
	String(const char *str = "");
	String(size_t n, char c);
	void append(String &other);
	~String();
	size_t size;
	char *str;
};

String::String(const char *str)
{	
	size = 0;
	for(;;size++)
	{
		if(str[size]=='\0') break;
	}

	this->str = new char[size+1];
	
	for(int i=0;i<(size+1);i++)
	{
		this->str[i] = str[i];
	}
		 
}

String::String(size_t n, char c)
{
	str = new char[n+1];

	size = 0;	
	for(;size<n;size++)
	{
		str[size] = c;	
	}

	str[n]='\0';
}

void String::append(String &other)
{//error!
	if(this == &other) { strcpy(str,other.str); size = strlen(other.str); return; }

	size_t len = strlen(str);

	char *pstr = str;
	size = size+len;
	str = char new [size+1];

	strcpy(str,pstr);
	for(int i=size;i<size+1;i++)
	{
		str[i+size] = other.str[i];
	}
	
	delete [] pstr;
}

String::~String()
{
	delete [] str;	
}

int main(int,char**)
{
	String s;
	String ss("This is str");

	String s1("Hello,");
	String s2(" world!");
	s1.append(s2); //s1 is "Hello, world!"

	String sss("Hello");
	sss.append(sss); // "HelloHello"

	return 0;
}