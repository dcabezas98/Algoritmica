/*
  David Cabezas Berrido

  Simulador del problema de las reparaciones en
  el caso de varios electricistas. Tendremos
  n reparaciones y p electricistas.

  Siempre se realizan las tareas de un electricista
  ordenadas de menor a mayor tiempo, lo que optimiza el
  tiempo de espera total. Por lo que esta simulación 
  sólo depende de la forma de repartir los trabajos.
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MIN = 10;
const int MAX = 100;
const int SIMULACIONESALEATORIAS = 100;
int p;

int randInt(int min, int max){
  int range = max-min;
  return rand()%range + min;
}

int sumaTiempoEspera(const vector<int> &v){
  int suma = 0;
  
  for(int i = 0; i < v.size(); i++)
    suma += v[i]*(v.size()-i);

  return suma;
}

int optimo(vector<int> T){
  
  sort(T.begin(),T.end());

  vector<vector<int>> electricistas(p);
  for(int i = 0; i < T.size(); i++)
    electricistas[i%p].push_back(T[i]);

  int suma = 0;

  for(vector<int> e: electricistas)
    suma += sumaTiempoEspera(e);

  return suma;
}

int random(vector<int> T){
  
  vector<vector<int>> electricistas(p);
  
  for(int i = 0; i < T.size(); i++)
    electricistas[randInt(0,p)].push_back(T[i]);

  int suma = 0;
  for(vector<int> e: electricistas){
    sort(e.begin(),e.end());
    suma += sumaTiempoEspera(e);
  }

  return suma;  
}

int main(int argc, char* argv[]){

  if(argc < 3){
    cout << "Formato: <nº reparaciones> <nº electricistas>" << endl;
    exit(-1);
  }

  int n = atoi(argv[1]);
  p = atoi(argv[2]);

  srand(time(0));
  
  vector<int> T;
    
  for(int i = 0; i < n; i++)
    T.push_back(randInt(MIN,MAX));

  cout << "Tiempo para el algoritmo óptimo: " << optimo(T) << endl;
  cout << "Tiempos para soluciones aleatorias:\n";

  int best = random(T);
  int rt;
  cout << best << "\t";
  
  for(int i = 0; i < SIMULACIONESALEATORIAS-1; i++){
    rt = random(T);
    cout << rt << "\t";
    if(rt < best) best = rt;
  }
  cout << "\nMejor de los aleatorios: " << best << endl;
}
