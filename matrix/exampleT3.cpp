#include <iostream>
#include <iomanip>
 
//----------------
 
int** new2DArray(const int m, const int n)
{
   int** arr = new int*[m];
   for(int i = 0; i < m; ++i)
      arr[i] = new int[n];
   return arr;
}
 
//---------------
void delete2DArray(int** arr, const int m)
{
   for(int i = 0; i < m; ++i)
      delete[] arr[i];
   delete[] arr;
}
 
//--------------- 
 
int** newTransposeMatrix(int** matrix, const int m, const int n) 
{
   int** res = new2DArray(n, m);
   
   for(int i = 0; i < m; ++i)    
      for(int j = 0; j < n; ++j)        
     res[j][i] = matrix[i][j];            
   
   return res;
}
 
//----------------
void print2DArray(int** arr, const int m, const int n)
{
   for(int i = 0; i < m; ++i)
   {
      for(int j = 0; j < n; ++j)
     std::cout << std::setw(4) << arr[i][j];
      std::cout << '\n';
   }   
}
//---------------
 
int main()
{
   // вводим размеры матрицы
   std::cout << "Input m: ";
   int m;
   std::cin >> m;
   
   std::cout << "Input n: ";
   int n;
   std::cin >> n;
   
   // создаём новую матрицу MxN
   int** mtrx = new2DArray(m, n);
 
   // заполняем 
   for(int i = 0; i < m; ++i)   
      for(int j = 0; j < n; ++j)      
     mtrx[i][j] = j;
              
   // выводим
   std::cout << "Matrix\n";
   print2DArray(mtrx, m, n);
 
   // получаем транспонированную матрицу и выводим её на экран
   int** tmtrx = newTransposeMatrix(mtrx, m, n);
   std::cout << "\nTranspose matrix\n";   
   print2DArray(tmtrx, n, m);
 
   // освобождаем выделенную память
   delete2DArray(mtrx, m);
   delete2DArray(tmtrx, n);
 
   return 0;