/**
   @file Cálculo de la sucesión de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>


/**
   @brief Calcula el término n-ésimo de la sucesión de Fibonacci.

   @param n: número de orden del término buscado. n >= 1.

   @return: término n-ésimo de la sucesión de Fibonacci.
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
