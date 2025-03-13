#ifndef MINING_TRUCK_METRICS_HPP
#define MINING_TRUCK_METRICS_HPP

#include <iostream>
#include <vector>

// Status to track what state/operation the truck is currently in.
enum class MiningTruckStatus {
    TRAVELING_TO_STATION = 1,  // Truck is currently traveling to mining station.
    TRAVELING_TO_SITE = 2,     // Truck is currently traveling to mining site.
    MINING = 3,     // Truck is currently mining from Mining Site.
    IN_QUEUE = 4,   // Truck is currently in queue at a Unloading Station.
    UNLOADING = 5,  // Truck is currenlty unloading.
};

struct MiningTruckOperation {
    MiningTruckStatus status;
    int timeInOperation;
};

class MiningTruckMetrics {
private: 
    int numberOfUnloads;
    int timeMining;
    int timeTravelingToSite;
    int timeTravelingToStation;
    int timeInQueue;
    int totalTimeTraveling;
    int timeUnloading;
    std::vector<MiningTruckOperation> truckOperations;

    void calculateAndUpdateMetrics();

public:
    MiningTruckMetrics() :
        numberOfUnloads(0),
        timeMining(0),
        timeTravelingToSite(0),
        timeTravelingToStation(0),
        timeInQueue(0),
        totalTimeTraveling(0),
        timeUnloading(0),
        truckOperations() {};
    
    void increaseNumberOfUnloads();
    void addTruckOperation(MiningTruckStatus status, int timeInOperation);
    void displayTrucksMetrics(int truckId);

#ifdef UNIT_TESTING
    int getTimeMining() const {
        return timeMining;
    }

    int getNumberOfUnloads() const {
        return numberOfUnloads;
    }
#endif
};

#endif