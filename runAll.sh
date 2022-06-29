cd simFiles
g++ -o ising spins.cpp
./ising
cd ../visualization
python3 plotter.py
cd ..
./makeAnime.sh
