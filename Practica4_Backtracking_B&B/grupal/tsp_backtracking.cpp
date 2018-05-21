#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <climits>

void printVector(vector<int> v){
  for(int i = 0; i < v.size()-1; i++)
    cout << v[i] << ", ";
  cout << v.back() << endl;
}

void mostrarInfo(){
  cerr << "Ejemplo: ./tsp ulysses16\n";
}

class TSP{

private:
  int n;
  vector<vector<int>> map;

public:

  vector<double> xCords, yCords;

  TSP(string file){

    ifstream f(file);
    
    if(!f){
    	cerr << "Error de lectura del archivo " << file << endl;
    	mostrarInfo();
    	exit(-1);
    }
    
    string trash;
    f >> trash;
    f >> n;

    int i, j;
    double c;
    //Leo los datos del fichero
    for(j = 0; j < n; j++){
      f >> i;
      f >> c;
      xCords.push_back(c);
      f >> c;
      yCords.push_back(c);
    }

    f.close();

    int distance;
    vector<vector<int>> aux(n);
    
    for(i = 1; i < n; i++){
      for(j = 0; j < i; j++){
	distance = (int) rint(sqrt(pow(xCords[i]-xCords[j],2) + pow((yCords[i]-yCords[j]),2)));
	aux[i].push_back(distance);
      }
    }
    map = aux;
  }

  int getN() const{
    return n;
  }

  void printMap() const{
    int i, j;

    for(i = 0; i < n; i++){
      for(j = 0; j < i; j++){
	cout << map[i][j] << "\t";
      }
      cout << endl;
    }
  }

  int getDistance(int i, int j) const{
    if(0 <= i && i < n && 0 <= j && j < n)
      return map[max(i,j)][min(i,j)];

    return INT_MAX; // Para evitar considerar la distancia de una ciudad a sí misma
  }

  int totalWeight(vector<int> solution) const{
    assert(solution.size() == n);
    int weight = 0;
    for(int i = 0; i < n; i++)
      weight += getDistance(solution(i),solution((i-1+n)%n));

    return weight;
  }

  // Devuelve la distancia de city a su ciudad más cercana
  int bestDistance(int city) const{
    int minD = getDistance(city,0);
    
    for(int j = 1; j < n; j++)
      if(getDistance(city,j) < minD)
	minD = getDistance(city,j);

    return minD;
  }

  int weightBound(const vector<int> &visited, int currentWeight) const{
    int bound = currentWeight;

    for(int i = 1; i < n; i++)
      if(find(visited.begin(),visited.end(),i)==visited.end())
	bound += bestDistance(i);

    return bound;
  }
};

void backtracking(const TSP& tsp, const vector<int> &visited, vector<int> &bestSol, int currentWeight, int& minimumWeight){

  if(visited.size() == tsp.getN()){
    currentWeight += tsp.getDistance(visited.back(),visited.front());
    if(currentWeight < minimumWeight){
      minimumWeight = currentWeight;
      bestSol = visited;
    }
    return;
  }

  if(tsp.weightBound(visited, currentWeight) >= minimumWeight)
    return;

  int weight;
  vector<int> aux;

  for(int i = 1; i < tsp.getN(); i++){
    weight = currentWeight;
    aux = visited;
    if(find(visited.begin(),visited.end(),i)==visited.end()){
      aux.push_back(i);
      weight += tsp.getDistance(i,visited.back());
      backtracking(tsp, aux, bestSol, weight, minimumWeight);
    }
  }
}

int main(int argc, char* argv[]){

  if(argc < 2){
    cerr << "Formato incorrecto\n";
    mostrarInfo();
    exit(-1);
  }

  string nombre_entrada(argv[1]);
  string nombre_salida(argv[1]);

  nombre_entrada="datosTSP/" + nombre_entrada + ".tsp";
  nombre_salida="salidas/" + nombre_salida + "_solved.tsp";

  TSP tsp(nombre_entrada);

  // tsp.printMap(); cout << endl;

  vector<int> bestSol(tsp.getN());
  vector<int> visited;

  clock_t t1, t2;
  t1 = clock();
  for(int i = 0; i < tsp.getN(); i++) bestSol[i] = i; // Solución de referencia inicial
  int weight = tsp.totalWeight(bestSol);
  visited.push_back(0);
  backtracking(tsp, visited, bestSol, 0, weight);
  t2 = clock();
  
  cout << "Recorrido:\n";
  printVector(bestSol);
  cout << "Peso total: " << weight << endl;

  cout << "Tamaño\ttiempo" << endl;
  cout << tsp.getN() << "\t" << (t2-t1)/(float)CLOCKS_PER_SEC << endl;
  
  ofstream of(nombre_salida);

  if(!of){
    cerr << "Error en la apertura de " << nombre_salida <<endl;
    mostrarInfo();
    exit(-1);
  }

  of << "DIMENSIÓN: " << tsp.getN() << endl;

  for(int i=0; i<tsp.getN(); i++)
    of << bestSol[i]+1 << " " << tsp.xCords[bestSol[i]] << " " << tsp.yCords[bestSol[i]] << endl;
  
  of.close();
}
