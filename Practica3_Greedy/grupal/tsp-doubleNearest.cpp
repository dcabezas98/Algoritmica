#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>
#include <iterator>
#include <ctime>

using namespace std;

void mostrarInfo(){
  cerr << "Ejemplo: ./tsp-doubleNearest gr202\n";
}

int main(int argc, char *argv[]){

  if(argc < 2){
    cerr << "Formato incorrecto\n";
    mostrarInfo();
    exit(-1);
  }

  string nombre_entrada(argv[1]);
  string nombre_salida(argv[1]);

  nombre_entrada="datosTSP/" + nombre_entrada + ".tsp";
  nombre_salida="salidas/" + nombre_salida + "_doubleNearest.tsp";
  
  ifstream f(nombre_entrada);
  if(!f){
    cerr << "Error apertura " << nombre_entrada << endl;
    mostrarInfo();
    exit(-1);
  }

  int n;
  string dimension;

  f >> dimension;
  f >> n;

  if(n < 3){
    f.close();
    cerr << "Hay menos de tres ciudades\n";
    exit(-1);
  }
  
  int i,j;
  vector<double> xCords(n), yCords(n);

  //Leo los datos del fichero
  for(j = 0; j < n; j++){
    f >> i;
    f >> xCords[j];
    f >> yCords[j];
  }

  f.close();

  //Genero la matriz triangular con las distancias
  vector<vector<int>> map(n);

  int distance;

  /*
    Como la matriz de distancias es simétrica, sólo hemos almacenado el triángulo inferior.
    Por lo que para consultar la distancia entre las ciudades con índices i, j, hay 
    que acceder de esta forma: map[max(i,j)][min(i,j)]
  */
  
  for(i = 0; i < n; i++){
    for(j = 0; j < i; j++){
      distance = (int) rint(sqrt(pow(xCords[i]-xCords[j],2) + pow((yCords[i]-yCords[j]),2)));
      map[i].push_back(distance);
    }
  }
  
  //xCords.clear();
  //yCords.clear();
  
  /*
  for(i = 0; i < n; i++){
    for(j = 0; j < i; j++){
      cout << map[i][j] << "\t";
    }
    cout << endl;
  }
  */
  
  vector<int> result(n);
  result[0]=0;

  vector<int> candidates(n-1);

  for(i = 1; i < n; i++) candidates[i-1]=i;

  int sumDistances=0, d1, d2, bestD, bestCity1, bestCity2;

  clock_t t_antes, t_despues;

  t_antes = clock();
  
  for(int k = 1; k < (n+1)/2; k++){ // Relleno el vector result
    bestD = INT_MAX;
    for(i = 0; i < candidates.size(); i++){ // Para cada candidato
      d1 = map[max(candidates[i],result[2*k-2])][min(candidates[i],result[2*k-2])];
      d2 = INT_MAX;
      for(j = 0; j < candidates.size(); j++){ // Para el resto de candidatos
	if(candidates[j] != candidates[i]){
	  d2 = map[max(candidates[i],candidates[j])][min(candidates[i],candidates[j])];
	  if(d1 + d2 < bestD){
	    bestD = d1 + d2;
	    bestCity1 = candidates[i];
	    bestCity2 = candidates[j];
	  }
	}
      }
    }
    result[2*k-1] = bestCity1;
    result[2*k] = bestCity2;
    sumDistances += bestD;
    candidates.erase(remove(candidates.begin(),candidates.end(),bestCity1));
    candidates.erase(remove(candidates.begin(),candidates.end(),bestCity2));
  }

  t_despues = clock();

  if(!(n%2)){
    result[n-1] = candidates[0];
    sumDistances += map[max(result[n-1],result[n-2])][min(result[n-1],result[n-2])];
  }

  sumDistances += map[max(result[n-1],result[0])][min(result[n-1],result[0])];

  cout << "Recorrido: ";
  for(i = 0; i < n-1; i++)
    cout << result[i]+1 << ", ";
  
  cout << result[n-1]+1 << endl;
  cout << "Distancia: " << sumDistances << endl;
  
  ofstream of(nombre_salida);

  if(!of){
    cerr << "Error en la apertura de " << nombre_salida <<endl;
    mostrarInfo();
    exit(-1);
  }

  of << dimension << " " << n << endl;

  for(i=0; i<n; i++)
    of << result[i]+1 << " " << xCords[result[i]] << " " << yCords[result[i]] << endl;

  of << result[0]+1 << " " << xCords[result[0]] << " " << yCords[result[0]] << endl;
  
  of.close();
  
  
  cout << n << "\t" << (t_despues-t_antes)/(float)CLOCKS_PER_SEC << endl;
}
