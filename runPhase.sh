mkdir -p data
mkdir -p derived
mkdir -p figures
cd simFiles
g++ -o isingPhases phaseTransitioner.cpp
./isingPhases
cd ../visualization
python3 plotter.py
cd ..
./makeAnime.sh
