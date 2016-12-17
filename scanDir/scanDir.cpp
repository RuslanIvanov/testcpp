#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

char pathDir[BUFSIZ];
char ipAdress[BUFSIZ];

struct files
{
        char fname[BUFSIZ];
        size_t fsize;
        time_t  ftime;
        unsigned char fblock[32];
};

bool scanDir(/*const*/ char*);

int main (int argc, char* argv[])
{
        int opt;
        while((opt= getopt(argc, argv, "hp:")) != -1)
        switch(opt)
        {
                case 'p': strcpy(&pathDir[0],""); sscanf(optarg,"%s",&pathDir[0]); break;
                case 'h':
                printf("\nclient menu :\n");
                printf("\t-p\tPath to scan a directory\n");

                return 0;
        }

	if(strcmp(pathDir,"")==0)
        {//если пользователь не указал директорию
                strcpy(pathDir,"./"); //getcwd(pathDir,BUFSIZ);
        }

        DIR *pDir = opendir(pathDir);

        if(pDir==NULL) 
        {
                printf("\nDirectory does not exist.\nExit...\n"); 
                return  0; 
        }
	closedir(pDir);

	scanDir(pathDir);

	return 0;
}

bool scanDir(/*const*/ char * path)
{
	printf("\ncurrent path '%s'",path);
	DIR* pdir =  opendir(path);
        dirent *pdirent;
        while( NULL != (pdirent = readdir(pdir)) ) //читает директорию
        {
                struct stat statbuf;
                lstat( pdirent->d_name, &statbuf ); // считываем информацию о файле в структуру

		if(strcmp( ".", pdirent->d_name ) == 0 ||
                   strcmp( "..",pdirent->d_name ) == 0 )
                	{continue;}

		if (S_ISREG( statbuf.st_mode ))
		{// если это file

                       	printf("%s ",pdirent->d_name);
			printf("size: %ld ", statbuf.st_size);
			printf("%s ",asctime(localtime(&statbuf.st_mtime)));

    		}else
		if (S_ISDIR( statbuf.st_mode ))
                {// если это директория
		        char nextDir[1025];
			sprintf(nextDir,"%s%s/",path,pdirent->d_name);
			printf("\nThe dir '%s'", nextDir);
			scanDir(nextDir);

			// printf("\nThe dir '%s'", pdirent->d_name);
                       //scanDir(pdirent->d_name);
                } else break;


        }

	closedir(pdir);
}
