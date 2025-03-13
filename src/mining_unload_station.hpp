#ifndef MINING_UNLOAD_STATION_HPP
#define MINING_UNLOAD_STATION_HPP

#include <iostream>
#include <queue>
#include "unload_station_metrics.hpp"


class MiningUnloadStation : public UnloadStationMetrics {
private:
    // Store the id of the Truck
    std::queue<int> miningTrucksQueued;
    int stationId;

public:
    MiningUnloadStation(int stationId) : UnloadStationMetrics(), stationId(stationId) {};

    bool isTruckQueueEmpty();
    bool popTruckFromQueue();
    int getStationId();
    int frontTruckInQueue();
    int getNumberOfTrucksAssignedToStation();
    std::queue<int> getStationQueue();
    void queueMiningTruck(int truckId);
    void printQueue();
};

#endif