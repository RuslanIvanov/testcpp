#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
 
void showMatrix(const char*, int**, size_t);
void transpose(int**, size_t);
void swap(void*, void*, size_t);
void errExit(size_t, const char*, ...);
 
#define safeFree(PTR) free(PTR), PTR = NULL
#define readMatrix(M, I, J) printf("Input " #M "[%u][%u]: ", I, J), scanf("%d", &M[I][J])
 
int main()
{
    size_t n;
    int** matrix;
    size_t i, j;
    
    fputs("Input n: ", stdout);
    scanf("%u", &n);
 
    if((matrix = (int**) malloc(n * sizeof(int*))) == NULL)
    errExit(1, "Can't allocate memory for %u rows.\n", n);
 
    for(i = 0; i < n; ++i)
    if((matrix[i] = (int*) malloc(n * sizeof(int))) == NULL)
        errExit(2, "Can't allocate memory for #%u row.\n", i);
 
    for(i = 0; i < n; ++i)
    for(j = 0; j < n; ++j)
        readMatrix(matrix, i, j);
 
    showMatrix("Initial matrix", matrix, n);
    
    transpose(matrix, n);
 
    showMatrix("Transposed matrix", matrix, n);
        
    for(i = 0; i < n; ++i)
    safeFree(matrix[i]);
    safeFree(matrix);
    
    exit(0);
}
 
void showMatrix(const char* prompt, int** matrix, size_t n)
{
    size_t i, j;
 
    puts(prompt);
    for(i = 0; i < n; ++i, putchar('\n'))
    for(j = 0; j < n; ++j)
        printf("%-6u", matrix[i][j]);
}
 
void transpose(int** matrix, size_t n)
{
    size_t i, j;
    for(i = 0; i < n; ++i)
    for(j = i + 1; j < n; ++j)
        swap(&matrix[i][j], &matrix[j][i], sizeof(int));
}
 
void swap(void* a, void* b, size_t size)
{
    static void* tmp = NULL;
    if((tmp = malloc(size)) == NULL)
    errExit(3, "Can't allocate memory.\n");
    
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    safeFree(tmp);
}
 
void errExit(size_t code, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    if(code)
    exit(code);
}