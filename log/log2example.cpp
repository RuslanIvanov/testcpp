//логарифм по основанию

/*В стандартном С определён натуральный логарифм - функция log() в math.h и по основанию 10 - log10()*/
/* Натуральный логарифм – это функция   y(x) = ln x, обратная к экспоненте, x(y) = e^y, и являющаяся логарифмом по основанию числа е (е ≅ 2,718281828459045). */

#include <iostream>
#include <cstdlib>
#include <cmath>

double log(double a, double b)
{
    return log(b) / log(a);
}
 
int main()
{
    std::cout << log(4, 16);
    return EXIT_SUCCESS;
}
