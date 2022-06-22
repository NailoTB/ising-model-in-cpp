cd simFiles
g++ -o ising spins.cpp
./ising
cd ../visualization
python3 plotter.py
cd ..
convert -delay 30 -loop 0 `find $PWD/visualization/figures/ -type f | sort -V` animation.gif
