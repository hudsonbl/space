#include <catch2/catch_test_macros.hpp>
#include <queue>
#include "../src/mining_unload_station.hpp"

TEST_CASE("MiningUnloadStation Class Test - getStationId()", "ID should match") {
    MiningUnloadStation station(1);
    REQUIRE(station.getStationId() == 1);
}

TEST_CASE("MiningUnloadStation Class Test - Test queue operations", "Queues should match sizes accordingly") {
    MiningUnloadStation station(1);

    REQUIRE(station.isTruckQueueEmpty() == true);
    station.queueMiningTruck(1);
    station.queueMiningTruck(2);
    station.queueMiningTruck(3);
    station.queueMiningTruck(4);
    station.queueMiningTruck(5);

    std::queue<int> stationQueue = station.getStationQueue();
    REQUIRE(station.getNumberOfTrucksAssignedToStation() == 5);

    bool didQueuePop = station.popTruckFromQueue();
    REQUIRE(station.getNumberOfTrucksAssignedToStation() == 4);
    REQUIRE(didQueuePop == true);
    REQUIRE(station.frontTruckInQueue() == 2);
}