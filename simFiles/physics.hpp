#include <random>

random_device os_seed;
mt19937 generator(os_seed());

void generateInitialLattice(int size, string datapath, int seed = 595, float spinRatio = 0.5){
  ofstream spinLattice(datapath + "spinLattice0.txt");
  mt19937 initialGenerator( seed ); uniform_real_distribution<> dist(0, 1);

  for (int i = 0 ; i < size; i++){
    for (int j = 0; j < size; j++){
      if(dist( initialGenerator ) > spinRatio){
        spinLattice << "1,";
      }else{
        spinLattice << "-1,";
      }
    }
    spinLattice << "\n";
  }
  spinLattice.close();
};

float magnetization(vector<vector<int>> state){
  int N = state.size();
  float magSum = 0;
  for(int i = 0 ; i < N; i++){
    for(int j = 0 ; j < N; j++){
    magSum = magSum + state[i][j];
    }
}
  return abs(magSum)/(N*N);
};

float flipEnergyDifference(vector<vector<int>> state, vector<int> randomCell, float eps, float extForce){
  const unsigned int N = state.size(), i = randomCell[0], j = randomCell[1];
  float oldSpin = state[i][j]*(state[(i+1)%N][j] + state[(N - 1 + i)%N][j] + state[i][(j+1)%N] + state[i][(N - 1 + j)%N]) - extForce*state[i\
][j];
  return 2.0*eps*oldSpin; //newSpin = -oldSpin
};

bool checkFlipProbability(float spinDifference, float boltz, float temp){
  uniform_real_distribution<> dist(0, 1);
  auto prob = exp(-spinDifference/(boltz*temp));
  return ( dist(generator) < prob ) ;
};

float totalPairEnergy(vector<vector<int>> state){
  int N = state.size();
  int spinSum = 0;
  for(int i = 0 ; i < N; i++){
    for(int j = 0 ; j < N; j++){
    spinSum = spinSum + state[i][j]*(state[(i+1)%N][j] + state[i][(j+1)%N]);
    }
  }
  return spinSum;
};

vector<int> getRandomCell(int size){
  uniform_int_distribution<> dist(0, size-1);
  vector<int> cell{dist( generator ), dist( generator ) };
  return cell;
};
