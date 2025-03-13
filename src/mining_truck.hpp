#ifndef MINING_TRUCK_HPP
#define MINING_TRUCK_HPP

#include <iostream>
#include <string>
#include <random>
#include "mining_truck_metrics.hpp"

class MiningTruck : public MiningTruckMetrics {
private:
    int truckId;
    int timeInCurrentOperation;
    MiningTruckStatus status;

public:
    MiningTruck(int truckId) : 
        MiningTruckMetrics(),
        truckId(truckId),
        timeInCurrentOperation(0),
        status(MiningTruckStatus::MINING) {}; // Default start of simulation operation. 

    bool readyToUnload();
    void updateTruck();
    void startMining();
    void setTruckMining();
    void setUnloadStationDestination(int stationId);
    void setMiningSiteDestination();
    void setTruckInQueue(int stationId);
    void setTruckUnloading(int stationId);
    int getTimeInCurrentOperation();
    int getTruckId();
    MiningTruckStatus getCurrentOperationStatus();
};

#endif