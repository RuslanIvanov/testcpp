#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
 
void cmp(DIR *, DIR *);
 
int main(int argc, char *argv[])
{
        DIR *d1, *d2;
        
        if ( !(d1 = opendir(argv[1])) || ! (d2 = opendir(argv[2])) || argc < 3 )
        {
                fprintf(stderr, "$s: error dir or arg\n", argv[0]);
                exit(1);
        }
 
        cmp(d1, d2);
 
        return 0;
}
 
void cmp(DIR *d1, DIR *d2)
{
        struct dirent *f1;
        struct dirent *f2;
        
        while ( (f1 = readdir(d1)) )
        {
                if ( f1->d_type == DT_DIR )
                {
                        DIR *t1;
                        if ( (t1 = opendir(f1->d_name)) )
                                cmp(t1, d2);
                }
                else
                {
                        while ( (f2 = readdir(d2)) )
                        {
                                if ( f2->d_type == DT_DIR )
                                {
                                        DIR *t2;
                                        if ( (t2 = opendir(f2->d_name)) )
                                                cmp(d1, t2);
                                }
                                else
                                        printf("%s - %s\n", f1->d_name, f2->d_name);
                        }
                }
        }   
}