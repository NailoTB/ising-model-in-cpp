mkdir -p simFiles/data
mkdir -p simFiles/derived
mkdir -p visualization/figures
cd simFiles
g++ -o ising spins.cpp
./ising
cd ../visualization
python3 plotter.py
cd ..
./makeAnime.sh
