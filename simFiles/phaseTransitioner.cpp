#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;
#include "ioTools.hpp"
#include "physics.hpp"

int main() {
  const float k = 1.0, epsilon = 1.0, magField = 0.0;
  const unsigned int size = 50, tempSteps = 200, flipsPerStep = 1000000;

  auto lattice = vector<vector<int>>(size, vector<int>(size, 0));
  auto totMag = vector<float>(tempSteps);
  auto tempStepSize = 0.015;
  const string dataPath = "../data/";

  cout << "Starting phase simulation...\n";
  cout << "Tempstep: " << endl;
  cout << "1/" << tempSteps << flush;
  generateInitialLattice(size, dataPath, 38924, 0.99);
  lattice = readDataToLattice(lattice, dataPath, 0);
  totMag[0] = magnetization(lattice);
  for(unsigned int t = 1 ; t < tempSteps; t++){    
    for(unsigned int flip = 0 ; flip < flipsPerStep; flip++){
      vector<int> cell = getRandomCell(size);
      float spinDiff = flipEnergyDifference(lattice, cell, epsilon, magField);
      if(spinDiff < 0){
	lattice[cell[0]][cell[1]] = -1*lattice[cell[0]][cell[1]]; 
      } else{
	if(checkFlipProbability(spinDiff, k, t*tempStepSize)){
	  lattice[cell[0]][cell[1]] = -1*lattice[cell[0]][cell[1]];
	}
      }
      
    }
    writeLatticeToFile(lattice, dataPath, t);
    totMag[t] = magnetization(lattice);
    cout << "\r" << t+1 << "/" << tempSteps << flush;
  }
  writeDerivedData(totMag, "totalPhaseMagnetization");
  cout << "\nSimulation done." << endl;
  
  return 0;
}
