//http://www.cyberforum.ru/cpp-beginners/thread1541665.html
#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int ** create_array2d(const int& rows, const int& cols) 
{
   int **m = new int*[rows];
   for(int i = 0; i < rows; ++i)
      m[i] = new int [cols];
   return m;
}
 
int ** transpose(const int * const * m_, const int& rows, const int& cols)
{
    int **mt_ = create_array2d(cols, rows);
 
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j)
            mt_[i][j] = m_[j][i];
    }
    
    return mt_;
}
 
/*Дублирующийся код выделяем в отдельные функции/процедуры*/
void show(const int * const * m_, const int& rows, const int& cols)
{
   for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << m_[i][j] << " ";
        cout << endl;
    }
}
 
void destroy(int** m_, const int& rows)
{
   for (int i = 0; i < rows; ++i)
        delete[] m_[i];
   delete[] m_;
}
 
int main() 
{
    int rows =3, cols = 5;
    int **m = create_array2d(rows, cols);
    
    int count = 0;
    for (int i = 0; i < rows; ++i) // безопаснее использовать неравенства вместо != или ==
    {
         for (int j = 0; j < cols; ++j)
         {
              m[i][j] = count;
              count++;
         }
    }
    show(m, rows, cols);
 
    int **mt = transpose(m, rows, cols);
    show(mt, cols, rows);
    
    /*Обязательно чистим за собой!*/
    destroy(m, rows);
    destroy(mt, cols);
    return 0;
}
