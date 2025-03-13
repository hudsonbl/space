/**
 * @file mining_unload_station.hpp
 * @brief Header file for the MiningUnloadStation class.
 *
 * This file contains the declaration of the MiningUnloadStation class.
 */

#ifndef MINING_UNLOAD_STATION_HPP
#define MINING_UNLOAD_STATION_HPP

#include <iostream>
#include <queue>
#include "unload_station_metrics.hpp"

/**
 * @class MiningUnloadStation
 * @brief Contains the state and controls of a MiningUnloadStation.
 */
class MiningUnloadStation : public UnloadStationMetrics {
private:
    /** Stores a queue of truckId's. */
    std::queue<int> miningTrucksQueued;
    /** The MiningUnloadStation identification. */
    int stationId;

public:
    /**
     * @brief Constructor for the MiningUnloadStation object
     *
     * @param truckId The unique ID passed to a MiningUnloadStation.
     */
    MiningUnloadStation(int stationId) : 
        UnloadStationMetrics(), 
        stationId(stationId) {};

    /**
     * @brief Checks if the stations queue is empty.
     *
     * @return True if MiningUnloadStation does not have any truckId's.
     */
    bool isTruckQueueEmpty();

    /**
     * @brief Removes a truckId from the queue.
     *
     * @return True if the pop operation was successful.
     */
    bool popTruckFromQueue();

    /**
     * @brief Gets the MiningUnloadStation Id.
     *
     * @return stationId.
     */
    int getStationId();

    /**
     * @brief Gets the truckId of the first truck in line.
     *
     * @return truckId of a MiningTruck.
     */
    int frontTruckInQueue();

    /**
     * @brief Gets the number of trucks in the queue. The queue may include
     *        MiningTrucks that are TRAVELING_TO_STATION, IN_QUEUE, UNLOADING.
     *
     * @return size of queue.
     */
    int getNumberOfTrucksAssignedToStation();

    /**
     * @brief Gets the MiningUnloadStations queue.
     *
     * @return queue of truckId's
     */
    std::queue<int> getStationQueue();

    /**
     * @brief Adds a MiningTrucks ID to the station's queue to later be serviced.
     * 
     * @param truckId MiningTrucks Id.
     */
    void queueMiningTruck(int truckId);

    /**
     * @brief Debugging function used to see the queue of a given station.
     */
    void printQueue();
};

#endif