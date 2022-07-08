#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;
#include "ioTools.h"

random_device os_seed;
mt19937 generator(os_seed());

void generateInitialLattice(int size, string datapath, int seed = 595){ //implement ratio
  ofstream spinLattice(datapath + "spinLattice0.txt");
  mt19937 generator( seed ); uniform_real_distribution<> dist(0, 1);
  
  for (int i = 0 ; i < size; i++){
    for (int j = 0; j < size; j++){
      if(dist( generator ) > 0.5){
	spinLattice << "1,";
      }else{
	spinLattice << "-1,";
      }
    }
    spinLattice << "\n";
  }
  spinLattice.close();
}

float totalPairEnergy(vector<vector<int>> state){
  int N = state.size();
  int spinSum = 0;
  for(int i = 0 ; i < N; i++){
    for(int j = 0 ; j < N; j++){
    spinSum = spinSum + state[i][j]*(state[(i+1)%N][j] + state[i][(j+1)%N]);  
    }
  }
  return spinSum;
}

float magnetization(vector<vector<int>> state){
  int N = state.size();
  float magSum = 0;
  for(int i = 0 ; i < N; i++){
    for(int j = 0 ; j < N; j++){
    magSum = magSum + state[i][j];  
    }
  }
  return abs(magSum)/N;
};

vector<int> getRandomCell(int size){
  uniform_int_distribution<> dist(0, size-1);
  vector<int> cell{dist( generator ), dist( generator ) };
  return cell;
};

float flipEnergyDifference(vector<vector<int>> state, vector<int> randomCell, float eps, float extForce){
  int N = state.size(), i = randomCell[0], j = randomCell[1];
  float oldSpin = state[i][j]*(state[(i+1)%N][j] + state[(N - 1 + i)%N][j] + state[i][(j+1)%N] + state[i][(N - 1 + j)%N]) - extForce*state[i][j];
  return 2.0*eps*oldSpin; //newSpin = -oldSpin
};

bool checkFlipProbability(float spinDifference, float boltz, float temp){
  uniform_real_distribution<> dist(0, 1);
  auto prob = exp(-spinDifference/(boltz*temp));
  return ( dist(generator) < prob ) ;
  };

int main() {
  const float k = 1.0, T = 0.5, epsilon = 1.0,  magField = 0.0; //boltzmann, temperature, interaction_energy
  const int size = 400, timeSteps = 100, flipsPerStep = 25000;

  auto lattice = vector<vector<int>>(size, vector<int>(size, 0));
  auto totMag = vector<float>(timeSteps);

  const string dataPath = "data/";
  generateInitialLattice(size, dataPath);
  lattice = readDataToLattice(lattice, dataPath, 0);
  totMag[0] = magnetization(lattice);

  cout << "Starting the simulation...\n";
  cout << "Timestep: " << endl;
  cout << "1/" << timeSteps << flush;

  for(int t = 1 ; t < timeSteps; t++){
    for(int flip = 0 ; flip < flipsPerStep; flip++){
      vector<int> cell = getRandomCell(size);
      float spinDiff = flipEnergyDifference(lattice, cell, epsilon, magField);
      if(spinDiff < 0){
	lattice[cell[0]][cell[1]] = -1*lattice[cell[0]][cell[1]]; 
      } else{
	if(checkFlipProbability(spinDiff, k, T)){
	  lattice[cell[0]][cell[1]] = -1*lattice[cell[0]][cell[1]];
	}
      }
      
    }
    writeLatticeToFile(lattice, dataPath, t);
    totMag[t] = magnetization(lattice);
    cout << "\r" << t+1 << "/" << timeSteps << flush;
  }
  writeDerivedData(totMag, "totalMagnetization");
  cout << "\nSimulation done." << endl;
  
  return 0;
}
