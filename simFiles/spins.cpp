#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;
#include "ioTools.hpp"
#include "physics.hpp"

int main() {
  const float k = 1.0, T = 1.0, epsilon = 1.0,  magField = 0.0; //boltzmann, temperature, interaction_energy
  const unsigned int size = 100, timeSteps = 100, flipsPerStep = 100000;

  auto lattice = vector<vector<int>>(size, vector<int>(size, 0));
  auto totMag = vector<float>(timeSteps);

  const string dataPath = "../data/";
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
