#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

int enSuPosicionLims(int *T, int l, int r){

  if(r <= l)
    return -1;

  int p = (l+r-1)/2;
    
  if(p == T[p])
    return p;

  int res;
    
  if(p < T[p]){
    if((res = enSuPosicionLims(T, l, p)) != -1)
      return res;

      
    return enSuPosicionLims(T, T[p], r);
  }
    
  if((res = enSuPosicionLims(T, p+1, r)) != -1)
    return res;
    
  return enSuPosicionLims(T, l, T[p]+1);
}

int enSuPosicion(int *T, int n){
  return enSuPosicionLims(T, 0, n);
}

int main(int argc, char* argv[]){

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int m=2*n-1;

  
  int *T = new int[n];

  double suma = 0;

  for(int k = 0; k < 100; k++){
    srand(time(0));

    int r;
  
    for(int i = 0; i < n; i++){
      r = rand() %m -n+1;
      T[i] = r;
    }

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
  
  cout << n << "\t" << suma/100.0 << endl;

  delete [] T;
}
