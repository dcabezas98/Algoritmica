#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

void mostrarInfo(){
  cerr << "Ejemplo: ./tsp-nearest gr202\n";
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
  nombre_salida="salidas/" + nombre_salida + "_nearest.tsp";
    
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
 
  int i,j;
  vector<double> xCords(n), yCords(n);

  for(j = 0; j < n; j++){
    f >> i;
    f >> xCords[j];
    f >> yCords[j];
  }

  f.close();
  
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

  // xCords.clear();
  // yCords.clear();
  /*
  for(i = 0; i < n; i++){
    for(j = 0; j < i; j++){
      cout << map[i][j] << "\t";
    }
    cout << endl;
    }
  */
  vector<int> result(n);
  result[0] = 0;

  int dmin;
  int sumDistances=0;
  for(int k = 1; k < n; k++){ //Relleno el vector de resultados
    dmin = INT_MAX;
    for(j = 0; j < n; j++) //Recorro todas las cuidades buscando cual de ellas está mas cerca de la última escogida
      if(find(result.begin(),result.end(),j) == result.end()){
	distance = map[max(j,result[k-1])][min(j,result[k-1])];
	if(distance < dmin){
	  i = j;
	  dmin = distance;
	}
      }
    sumDistances += dmin;
    result[k] = i;
  }

  sumDistances += map[max(result[0],result[n-1])][min(result[0],result[n-1])];

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
}
