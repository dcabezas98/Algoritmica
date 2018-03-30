#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>

//#define _OBVIO_

using namespace std;

#ifdef _OBVIO_
int enSuPosicion(int* T, int n){
  int i = -1, j;
  bool found = false;

  for(j = 0; j < n && !found; j++){
    if(T[j] == j){
      i = j;
      found = true;
    }
  }

  return i;
}

#else
int enSuPosicion(int *T, int n){
  
  int result = -1;
  int left=0, right=n-1;
  int p = (left+right)/2;
  bool found = false;
  
  while(!found and left <= right){
    if(p == T[p]){
      result = p;
      found = true;
    }
    else if(p < T[p])
      right = p-1;
    else
      left = p+1;

    p = (left+right)/2;
  }

  return result;
}

#endif

double uniforme() //Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C. 
{
  int t = rand();
  double f = ((double)RAND_MAX+1.0);
  return (double)t/f;
}

int main(int argc, char* argv[]){

  if (argc < 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int m=2*n-1;

  int * T = new int[n];
  int * aux = new int[m];

  double suma = 0;

  for(int k = 0; k < 100; k++){
    srand(time(0));
    //genero todos los enteros entre -(n-1) y n-1
    for (int j=0; j<m; j++) aux[j]=j-(n-1);

    //algoritmo de random shuffling the Knuth (permutación aleatoria) 
    for (int j=m-1; j>0; j--) {
      double u=uniforme();
      int k=(int)(j*u);
      int tmp=aux[j];
      aux[j]=aux[k];
      aux[k]=tmp;
    }
    //me quedo con los n primeros del vector
    for (int j=0; j<n; j++) T[j]=aux[j];
    //for (int j=0; j<n; j++) cout << T[j] << " ";

    //Y ahora ordeno el vector T
    vector<int> myvector (T, T+n);
    vector<int>::iterator it;

    sort(myvector.begin(),myvector.end());

    int i;
    for (it=myvector.begin(), i = 0; it!=myvector.end(); ++it, ++i)
      T[i] = *it;

    clock_t t_antes, t_despues;

    t_antes = clock();
    enSuPosicion(T, n);
    t_despues = clock();

    suma += (t_despues-t_antes)/(float)CLOCKS_PER_SEC;
  }

  cout << n << "\t" << suma/100 << endl;

  delete [] T;
  delete [] aux;
}
