/*
  David Cabezas Berrido

  Simulador del problema de las reparaciones en
  el caso de varios electricistas. Tendremos
  n reparaciones y p electricistas.
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int p, n;

int sumaTiempoEspera(vector<int> v){
  int suma = 0;
  
  for(int i = 0; i < v.size(); i++){
    suma += v[i]*(n-i);
  }
}

int distribuyeYSuma(int* T, int n){
  vector<vector<int>> electricistas(p);
  for(int i = 0; i < v.size(); i++)
    electricistas[i%p].push_back(v[i]);

  int suma += 0;

  for(vector<int> e: electricistas)
    suma += sumaTiempoEspera(e);

  return suma;
}

int main(int argc, char* argv[]){
i
  if(argc < 3){
    cout << "Formato: <nº reparaciones> <nº electricistas>" << endl;
    exit(-1);
  }

  n = atoi(argv[1]);
  p = atoi(argv[2]);

  int* T = new int[n];

  int r;
  srand(time(0));
  for(int i = 0; i < n; i++){
    r = rand() %100 + 50;
    T[i]=r;
  }

  for(int i = 0; i < n; i++)
    cout << T[i] << endl;
}
