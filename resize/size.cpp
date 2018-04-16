#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct verinfo 
{
	char name[22];//имя модуля
	time_t time;  //время создания
	unsigned int  size;
	unsigned short crc;

	verinfo ()
	{
		strcpy(name,"");
		time =0;
		size = 0;
		crc = 0;
		printf("\n constr");
	}

}VERINFO;

int main()
{

	printf("\n size: %d ",sizeof(VERINFO));


	verinfo v;
	VERINFO ver;
	return 0;
}
