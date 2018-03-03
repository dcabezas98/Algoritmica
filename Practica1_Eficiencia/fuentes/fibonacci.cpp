/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char* argv[])
{

  int n = atoi(argv[1]);
  int f;
 
  clock_t t_antes = clock();
  
  f = fibo(n);

  clock_t t_despues = clock();

  cout << n << "\t" << (t_despues - t_antes)/(float)CLOCKS_PER_SEC << endl;
  
  return 0;
}
