#include "simulation.hpp"

void Simulation::updateTimeLoop() {
    updateTrucks();
    updateStations();
}

void Simulation::start() {
    startMiningOperations();

    // Each iteration is equivalent to 5 minutes.
    for (int timeTick = 0; timeTick < MAX_RUNTIME; timeTick++) {
        evaluateTruckOperations();
        displayMiningOperationInfo(timeTick);
        updateTimeLoop();
    }
    displayStationMetrics();
    displayTruckMetrics();
}