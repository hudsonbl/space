#include "mining_truck.hpp"

int MiningTruck::getTruckId() {
    return truckId;
}

int MiningTruck::getTimeInCurrentOperation(){
    return timeInCurrentOperation;
}

void MiningTruck::startMining() {
    // Get a random mining time for 1-5 hours.
    int minTime = 1;
    int maxTime = 5;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(minTime, maxTime);
   
    // TODO: Have a util function to convert time? util.convertHoursToTicks()
    timeInCurrentOperation = distrib(gen);
    timeInCurrentOperation *= 60; // Convert to minutes.
    std::cout << "Mining time: " << timeInCurrentOperation << " minutes for Truck ID: " << truckId << std::endl;
    timeInCurrentOperation = timeInCurrentOperation / 5; // Convert to simulation time tick.

    setTruckMining();
}

void MiningTruck::setTruckMining() {
    std::cout << "Setting truck: " << truckId << " to mining" << std::endl;
    status = MiningTruckStatus::MINING;
}

void MiningTruck::setTruckInQueue(int stationId) {
    std::cout << "Adding truck: " << truckId << " to IN_QUEUE at Station ID: " << stationId << std::endl;
    status = MiningTruckStatus::IN_QUEUE;
    timeInCurrentOperation = 0;
}

void MiningTruck::setTruckUnloading(int stationId) {
    std::cout << "Setting truck: " << truckId << " to UNLOADING at Station ID: " << stationId << std::endl;
    status = MiningTruckStatus::UNLOADING;
    timeInCurrentOperation = 1;
}

void MiningTruck::setMiningSiteDestination() {
    std::cout << "Setting truck: " << truckId << " to TRAVELING_TO_SITE" << std::endl;
    status = MiningTruckStatus::TRAVELING_TO_SITE;
    timeInCurrentOperation = (30 / 5);  // Minutes / time ticks.
}

void MiningTruck::setUnloadStationDestination(int stationId) {
    std::cout << "Setting truck: " << truckId << " to TRAVELING_TO_STATION at Station ID: " << stationId << std::endl;
    status = MiningTruckStatus::TRAVELING_TO_STATION;
    timeInCurrentOperation = (30 / 5); // Minutes / time ticks.
}

bool MiningTruck::readyToUnload() {
    if (status == MiningTruckStatus::MINING) {
        return timeInCurrentOperation == 0;
    }
    return false;
}

void MiningTruck::updateTruck() {
    // Updating information
    timeInCurrentOperation -= 1;
    
    if (timeInCurrentOperation < 0) {
        timeInCurrentOperation = 0;
    }
    // For the current time frame update what the vehicle was doing.
    addTruckOperation(status, timeInCurrentOperation);
}

MiningTruckStatus MiningTruck::getCurrentOperationStatus() {
    return status;
}