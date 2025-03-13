#include "home_base.hpp"

HomeBase::HomeBase(int numTrucks, int numStations) {
    // Initialize the Mining Trucks
    for (int truckId = 0; truckId < numTrucks; truckId++) {
        MiningTruck miningTruck(truckId);
        miningTrucks.push_back(miningTruck);
    }
    // Initialize the Mining Unload Stations
    for (int stationId = 0; stationId < numStations; stationId++) {
        MiningUnloadStation unloadStation(stationId);
        miningUnloadStations.push_back(unloadStation);
    }
}

void HomeBase::startMiningOperations() {
    // Start off each truck empty at a mining site.
    for (MiningTruck& truck : miningTrucks) {
        truck.startMining();
    }
}

void HomeBase::updateTrucks() {
    // For each truck, update the time in operation.
    for (MiningTruck& truck : miningTrucks) {
        truck.updateTruck();
    }
}

void HomeBase::updateStations() {
    for (MiningUnloadStation& station : miningUnloadStations) {
        std::queue<int> trucksInQueue = station.getStationQueue();
        // If there are no trucks in the queue move to next station
        if (trucksInQueue.empty()) {
            continue;
        }

        while (!trucksInQueue.empty()) {
            int truckId = trucksInQueue.front();

            auto miningTruckRef = getTruckWithTruckId(truckId);

            // Ensure a truck with the ID is returned.
            if (miningTruckRef.has_value()) {
                MiningTruck* miningTruck = &miningTruckRef->get();
                if (miningTruck->getCurrentOperationStatus() == MiningTruckStatus::IN_QUEUE) {
                    station.increaseTimeTrucksInQueue();
                    return;
                }
            } else {
                std::cout << "Failed to process the next Truck in Queue. for station ID: " << station.getStationId() << std::endl;
                exit(1);
            }
            trucksInQueue.pop();
        }
    }
}

std::vector<int> HomeBase::getTrucksToUnload() {
    // Vector of truck Id's
    std::vector<int> trucksToUnload; 
    for (MiningTruck& truck : miningTrucks) {
        if (truck.readyToUnload()) {
            std::cout << "Truck: " << truck.getTruckId() << " is ready to unload." << std::endl;
            trucksToUnload.push_back(truck.getTruckId());
        }
    }
    return trucksToUnload;
}

void HomeBase::assignTruckToUnloadStationByStationId(int truckId, int stationId) {
    for (MiningUnloadStation& station : miningUnloadStations) {
        if (station.getStationId() == stationId) {
            station.queueMiningTruck(miningTrucks[truckId].getTruckId());
            return;
        }
    }
    std::cout << "Did not find station ID: " << stationId << std::endl;
    exit(1);
}

int HomeBase::assignTruckToUnloadStation(int truckId) {
    int storedStationId = miningUnloadStations[0].getStationId();
    int storedStationQueueTime = miningUnloadStations[0].getNumberOfTrucksAssignedToStation() - 6;

    for (MiningUnloadStation& station : miningUnloadStations) {
        // TODO: May be able to clean up - 6 and make it more pertinent to the logic of
        // I don't want 6 to be hardcoded.
        // I want it to represent the number of ticks and that logic may be from outside HomeBase logic.
        int currentStationsQueueTime = station.getNumberOfTrucksAssignedToStation() - 6;

        // Instantly assign if station queue is empty upon mining truck arrival.
        if (station.isTruckQueueEmpty()) {
            storedStationId = station.getStationId();
            storedStationQueueTime = currentStationsQueueTime;
            break;
        }
        // If the current station has a shorter Queue time, store the queue time as new lowest.
        if (currentStationsQueueTime < storedStationQueueTime) {
            storedStationId = station.getStationId();
            storedStationQueueTime = currentStationsQueueTime;
        }
    }
    // Queue truck with station id.
    assignTruckToUnloadStationByStationId(truckId, storedStationId);
    return storedStationId;
}

std::optional<std::reference_wrapper<MiningTruck>> HomeBase::getTruckWithTruckId(int truckId) {
    for (MiningTruck& miningTruck : miningTrucks) {
        if (miningTruck.getTruckId() == truckId) {
            // Return reference to mining truck.
            return std::ref(miningTruck);
        }
    }
    return std::nullopt;
}

