#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <sstream>
#include<ctime>

using namespace std;
#include "ioTools.h"
//to do add new force
void generateInitialLattice(int size, string datapath){ //implement ratio
  ofstream spinLattice(datapath + "spinLattice0.txt");
  random_device rd; mt19937 e2(rd()); normal_distribution<> dist(0, 3);
  
  for (int i = 0 ; i < size; i++){
    for (int j = 0; j < size; j++){
      if(dist(e2) > -100){
	spinLattice << "1,";
      }else{
	spinLattice << "-1,";
      }
    }
    spinLattice << "\n";
  }
  spinLattice.close();
}

float totalPairSpin(vector<vector<int>> state){
  int N = state.size();
  int spinSum = 0;
  for(int i = 0 ; i < N; i = i + 2){
    for(int j = 0 ; j < N; j++){
      spinSum = spinSum + state[i][j]*(state[(i+1)%N][j] + state[(N - 1 + i)%N][j] + state[i][(j+1)%N]);
    }
  }
  return spinSum;
}
float totalPairSpinDelta(vector<vector<int>> state){
  int N = state.size();
  int spinSum = 0;
  for(int i = 0 ; i < N; i++){
    for(int j = 0 ; j < N; j++){
    spinSum = spinSum + state[i][j]*(state[(i+1)%N][j] + state[i][(j+1)%N]);  
    }
  }
  return spinSum;
}

int totalMagnetization(vector<vector<int>> state){
  int N = state.size();
  int magSum = 0;
  for(int i = 0 ; i < N; i++){
    for(int j = 0 ; j < N; j++){
    magSum = magSum + state[i][j];  
    }
  }
  return abs(magSum);
}

vector<int> getRandomCell(int size){
  random_device rd; mt19937 e2(rd()); uniform_real_distribution<> dist(0, size-1);
  vector<int> cell{ (int)round(dist(e2)), (int)round(dist(e2)) };
  return cell;
}

float flipEnergyDifference(vector<vector<int>> state, vector<int> randomCell, float eps){
  int N = state.size(); int i = randomCell[0]; int j = randomCell[1];
  float oldSpin = state[i][j]*(state[(i+1)%N][j] + state[(N - 1 + i)%N][j] + state[i][(j+1)%N] + state[i][(N - 1 + j)%N]);
  return 2.0*eps*oldSpin; //newSpin = -oldSpin
}

bool checkFlipProbability(float spinDifference, float boltz, float temp){
  random_device rd; mt19937 e2(rd()); uniform_real_distribution<> dist(0, 1);
  float prob = exp(-spinDifference/(boltz*temp));
  if(dist(e2) < prob){
    return true;
  } else{
    return false;
  }
}

int main() {
  const float k = 1.0 ; const float T = 0.5; const float epsilon = 1.0; //boltzmann, temperature, interaction_energy
  string dataPath = "data/";
  const int size = 400; const int timeSteps = 100; const int flipsPerStep = 20000;
  vector<vector<int>> lattice = vector<vector<int>>(size, vector<int>(size, 0));
  generateInitialLattice(size, dataPath);
  lattice = readDataToLattice(lattice, dataPath, 0);
  for(int t = 1 ; t < timeSteps; t++){
    for(int flip = 0 ; flip < flipsPerStep; flip++){
      vector<int> cell = getRandomCell(size);
      float spinDiff = flipEnergyDifference(lattice, cell, epsilon);
      if(spinDiff < 0){
	lattice[cell[0]][cell[1]] = -1*lattice[cell[0]][cell[1]]; 
      } else{
	if(checkFlipProbability(spinDiff, k, T)){
	  lattice[cell[0]][cell[1]] = -1*lattice[cell[0]][cell[1]];
	}
      }
    }
    writeLatticeToFile(lattice, dataPath, t);
  }
  return 0;
}
