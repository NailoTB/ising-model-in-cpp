# Ising model simulator in C++
A simple Ising model simulator made in C++. Made for lattice method practice and to store my common plotting scripts.

The simulations can be run simply by calling either bash scripts:
```
./runOne.sh
./runPhase.sh
```
The first simulation depicts the magnetization process from a dispersed state at T = 1. The second simulation depicts the phase transition from a magnetized state to a dispersed state.

The scripts compile the simulator, runs it and creates an animation. The initial state is seeded. The spin-flip algorithm is the Metropolis-Hastings algorithm.
To do: More refactoring. Explain physics.

<p align="center">
  <img height="400" src="https://github.com/NailoTB/spins-on-lattice/blob/main/metastable_animation.gif">
  <img height="400" src="https://github.com/NailoTB/spins-on-lattice/blob/main/phase_animation.gif">
</p>

<p align="center">
  <img height="400" src="https://github.com/NailoTB/spins-on-lattice/blob/main/totalPhaseMagnetization.png">
</p>

The left animation depicts a meta-stable state. The right animation shows how the phase transition occurs from a completely magnetized state (it takes a couple of seconds).
The bottom graph shows the total magnetization as a function of temperature. The red line shows the analytical solution for the critical temperature (T = 2.27).
