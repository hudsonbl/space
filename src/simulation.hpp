/**
 * @file simulation.hpp
 * @brief Header file for the Simulation class.
 *
 * This file contains the declaration of the Simulation class.
 */

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <queue>
#include <vector>
#include "home_base.hpp"


/**
 * @class Simulation
 * @brief This contains any logic pertaining to the higher level of abstraction
 *        controlling the simulation.
 */
class Simulation : public HomeBase {
private:
    // Converted MAX_RUNTIME to minutes per iteration in Simulation
    // This translates to 5 minutes per iteration.
    //      (72 * 60) -> hours converted to minutes.
    //      (min) / 5 -> 5 minutes per iteratoin.
    int MAX_RUNTIME = (72 * 60) / 5;
 
    /**
     * @brief Updates the logical time passed each iteration of the Simulation.
     *        Each iteration is equivalent to 5 minutes passing.
     */
    void updateTimeLoop();
public:
    /**
     * @brief Constructor for the Simulation object
     *
     * @param numTrucks Number of MiningTruck's in the simulation.
     * @param numStations Number of MiningUnloadStation's in the simulation.
     */
    Simulation(int numTrucks, int numStations) : 
        HomeBase(numTrucks, numStations) {};

    /**
     * @brief Used to start the simulation. This contains the core logic behind
     *        the iterative approach to time and running the components within
     *        the simulation.
     */
    void start();
};

#endif