/**
 * @file unload_station_metrics.hpp
 * @brief Header file for the UnloadStationMetrics class.
 *
 * This file contains the declaration of the UnloadStationMetrics class.
 */

#ifndef UNLOAD_STATION_METRICS_HPP
#define UNLOAD_STATION_METRICS_HPP

#include <iostream>
#include <queue>

/**
 * @class UnloadStationMetrics
 * @brief Holds the metrics to track efficiency and performance
 *        of a given MiningUnloadStation.
 *
 * It also does any calculations needed on those metrics for post
 * simulation analysis.
 */
class UnloadStationMetrics {
private:
    /** The number of MiningTruck's unloaded for a MiningUnloadStation. */
    int numberOfTrucksUnloaded;
    /** The total time of MiningTruck's IN_QUEUE for a MiningUnloadStation. */
    int timeTrucksInQueue;
    /** The total time a MiningUnloadStation had no activity. */
    int timeIdle;
    /** The maximum number of MiningTruck's waiting IN_QUEUE for a MiningUnloadStation. */
    int maxNumberOfTrucksInQueue;

public:
    /**
     * @brief Constructor for the UnloadStationMetrics object
     */
    UnloadStationMetrics() : 
        numberOfTrucksUnloaded(0),
        timeTrucksInQueue(0),
        timeIdle(0),
        maxNumberOfTrucksInQueue(0) {};

    /**
     * @brief Increases the Idle time for a MiningUnloadStation.
     */
    void increaseIdleTime();

    /**
     * @brief Increases the time MiningTrucks are IN_QUEUE for a MiningUnloadStation.
     */
    void increaseTimeTrucksInQueue();

    /**
     * @brief Increases the number of trucks unloaded for a MiningUnloadStation.
     */
    void increaseNumberOfTrucksUnloaded();

    /**
     * @brief Updates the maximum queue size a MiningUnloadStation experienced.
     * 
     * @param queueSize of the current MiningUnloadStations queue.
     */
    void updateMaxTrucksInQueue(int queueSize);

    /**
     * @brief Displays the stations metrics to STDOUT.
     *
     * @param stationId The MiningUnloadStation's Id.
     */
    void displayStationMetrics(int stationId);

    /**
     * @brief Added for unit testing to expose the values for testing.
     */
#ifdef UNIT_TESTING
    int getNumberOfTrucksUnloaded() const {
        return numberOfTrucksUnloaded;
    }

    int getTimeTrucksInQueue() const {
        return timeTrucksInQueue;
    }

    int getTimeIdle() const {
        return timeIdle;
    }

    int getMaxNumberOfTrucksInQueue() const {
        return maxNumberOfTrucksInQueue;
    }
#endif
};

#endif