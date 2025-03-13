#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "home_base.hpp"


class Simulation : public HomeBase {
private:
    int currentRuntime = 0;
    // Converted RUNTIME to minutes per iteration in Simulation
    // This translates to 5 minutes per iteration.
    //      (72 * 60) -> hours converted to minutes.
    //      (min) / 5 -> 5 minutes per iteratoin.
    int MAX_RUNTIME = (72 * 60) / 5;
 
    void updateTimeLoop();
public:
    Simulation(int numTrucks, int numStations) : HomeBase(numTrucks, numStations) {};

    void start();
    void printInfo();
};

#endif