bool HomeBase::hasMiningTruckArrivedToMiningSite(MiningTruckStatus truckStatus, int timeInOperation) {
    return truckStatus == MiningTruckStatus::TRAVELING_TO_SITE && timeInOperation == 0;
}

bool HomeBase::hasMiningTruckArrivedToStation(MiningTruckStatus truckStatus, int timeInOperation) {
    return truckStatus == MiningTruckStatus::TRAVELING_TO_STATION && timeInOperation == 0;
}

void HomeBase::serviceMiningTrucksToUnload() {
    std::vector<int> trucksToUnloadById = getTrucksToUnload();
    while (!trucksToUnloadById.empty()) {
        int truckId = trucksToUnloadById.back();
        int stationId = assignTruckToUnloadStation(truckId);
        auto truckRef = getTruckWithTruckId(truckId);
        if (truckRef.has_value()) {
            MiningTruck* truck = &truckRef->get();
            // Set the status of trucks operation. and time of operation.
            truck->setUnloadStationDestination(stationId); 
        } else {
            std::cout << "Truck with truck ID: " << truckId << " not found." << std::endl;
            exit(1);
        }
        
        trucksToUnloadById.pop_back();
    }
}

void HomeBase::updateMiningTrucksQueueStatus(std::queue<int> miningTruckQueue, int stationId) {
    while (!miningTruckQueue.empty()) {
        int truckId = miningTruckQueue.front();

        auto miningTruckRef = getTruckWithTruckId(truckId);

        // Ensure a truck with the ID is returned.
        if (miningTruckRef.has_value()) {
            MiningTruck* miningTruck = &miningTruckRef->get();
            MiningTruckStatus truckStatus = miningTruck->getCurrentOperationStatus();
            int timeInOperation = miningTruck->getTimeInCurrentOperation();

            if (hasMiningTruckArrivedToStation(truckStatus, timeInOperation)) {
                miningTruck->setTruckInQueue(stationId);
            }
        } else {
            std::cout << "Failed to process the next Truck in Queue. for station ID: " << stationId << std::endl;
            exit(1);
        }
        miningTruckQueue.pop();
    }
 }

void HomeBase::serviceMiningUnloadStations() {
    for (MiningUnloadStation& station : miningUnloadStations) {
        // If mining station doesn't have any trucks to service, move on.
        if (station.isTruckQueueEmpty()) {
            std::cout << "Station Id: " << station.getStationId() << " is empty queue." << std::endl;
            station.increaseIdleTime();
            continue;
        }
        // Get truck with truck id.
        int truckId = station.frontTruckInQueue();
        auto miningTruckRef = getTruckWithTruckId(truckId);
        // Ensure a truck with the ID is returned.
        if (miningTruckRef.has_value()) {
            MiningTruck* miningTruck = &miningTruckRef->get();
            MiningTruckStatus truckStatus = miningTruck->getCurrentOperationStatus();
            int timeInOperation = miningTruck->getTimeInCurrentOperation();
            // Case truck is done UNLOADING
            if (truckStatus == MiningTruckStatus::UNLOADING && timeInOperation == 0) {
                miningTruck->setMiningSiteDestination();
                if (station.popTruckFromQueue()) {
                    station.increaseNumberOfTrucksUnloaded();
                    miningTruck->increaseNumberOfUnloads();
                    std::cout << "Truck ID: " << truckId << " serviced from Station ID: " << station.getStationId() << std::endl;
                } else {
                    std::cout << "Failed to remove Truck Id: " << truckId << " from Station ID: " << station.getStationId() << std::endl;
                }
                // Process the next truck IN_QUEUE if queue is not empty.
                if (station.isTruckQueueEmpty()) {
                    std::cout << "Truck queue is empty after servicing in station Id: " << station.getStationId() << std::endl;
                    continue;
                }

                // Reassign to process the next truck.
                truckId = station.frontTruckInQueue();
                auto nextMiningTruck = getTruckWithTruckId(truckId);
                if (nextMiningTruck.has_value()) {
                    miningTruck = &nextMiningTruck->get();
                    truckId = miningTruck->getTruckId();
                    truckStatus = miningTruck->getCurrentOperationStatus();
                    timeInOperation = miningTruck->getTimeInCurrentOperation();
                } else {
                    std::cout << "Failed to process the next Truck in Queue for Station ID: " << station.getStationId() << std::endl;
                    exit(1);
                }
            }
            
            // Case truck is done traveling and can instantly go into UNLOADING.
            if (truckStatus == MiningTruckStatus::TRAVELING_TO_STATION && timeInOperation == 0) {
                miningTruck->setTruckUnloading(station.getStationId());
            }

            // Case truck is IN_QUEUE and can go into UNLOADING.
            if (truckStatus == MiningTruckStatus::IN_QUEUE) {
                miningTruck->setTruckUnloading(station.getStationId());
            }
            std::queue<int> currentStationQueue = station.getStationQueue();
            station.updateMaxTrucksInQueue(currentStationQueue.size());
            
            // Lastly iterate through queue to put arrived trucks IN_QUEUE
            updateMiningTrucksQueueStatus(currentStationQueue, station.getStationId());
        } else {
            std::cout << "Truck with truck id: " << truckId << " not found." << std::endl;
            exit(1);
        }
    }
}

