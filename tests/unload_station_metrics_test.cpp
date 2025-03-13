#include <catch2/catch_test_macros.hpp>
#include "../src/unload_station_metrics.hpp"

TEST_CASE("UnloadStationMetrics Class Test - Testing class operations", "Metrics should match") {
    UnloadStationMetrics stationMetrics;

    stationMetrics.increaseIdleTime();
    stationMetrics.increaseTimeTrucksInQueue();
    stationMetrics.increaseNumberOfTrucksUnloaded();
    stationMetrics.updateMaxTrucksInQueue(5);

#ifdef UNIT_TESTING
    REQUIRE(stationMetrics.getNumberOfTrucksUnloaded() == 1);
    REQUIRE(stationMetrics.getTimeTrucksInQueue() == 1);
    REQUIRE(stationMetrics.getTimeIdle() == 1);
    REQUIRE(stationMetrics.getMaxNumberOfTrucksInQueue() == 5);
#endif
}