#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

char pathDir[PATH_MAX];
char ipAdress[BUFSIZ];

struct files
{
        char fname[BUFSIZ];
        size_t fsize;
        time_t  ftime;
        unsigned char fblock[32];
};

bool scanDir(const char*);

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
                //strcpy(pathDir,"./");
		getcwd(pathDir,BUFSIZ);
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


bool scanDir(const char * path)
{
	char nextDir[PATH_MAX];
	
	DIR* pdir =  opendir(path);
	if(pdir == NULL){ perror("opendir "); return false; }
        dirent *pdirent;
        while( NULL != (pdirent = readdir(pdir)) ) //читает директорию
        {
                struct stat statbuf;
                lstat( pdirent->d_name, &statbuf ); //считываем информацию о файле в структуру

		if(strcmp( ".", pdirent->d_name ) == 0 ||
                   strcmp( "..",pdirent->d_name ) == 0 )
                	{continue;}		
			
		if((pdirent->d_type & DT_DIR) == DT_DIR) 
                {// если это директория		   
				
			if(strcmp(path,"/")==0 || strcmp(path,"./")==0)
				sprintf(nextDir,"%s%s",path,pdirent->d_name);
			else sprintf(nextDir,"%s/%s",path,pdirent->d_name);
			
			printf("\nDIR: '%s':\n", nextDir);		

			scanDir(nextDir);
			
                }		
		if((pdirent->d_type & DT_REG) == DT_REG )
		{// если это file
			printf("file: '%s' ",pdirent->d_name);
			printf("size: %16.6f ", ((double)statbuf.st_size/1024)/1024);//размер в Mб
			printf("size: %ld ", statbuf.st_size);//размер в байтах
			printf("time: %s",asctime(localtime(&statbuf.st_mtime)));
    		}
        }

	closedir(pdir);
	return true;
}