void HomeBase::serviceMiningSiteArrivals() {
    for (MiningTruck& miningTruck : miningTrucks) {
        MiningTruckStatus truckStatus = miningTruck.getCurrentOperationStatus();
        int timeInOperation = miningTruck.getTimeInCurrentOperation();

        if (hasMiningTruckArrivedToMiningSite(truckStatus, timeInOperation)) {
            miningTruck.startMining();
        }
    }
}

// =====================================================================================

void HomeBase::evaluateTruckOperations() {
    // Checks / updates the MINING status
    serviceMiningTrucksToUnload();

    // Check / update UNLOADING status
    // Check / update IN_QUEUE status
    serviceMiningUnloadStations();

    // Check / update the TRAVELING status - can be to and from mining sites / unload stations
    serviceMiningSiteArrivals();
}

// ======================================================================================

void HomeBase::displayMiningOperationInfo(int timeTick){
    std::cout << "=======================================================" << std::endl;
    std::cout << "Simulation Step: " << timeTick << std::endl;
    for (MiningTruck& truck : miningTrucks) {
        switch (truck.getCurrentOperationStatus()) {
        case MiningTruckStatus::MINING:
            std::cout << "Truck: " << truck.getTruckId() << " is MINING" << std::endl;
            std::cout << "Time in operation: " << truck.getTimeInCurrentOperation() << std::endl;
            break;
        case MiningTruckStatus::TRAVELING_TO_STATION:
            std::cout << "Truck: " << truck.getTruckId() << " is TRAVELING to mining station" << std::endl;
            std::cout << "Time in operation: " << truck.getTimeInCurrentOperation() << std::endl;
            break;
        case MiningTruckStatus::TRAVELING_TO_SITE:
            std::cout << "Truck: " << truck.getTruckId() << " is TRAVELING to mining site" << std::endl;
            std::cout << "Time in operation: " << truck.getTimeInCurrentOperation() << std::endl;
            break;
        case MiningTruckStatus::IN_QUEUE:
            std::cout << "Truck: " << truck.getTruckId() << " is IN QUEUE" << std::endl;
            std::cout << "Time in operation: " << truck.getTimeInCurrentOperation() << std::endl;
            break;
        case MiningTruckStatus::UNLOADING:
            std::cout << "Truck: " << truck.getTruckId() << " is UNLOADING" << std::endl;
            std::cout << "Time in operation: " << truck.getTimeInCurrentOperation() << std::endl;
            break;
        default:
            std::cout << "Unkown status was taken...\n\n";
            break;
        }
    }

    std::cout << "=======================================================" << std::endl;
}

void HomeBase::displayTruckMetrics() {
    for (MiningTruck truck : miningTrucks) {
        truck.displayTrucksMetrics(truck.getTruckId());
    }
}

void HomeBase::displayStationMetrics() {
    for (MiningUnloadStation station : miningUnloadStations) {
        station.displayStationMetrics(station.getStationId());
    }
}