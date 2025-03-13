/**
 * @file home_base.hpp
 * @brief Header file for the HomeBase class.
 *
 * This file contains the declaration of the HomeBase class, which
 * controls communication between MiningTruck and MiningUnloadStation objects.
 * 
 * Furthermore it is responsible for controlling the state of each component.
 */

#ifndef HOME_BASE_HPP
#define HOME_BASE_HPP

#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <vector>
#include "mining_truck.hpp"
#include "mining_unload_station.hpp"


/**
 * @class HomeBase
 * @brief Represents a mining truck in the simulation.
 *
 * This class manages the state and behavior of a collection of
 * MiningTrucks and MiningUnloadStations.
 */
class HomeBase {
private:
    /** Holds all of the mining trucks. */
    std::vector<MiningTruck> miningTrucks;
    /** Holds all of the mining unload stations. */
    std::vector<MiningUnloadStation> miningUnloadStations;

    /**
     * @brief Gets the truckId's of each truck that has completed MINING
     *
     * @return List of truckId's
     */
    std::vector<int> getTrucksToUnload();

    /**
     * @brief Given a truckId, search for a MiningUnloadStation with the
     *        shortest queue time.
     *
     * @param truckId The MiningTruck Id.
     * @return stationId of the station the truck was assigned to.
     */
    int assignTruckToUnloadStation(int truckId);
    
    /**
     * @brief Given a truckId, and stationId. Assign the truckId to the
     *        corresponding stations queue.
     *
     * @param truckId The MiningTruck Id.
     * @param stationId The MiningUnloadStation Id.
     */
    void assignTruckToUnloadStationByStationId(int truckId, int stationId);

    /**
     * @brief Get the MiningTrucks that have completed mining. Assign them
     *        to an MiningUnloadStation.
     */
    void serviceMiningTrucksToUnload();

    /**
     * @brief Check each MiningUnloadStation to service their queue. Updating
     *        MiningUnload trucks to reassign their operation given the proper
     *        state.
     */
    void serviceMiningUnloadStations();

    /**
     * @brief Check each MiningTruck if they are TRAVELING_TO_SITE. If they
     *        have arrived, set them to MINING.
     */
    void serviceMiningSiteArrivals();

    /**
     * @brief Iterates through a MiningUnloadStation's queue, to update the
     *        status of MiningTruck's to IN_QUEUE if it has arrived to the station.
     *
     * @param truckId The MiningTruck Id.
     * @param stationId The MiningUnloadStation Id.
     */
    void updateMiningTrucksQueueStatus(std::queue<int> miningTruckQueue, int stationId);
    
    /**
     * @brief Checks if a MiningTruck has arrived to a Mining Site
     *
     * @param truckStatus The status of a MiningTruck.
     * @param timeInOperation The time left in the operation.
     * @return True if the status is TRAVELING_TO_SITE and timeInOperation is 0
     */
    bool hasMiningTruckArrivedToMiningSite(MiningTruckStatus truckStatus, int timeInOperation);
    
    /**
     * @brief Checks if a MiningTruck has arrived to a Mining Unload Station
     *
     * @param truckStatus The status of a MiningTruck.
     * @param timeInOperation The time left in the operation.
     * @return True if the status is TRAVELING_TO_STATION and timeInOperation is 0
     */
    bool hasMiningTruckArrivedToStation(MiningTruckStatus truckStatus, int timeInOperation);

    /**
     * @brief Get a MiningTruck given a truckId
     *
     * @param truckId The MiningTruck Id.
     * @return An optional reference to the proper MiningTruck object.
     */
    std::optional<std::reference_wrapper<MiningTruck>> getTruckWithTruckId(int truckId);

public:
    /**
     * @brief Constructor for the HomeBase object
     *
     * @param numTrucks Initializes the number of MiningTruck's.
     * @param numStations Initializes the number of MiningUnloadStation's.
     */
    HomeBase(int numTrucks, int numStations);


    /**
     * @brief Kickoff mining operations. Each MiningTruck starts mining and
     *        is at a Mining Site upon the start.
     */
    void startMiningOperations();

    /**
     * @brief Manages the state of the MiningTruck's operations.
     */
    void evaluateTruckOperations();

    /**
     * @brief Updates the MiningTruck's each iteration in the simulated time loop.
     */
    void updateTrucks();

    /**
     * @brief Updates the MiningUnloadStation's each iteration in the simulated time loop.
     */
    void updateStations();

    /**
     * @brief Shows the current MiningTruckStatus and timeInOperation for each truck.
     *        Called each simulated step.
     */
    void displayMiningOperationInfo(int timeTick);

    /**
     * @brief Displays and reports statistics for the performance and efficiency of
     *        each MiningTruck.
     */
    void displayTruckMetrics();

    /**
     * @brief Displays and reports statistics for the performance and efficiency of
     *        each MiningUnloadStation.
     */
    void displayStationMetrics();
};

#endif