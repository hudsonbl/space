#include "unload_station_metrics.hpp"

void UnloadStationMetrics::increaseNumberOfTrucksUnloaded() {
    numberOfTrucksUnloaded++;
}

void UnloadStationMetrics::increaseIdleTime() {
    timeIdle++;
}

void UnloadStationMetrics::updateMaxTrucksInQueue(int queueSize) {
    // -1 because the first truck in line is UNLOADING.
    maxNumberOfTrucksInQueue = std::max(maxNumberOfTrucksInQueue, queueSize - 1);
}

void UnloadStationMetrics::increaseTimeTrucksInQueue() {
   timeTrucksInQueue++;
}

void UnloadStationMetrics::displayStationMetrics(int stationId) {
    std::cout << "============================================" << std::endl;
    std::cout << "Metrics for Mining Unload Station: " << stationId << std::endl;
    std::cout << "  - Time Idle: " << timeIdle * 5  << " minutes" << std::endl;
    std::cout << "  - Time trucks spent in Queue: " << timeTrucksInQueue * 5  << " minutes" << std::endl;
    std::cout << "  - Number of Trucks Unloaded: " << numberOfTrucksUnloaded  << std::endl;
    std::cout << "  - Max number of Trucks waiting: " << maxNumberOfTrucksInQueue << std::endl;
}