#include <catch2/catch_test_macros.hpp>
#include "../src/mining_truck_metrics.hpp"

TEST_CASE("MiningTruckMetrics Class Test - Testing class operations", "Metrics should match") {
    MiningTruckMetrics truckMetrics;
    MiningTruckStatus status = MiningTruckStatus::MINING;
    int timeInOperation = 2;

    truckMetrics.addTruckOperation(status, timeInOperation);
    truckMetrics.addTruckOperation(status, timeInOperation);
    truckMetrics.addTruckOperation(status, timeInOperation);
    truckMetrics.addTruckOperation(status, timeInOperation);
    truckMetrics.increaseNumberOfUnloads();
#ifdef UNIT_TESTING
    REQUIRE(truckMetrics.getTimeMining() == 4);
    REQUIRE(truckMetrics.getNumberOfUnloads() == 1);
#endif
}