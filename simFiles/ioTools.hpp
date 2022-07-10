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

void writeLatticeToFile(vector<vector<int>> lattice, string datapath, int time){
  ofstream spinLattice(datapath + "spinLattice" + to_string(time) + ".txt");
  const int size = lattice.size();
  for (int i = 0 ; i < size; i++){
    for (int j = 0; j < size; j++){
      if(j == 0){
	spinLattice << to_string(lattice[i][j]);
      } else{
	spinLattice << "," + to_string(lattice[i][j]);
      }
    }
    spinLattice << "\n";
  }
  spinLattice.close();
}

void writeDerivedData(vector<float> dataVector, string name){
  ofstream derivedData("../derived/" + name + ".txt");
  const int size = dataVector.size();
  for(int i = 0 ; i < size; i++){
      if(i == 0){
        derivedData << to_string(dataVector[i]);
      } else{
        derivedData << "," + to_string(dataVector[i]);
      }
  }
  derivedData.close();
};
