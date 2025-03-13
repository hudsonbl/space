/**
 * @file mining_truck.hpp
 * @brief Header file for the MiningTruck class.
 *
 * This file contains the declaration of the MiningTruck class.
 */

#ifndef MINING_TRUCK_HPP
#define MINING_TRUCK_HPP

#include <iostream>
#include <random>
#include <string>
#include "mining_truck_metrics.hpp"


/**
 * @class MiningTruck
 * @brief Contains the state and controls of a MiningTruck.
 */
class MiningTruck : public MiningTruckMetrics {
private:
    /** The MiningTrucks identification. */
    int truckId;
    /** The MiningTrucks time in current operation. */
    int timeInCurrentOperation;
    /** The MiningTrucks status for current operation e.g. MINING. */
    MiningTruckStatus status;

public:
    /**
     * @brief Constructor for the MiningTruck object
     *
     * @param truckId The unique ID passed to a Mining Truck.
     */
    MiningTruck(int truckId) : 
        MiningTruckMetrics(),
        truckId(truckId),
        timeInCurrentOperation(0),
        status(MiningTruckStatus::MINING) {}; // Default start of simulation operation. 

    /**
     * @brief Checks if a MiningTruck is done MINING.
     *
     * @return True if MiningTruck is done MINING.
     */
    bool readyToUnload();

    /**
     * @brief Updates the trucks timeInOperation and metrics tracking its operation.
     */
    void updateTruck();

    /**
     * @brief Sets the MiningTruck's status to MINING. Mining takes anywhere between
     *        1-5 hours. Setting the timeInOperation accordingly.
     */
    void startMining();

    /**
     * @brief Set the status of a MiningTruck to MINING.
     */
    void setTruckMining();
    
    /**
     * @brief Set the status of a MiningTruck to TRAVELING_TO_STATION. Time it takes
     *        is 30 mins for travel.
     */
    void setUnloadStationDestination(int stationId);

    /**
     * @brief Set the status of a MiningTruck to TRAVELING_TO_SITE. Time it takes
     *        is 30 mins for travel.
     */
    void setMiningSiteDestination();

    /**
     * @brief Set the status of a MiningTruck to IN_QUEUE. Time it takes
     *        is 30 mins for travel.
     * 
     * @param stationId Identification of a MiningUnloadStation.
     */
    void setTruckInQueue(int stationId);

    /**
     * @brief Set the status of a MiningTruck to UNLOADING. Time it takes
     *        is 5 mins.
     * 
     * @param stationId Identification of a MiningUnloadStation.
     */
    void setTruckUnloading(int stationId);

    /**
     * @brief Get the time left in the MiningTrucks current operation.
     * 
     * @return time left in current operation.
     */
    int getTimeInCurrentOperation();

    /**
     * @brief Get the identification of a MiningTruck object.
     * 
     * @return truckId.
     */
    int getTruckId();

    /**
     * @brief Get the current status of a MiningTruck.
     * 
     * @return MiningTruckStatus of a MiningTruck.
     */
    MiningTruckStatus getCurrentOperationStatus();
};

#endif