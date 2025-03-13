#include "mining_unload_station.hpp"

int MiningUnloadStation::getStationId() {
    return stationId;
}

std::queue<int> MiningUnloadStation::getStationQueue() {
    return miningTrucksQueued;
}

int MiningUnloadStation::getNumberOfTrucksAssignedToStation() {
    return miningTrucksQueued.size();
}

bool MiningUnloadStation::isTruckQueueEmpty() {
    return miningTrucksQueued.empty();
}

int MiningUnloadStation::frontTruckInQueue() {
    return miningTrucksQueued.front();
}

bool MiningUnloadStation::popTruckFromQueue() {
    if (miningTrucksQueued.empty()) {
        return false;
    }
    miningTrucksQueued.pop();
    return true;
}

void MiningUnloadStation::queueMiningTruck(int truckId) {
    miningTrucksQueued.push(truckId);
}

void MiningUnloadStation::printQueue() {
    std::queue<int> tempStation = miningTrucksQueued;
    while (!tempStation.empty()) {
        int truckId = tempStation.front();
        std::cout << "Truck id: " << truckId << " In station Id: " << stationId << std::endl;
        tempStation.pop();
    }
}