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
  cerr << "Ejemplo: ./tsp-insertion gr202\n";
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
  nombre_salida="salidas/" + nombre_salida + "_insertion.tsp";
  
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

  //Busco 3 ciudades, la que tenga la coordenada X mayor, la que tenga la coor. X menor y la que tenga la coord. Y mayor 
  int minX = 0;
  int maxX = 0;

  for(i = 1; i < n; i++){
    if(xCords[i]>xCords[maxX]) maxX = i;
    else if(xCords[i]<=xCords[minX]) minX = i;
  }
  
  //xCords.clear();

  int maxY=0, yC = INT_MIN;
  for(i = 0; i < n; i++){
    if(yCords[i]>=yC)
      if(i != minX && i != maxX){
	maxY = i;
	yC = yCords[i];
      }
  }
  
  //yCords.clear();
  
  /*
  for(i = 0; i < n; i++){
    for(j = 0; j < i; j++){
      cout << map[i][j] << "\t";
    }
    cout << endl;
  }
  */
  
  int sumDistances=0;
  vector<int> result(3);

  //Añado las tres cuidades al vector de resultados 
  result[0]=maxX;
  result[1]=minX;
  result[2]=maxY;

  //Sumo las distancias de las 3 ciudades entre ellas
  sumDistances += map[max(result[1],result[0])][min(result[1],result[0])];
  sumDistances += map[max(result[2],result[0])][min(result[2],result[0])];
  sumDistances += map[max(result[1],result[2])][min(result[1],result[2])];

  //Creo un vector con las ciudades que quedan por recorrer (borro las 3 ya escogidas)
  vector<int> candidates(n);
  for(i = 0; i < n; i++) candidates[i]=i;
  candidates.erase(remove(candidates.begin(),candidates.end(),maxX));
  candidates.erase(remove(candidates.begin(),candidates.end(),minX));
  candidates.erase(remove(candidates.begin(),candidates.end(),maxY));
  
  int bestCity;
  int bestPosition;
  int bestD;
  int d;

  clock_t t_antes, t_despues;

  t_antes = clock();

  while(candidates.size()>0){ // Mientras que queden candidatos (ciudades sin recorrer)
    for(i = 0; i < candidates.size(); i++){ //Recorro las ciudades
      bestD = INT_MAX;
      for(j = 0; j < result.size(); j++){ //Miro cual es la distancia mínima de una ciudad concreta a las que ya tenemos
	d = map[max(result[j],candidates[i])][min(result[j],candidates[i])] //Distancia de una ciudad a otras 2 de resultado
	  + map[max(result[(j+1)%result.size()],candidates[i])][min(result[(j+1)%result.size()],candidates[i])]
	  - map[max(result[(j+1)%result.size()],result[j])][min(result[(j+1)%result.size()],result[j])];
	if(d < bestD){ //Si la distancia es menor a la ya calculada a otras dos ciudades de resultado, almaceno su indice...
	  bestCity = candidates[i];
	  bestPosition = (j+1)%result.size();
	  bestD = d;
	}
      }
    }
    result.insert(next(result.begin(),bestPosition),bestCity); //inserto la ciudad en el vector de resultados
    candidates.erase(remove(candidates.begin(),candidates.end(),bestCity)); //borro la ciudad del vector de candidatos
    sumDistances += bestD; //Sumo la distancia a la distancia total del recorrido
  }

  t_despues = clock();

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
