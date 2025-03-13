#include "simulation.hpp"

void Simulation::printInfo() {
    std::cout << "Program done" << std::endl;
}

void Simulation::updateTimeLoop() {
    updateTrucks();
    updateStations();
}

void Simulation::start() {
    startMiningOperations();

    // Each iteration is equivalent to 5 minutes.
    for (int timeTick = 0; timeTick < MAX_RUNTIME; timeTick++) {
        // TODO add comments to specify each thing.
        evaluateTruckOperations();
        displayMiningOperationInfo(timeTick);
        updateTimeLoop();
    }
    displayStationMetrics();
    displayTruckMetrics();
}