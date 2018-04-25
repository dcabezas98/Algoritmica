#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main(int argc, char *argv[]){

  if(argc < 2){
    cerr << "Falta fichero\n";
    exit(-1);
  }
  
  ifstream f(argv[1]);
  if(!f){
    cerr << "Error apertura " << argv[1] << endl;
    exit(-1);
  }

  int n;
  string trash;

  f >> trash;
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
  
  for(i = 0; i < n; i++){
    for(j = 0; j < i; j++){
      distance = (int) rint(sqrt(pow(xCords[i]-xCords[j],2) + pow((yCords[i]-yCords[j]),2)));
      map[i].push_back(distance);
    }
  }

  xCords.clear();
  yCords.clear();
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
  for(int k = 1; k < n; k++){
    dmin = INT_MAX;

    for(j = 0; j < n; j++)
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
}
