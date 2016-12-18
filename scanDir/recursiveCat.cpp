#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
 
typedef int           /* 1 в случае ошибки, 0 в прот. случае */
(*PFUNC)(const char*,         /* обрабатываемый файл */
     const struct stat*); /* информация о файле */
 
int             /* 1 в случае ошибки, 0 в прот. случае */
walk(const char*,       /* начальная директория */
     PFUNC,         /* функция, которая вызывается для каждого
                   элемента директории */
     int);          /* вызывать функцию для каталогов? */
 
int print_entry(const char* name, const struct stat* st)
{
    printf("%s%s ", name,
       /* добавляем "/" к именам каталогов при выводе
        * для наглядности
        */
       (S_ISDIR(st->st_mode) ? "/" : ""));

	printf("size Mb: %16.6f ", ((double)(st->st_size)/1024)/1024);//размер в Mб
	printf("size in bytes: %ld ", st->st_size);//размер в байтах
	printf("time: %s",asctime(localtime(&st->st_mtime)));
 
    return 0;
}
 
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
    fprintf(stderr, "Usage: %s DIR\n", argv[0]);
    exit(1);
    }
 
    /* печать всего дерева каталогов, начиная
     * с argv[1] (каталоги тоже печатаются)
     */
    exit(walk(argv[1], print_entry, 1));
}
 
/* делаем глобальной переменной, чтобы не допустить разрастания
 * стека при рекурсивных вызовах (рекурсия-то древовидная)
 */
char buf[PATH_MAX];
 
int walk(const char* dirname, PFUNC pfunc, int do_dirs)
{
    DIR* dp;
    struct stat st;
    struct dirent* dirp;
    int retval = 0;
 
    size_t len = strlen(dirname);
 
    if((dp = opendir(dirname)) == NULL)
    {
    perror(dirname);
    return 1;
    }
 
    strncpy(buf, dirname, len);
 
    while((dirp = readdir(dp)) != NULL)
    {
    if(strcmp(dirp->d_name, ".") == 0 ||
       strcmp(dirp->d_name, "..") == 0)
        continue;
 
    buf[len] = '/';
    buf[len+1] = '\0';
 
    strcat(buf, dirp->d_name);
    
    if(lstat(buf, &st) == -1)
    {
        perror(dirp->d_name);
        retval = 1;
        break;
    }
 
    if(S_ISDIR(st.st_mode))
    {
        if(do_dirs)
        {
        if(pfunc(buf, &st) == 1)
        {
            retval = 1;
            break;
        }
        }
                
        if(walk(buf, pfunc, do_dirs) == 1)
        {
        retval = 1;
        break;
        }
        
    }
    else if(pfunc(dirp->d_name, &st) == 1)
    {
        retval = 1;
        break;
    }
 
    buf[len] = '\0';
    }
 
    closedir(dp);
    return retval;
}
