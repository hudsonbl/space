#include <catch2/catch_test_macros.hpp>
#include "../src/mining_truck.hpp"

TEST_CASE("MiningTruck Class Test - getTruckId()", "ID should match") {
    MiningTruck miningTruck(1);
    REQUIRE(miningTruck.getTruckId() == 1);
}

TEST_CASE("MiningTruck Class Test - Test Status setting functions", "operation status and time should be set.") {
    MiningTruck miningTruck(1);

    miningTruck.startMining();
    REQUIRE(miningTruck.getCurrentOperationStatus() == MiningTruckStatus::MINING);
    REQUIRE(miningTruck.getTimeInCurrentOperation() > 0);

    int stationId = 3;

    miningTruck.setTruckInQueue(stationId);
    REQUIRE(miningTruck.getCurrentOperationStatus() == MiningTruckStatus::IN_QUEUE);
    REQUIRE(miningTruck.getTimeInCurrentOperation() == 0);

    miningTruck.setTruckUnloading(stationId);
    REQUIRE(miningTruck.getCurrentOperationStatus() == MiningTruckStatus::UNLOADING);
    REQUIRE(miningTruck.getTimeInCurrentOperation() == 1);

    miningTruck.setMiningSiteDestination();
    REQUIRE(miningTruck.getCurrentOperationStatus() == MiningTruckStatus::TRAVELING_TO_SITE);
    REQUIRE(miningTruck.getTimeInCurrentOperation() == 6);

    miningTruck.setUnloadStationDestination(stationId);
    REQUIRE(miningTruck.getCurrentOperationStatus() == MiningTruckStatus::TRAVELING_TO_STATION);
    REQUIRE(miningTruck.getTimeInCurrentOperation() == 6);
}

TEST_CASE("MiningTruck Class Test - readyToUnload()", "If the truck is ready to unload.") {
    MiningTruck miningTruck(1);
    miningTruck.setTruckMining();

    REQUIRE(miningTruck.readyToUnload() == true);
}

TEST_CASE("MiningTruck Class Test - updateTruck()", "After called twice it should subtract from operation twice.") {
    MiningTruck miningTruck(1);
    miningTruck.setMiningSiteDestination();
    miningTruck.updateTruck();
    miningTruck.updateTruck();

    REQUIRE(miningTruck.getTimeInCurrentOperation() == 4);
}
