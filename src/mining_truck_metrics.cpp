#include "mining_truck_metrics.hpp"

void MiningTruckMetrics::addTruckOperation(MiningTruckStatus status, int timeInOperation) {
    MiningTruckOperation truckOperation = {status, timeInOperation};
    truckOperations.push_back(truckOperation);
}

void MiningTruckMetrics::increaseNumberOfUnloads() {
    numberOfUnloads++;
}

void MiningTruckMetrics::calculateAndUpdateMetrics() {
    timeMining = 0;
    timeTravelingToSite = 0;
    timeTravelingToStation = 0;
    timeInQueue = 0;
    totalTimeTraveling = 0;
    timeUnloading = 0;

    for (MiningTruckOperation operation : truckOperations) {
        switch (operation.status) {
            case MiningTruckStatus::MINING:
                timeMining++;
                break;
            case MiningTruckStatus::TRAVELING_TO_STATION:
                timeTravelingToStation++;
                break;
            case MiningTruckStatus::TRAVELING_TO_SITE:
                timeTravelingToSite++;
                break;
            case MiningTruckStatus::IN_QUEUE:
                timeInQueue++;
                break;
            case MiningTruckStatus::UNLOADING:
                timeUnloading++;
                break;
            default:
                break;
        }
    }
    totalTimeTraveling = timeTravelingToSite + timeTravelingToStation;
}

void MiningTruckMetrics::displayTrucksMetrics(int truckId) {
    calculateAndUpdateMetrics();
    std::cout << "============================================" << std::endl;
    std::cout << "Metrics for Mining Truck: " << truckId << std::endl;
    std::cout << "  - Time Spent Mining: " << timeMining * 5  << " minutes" << std::endl;
    std::cout << "  - Time Spent Traveling to Mining Site: " << timeTravelingToSite * 5  << " minutes" << std::endl;
    std::cout << "  - Time Spent Traveling to Unload Station: " << timeTravelingToStation * 5  << " minutes" << std::endl;
    std::cout << "  - Total Time Spent Traveling: " << totalTimeTraveling * 5  << " minutes" << std::endl;
    std::cout << "  - Time Spent in Station Queue: " << timeInQueue * 5  << " minutes" << std::endl;
    std::cout << "  - Time Spent Unloading: " << timeUnloading* 5  << " minutes" << std::endl;
    std::cout << "  - Total number of truck unloads: " << numberOfUnloads << std::endl;
}