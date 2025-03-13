/**
 * @file mining_truck_metrics.hpp
 * @brief Header file for the 
 *          - MiningTruckMetrics class
 *          - MiningTruckStatus enum class
 *          - MiningTruckOperation struct
 *
 * This file contains the declaration of the MiningTruckMetrics class.
 */

#ifndef MINING_TRUCK_METRICS_HPP
#define MINING_TRUCK_METRICS_HPP

#include <iostream>
#include <vector>

/**
 * @brief Represents the state of a MiningTruck.
 *
 * This state will be tracked each iteration in the
 * simulation.
 */
enum class MiningTruckStatus {
    /** Truck is currently traveling to a MiningUnloadStation. */
    TRAVELING_TO_STATION = 1,
    /** Truck is currently traveling to Mining Site. */
    TRAVELING_TO_SITE = 2,
    /** Truck is currently mining in a Mining Site. */
    MINING = 3,
    /** Truck is currently in queue at a MiningUnloadStation. */
    IN_QUEUE = 4,
    /** Truck is currenlty unloading Helium-3. */
    UNLOADING = 5,
};

/**
 * @brief Metadata to hold the MiningTruck's status and
 *        timeInOperation.
 */
struct MiningTruckOperation {\
    /** Status the MiningTruck is currently in. */
    MiningTruckStatus status;
    /** current timeInOperation given the iteration in time loop. */
    int timeInOperation;
};

/**
 * @class MiningTruckMetrics
 * @brief Holds the metrics to track efficiency and performance
 *        of a given MiningTruck.
 *
 * It also does any calculations needed on those metrics for post
 * simulation analysis.
 */
class MiningTruckMetrics {
private:
    /** The number of unloads for a MiningTruck. */
    int numberOfUnloads;
    /** The total time spent MINING for a MiningTruck. */
    int timeMining;
    /** The total time spent TRAVELING_TO_SITE for a MiningTruck. */
    int timeTravelingToSite;
    /** The total time spent TRAVELING_TO_STATION for a MiningTruck. */
    int timeTravelingToStation;
    /** The total time spent traveling for a MiningTruck. */
    int totalTimeTraveling;
    /** The total time a MiningTruck spent IN_QUEUE within all MiningUnloadStations. */
    int timeInQueue;
    /** The total time a MiningTruck spent UNLOADING. */
    int timeUnloading;
    /** A list of the MiningTruck's operational status. */
    std::vector<MiningTruckOperation> truckOperations;

    /**
     * @brief Calculates a MiningTrucks metrics.
     */
    void calculateAndUpdateMetrics();

public:
    /**
     * @brief Constructor for the MiningTruckMetrics object
     */
    MiningTruckMetrics() :
        numberOfUnloads(0),
        timeMining(0),
        timeTravelingToSite(0),
        timeTravelingToStation(0),
        totalTimeTraveling(0),
        timeInQueue(0),
        timeUnloading(0),
        truckOperations() {};
    
    /**
     * @brief Increases the number of unloads for a MiningTruck
     */
    void increaseNumberOfUnloads();

    /**
     * @brief Add's the current MiningTruck's operation to the list tracking
     *        it.
     *
     * @param status Current MiningTruckStatus of a MiningTruck.
     * @param timeInOperation Current time left in the operation.
     */
    void addTruckOperation(MiningTruckStatus status, int timeInOperation);
    
    /**
     * @brief Displays the trucks metrics to STDOUT.
     *
     * @param truckId The MiningTruck's Id.
     */
    void displayTrucksMetrics(int truckId);

    /**
     * @brief Added for unit testing to expose the values for testing.
     */
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