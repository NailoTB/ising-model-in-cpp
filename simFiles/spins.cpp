#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <sstream>

using namespace std;

void generateSpinLattice(int size, string datapath){
  ofstream spinLattice(datapath + "spinLattice0.txt");
  random_device rd; mt19937 e2(rd()); normal_distribution<> dist(0, 3);
  
  for (int i = 0 ; i < size; i++){
    for (int j = 0; j < size; j++){
      if(dist(e2) > -4){
	spinLattice << "1,";
      }else{
	spinLattice << "-1,";
      }
    }
    spinLattice << "\n";
  }
  spinLattice.close();
}

vector<vector<int>> readDataToLattice(vector<vector<int>> latt, string datapath, int time){
  ifstream dataLattice(datapath + "/spinLattice" + to_string(time) + ".txt");
  int rowIdx = 0;
  int val; string line;
  
  while(getline(dataLattice, line)){
    stringstream ss(line);
    int colIdx = 0;
	while(ss >> val){
      latt[rowIdx][colIdx] = val;
	if(ss.peek() == ',') ss.ignore();
      colIdx++;
    }
    rowIdx++;
  }
  dataLattice.close();
  return latt;
}

int main() {
  string dataPath = "data/";
  string dataName = "spinLattice";
  int size = 20;
  generateSpinLattice(size, dataPath);
  
  vector<vector<int>> lattice = vector<vector<int>>(size, vector<int>(size, 0));
  lattice = readDataToLattice(lattice, dataPath, 0);
  
  for(int k = 0 ; k < size; k++){
    cout << lattice[2][k] << endl;
  }

  return 0;
}
