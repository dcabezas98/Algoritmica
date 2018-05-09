/*
  Simulación del problema de la cena de gala.
  
  David Cabezas Berrido
 */

#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <ctime>

int randInt(){
  return rand()%101;
}

void imprimeVector(vector<int> v){
  for(int i = 0; i < v.size()-1; i++)
    cout << v[i] << ", ";
  cout << v.back() << endl;
}

class Cena{
  
private:
  const int n;
  vector<vector<int>> afinidad;

public:

  Cena(int k):n(k){
    int i,j;

    vector<int> afin;
    
    for(i = 0; i < n; i++){
      afin.clear();
      
      for(j = 0; j < i; j++)
	afin.push_back(randInt());

      afin.push_back(-1);
      for(j = i+1; j < n; j++)
	afin.push_back(randInt());

      afinidad.push_back(afin);
    }
  }

  int getN() const{
    return n;
  }

  void printAfinidades() const{
    int i, j;

    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++)
	cout << afinidad[i][j] << "\t";
      cout << endl;
    }
  }

  int getAfinidad(int i, int j) const{
    if(0 <= i && i < n && 0 <= j && j < n)
      return afinidad[i][j];

    return -1;
  }

  int afinidadTotal(vector<int> solution) const{
    assert(solution.size() == n);
    int affinity = 0;
    for(int i = 0; i < n; i++)
      affinity += afinidad[i][(i-1+n)%n] + afinidad[i][(i+1)%n];

    return affinity;      
  }

  void mayoresAfinidades(int persona, int& max1, int& max2) const{
    max1 = max2 = 0;

    for(int j = 0; j < n; j++)
      if(afinidad[persona][j] > max1){
	max2 = max1;
	max1 = afinidad[persona][j];
      }
      else if(afinidad[persona][j] > max2)
	max2 = afinidad[persona][j];
  }

  int cotaAfinidad(const vector<int> &sentados, int afActual) const{
    int maxA = afActual;
    int max1, max2;

    for(int i = 1; i < n; i++)
      if(find(sentados.begin(),sentados.end(),i)==sentados.end()){
	mayoresAfinidades(i,max1,max2);
	maxA += max1+max2; 
      }
    // Se asumen al menos dos personas sentados
    mayoresAfinidades(sentados.front(),max1,max2);
    maxA += max1;
    mayoresAfinidades(sentados.back(),max1,max2);
    maxA += max1;

    return maxA;
  }
};

void backtracking(const Cena& cena, const vector<int> &sentados, vector<int> &bestSol, int currentAffinity, int& bestAffinity){

  if(sentados.size() == cena.getN()){
    currentAffinity += cena.getAfinidad(sentados.back(),sentados.front()) + cena.getAfinidad(sentados.front(),sentados.back());
    if(currentAffinity > bestAffinity){
      bestAffinity = currentAffinity;
      bestSol = sentados;
    }
    return;
  }
  // Poda cuando la solución no tenga posibilidades de ser la mejor
  if(cena.cotaAfinidad(sentados, currentAffinity) <= bestAffinity){
    return;
  }
  
  int aff;
  vector<int> aux;
  
  for(int i = 1; i < cena.getN(); i++){
    aff = currentAffinity;
    aux = sentados;
    if(find(sentados.begin(),sentados.end(),i)==sentados.end()){
      aux.push_back(i);
      aff += cena.getAfinidad(i,sentados.back()) + cena.getAfinidad(sentados.back(),i);
      backtracking(cena, aux, bestSol, aff, bestAffinity);
    }
  }
}
  
int main(int argc, char* argv[]){

  if(argc < 2){
    cerr << "Error de parámetros. Formato:\n ./cena <nº_comensales>\n";
    exit(-1);
  }

  int n = atoi(argv[1]);
  
  int suma = 0;
  for(int k = 0; k < 10; k++){
    
    srand(k);
    
    Cena cena(n);

    //cena.printAfinidades(); cout << endl;

    clock_t t1, t2;

    t1 = clock();
    vector<int> bestSol(n);
    vector<int> sentados;
  
    for(int i = 0; i < n; i++) bestSol[i] = i; // Solución de referencia inicial
    int affinity = cena.afinidadTotal(bestSol);
    sentados.push_back(0);
    backtracking(cena, sentados, bestSol, 0, affinity);  
    t2 = clock();

    suma += t2-t1;
    /*
      imprimeVector(bestSol);
      cout << "Suma de afinidades: " << affinity << endl;
    */
  }
  
  cout << n << "\t" << suma/(float)CLOCKS_PER_SEC/10.0 << endl;
}
