#ifndef HOME_BASE_HPP
#define HOME_BASE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <optional>
#include "mining_truck.hpp"
#include "mining_unload_station.hpp"

/* 
    HomeBase stores the logic for all mining operations.
    It will distribute and coordinate work done by
    Mining Trucks and Mining Unload Stations.

*/
class HomeBase {
private:
    std::vector<MiningTruck> miningTrucks;
    std::vector<MiningUnloadStation> miningUnloadStations;

    std::vector<int> getTrucksToUnload();
    int assignTruckToUnloadStation(int truckId);
    void assignTruckToUnloadStationByStationId(int truckId, int stationId);
    void serviceMiningTrucksToUnload();
    void serviceMiningUnloadStations();
    void serviceMiningSiteArrivals();
    void updateMiningTrucksQueueStatus(std::queue<int> miningTruckQueue, int stationId);
    bool hasMiningTruckArrivedToMiningSite(MiningTruckStatus truckStatus, int timeInOperation);
    bool hasMiningTruckArrivedToStation(MiningTruckStatus truckStatus, int timeInOperation);
    std::vector<MiningTruck>& getMiningTrucks();
    std::optional<std::reference_wrapper<MiningTruck>> getTruckWithTruckId(int truckId);

public:
    HomeBase(int numTrucks, int numStations);

    void startMiningOperations();
    void evaluateTruckOperations();
    void updateTrucks();
    void updateStations();
    void displayMiningOperationInfo(int timeTick);
    void displayTruckMetrics();
    void displayStationMetrics();
};

#endif