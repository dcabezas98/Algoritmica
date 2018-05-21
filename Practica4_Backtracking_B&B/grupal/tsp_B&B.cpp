#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <climits>
#include <queue>

void printVector(vector<int> v){
  for(int i = 0; i < v.size()-1; i++)
    cout << v[i] << ", ";
  cout << v.back() << endl;
}

struct node{
  vector<int> visited;
  int bound;
  int currentWeight;

  bool operator<(node other) const
    {
        return bound > other.bound;
    }
};
  
class TSP{

private:
  int n;
  vector<vector<int>> map;

public:

  vector<double> xCords, yCords;

  TSP(string file){

    ifstream f(file);
    
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
    if(0 <= i && i < n && 0 <= j && j < n && i != j)
      return map[max(i,j)][min(i,j)];

    cout << "INT_MAX" << INT_MAX << endl;
    return INT_MAX; // Para evitar considerar la distancia de una ciudad a sí misma
  }

  int totalWeight(vector<int> solution) const{
    assert(solution.size() == n);
    int weight = 0;
    for(int i = 0; i < n; i++)
      weight += getDistance(solution[i],solution[(i-1+n)%n]);

    return weight;
  }

  // Devuelve la distancia de city a su ciudad más cercana
  int bestDistance(int city) const{
    int minD = getDistance(city,0);
    
    for(int j = 1; j < n; j++)
      if(getDistance(city,j) < minD){
	minD = getDistance(city,j);
	if (minD==0) cout << "Ciudades " << city << "  " << j << endl; 
      }

    cout << "BestDistance " << minD << endl;
    return minD;
  }

  int weightBound(const vector<int> &visited, int currentWeight) const{
    int bound = currentWeight;

    for(int i = 1; i < n; i++)
      if(find(visited.begin(),visited.end(),i)==visited.end())
	bound += bestDistance(i);

    bound += bestDistance(visited.front());

    return bound;
  }
};

void BandB(const TSP& tsp, priority_queue<node> &alive_nodes, vector<int> &bestSol, int& minimumWeight, int &maxsize, int &expanded){
  
  if(alive_nodes.size() > maxsize)
    maxsize = alive_nodes.size();
  
  node n = alive_nodes.top();
  printVector(n.visited);
  alive_nodes.pop();

  cout << "Min weight: " << minimumWeight << endl;
  cout << "Bound " << n.bound << endl;
  if(n.bound >= minimumWeight){
    cout << "Poda" << endl;
    return;
  }

  if(n.visited.size() == tsp.getN()){
    cout << "Solución" << endl;
    n.currentWeight += tsp.getDistance(n.visited.front(), n.visited.back());
    if(n.currentWeight < minimumWeight){
      minimumWeight = n.currentWeight;
      bestSol = n.visited;
    }
    return;
  }

  node aux;

  expanded++;
  
  for(int i = 1; i < tsp.getN(); i++){
    if(find(n.visited.begin(), n.visited.end(), i) == n.visited.end()){
      aux = n;
      aux.visited.push_back(i);
      aux.currentWeight += tsp.getDistance(i, n.visited.back());
      aux.bound = tsp.weightBound(aux.visited, aux.currentWeight);
      alive_nodes.push(aux);
    }
  }

  BandB(tsp, alive_nodes, bestSol, minimumWeight, maxsize, expanded);
}

void mostrarInfo(){
  cerr << "Ejemplo: ./tsp ulysses16\n";
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

  tsp.printMap(); cout << endl;

  vector<int> bestSol(tsp.getN());
  vector<int> visited;

  clock_t t1, t2;
  t1 = clock();
  
  for(int i = 0; i < tsp.getN(); i++) bestSol[i] = i; // Solución de referencia inicial
  int weight = tsp.totalWeight(bestSol);

  visited.push_back(0);

  node nod = {visited, 0, 0};

  priority_queue<node> queue;
  queue.push(nod);

  int maxsize = 0, expanded = 0;
  
  BandB(tsp, queue, bestSol, weight, maxsize, expanded);

  t2 = clock();
  
  cout << "Recorrido:\n";
  printVector(bestSol);
  cout << "Peso total: " << weight << endl;

  cout << "Tamaño\ttiempo" << endl;
  cout << tsp.getN() << "\t" << (t2-t1)/(float)CLOCKS_PER_SEC << endl;

  cout << "Nodos expandidos: " << expanded << endl;
  cout << "Podas: " << queue.size()+1 << endl;
  cout << "Tamaño máximo de la cola de nodos vivos: " << maxsize << endl;
  
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
